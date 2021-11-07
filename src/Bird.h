#pragma once
#include "Object.h"

static int b_Width;
static int b_Height;

class Bird : public Object
{
private:
	SDL_Texture* tex1;
	SDL_Texture* tex2;

	int animationTimer;

	float angle;
	SDL_Point coordinate;
	
	double speed;
	double g; //Type of acceleration
	int Ypos; //Bird position
	bool inJump;
	double jumpHeight;
	double jumpTimer;
	double lastJump;

public:
	Bird();
	Bird(int b_Src_Width, int b_Src_Height);
	void Gravity(bool touchBase, bool playing);
	double GetTimeJump(double jumpTimer);
	bool JumpState();
	void Jump();
	void SetCoordinate(int x, int y);
	SDL_Point* GetCoordinate();
	void CreateTexture1(const char* address, SDL_Renderer* ren);
	void CreateTexture2(const char* address, SDL_Renderer* ren);
	void Render(SDL_Renderer* ren);
};