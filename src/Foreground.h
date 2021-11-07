#pragma once
#include "Object.h"

class Foreground : public Object
{
private:
public:
	void Render(SDL_Renderer* ren, const double angle);
};