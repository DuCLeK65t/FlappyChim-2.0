#pragma once
#include "Object.h"
#include <ctime>

static int p1h[3];		//Height of the up pipe
static int xPos[3];		//Distance of pipes

class Pipe : public Object
{
private:
public:
	int pipeWidth;
	int pipeHeight;
	int space;

	int p2h[3];
	Pipe();
	Pipe(int xPipe);
	int pipeRandHeight();
	void PipeUpdate1(int i, bool birdDie);
	void PipeUpdate2(int i);
	int getp1h(int i);
	int getxPos(int i);
	void SpaceScore(int i);
	void Render(SDL_Renderer* ren);
};