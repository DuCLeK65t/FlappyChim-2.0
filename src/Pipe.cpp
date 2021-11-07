#include "Pipe.h"
#include <ctime>
#include <iostream>

Pipe::Pipe()
{
	pipeWidth = 80;
	pipeHeight = 360;
	space = 190;
}

Pipe::Pipe(int xPipe)
{
	srand(time(NULL));
	xPos[xPipe] = (xPipe + 4) * 320;
	p1h[xPipe] = Pipe::pipeRandHeight();
	p2h[xPipe] = p1h[xPipe] + space;
	setDest(xPos[xPipe], p1h[xPipe] - pipeHeight, pipeWidth, pipeHeight);
}

int Pipe::pipeRandHeight()
{
	return rand() * rand() % (330 - 100 + 1) + 100;
}

void Pipe::PipeUpdate1(int i, bool birdDie)
{
	if (xPos[i] <= -pipeWidth)
	{
		p1h[i] = Pipe::pipeRandHeight();
		xPos[i] = 880;
	}
	else
	{
		if(!birdDie)
		xPos[i]--;
		//setSrc(0, 0, 125, 500);
		setDest(xPos[i], p1h[i] - pipeHeight, pipeWidth, pipeHeight);
	}
}

void Pipe::PipeUpdate2(int i)
{
	p2h[i] = p1h[i] + space;
	setSrc(0, 0, 125, 500);
	setDest(xPos[i], p2h[i], pipeWidth, pipeHeight);
}

int Pipe::getp1h(int i)
{
	return p1h[i];
}

int Pipe::getxPos(int i)
{
	return xPos[i];
}

void Pipe::SpaceScore(int i)
{
	setSrc(0, 0, NULL, NULL);
	//setSrc(0, 0, 78, 69);	//test spaceScore
	setDest(xPos[i] + 20, p1h[i], 3, space);
}

void Pipe::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}