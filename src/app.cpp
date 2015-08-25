#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/signals.h>
#include <ClanLib/gui.h>
#include "log.hpp"
#include "game.hpp"
#include "gamesettings/settingsmanager.hpp"
#include "app.hpp"

App::App()
{
}

App::~App()
{
}

int App::main(int argc, char **argv)
{
	//Redirection de la sortie standart
	CL_ConsoleWindow console("Pongo");
	console.redirect_stdio();

	try
	{
		std::string nameFirstPlayer = "jojolapin";
		std::string nameSecondPlayer = "BenO";
		
		CL_SetupCore::init();

		if(argc > 1)
		{
			nameFirstPlayer = argv[1];
			if(argc > 2)
				nameSecondPlayer = argv[2];
		}

		try
		{
			Log::open("log.txt");
		}
		catch(CL_Error errlog)
		{
			std::cout << errlog.message.c_str() << std::endl;
			CL_SetupCore::deinit();
			return 0;
		}

		CL_SetupGUI::init();
		CL_SetupGL::init();
		CL_SetupDisplay::init();
		
		SettingsManager *settingsManager = SettingsManager::getInstance();

		//Initialisation graphique
		CL_OpenGLWindow window("Pongo", settingsManager->screenWidth, settingsManager->screenHeight, settingsManager->screenFullscreen);
		CL_Slot slotCloseWindow = window.sig_window_close().connect(this, &App::onClose);

		game = new Game(nameFirstPlayer, nameSecondPlayer);
		game->run();
		delete game;
		
	    settingsManager->dispose();
		
		CL_SetupDisplay::deinit();
		CL_SetupGL::deinit();
		CL_SetupGUI::deinit();
		CL_SetupCore::deinit();
	}
	catch(CL_Error err)
	{
		Log::print(LOG_ERR, "Une exception est survenue : " + err.message + ".");
		console.display_close_message();
	}
    
	return 0;
}

void App::onClose()
{
	game->kill();
}
