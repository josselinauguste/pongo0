#include "../game.hpp"
#include "localplayer.hpp"
#include "../tools.hpp"
#include "../world.hpp"
#include "../projectile/projectile.hpp"

LocalPlayer::LocalPlayer(SIDE _side, float _width, float _height, float _depth) : Player(_side, _width, _height, _depth), nextVelocity(new CL_Vector(0.0f, 0.0f, 0.0f)), accelerationRate(0.005f), decelerationRate(0.01f)
{
	position->x = 0.0;
	position->y = 0.0;
	position->z = ((Game::getInstance()->getWorld()->getDepth() / 2) - 2 - (_depth / 2)) * _side;
	firstPosition = new CL_Vector(*position);
}

LocalPlayer::~LocalPlayer()
{
	delete firstPosition;
	delete nextVelocity;
}

void LocalPlayer::resetPosition()
{
	position->x = firstPosition->x;
	position->y = firstPosition->y;
	position->z = firstPosition->z;

	velocity->x = 0;
	velocity->y = 0;
	velocity->z = 0;

	acceleration->x = 0;
	acceleration->y = 0;
	acceleration->z = 0;
}

void LocalPlayer::updatePosition(unsigned int time)
{
	previousPosition->x = position->x;
	previousPosition->y = position->y;
	previousPosition->z = position->z;

	position->x = 0.5f * acceleration->x * time * time + velocity->x * time + position->x;
	position->y = 0.5f * acceleration->y * time * time + velocity->y * time + position->y;
	position->z = 0.5f * acceleration->z * time * time + velocity->z * time + position->z;

	velocity->x = acceleration->x * time + velocity->x;
	velocity->y = acceleration->y * time + velocity->y;
	velocity->z = acceleration->z * time + velocity->z;

	nextVelocity->x = acceleration->x * time + velocity->x;
	nextVelocity->y = acceleration->y * time + velocity->y;
	nextVelocity->z = acceleration->z * time + velocity->z;
}

void LocalPlayer::accelerate(AXIS axis, DIRECTION direction)
{
	switch(axis)
	{
	case 0:
		acceleration->x = direction * accelerationRate;
		break;
	case 1:
		acceleration->y = direction * accelerationRate;
		break;
	case 2:
		acceleration->z = direction * accelerationRate;
		break;
	}
}

void LocalPlayer::decelerate(AXIS axis)
{
	switch(axis)
	{
	case 0:
		if(velocity->x != 0)
		{
			if(Tools<float>::sign(velocity->x) == Tools<float>::sign(nextVelocity->x))
				acceleration->x = ((velocity->x > 0) ? -1.0f : 1.0f) * decelerationRate;
			else
			{
				acceleration->x = 0;
				velocity->x = 0;
			}
		}
		break;
	case 1:
		if(velocity->y != 0)
		{
			if(Tools<float>::sign(velocity->y) == Tools<float>::sign(nextVelocity->y))
				acceleration->y = ((velocity->y > 0) ? -1.0f : 1.0f) * decelerationRate;
			else
			{
				acceleration->y = 0;
				velocity->y = 0;
			}
		}
		break;
	case 2:
		if(velocity->z != 0)
		{
			if(Tools<float>::sign(velocity->z) == Tools<float>::sign(nextVelocity->z))
				acceleration->z = ((velocity->z > 0) ? -1.0f : 1.0f) * decelerationRate;
			else
			{
				acceleration->z = 0;
				velocity->z = 0;
			}
		}
		break;
	}
}

void LocalPlayer::checkBordersCollision()
{
	if(position->x < -Game::getInstance()->getWorld()->getWidth() / 2 + getWidth() / 2 || position->x > Game::getInstance()->getWorld()->getWidth() / 2 - getWidth() / 2)
	{
		position->x = Tools<float>::sign(position->x) * (Game::getInstance()->getWorld()->getWidth() / 2 - getWidth() / 2);
		velocity->x = 0;
		acceleration->z = 0;
	}
	if(position->y < -Game::getInstance()->getWorld()->getHeight() / 2 + getHeight() / 2 || position->y > Game::getInstance()->getWorld()->getHeight() / 2 - getHeight() / 2)
	{
		position->y = Tools<float>::sign(position->y) * (Game::getInstance()->getWorld()->getHeight() / 2 - getHeight() / 2);
		velocity->y = 0;
		acceleration->y = 0;
	}
	if(position->z < -Game::getInstance()->getWorld()->getDepth() / 2 + getDepth() / 2 || position->z > Game::getInstance()->getWorld()->getDepth() / 2 - getDepth() / 2)
	{
		position->z = Tools<float>::sign(position->z) * (Game::getInstance()->getWorld()->getDepth() / 2 - getDepth() / 2);
		velocity->z = 0;
		acceleration->z = 0;
	}
}

void LocalPlayer::checkProjectileCollision(Projectile *projectile)
{
	float radius = projectile->getRadius();
	
	if(projectile->getPosition().y - radius < position->y + getHeight() / 2 && \
	projectile->getPosition().y + radius > position->y - getHeight() / 2 && \
	projectile->getPosition().x - radius < position->x + getWidth() / 2 && \
	projectile->getPosition().x + radius > position->x - getWidth() / 2 && \
	( \
		( \
		position->z < 0 && \
		projectile->getPosition().z - radius < position->z + getDepth() / 2 && \
		projectile->getPosition().z - radius > position->z - getDepth() / 2 \
			) || \
		( \
		position->z >= 0 && \
		projectile->getPosition().z + radius > position->z - getDepth() / 2 && \
		projectile->getPosition().z + radius < position->z + getDepth() / 2 \
			) \
		) \
		)
	{
		projectile->replace();
		projectile->inverseZVelocity();
	}
}
