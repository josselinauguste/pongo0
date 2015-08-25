#include "../game.hpp"
#include "../projectile/projectile.hpp"
#include "../world.hpp"
#include "../gamesettings/settingsmanager.hpp"
#include "aiplayer.hpp"

AIPlayer::AIPlayer(SIDE _side, float _width, float _height, float _depth) : LocalPlayer(_side, _width, _height, _depth)
{
	//tirage au sort de la couleur
	unsigned int c = rand() % ((unsigned int)SettingsManager::getInstance()->racketColors.size());
	CL_Color color = SettingsManager::getInstance()->racketColors[c];
	setColor(color.get_red(), color.get_green(), color.get_blue());

	//tirage au sort du nickname
	unsigned int n = rand() % ((unsigned int)SettingsManager::getInstance()->aiNicknames.size());
	setNickname(SettingsManager::getInstance()->aiNicknames[n]);
}

AIPlayer::~AIPlayer()
{
}

void AIPlayer::updateInfos(unsigned int time)
{
	Projectile *projectile = Game::getInstance()->getProjectile();
	if(projectile->getPosition().x < position->x - getWidth() / 2)
		accelerate(X, NEGATIVE);
	else if(projectile->getPosition().x > position->x + getWidth() / 2)
		accelerate(X, POSITIVE);
	else
		decelerate(X);
	if(projectile->getPosition().y < position->y - getHeight() / 2)
		accelerate(Y, NEGATIVE);
	else if(projectile->getPosition().y > position->y + getHeight() / 2)
		accelerate(Y, POSITIVE);
	else
		decelerate(Y);

	updatePosition(time);
}
