#pragma once
#include <SDL_mixer.h>
#include "Button.h"
#include "Background.h"
#include "Howtoplay.h"

class Menu
{
private:
	enum ButtonNames { PLAY, QUIT, HELP, SOUND };
	Button* button[4];

	Background bg;
	Howtoplay h;

	bool sound;

public:
	Menu();
	~Menu();
	bool bgSound();
	bool Enter(SDL_Texture* menu, SDL_Texture* menuButton, Mouse* m, SDL_Renderer* ren);
};