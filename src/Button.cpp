#include "Button.h"

Button::Button(SDL_Renderer* ren)
{
	selected = false;
}

//sRect là diện tích lấy ảnh gồm chiều dài - ngang x chiều rộng - dọc.
//dRect là chiều dài và rộng của ảnh hiển thị.
Button::Button(int x, int y) : sRect{ x, y, 384, 168 }, dRect{ x, y, 185, 81 }
{
	selected = false;
}

void Button::setXY(int x, int y)
{
	dRect.x = x;
	dRect.y = y;
}

void Button::CheckSelected(Mouse* mouse)
{
	if (SDL_HasIntersection(&(mouse->tip), &dRect)) 
	{
		selected = true;
		//vị trí lấy ảnh đã được chọn
		sRect.x = 400;
	}
	else 
	{
		selected = false;
		sRect.x = 0;
	}
}

void Button::Render(SDL_Renderer* ren, SDL_Texture* menuButton)
{
	SDL_RenderCopy(ren, menuButton, &sRect, &dRect);
}