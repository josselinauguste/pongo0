#ifndef STYLEMANAGERH
#define STYLEMANAGERH

#include <string>

#include <ClanLib/guistylesilver.h>

class CL_ResourceManager;
class CL_Component;

class PongoStyleManager : public CL_StyleManager_Silver
{
public:
	PongoStyleManager(CL_ResourceManager*);
	~PongoStyleManager();
	
	//Connecte le style au composant
	//Le parametre 'type' indique le type du composant
	virtual void connect_styles(const std::string &type, CL_Component *parent);

private:
};

#endif
