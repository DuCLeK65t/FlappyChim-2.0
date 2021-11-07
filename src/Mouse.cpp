#include "Mouse.h"

Mouse::Mouse()
{
	cursor = { 0, 0, 75, 75 };
	tip = { 0, 0, 1, 1 };
}

Mouse::~Mouse()
{

}

void Mouse::Render(SDL_Renderer* ren) 
{
	tip.x = cursor.x;
	tip.y = cursor.y;

	SDL_RenderCopy(ren, getTexture(), NULL, &cursor);
}