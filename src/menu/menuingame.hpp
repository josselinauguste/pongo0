#ifndef MENUINGAMEH
#define MENUINGAMEH

#include "menugeneric.hpp"

class CL_ResourceManager;

class MenuInGame : public MenuGeneric
{
public:
	MenuInGame(CL_ResourceManager*);
	virtual ~MenuInGame();

	virtual void execute();
};

#endif
