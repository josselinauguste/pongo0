#include "player.hpp"

Player::Player(SIDE _side, float _width, float _height, float _depth) : side(_side), score(0), width(_width), height(_height), depth(_depth)
{
	materialSpecular[0] = 1.0;
	materialSpecular[1] = 1.0;
	materialSpecular[2] = 1.0;
	materialSpecular[3] = 1.0;
	materialShininess[0] = 50.0;
}

Player::~Player()
{
}

void Player::draw()
{
	glPushMatrix();
	
	if(getSide() == SECOND)
		glRotatef(0.5f, 0.0f, 1.0f, 0.0f);
	glTranslatef(getPosition().x, getPosition().y, getPosition().z);

	materialAmbientDiffuse[0] = static_cast<float>(getColor().get_red()) / 255;
	materialAmbientDiffuse[1] = static_cast<float>(getColor().get_green()) / 255;
	materialAmbientDiffuse[2] = static_cast<float>(getColor().get_blue()) / 255;
	materialAmbientDiffuse[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbientDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	//contrôle la brillance
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

	//Face avant
	glBegin(GL_QUADS);
	glNormal3f(1.0, -1.0, 1.0); glVertex3f(getWidth() / 2, -(getHeight() / 2), getDepth() / 2);
	glNormal3f(-1.0, -1.0, 1.0); glVertex3f(-(getWidth() / 2), -(getHeight() / 2), getDepth() / 2);
	glNormal3f(-1.0, 1.0, 1.0); glVertex3f(-(getWidth() / 2), getHeight() / 2, getDepth() / 2);
	glNormal3f(1.0, 1.0, 1.0); glVertex3f(getWidth() / 2, getHeight() / 2, getDepth() / 2);
	glEnd();

	//Face doite
	glBegin(GL_QUADS);
	glNormal3f(-1.0, -1.0, 1.0); glVertex3f(-(getWidth() / 2), -(getHeight() / 2), getDepth() / 2);
	glNormal3f(-1.0, -1.0, -1.0); glVertex3f(-(getWidth() / 2), -(getHeight() / 2), -(getDepth() / 2));
	glNormal3f(-1.0, 1.0, -1.0); glVertex3f(-(getWidth() / 2), getHeight() / 2, -(getDepth() / 2));
	glNormal3f(-1.0, 1.0, 1.0); glVertex3f(-(getWidth() / 2), getHeight() / 2, getDepth() / 2);
	glEnd();

	//Face arriére
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0, -1.0); glVertex3f(getWidth() / 2, getHeight() / 2, -(getDepth() / 2));
	glNormal3f(-1.0, 1.0, -1.0); glVertex3f(-(getWidth() / 2), getHeight() / 2, -(getDepth() / 2));
	glNormal3f(-1.0, -1.0, -1.0); glVertex3f(-(getWidth() / 2), -(getHeight() / 2), -(getDepth() / 2));
	glNormal3f(1.0, -1.0, -1.0); glVertex3f(getWidth() / 2, -(getHeight() / 2), -(getDepth() / 2));
	glEnd();

	//Face gauche
	glBegin(GL_QUADS);
	glNormal3f(1.0, -1.0, -1.0); glVertex3f(getWidth() / 2, -(getHeight() / 2), -(getDepth() / 2));
	glNormal3f(1.0, -1.0, 1.0); glVertex3f(getWidth() / 2, -(getHeight() / 2), getDepth() / 2);
	glNormal3f(1.0, 1.0, 1.0); glVertex3f(getWidth() / 2, getHeight() / 2, getDepth() / 2);
	glNormal3f(1.0, 1.0, -1.0); glVertex3f(getWidth() / 2, getHeight() / 2, -(getDepth() / 2));
	glEnd();

	//Face top
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0, 1.0); glVertex3f(getWidth() / 2, getHeight() / 2, getDepth() / 2);
	glNormal3f(-1.0, 1.0, 1.0); glVertex3f(-(getWidth() / 2), getHeight() / 2, getDepth() / 2);
	glNormal3f(-1.0, 1.0, -1.0); glVertex3f(-(getWidth() / 2), getHeight() / 2, -(getDepth() / 2));
	glNormal3f(1.0, 1.0, -1.0); glVertex3f(getWidth() / 2, getHeight() / 2, -(getDepth() / 2));
	glEnd();

	//Face bottom
	glBegin(GL_QUADS);
	glNormal3f(1.0, -1.0, -1.0); glVertex3f(getWidth() / 2, -(getHeight() / 2), -(getDepth() / 2));
	glNormal3f(-1.0, -1.0, -1.0); glVertex3f(-(getWidth() / 2), -(getHeight() / 2), -(getDepth() / 2));
	glNormal3f(-1.0, -1.0, 1.0); glVertex3f(-(getWidth() / 2), -(getHeight() / 2), getDepth() / 2);
	glNormal3f(1.0, -1.0, 1.0); glVertex3f(getWidth() / 2, -(getHeight() / 2), getDepth() / 2);
	glEnd();
	
	glPopMatrix();
}

int Player::drawScore(CL_Font *font, int x, int y)
{
	std::string sentence = CL_String::to_upper(getNickname() + " : " + CL_String::from_int(getScore()));

	font->set_alignment(origin_top_left);
	font->draw(x, y, sentence);

	return font->get_height(sentence) + font->get_height_offset();
}
