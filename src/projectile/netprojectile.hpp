#ifndef NETPROJECTILEH
#define NETPROJECTILEH

#include "projectile.hpp"

class Game;
class CL_Vector;

class NetProjectile : public Projectile
{
public:
	NetProjectile();
	virtual ~NetProjectile();

	virtual void updateInfos(unsigned int);
	virtual void checkBordersCollision();
};

#endif
