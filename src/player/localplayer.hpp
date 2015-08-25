#ifndef LOCALPLAYERH
#define LOCALPLAYERH

#include "player.hpp"

class CL_Vector;

class Game;
class Projectile;

typedef enum {X, Y, Z} AXIS;
typedef enum {NEGATIVE = -1, POSITIVE = 1} DIRECTION;

class LocalPlayer : public Player
{
public:
	LocalPlayer(SIDE, float, float, float);
	~LocalPlayer();

	virtual void checkBordersCollision();
	void checkProjectileCollision(Projectile*);
	void resetPosition();

	void incScore() { setScore(getScore()+1); }

protected:
	void updatePosition(unsigned int);
	void accelerate(AXIS, DIRECTION);
	void decelerate(AXIS);

	CL_Vector *firstPosition;
	CL_Vector *nextVelocity;

	const float accelerationRate;
	const float decelerationRate;
};

#endif
