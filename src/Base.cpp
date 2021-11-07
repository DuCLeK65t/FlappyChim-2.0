#include "Base.h"

void Base::BaseUpdate1(bool birdDie)
{
	if (distance1 <= -720)
	{
		distance1 = 0;
	}
	else
	{
		if (!birdDie)
		{
			distance1--;
		}
		setDest(distance1, 600, 720, 120);
	}
}

void Base::BaseUpdate2(bool birdDie)
{
	if (distance2 <= 0)
	{
		distance2 = 720;
	}
	else
	{
		if (!birdDie)
		{
			distance2--;
		}
		setDest(distance2, 600, 720, 120);
	}
}

void Base::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}