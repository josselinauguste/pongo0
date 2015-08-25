#include <ClanLib/core.h>
#include <ClanLib/gui.h>
#include "stylemanager.hpp"
#include "button.hpp"

PongoStyleManager::PongoStyleManager(CL_ResourceManager *_resources) : CL_StyleManager_Silver(_resources)
{
}

void PongoStyleManager::connect_styles(const std::string &type, CL_Component *component)
{
	if(type == "button")
	{
		CL_Button *button = static_cast<CL_Button*>(component);
		button->set_style(new PongoButton(button, this));
	}
	else
	{
		CL_StyleManager_Silver::connect_styles(type, component);
	}
}

PongoStyleManager::~PongoStyleManager()
{
}
