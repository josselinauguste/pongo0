#ifndef GAMEENTITYH
#define GAMEENTITYH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

class GraphicObject;
class Game;

class GameEntity
{
public:
	GameEntity();
	virtual ~GameEntity();

	virtual void updateInfos(unsigned int) = 0;
	virtual void checkBordersCollision() = 0;

	CL_Vector getPosition() const { return *position; }
	CL_Vector getVelocity() const { return *velocity; }
	CL_Vector getAcceleration() const { return *acceleration; }
	CL_Color getColor() const { return color; }

	//méthodes utilisées pour les collisions
	void inverseXVelocity() { velocity->x = -velocity->x; }
	void inverseYVelocity() { velocity->y = -velocity->y; }
	void inverseZVelocity() { velocity->z = -velocity->z; }
	void replace();

	virtual void draw() = 0;

protected:
	GLfloat materialAmbientDiffuse[4];
	GLfloat materialSpecular[4];
	GLfloat materialShininess[1];

	CL_Vector *previousPosition;
	CL_Vector *position;
	CL_Vector *velocity;
	CL_Vector *acceleration;

	void setColor(unsigned int red, unsigned int green, unsigned int blue) { color = CL_Color(red, green, blue); }

private:
	CL_Color color;
};

#endif
