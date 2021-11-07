#pragma once
#include "Object.h"

class Mouse : public Object
{
private:
public:
	SDL_Rect cursor, tip;

	Mouse();
	~Mouse();
	void Render(SDL_Renderer* ren);
};