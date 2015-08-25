#include "playersettings.hpp"
#include <ClanLib/display.h>

PlayerSettings::PlayerSettings(std::string _nickname, CL_Color _racketColor, int _rightKey, int _leftKey, int _upKey, int _downKey) : nickname(_nickname), racketColor(_racketColor), rightKey(_rightKey), leftKey(_leftKey), upKey(_upKey), downKey(_downKey)
{
}

PlayerSettings::~PlayerSettings()
{
}
