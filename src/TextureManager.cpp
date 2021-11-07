#include "TextureManager.h"

SDL_Texture* TextureManager::Texture(const char* filelocation, SDL_Renderer* ren)
{
	SDL_Surface* surface;
	surface = IMG_Load(filelocation);
	if (surface == NULL)
		cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << endl;
	SDL_Texture* tex;
	tex = SDL_CreateTextureFromSurface(ren, surface);

	return tex;
}