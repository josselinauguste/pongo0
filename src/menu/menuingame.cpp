#include "menuingame.hpp"
#include "menumanager.hpp"
#include "../game.hpp"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

MenuInGame::MenuInGame(CL_ResourceManager *resourceManager) : MenuGeneric(2)
{
	buttons[0][0] = new CL_Sprite("Game/menu-continue1", resourceManager);
	buttons[0][1] = new CL_Sprite("Game/menu-continue2", resourceManager);
	buttons[1][0] = new CL_Sprite("Game/menu-quit1", resourceManager);
	buttons[1][1] = new CL_Sprite("Game/menu-quit2", resourceManager);
}

MenuInGame::~MenuInGame()
{
}

void MenuInGame::execute()
{
	if(nButtons > 0)
	{
		unsigned int left = (CL_Display::get_current_window()->get_gc()->get_width() >> 1) - ((buttons[0][0]->get_width()) >> 1);
		unsigned int top = (CL_Display::get_current_window()->get_gc()->get_height() >> 1) - ((nButtons * buttons[0][0]->get_height()) >> 1);
		focused = -1;

		for(unsigned int i = 0;i < nButtons;i++)
		{
			if(CL_Mouse::get_x() > (int)left && CL_Mouse::get_x() < (int)(left + buttons[0][0]->get_width()) && CL_Mouse::get_y() > (int)(top + i * buttons[0][0]->get_height()) && CL_Mouse::get_y() < (int)(top + (i + 1) * buttons[0][0]->get_height()))
			{
				focused = i;
			}
		}
	}

	if(CL_Mouse::get_keycode(CL_MOUSE_LEFT) && focused == 0)
	{
		MenuManager::dispose();
	}

	if(CL_Mouse::get_keycode(CL_MOUSE_LEFT) && focused == 1)
	{
		MenuManager::dispose();
		Game::getInstance()->kill();
	}
}
