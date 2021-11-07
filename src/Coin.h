#pragma once
#include "Object.h"
#include "Pipe.h"

class Coin : public Pipe
{
private:
	int animationTimer;
	int timer;

	int coinWidth = 55;
	int coinHeight = 55;

	int xCoin;
	int yCoin;
	int xPosCoin[3];
	int yPosCoin[3];

	bool touchCoin;

public:
	bool eated_[3];

	Coin();
	void CoinUpdate(int i, bool checkTouch);
	void Render(SDL_Renderer* ren);
};