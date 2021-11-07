#pragma once
#include "Object.h"
#include "Mouse.h"

class Button : public Object
{
private:
	SDL_Texture* buttonTex;
	SDL_Rect sRect, dRect;

public:
	bool selected;

	Button(SDL_Renderer* ren);
	Button(int x, int y);
	void setXY(int x, int y);

	void CheckSelected(Mouse* mouse);
	void Render(SDL_Renderer* ren, SDL_Texture* menuButton);
};