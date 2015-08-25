#ifndef AIPLAYERH
#define AIPLAYERH

#include "localplayer.hpp"

class Game;
class CL_Vector;

class AIPlayer : public LocalPlayer
{
public:
	AIPlayer(SIDE, float, float, float);
	~AIPlayer();

	virtual void updateInfos(unsigned int);
};

#endif
