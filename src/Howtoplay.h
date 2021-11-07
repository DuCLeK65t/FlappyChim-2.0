#pragma once
#include "Object.h"

class Howtoplay : public Object
{
private:
	int animationTimer;
	int timer;

public:
	Howtoplay();
	~Howtoplay();

	void Render(SDL_Renderer* ren);
};