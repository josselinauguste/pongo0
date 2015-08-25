#include "../game.hpp"
#include "projectile.hpp"

Projectile::Projectile(float _radius) : GameEntity(), radius(_radius)
{
	setColor(255, 255, 0);

	quadricObj = gluNewQuadric();
	gluQuadricNormals(quadricObj, GLU_FLAT);

	materialSpecular[0] = 1.0;
	materialSpecular[1] = 1.0;
	materialSpecular[2] = 1.0;
	materialSpecular[3] = 1.0;
	materialShininess[0] = 50.0;
}

Projectile::~Projectile()
{
	gluDeleteQuadric(quadricObj);
}

void Projectile::draw()
{
	glPushMatrix();
	
	glTranslatef(getPosition().x, getPosition().y, getPosition().z);

	materialAmbientDiffuse[0] = static_cast<float>(getColor().get_red()) / 255;
	materialAmbientDiffuse[1] = static_cast<float>(getColor().get_green()) / 255;
	materialAmbientDiffuse[2] = static_cast<float>(getColor().get_blue()) / 255;
	materialAmbientDiffuse[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbientDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	//controle la brillance
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

	gluSphere(quadricObj, getRadius(), 76, 76);
	
	glPopMatrix();
}
