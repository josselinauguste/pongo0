#ifndef WORLDH
#define WORLDH

#include <ClanLib/gl.h>

class CL_ResourceManager;

class World
{
public:
	World(CL_ResourceManager*, float, float, float);
	~World();

	void initDisplay();
	void render();

	float getWidth() const { return width; }
	float getHeight() const { return height; }
	float getDepth() const { return depth; }

private:
	float width, height, depth;

	CL_OpenGLSurface *texBorders;
	GLuint displayListBorders;
};

#endif
