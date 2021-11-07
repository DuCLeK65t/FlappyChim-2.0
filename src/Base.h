#pragma once
#include "Object.h"

class Base : public Object
{
private:
	int distance1 = 0;
	int distance2 = 720;

public:
	void BaseUpdate1(bool birdDie);
	void BaseUpdate2(bool birdDie);
	void Render(SDL_Renderer* ren);
};