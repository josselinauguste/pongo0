#include "menugeneric.hpp"
#include <ClanLib/display.h>

MenuGeneric::MenuGeneric(unsigned int _nButtons) : nButtons(_nButtons), focused(-1)
{
	buttons = new CL_Sprite**[nButtons];
	for(unsigned int i = 0;i < nButtons;i++)
		buttons[i] = new CL_Sprite*[2];
}

/*MenuGeneric::MenuGeneric(CL_StyleManager *styleManager) : CL_GUIManager(styleManager)
{
}*/

MenuGeneric::~MenuGeneric()
{
	for(unsigned int i = 0;i < nButtons;i++)
	{
		delete buttons[i][0];
		delete buttons[i][1];
		delete buttons[i];
	}
	delete buttons;
}

void MenuGeneric::draw()
{
	CL_GraphicContext *gc = CL_Display::get_current_window()->get_gc();
	if(nButtons > 0)
	{
		unsigned int left = (gc->get_width() >> 1) - ((buttons[0][0]->get_width()) >> 1);
		unsigned int top = (gc->get_height() >> 1) - ((nButtons * buttons[0][0]->get_height()) >> 1);

		for(unsigned int i = 0;i < nButtons;i++)
		{
			buttons[i][(focused == (int)i)?1:0]->draw(left, top + i * buttons[0][0]->get_height());
		}
	}
}
