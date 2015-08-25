#include "../game.hpp"
#include "localprojectile.hpp"
#include "../world.hpp"
#include "../tools.hpp"
#include "../player/localplayer.hpp"
#include "../log.hpp"

LocalProjectile::LocalProjectile(float _radius) : Projectile(_radius)
{
	position->x = 0.0f;
	position->y = 0.0f;
	position->z = 0.0f;
	firstPosition = new CL_Vector(*position);

	generateVelocity();
}

LocalProjectile::~LocalProjectile()
{
	delete firstPosition;
}

void LocalProjectile::generateVelocity()
{
	velocity->x = ((float)(rand()%21 - 10)) / 100;
	velocity->y = ((float)(rand()%21 - 10)) / 100;
	do
	{
		velocity->z = ((float)(rand()%21 - 10)) / 100;
	} while(velocity->z == 0.0);
}

void LocalProjectile::resetPosition()
{
	position->x = firstPosition->x;
	position->y = firstPosition->y;
	position->z = firstPosition->z;

	generateVelocity();

	//reset des positions des players
	std::list<Player*>::iterator itPlayers = Game::getInstance()->getPlayers()->begin();
	while(itPlayers != Game::getInstance()->getPlayers()->end())
	{
		if(LocalPlayer *localPlayer = dynamic_cast<LocalPlayer*>(*itPlayers))
		{
			localPlayer->resetPosition();
		}
		itPlayers++;
	}
}

void LocalProjectile::updateInfos(unsigned int time)
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
}

void LocalProjectile::checkBordersCollision()
{
	if(Tools<float>::abs(position->x) + getRadius() >= Game::getInstance()->getWorld()->getWidth() / 2)
	{
		replace();
		inverseXVelocity();
	}
	if(Tools<float>::abs(position->y) + getRadius() >= Game::getInstance()->getWorld()->getHeight() / 2)
	{
		replace();
		inverseYVelocity();
	}
	if(Tools<float>::abs(position->z) + getRadius() >= Game::getInstance()->getWorld()->getDepth() / 2)
	{
		std::list<Player*>::iterator itPlayers = Game::getInstance()->getPlayers()->begin();
		while(itPlayers != Game::getInstance()->getPlayers()->end())
		{
			if(LocalPlayer *localPlayer = dynamic_cast<LocalPlayer*>(*itPlayers))
			{
				if((*itPlayers)->getSide() != Tools<float>::sign(position->z))
				{
					localPlayer->incScore();
				}
			}
			itPlayers++;
		}
		
		resetPosition();
	}
}
