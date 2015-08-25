#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "playersettings.hpp"
#include "settingsmanager.hpp"
#include "../log.hpp"

//initialisation du champ statique 'instance'
SettingsManager *SettingsManager::instance = NULL;

SettingsManager* SettingsManager::getInstance()
{
	if(!SettingsManager::instance)
	{
		SettingsManager::instance = new SettingsManager();
		SettingsManager::instance->load("settings.xml");
	}
	return SettingsManager::instance;
}

void SettingsManager::dispose()
{
	if(SettingsManager::instance)
		delete SettingsManager::instance;
}

void SettingsManager::load(std::string filename)
{
	this->filename = filename;
	
	loadDefaultSettings();
	
	try
	{
		CL_DomDocument document;
		document.load(new CL_InputSource_File(filename), true, true);

		CL_DomNode element = document.get_document_element().get_first_child();
		while(!element.is_null())
		{
			std::string nodeName = element.get_node_name();
			if(nodeName == "screen")
			{
				CL_DomNode screenElement = element.get_first_child();
				while(!screenElement.is_null())
				{
					std::string screenNodeName = screenElement.get_node_name();
					if(screenNodeName == "width")
					{
						screenWidth = CL_String::to_int(screenElement.to_element().get_attribute("value"));
					}
					else if(screenNodeName == "height")
					{
						screenHeight = CL_String::to_int(screenElement.to_element().get_attribute("value"));
					}
					else if(screenNodeName == "fullscreen")
					{
						screenFullscreen = CL_String::to_bool(screenElement.to_element().get_attribute("value"));
					}
					screenElement = screenElement.get_next_sibling();
				}
			}
			else if(nodeName == "player")
			{
				std::string nickname = element.to_element().get_attribute("nickname");
				int rightKey;
				int leftKey;
				int upKey;
				int downKey;
				CL_Color racketColor;
				CL_DomNode playerElement = element.get_first_child();
				while(!playerElement.is_null())
				{
					std::string playerNodeName = playerElement.get_node_name();
					if(playerNodeName == "right_key")
					{
						rightKey = (int) playerElement.to_element().get_attribute("value").c_str()[0];
					}
					else if(playerNodeName == "left_key")
					{
						leftKey = (int) playerElement.to_element().get_attribute("value").c_str()[0];
					}
					else if(playerNodeName == "up_key")
					{
						upKey = (int) playerElement.to_element().get_attribute("value").c_str()[0];
					}
					else if(playerNodeName == "down_key")
					{
						downKey = (int) playerElement.to_element().get_attribute("value").c_str()[0];
					}
					else if(playerNodeName == "color")
					{
						unsigned int r = CL_String::to_int(playerElement.to_element().get_attribute("r"));
						unsigned int g = CL_String::to_int(playerElement.to_element().get_attribute("g"));
						unsigned int b = CL_String::to_int(playerElement.to_element().get_attribute("b"));

						racketColor = CL_Color(r, g, b);
					}

					playerElement = playerElement.get_next_sibling();
				}

				players[nickname] = new PlayerSettings(nickname, racketColor, rightKey, leftKey, upKey, downKey);
			}
			else if(nodeName == "ai-nickname")
			{
				aiNicknames.push_back(element.to_element().get_attribute("value"));
			}
			else if(nodeName == "racket-color")
			{
				unsigned int r = CL_String::to_int(element.to_element().get_attribute("r"));
				unsigned int g = CL_String::to_int(element.to_element().get_attribute("g"));
				unsigned int b = CL_String::to_int(element.to_element().get_attribute("b"));
				racketColors.push_back(CL_Color(r, g, b));
			}

			element = element.get_next_sibling();
		}
	}
	catch(CL_Error err)
	{
		Log::print(LOG_ERR, "Une erreur est survenue lors de l'analyse du fichier de configuration " + filename + ".");
        filename = "\0";
	}
}

void SettingsManager::save()
{
}

void SettingsManager::loadDefaultSettings()
{
	screenWidth = 640;
	screenHeight = 480;
	screenFullscreen = false;
	players.clear();
	aiNicknames.clear();
	racketColors.clear();
}

SettingsManager::SettingsManager()
{
    filename = "\0";
}

SettingsManager::~SettingsManager()
{
	typedef std::map<std::string, PlayerSettings*>::const_iterator MI;
	for(MI p = players.begin();p != players.end();p++)
	{
		delete p->second;
	}
}
