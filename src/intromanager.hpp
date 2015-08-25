#ifndef INTROMANAGERH
#define INTROMANAGERH

class CL_Font;

class IntroManager
{
public:
	static IntroManager* getInstance();
	static void dispose();
	static bool exists();

	void execute();
	void pause();
	void draw(CL_Font*, CL_Font*);

private:
	IntroManager();
	~IntroManager();

	static IntroManager *instance;

	int counter;
	unsigned int counterMax;
	bool countDown;
	unsigned int lastCountDownTime;
};

#endif
