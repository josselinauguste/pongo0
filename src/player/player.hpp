#ifndef PLAYERH
#define PLAYERH

#include "../gameentity.hpp"

class Game;
class CL_Vector;
class CL_Color;

typedef enum {FIRST = -1, SECOND = 1} SIDE;

class Player : public GameEntity
{
public:
	Player(SIDE, float, float, float);
	virtual ~Player();

	virtual void draw();
	int drawScore(CL_Font*, int, int);

	int getScore() const { return score; }
	std::string getNickname() const { return nickname; }

	float getWidth() const { return width; }
	float getHeight() const { return height; }
	float getDepth() const { return depth; }

	SIDE getSide() const { return side; }

protected:
	void setSide(SIDE _side) { side = _side; }
	void setWidth(float _width) { width = _width; }
	void setHeight(float _height) { height = _height; }
	void setDepth(float _depth) { depth = _depth; }
	void setNickname(std::string _nickname) { nickname = _nickname; }
	void setScore(int _score) { score = _score; }

private:
	SIDE side;
	int score;
	std::string nickname;
	float width, height, depth;
};

#endif
