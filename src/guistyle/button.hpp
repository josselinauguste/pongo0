#ifndef BUTTONH
#define BUTTONH

#include <ClanLib/gui.h>

class CL_Color;
class CL_Slot;

class PongoStyleManager;

class PongoButton : public CL_ComponentStyle
{
public:
	PongoButton(CL_Button*, PongoStyleManager*);
	~PongoButton();
	
private:
	void drawButton(CL_Color);
	void onPressed();
	void onReleased();
	void onPaint();
	
	CL_Slot slotPaint;
	CL_Slot slotPressed, slotReleased;

	CL_Button *button;
	bool bDown;
};

#endif
