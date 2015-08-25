#ifndef MENUGENERICH
#define MENUGENERICH

#include <ClanLib/gui.h>

class CL_Sprite;

class MenuGeneric
{
public:
	MenuGeneric(unsigned int);
	virtual ~MenuGeneric();

	virtual void execute() = 0;
	void draw();

protected:
	unsigned int nButtons;
	CL_Sprite ***buttons;
	int focused;
};

/*class MenuGeneric : public CL_GUIManager
{
public:
	MenuGeneric(CL_StyleManager*);
	~MenuGeneric();

private:
	CL_ComponentManager *componentManager;
};*/

#endif
