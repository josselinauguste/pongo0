#include <ClanLib/display.h>
#include <ClanLib/signals.h>
#include "button.hpp"

PongoButton::PongoButton(CL_Button*_button, PongoStyleManager* _style) : CL_ComponentStyle(_button)
{
	button = _button;

	slotPaint = button->sig_paint().connect(this, &PongoButton::onPaint);
	slotPressed = button->sig_pressed().connect(this, &PongoButton::onPressed);
	slotReleased = button->sig_released().connect(this, &PongoButton::onReleased);
}

PongoButton::~PongoButton()
{
}

void PongoButton::drawButton(CL_Color color)
{
	int buttonWidth = button->get_width();
	int buttonHeight = button->get_height();
	CL_Display::fill_rect(CL_Rect(0, 0, buttonWidth, buttonHeight), CL_Color(59, 63, 72));
	CL_Display::draw_rect(CL_Rect(2, 2, buttonWidth - 3, buttonHeight - 3), color);
}

void PongoButton::onPaint()
{
	if(button->is_enabled() == false)
	{
	}
	else
	{
		bool beingClicked = button->has_mouse_over() ? bDown : false;
		if((button->is_down() && !beingClicked) || (!button->is_down() && beingClicked))
			drawButton(CL_Color(159, 95, 96));
		else if(button->has_mouse_over())
			drawButton(CL_Color(69, 92, 133));
		else
			drawButton(CL_Color(92, 184, 92));
	}
}

void PongoButton::onPressed()
{
	bDown = true;
}

void PongoButton::onReleased()
{
	bDown = false;
}
