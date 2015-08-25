#ifndef LOCALPROJECTILEH
#define LOCALPROJECTILEH

#include "projectile.hpp"

class Game;
class CL_Vector;

class LocalProjectile : public Projectile
{
public:
	LocalProjectile(float);
	virtual ~LocalProjectile();

	virtual void updateInfos(unsigned int);
	virtual void checkBordersCollision();

private:
	void generateVelocity();
	void resetPosition();

	CL_Vector *firstPosition;
};

#endif
