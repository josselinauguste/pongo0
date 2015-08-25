#include <ClanLib/core.h>
#include <time.h>
#include "player/humanplayer.hpp"
#include "player/aiplayer.hpp"
#include "player/netplayer.hpp"
#include "projectile/localprojectile.hpp"
#include "projectile/netprojectile.hpp"
#include "world.hpp"
#include "menu/menumanager.hpp"
#include "game.hpp"
#include "intromanager.hpp"
#include "tools.hpp"
#include "log.hpp"

Game* Game::instance = NULL;

Game::Game(std::string nameFirstPlayer, std::string nameSecondPlayer) : playingTime(0), bMustQuitGame(false)
{
	Game::instance = this;
	srand((unsigned) time(NULL));

	try
	{
		resourceManager = new CL_ResourceManager("resources.xml");
	
		font[0] = new CL_Font("Game/font36", resourceManager);
		font[1] = new CL_Font("Game/font58", resourceManager);
		font[2] = new CL_Font("Game/font100", resourceManager);
	}
	catch(CL_Error err)
	{
		throw CL_Error(err.message);
	}
	
	viewpoint = new CL_Viewpoint();
	framerateCounter = new CL_FramerateCounter();
	world = new World(resourceManager, 200, 200, 200);
	CL_Mouse::hide();

	players = new std::list<Player*>();
	players->clear();

	if(nameFirstPlayer != "")
	{
		Player *p1 = new HumanPlayer(FIRST, 20.0, 20.0, 4.0, nameFirstPlayer);
		players->push_back(p1);
		setupViewpoint(p1->getSide());
	}
	else
	{
		throw CL_Error("Le nom du premier joueur (nameFirstPlayer) n'est pas specifie.");
	}

	if(nameSecondPlayer != "")
	{
		players->push_back(new HumanPlayer(SECOND, 20.0, 20.0, 4.0, nameSecondPlayer));
	}
	else
	{
		players->push_back(new AIPlayer(SECOND, 20.0, 20.0, 4.0));
	}

	projectile = new LocalProjectile(5.0);

	//initialisation de l'intro manager
	IntroManager::getInstance();

	this->initDisplay();
}

Game::~Game()
{
	std::list<Player*>::iterator it2 = players->begin();
	while(it2 != players->end())
	{
		delete *it2;
		it2++;
	}
	delete players;

	delete world;
	delete viewpoint;
	delete projectile;

	if(IntroManager::exists())
		IntroManager::dispose();

	if(MenuManager::exists())
		MenuManager::dispose();

	if(framerateCounter != NULL)
		delete framerateCounter;
	delete resourceManager;
	delete mainOpenGLState;
}

//renvoie true pour fermer l'application, sinon false
void Game::run()
{
	lastTime = CL_System::get_time();
	dTime = 0;

    while(!bMustQuitGame)
	{
		if(MenuManager::exists() || IntroManager::exists())
		{
			if(MenuManager::exists())
			{
				MenuManager::getInstance()->execute();
			}

			if(IntroManager::exists())
			{
				//le menu est prioritaire sur l'intromanager
				if(MenuManager::exists())
					IntroManager::getInstance()->pause();
				else
					IntroManager::getInstance()->execute();
			}
		}
		else
		{
			projectile->updateInfos(dTime);
			if(LocalProjectile *localProjectile = dynamic_cast<LocalProjectile*>(projectile))
				localProjectile->checkBordersCollision();

			std::list<Player*>::iterator itPlayers = players->begin();
			while(itPlayers != players->end())
			{
				(*itPlayers)->updateInfos(dTime);
				
				if(LocalPlayer *localPlayer = dynamic_cast<LocalPlayer*>(*itPlayers))
				{
					localPlayer->checkBordersCollision();

					if(LocalProjectile *localProjectile = dynamic_cast<LocalProjectile*>(projectile))
						localPlayer->checkProjectileCollision(localProjectile);
				}

				itPlayers++;
			}

			playingTime += dTime;
		}

		this->display();
		this->checkInput();

		//met à jour le temps
		dTime = CL_System::get_time() - lastTime;
		lastTime = CL_System::get_time();

		//echange les buffers d'affichage
		CL_Display::flip();
		//permet la mise a jour des inputs - necessaire
		CL_System::keep_alive(10);
	}
}

