#pragma once
#include "MenuGlobals.h"
#include "MenuButton.h"
#include "MenuMouse.h"

using namespace std;

class State
{
public:
	SDL_Texture* background;
	Mouse* mouse;
	bool menuState;
	/*bool GetMenuState();*/
	State();
	virtual ~State();
	virtual void enter() = 0;
	virtual void update() = 0;

	void Initialize();
};

class Menu : public State
{
public:
	enum ButtonNames { PLAY, OPTIONS, EXIT, SOUND };
	Button* button[4];
	Menu();
	virtual ~Menu();
	void enter();
	void update();
	//bool GetMenuState();
};

class Options : public State {
public:
	enum ButtonNames { PLAY, BACK, SOUND };
	Button* button[3];
	Options();
	virtual ~Options();
	void enter();
	void update();
};