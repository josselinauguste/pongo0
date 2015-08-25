#include "menumanager.hpp"
#include "menuingame.hpp"
#include "ClanLib/display.h"

//initialisation du champ statique 'instance'
MenuManager *MenuManager::instance = NULL;

MenuManager* MenuManager::getInstance(CL_ResourceManager *resourceManager)
{
	if(!MenuManager::exists() && resourceManager != NULL)
		MenuManager::instance = new MenuManager(resourceManager);

	return MenuManager::instance;
}

void MenuManager::dispose()
{
	if(MenuManager::exists())
	{
		CL_Mouse::hide();
		MenuManager *b = MenuManager::instance;
		MenuManager::instance = NULL;
		delete b;
	}
}

bool MenuManager::exists()
{
	return (MenuManager::instance == NULL) ? false : true;
}

void MenuManager::execute()
{
	currentMenu->execute();
}

void MenuManager::draw()
{
	currentMenu->draw();
}

void MenuManager::switchMenu(std::string menuName)
{
	//inhiber les inputs du menu precedent, activer ceux du nouveau
	//verifier qu'a l'init des menus, les inputs soient inhibés, et que l'input du main soit activé lors de son premier affichage

	if(menus.find(menuName) != menus.end())
	{
		currentMenu = menus[menuName];
	}
}

MenuManager::MenuManager(CL_ResourceManager *resourceManager)
{
	MenuGeneric *menu = new MenuInGame(resourceManager);
	menus["in_game"] = menu;
	currentMenu = menu;

	CL_Mouse::show();
	CL_Mouse::set_position((CL_Display::get_current_window()->get_width()) >> 1, (CL_Display::get_current_window()->get_height()) >> 1);
}

MenuManager::~MenuManager()
{
	std::map<std::string, MenuGeneric*>::iterator itMenus = menus.begin();
	while(itMenus != menus.end())
	{
		delete itMenus->second;
		itMenus++;
	}
}
