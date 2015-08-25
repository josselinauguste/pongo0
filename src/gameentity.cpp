#include "game.hpp"
#include "gameentity.hpp"

GameEntity::GameEntity() : previousPosition(new CL_Vector(0.0f, 0.0f, 0.0f)), position(new CL_Vector(0.0f, 0.0f, 0.0f)), velocity(new CL_Vector(0.0f, 0.0f, 0.0f)), acceleration(new CL_Vector(0.0f, 0.0f, 0.0f))
{
}

GameEntity::~GameEntity()
{
	delete position;
	delete velocity;
	delete acceleration;
}

void GameEntity::replace()
{
	position->x = previousPosition->x;
	position->y = previousPosition->y;
	position->z = previousPosition->z;
}
