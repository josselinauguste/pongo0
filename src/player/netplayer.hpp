#ifndef NETPLAYERH
#define NETPLAYERH

#include "player.hpp"

class Game;
class CL_Vector;

class NetPlayer : public Player
{
public:
	NetPlayer();
	~NetPlayer();

	virtual void updateInfos(unsigned int);
	virtual void checkBordersCollision();
};

#endif
