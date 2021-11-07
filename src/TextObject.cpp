#include "TextObject.h"
#include <cstring>

TextObject::TextObject()
{
	textSurface = NULL;
	//color2 = { 30, 11, 02 };	//Birthday whose code this part:))
	//color = { 255, 255, 255 };
}

TextObject::~TextObject()
{
	TTF_CloseFont(font);
	font = NULL;
}

SDL_Texture* TextObject::getTextTexture()
{
	return texture;
}

void TextObject::WriteText(string text, TTF_Font* textFont, SDL_Color color, SDL_Renderer* ren)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		font = NULL;
	}
	
	font = textFont;
	if (font == NULL)
	{
		cout << "Unable to open font! Error: " << TTF_GetError() << endl;
	}
	else
	{
		textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (textSurface == NULL)
		{
			cout << "Unable to load text! Error: " << TTF_GetError() << endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(ren, textSurface);
			if (texture == NULL)
			{
				cout << "Unable to create texture from rendered text! SDL_ttf Error: " << TTF_GetError() << endl;
			}
			else
			{
				TTF_SizeText(font, text.c_str(), &(getSrc().w), &(getSrc().h));
			}
			SDL_FreeSurface(textSurface);
		}
	}
}

void TextObject::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTextTexture(), &getSrc(), &getDest());
}