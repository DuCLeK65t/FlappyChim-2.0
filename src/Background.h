#pragma once
#include "Object.h"

class Background : public Object
{
private:
public:
	void Render(SDL_Renderer* ren);
};