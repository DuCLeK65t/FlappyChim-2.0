#include "Coin.h"

Coin::Coin()
{
	animationTimer = 0;
	timer = 25;
	touchCoin = false;
	for (int i = 0; i < 3; i++)
	{
		eated_[i] = false;
	}
}

void Coin::CoinUpdate(int i, bool checkTouch)
{
	xCoin = (pipeWidth - coinWidth) / 2;
	yCoin = (space - coinHeight) / 2;
	xPosCoin[i] = getxPos(i) + xCoin;
	yPosCoin[i] = getp1h(i) + yCoin;

	touchCoin = checkTouch;
	if (touchCoin)
		eated_[i] = true;
	if (xPosCoin[i] <= coinWidth)
	{
		eated_[i] = false;
	}
	else
		if (!touchCoin && !eated_[i])
			setDest(xPosCoin[i], yPosCoin[i], coinWidth, coinHeight);
		else
			setDest(xPosCoin[i], yPosCoin[i], 0, 0);
}

void Coin::Render(SDL_Renderer* ren)
{
	animationTimer++;
	if (animationTimer < timer)
	{
		setSrc(0, 0, 80, 80);
	}
	else if (animationTimer >= timer && animationTimer <= timer * 2)
	{
		setSrc(0, 80, 80, 80);
	}
	else if (animationTimer >= timer * 2 && animationTimer <= timer * 3)
	{
		setSrc(0, 160, 80, 80);
	}
	else if (animationTimer >= timer * 3 && animationTimer <= timer * 4)
	{
		setSrc(0, 240, 80, 80);
	}
	else if (animationTimer >= timer * 4 && animationTimer <= timer * 5)
	{
		setSrc(0, 320, 80, 80);
	}
	else if (animationTimer >= timer * 5 && animationTimer <= timer * 6)
	{
		setSrc(0, 400, 80, 80);
	}
	else if (animationTimer >= timer * 6 && animationTimer <= timer * 7)
	{
		setSrc(0, 480, 80, 80);
	}
	else if (animationTimer >= timer * 7 && animationTimer <= timer * 8)
	{
		setSrc(0, 560, 80, 80);
	}
	else if (animationTimer >= timer * 8 && animationTimer <= timer * 9)
	{
		setSrc(0, 640, 80, 80);
	}
	else if (animationTimer >= timer * 9 && animationTimer <= timer * 10)
	{
		setSrc(0, 720, 80, 80);
	}
	if (animationTimer > timer * 11)
	{
		animationTimer = 0;
	}

	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}