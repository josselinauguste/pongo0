#include "intromanager.hpp"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

//initialisation du champ statique 'instance'
IntroManager *IntroManager::instance = NULL;

IntroManager* IntroManager::getInstance()
{
	if(!IntroManager::exists())
		IntroManager::instance = new IntroManager();

	return IntroManager::instance;
}

void IntroManager::dispose()
{
	if(IntroManager::exists())
	{
		IntroManager *b = IntroManager::instance;
		IntroManager::instance = NULL;
		delete b;
	}
}

bool IntroManager::exists()
{
	return (IntroManager::instance == NULL) ? false : true;
}

void IntroManager::execute()
{
	if(!countDown)
	{
		if(CL_Keyboard::get_keycode(CL_KEY_SPACE))
		{
			lastCountDownTime = CL_System::get_time();
			counter = counterMax;
			countDown = true;
		}
	}
	else
	{
		if(CL_System::get_time() - lastCountDownTime >= 1000)
		{
			counter--;
			lastCountDownTime = CL_System::get_time();
		}
	}

	if(counter < 0 && countDown == true)
	{
		IntroManager::dispose();
	}
}

void IntroManager::pause()
{
	lastCountDownTime = CL_System::get_time();
}

void IntroManager::draw(CL_Font *font58, CL_Font *font100)
{
	CL_GraphicContext *gc = CL_Display::get_current_window()->get_gc();
	if(!countDown)
	{
		font58->set_alignment(origin_bottom_center);
		font58->draw(gc->get_width() >> 1, gc->get_height() - 30, "PRESS SPACE BUTTON");
	}
	else
	{
		font100->set_alignment(origin_center);
		if(counter > 0)
			font100->draw(gc->get_width() >> 1, gc->get_height() >> 1, "(" + CL_String::from_int(counter) + ")");
		else if(counter == 0)
			font100->draw(gc->get_width() >> 1, gc->get_height() >> 1, "GO!");
	}
}

IntroManager::IntroManager() : counterMax(3), countDown(false)
{
}

IntroManager::~IntroManager()
{
}
