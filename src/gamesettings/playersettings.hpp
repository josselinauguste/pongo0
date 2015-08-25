#ifndef PLAYERSETTINGSH
#define PLAYERSETTINGSH

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class PlayerSettings
{
public:
	PlayerSettings(std::string, CL_Color, int, int, int, int);
	~PlayerSettings();

	std::string getNickname() const { return nickname; }
	CL_Color getRacketColor() const { return racketColor; }
	int getRightKey() const { return rightKey; }
	int getLeftKey() const { return leftKey; }
	int getUpKey() const { return upKey; }
	int getDownKey() const { return downKey; }

	void setNickname(const std::string _nickname) { nickname = _nickname; }
	void setRacketColor(const CL_Color _racketColor) { racketColor = CL_Color(_racketColor.get_red(), _racketColor.get_green(), _racketColor.get_blue()); }
	void setRightKey(const int _rightKey) { rightKey = _rightKey; }
	void setLeftKey(const int _leftKey) { leftKey = _leftKey; }
	void setUpKey(const int _upKey) { upKey = _upKey; }
	void setDownKey(const int _downKey) { downKey = _downKey; }

private:
	std::string nickname;
	CL_Color racketColor;
	int rightKey, leftKey, upKey, downKey;
};

#endif
