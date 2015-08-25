#include "../game.hpp"
#include "netprojectile.hpp"

NetProjectile::NetProjectile() : Projectile(0.0)
{
	setRadius(0);
}

NetProjectile::~NetProjectile()
{
}

void NetProjectile::updateInfos(unsigned int lastTime)
{
}

void NetProjectile::checkBordersCollision()
{
	//no implementation needed !
}
