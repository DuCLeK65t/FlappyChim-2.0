#include <iostream>
#include "Bird.h"

Bird::Bird()
{
	animationTimer = 0;
	speed = 0;
	g = 0.3;
	Ypos = 200;
	inJump = false;
	jumpHeight = -7.5;
	jumpTimer;
	lastJump = 0;
}

Bird::Bird(int b_Src_Width, int b_Src_Height)
{
	b_Width = b_Src_Width / 1.2;
	b_Height = b_Src_Height / 1.2;
	setDest(110, 200, b_Width, b_Height);
}

void Bird::Gravity(bool touchBase, bool playing)
{
	if (JumpState())
	{
		speed = jumpHeight; //Reset speed
		inJump = false;
	}
	if (!touchBase)
	Ypos += speed / 4.55;
	/*Upper collision limit*/
	if (Ypos <= - b_Height)
		Ypos = - b_Height;

	speed += g / 2.5;
	setDest(110, Ypos, b_Width, b_Height);
	
	/*Set Angle*/
	SetCoordinate(b_Width / 3, b_Height / 2);
	angle = (speed / 2) * 10 - 5;
	if (angle <= -45)
		angle = -45;
	else if (angle >= 90)
		angle = 90;

	if (!playing)
	{
		Ypos = 300;
		speed = 0;

		angle = 0;
	}
}

double Bird::GetTimeJump(double jumpTimer)
{
	return SDL_GetTicks();
}

void Bird::Jump()
{
	jumpTimer = GetTimeJump(jumpTimer);
	if (jumpTimer - lastJump > 165)
	{
		inJump = true;
		lastJump = jumpTimer;
	}
	else
	{
		inJump = false;
	}
}

bool Bird::JumpState()
{
	return inJump;
}

void Bird::SetCoordinate(int x, int y)
{
	coordinate.x = x;
	coordinate.y = y;
}

SDL_Point* Bird::GetCoordinate()
{
	return &coordinate;
}

void Bird::CreateTexture1(const char* address, SDL_Renderer* ren)
{
	tex1 = TextureManager::Texture(address, ren);
}

void Bird::CreateTexture2(const char* address, SDL_Renderer* ren)
{
	tex2 = TextureManager::Texture(address, ren);
}

void Bird::Render(SDL_Renderer* ren)
{
	animationTimer++;
	if (animationTimer < 25)
	{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), angle, GetCoordinate(), SDL_FLIP_NONE);
	}
	else if (animationTimer >= 25 && animationTimer <= 50)
	{
		SDL_RenderCopyEx(ren, tex1, &getSrc(), &getDest(), angle, GetCoordinate(), SDL_FLIP_NONE);
	}
	else if (animationTimer > 50)
	{
		SDL_RenderCopyEx(ren, tex2, &getSrc(), &getDest(), angle, GetCoordinate(), SDL_FLIP_NONE);
	}
	if (animationTimer > 75)
	{
		animationTimer = 0;
	}
}