#ifndef APPH
#define APPH

#include <ClanLib/application.h>

class Game;

class App : public CL_ClanApplication
{
public:
	App();
	~App();

	virtual int main(int, char**);

private:
	void onClose();
	
	Game *game;
} app;

#endif
