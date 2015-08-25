#include <ClanLib/display.h>
#include "../game.hpp"
#include "../gamesettings/settingsmanager.hpp"
#include "../gamesettings/playersettings.hpp"
#include "../world.hpp"
#include "humanplayer.hpp"

#include <map>

HumanPlayer::HumanPlayer(SIDE _side, float _width, float _height, float _depth, std::string _nickname) : LocalPlayer(_side, _width, _height, _depth)
{
	setNickname(_nickname);

	CL_Color racketColor = SettingsManager::getInstance()->players[getNickname()]->getRacketColor();
	setColor(racketColor.get_red(), racketColor.get_green(), racketColor.get_blue());
}

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::updateInfos(unsigned int time)
{
	PlayerSettings *settings = SettingsManager::getInstance()->players[getNickname()];
	bool x = false, y = false;

	if(CL_Keyboard::get_keycode(settings->getUpKey()))
	{
		accelerate(Y, POSITIVE);
		y = true;
	}

	if(CL_Keyboard::get_keycode(settings->getDownKey()))
	{
		accelerate(Y, NEGATIVE);
		y = true;
	}
	
	if(CL_Keyboard::get_keycode(settings->getLeftKey()))
	{
		(getSide() > 0) ? accelerate(X, NEGATIVE) : accelerate(X, POSITIVE);
		x = true;
	}
	
	if(CL_Keyboard::get_keycode(settings->getRightKey()))
	{
		(getSide() > 0) ? accelerate(X, POSITIVE) : accelerate(X, NEGATIVE);
		x = true;
	}

	if(x == false)
		decelerate(X);

	if(y == false)
		decelerate(Y);

	updatePosition(time);
}
