#include "Foreground.h"

void Foreground::Render(SDL_Renderer* ren, const double angle)
{
	SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
}