#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include "world.hpp"
#include "log.hpp"
#include "game.hpp"

World::World(CL_ResourceManager *_resourceManager, float _width, float _height, float _depth) : width(_width), height(_height), depth(_depth)
{
	texBorders = new CL_OpenGLSurface("Game/texture_borders", _resourceManager);
}

void World::initDisplay()
{
	displayListBorders = glGenLists(1);
	if(displayListBorders != 0)
	{
		glNewList(displayListBorders, GL_COMPILE);

		glEnable(GL_TEXTURE_2D);

		GLfloat ambient_diffuse[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat shininess[] = {50.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		//contrôle la brillance
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

		texBorders->bind();

		//Face avant
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-1.0, 1.0, 1.0); glVertex3f(this->width / 2, -(this->height / 2), -(this->depth / 2));
		glTexCoord2f(1.0f, 1.0f); glNormal3f(1.0, 1.0, 1.0); glVertex3f(-(this->width / 2), -(this->height / 2), -(this->depth / 2));
		glTexCoord2f(1.0f, 0.0f); glNormal3f(1.0, -1.0, 1.0); glVertex3f(-(this->width / 2), this->height / 2, -(this->depth / 2));
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-1.0, -1.0, 1.0); glVertex3f(this->width / 2, this->height / 2, -(this->depth / 2));
		glEnd();

		//Face arriére
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glNormal3f(-1.0, 1.0, 1.0); glVertex3f(this->width / 2, -(this->height / 2), this->depth / 2);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-1.0, -1.0, -1.0); glVertex3f(this->width / 2, this->height / 2, this->depth / 2);
		glTexCoord2f(0.0f, 0.0f); glNormal3f(1.0, -1.0, -1.0); glVertex3f(-(this->width / 2), this->height / 2, this->depth / 2);
		glTexCoord2f(1.0f, 0.0f); glNormal3f(1.0, 1.0, -1.0); glVertex3f(-(this->width / 2), -(this->height / 2), this->depth / 2);
		glEnd();

		//Face Top
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-1.0, -1.0, 1.0); glVertex3f(this->width / 2, this->height / 2, -(this->depth / 2));
		glTexCoord2f(1.0f, 1.0f); glNormal3f(1.0, -1.0, 1.0); glVertex3f(-(this->width / 2), this->height / 2, -(this->depth / 2));
		glTexCoord2f(1.0f, 0.0f); glNormal3f(1.0, -1.0, -1.0); glVertex3f(-(this->width / 2), this->height / 2, this->depth / 2);
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-1.0, -1.0, -1.0); glVertex3f(this->width / 2, this->height / 2, this->depth / 2);
		glEnd();

		//Face Bottom
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-1.0, 1.0, -1.0); glVertex3f(this->width / 2, -(this->height / 2), this->depth / 2);
		glTexCoord2f(1.0f, 1.0f); glNormal3f(1.0, 1.0, -1.0); glVertex3f(-(this->width / 2), -(this->height / 2), this->depth / 2);
		glTexCoord2f(1.0f, 0.0f); glNormal3f(1.0, 1.0, 1.0); glVertex3f(-(this->width / 2), -(this->height / 2), -(this->depth / 2));
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-1.0, 1.0, 1.0); glVertex3f(this->width / 2, -(this->height / 2), -(this->depth / 2));
		glEnd();

		//Face doite
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(1.0, 1.0, 1.0); glVertex3f(-(this->width / 2), -(this->height / 2), -(this->depth / 2));
		glTexCoord2f(1.0f, 1.0f); glNormal3f(1.0, 1.0, -1.0); glVertex3f(-(this->width / 2), -(this->height / 2), this->depth / 2);
		glTexCoord2f(1.0f, 0.0f); glNormal3f(1.0, -1.0, -1.0); glVertex3f(-(this->width / 2), this->height / 2, this->depth / 2);
		glTexCoord2f(0.0f, 0.0f); glNormal3f(1.0, -1.0, 1.0); glVertex3f(-(this->width / 2), this->height / 2, -(this->depth / 2));
		glEnd();

		//Face gauche
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glNormal3f(-1.0, 1.0, 1.0); glVertex3f(this->width / 2, -(this->height / 2), -(this->depth / 2));
		glTexCoord2f(1.0f, 0.0f); glNormal3f(-1.0, -1.0, 1.0); glVertex3f(this->width / 2, this->height / 2, -(this->depth / 2));
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-1.0, -1.0, -1.0); glVertex3f(this->width / 2, this->height / 2, this->depth / 2);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-1.0, 1.0, -1.0); glVertex3f(this->width / 2, -(this->height / 2), this->depth / 2);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glEndList();
	}
	else
	{
		Log::print(LOG_ERR, "Impossibilité de créer la liste d'affichage displayListBords.");
	}
}

World::~World()
{
}

void World::render()
{
	glPushMatrix();
	glCallList(displayListBorders);
	glPopMatrix();
}
