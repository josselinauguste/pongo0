#ifndef HUMANPLAYERH
#define HUMANPLAYERH

#include "localplayer.hpp"

class Game;
class CL_Vector;

class HumanPlayer : public LocalPlayer
{
public:
	HumanPlayer(SIDE, float, float, float, std::string);
	~HumanPlayer();

	virtual void updateInfos(unsigned int);

private:
};

#endif
