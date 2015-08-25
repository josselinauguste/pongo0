#include "../game.hpp"
#include "netplayer.hpp"

NetPlayer::NetPlayer() : Player(FIRST, 0.0, 0.0, 0.0)
{
}

NetPlayer::~NetPlayer()
{
}

void NetPlayer::updateInfos(unsigned int lastTime)
{
}

void NetPlayer::checkBordersCollision()
{
	//no implementation needed !
}
