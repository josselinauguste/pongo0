#ifndef MENUMANAGERH
#define MENUMANAGERH

#include "menugeneric.hpp"

class CL_ResourceManager;

class MenuManager
{
public:
	static MenuManager* getInstance(CL_ResourceManager *resourceManager = NULL);
	static void dispose();
	static bool exists();

	void execute();
	void draw();

private:
	MenuManager(CL_ResourceManager*);
	~MenuManager();

	static MenuManager *instance;

	void switchMenu(std::string);

	MenuGeneric *currentMenu;
	std::map<std::string, MenuGeneric*> menus;
};

#endif
