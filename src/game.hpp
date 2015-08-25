#ifndef GAMEH
#define GAMEH

#include <list>
#include <map>

#include <ClanLib/signals.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

#include "player/player.hpp"

class CL_ResourceManager;

class Projectile;
class World;
class MenuManager;
class IntroManager;

class Game
{
public:
	Game(std::string, std::string);
	~Game();
	
	void run(void);
	void kill(void) { bMustQuitGame = true;	sig_quit_game(); }

	World *getWorld() const { return world; }
	std::list<Player*> *getPlayers() const { return players; }
	Projectile *getProjectile() const { return projectile; }

	static Game *getInstance() { return instance; }
	
	CL_Signal_v0 sig_quit_game;

private:
	void initDisplay();
	void resizeGLScene();
	void checkInput();
	void display();
	void setupViewpoint(float, float, float, float, float, float, float upx = 0.0, float upy = 1.0, float upz = 0.0);
	void setupViewpoint(SIDE);

	CL_ResourceManager *resourceManager;

	CL_OpenGLState *mainOpenGLState;
	CL_Viewpoint *viewpoint;
	CL_FramerateCounter *framerateCounter;
	CL_Font *font[3];

	std::list<Player*> *players;
	Projectile *projectile;
	World *world;
	
	unsigned int lastTime;
	int dTime;
	unsigned int playingTime;
	
	bool bMustQuitGame;

	static Game *instance;
};

#endif
