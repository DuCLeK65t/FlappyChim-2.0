#include "Howtoplay.h"

Howtoplay::Howtoplay()
{
	animationTimer = 0;
	timer = 210;
}

Howtoplay::~Howtoplay()
{

}

void Howtoplay::Render(SDL_Renderer* ren)
{
	animationTimer++;
	if (animationTimer < timer)
	{
		setSrc(0, 0, 507, 102);
	}
	else if (animationTimer >= timer)
	{
		setSrc(0, 102, 507, 102);
	}
	if (animationTimer > timer * 2)
	{
		animationTimer = 0;
	}

	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}