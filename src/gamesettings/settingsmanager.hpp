#ifndef SETTINGSMANAGERH
#define SETTINGSMANAGERH

#include <map>
#include <vector>

#include <ClanLib/core.h>

class CL_Color;
class PlayerSettings;

class SettingsManager
{
public:
	static SettingsManager* getInstance();
	static void dispose();

	int screenWidth;
	int screenHeight;
	bool screenFullscreen;
	std::map<std::string, PlayerSettings*> players;
	std::vector<std::string> aiNicknames;
	std::vector<CL_Color> racketColors;

private:
	SettingsManager();
	~SettingsManager();
	
	void load(std::string);
	void loadDefaultSettings();
    void save();
	
	std::string filename;

    static SettingsManager *instance;
};

#endif