void Game::checkInput()
{
	//inhibe les contrôles si on est dans un menu
	if(!MenuManager::exists())
	{
		if(CL_Keyboard::get_keycode(CL_KEY_ESCAPE))
		{	
			MenuManager::getInstance(resourceManager);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//Gerance graphique/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Game::initDisplay()
{
	mainOpenGLState = new CL_OpenGLState(CL_Display::get_current_window()->get_gc());
	mainOpenGLState->set_active();

	resizeGLScene();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);

	//ne dessine que les faces avant des polygones
	glCullFace(GL_FRONT);
	//active le depth buffer
	glEnable(GL_DEPTH_TEST);
	//normalize les vecteurs
	glEnable(GL_NORMALIZE);
	//dessine que les polygones definis dans le sens trigonometrique
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	//modele de degrade
	glShadeModel(GL_SMOOTH);
	//filtrage des textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	
	//gestion des lumiéres
	GLfloat ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	
#ifndef WIN32
	//sépare la couleur spéculaire pour les textures
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
#endif

	//lumiére de position, donc w = 1.0 (sinon lumiére directionnelle)
	GLfloat position[] = {world->getWidth() / 2.0f - 2.0f, world->getHeight() / 2.0f - 2.0f, -world->getDepth() / 2.0f + 2.0f, 1.0f};
	GLfloat direction[] = {-1.0, -1.0, 1.0};
	GLfloat cutoff[] = {90.0f};
	GLfloat attenuation[] = {0.2f};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	world->initDisplay();
}

void Game::display()
{
	std::list<Player*>::iterator itPlayers;
	int yScore;

	mainOpenGLState->set_active();
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewpoint->setup_modelview();

	//Affichages tridimensionnels
	world->render();
	projectile->draw();
	for(itPlayers = players->begin();itPlayers != players->end();itPlayers++)
	{
		(*itPlayers)->draw();
	}

	//Affichages bidimensionnels
	glDisable(GL_LIGHTING);
	
	for(itPlayers = players->begin(), yScore = 5;itPlayers != players->end();itPlayers++)
	{
		yScore += (*itPlayers)->drawScore(font[0], 5, yScore);
	}

	if(MenuManager::exists())
	{
		MenuManager::getInstance()->draw();
	}
	if(IntroManager::exists())
	{
		IntroManager::getInstance()->draw(font[1], font[2]);
	}

	font[0]->set_alignment(origin_top_right);
	font[0]->draw(CL_Display::get_current_window()->get_gc()->get_width() - 5, 5, "FPS : " + CL_String::from_int(framerateCounter->get_fps()));
	mainOpenGLState->set_active();
}

//Fonction à appeller à chaque changement de résolution
void Game::resizeGLScene()
{
	CL_GraphicContext *gc = CL_Display::get_current_window()->get_gc();
	glViewport(0, 0, (GLsizei) gc->get_width(), (GLsizei) gc->get_height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat) gc->get_width() / (GLfloat) gc->get_height(), 0.1f, 500.f);
	glMatrixMode(GL_MODELVIEW);
}

void Game::setupViewpoint(float posx, float posy, float posz, float dirx, float diry, float dirz, float upx, float upy, float upz)
{
	viewpoint->pos.x = posx;
	viewpoint->pos.y = posy;
	viewpoint->pos.z = posz;
	viewpoint->dir.x = dirx;
	viewpoint->dir.y = diry;
	viewpoint->dir.z = dirz;
	viewpoint->up.x = upx;
	viewpoint->up.y = upy;
	viewpoint->up.z = upz;
}

void Game::setupViewpoint(SIDE side)
{
	//22.5 correspond à l'angle de vision du viewport divisé par 2, en degrés
	setupViewpoint(
		0.0,
		0.0,
		static_cast<float>(side * (world->getDepth() / 2 + Tools<float>::maximum(world->getHeight(), world->getWidth()) / (2 * tan(22.5 * Tools<int>::pi() / 180)))),
		0.0,
		0.0,
		1.0f
		);
}
