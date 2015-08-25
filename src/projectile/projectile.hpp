#ifndef PROJECTILEH
#define PROJECTILEH

#include "../gameentity.hpp"

class Game;
class CL_Vector;

class Projectile : public GameEntity
{
public:
	Projectile(float);
	virtual ~Projectile();

	virtual void draw();

	float getRadius() const { return radius; }
	
protected:
	void setRadius(float _radius) { radius = _radius; }

private:
	float radius;
	GLUquadricObj *quadricObj;
};

#endif
