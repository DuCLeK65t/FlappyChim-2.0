#include "Gameloop.h"

Gameloop* g = new Gameloop();

int main(int argc, char* argv[])
{
	const int FPS = 290;
	const int DELAY_TIME = 1000 / FPS;

	Uint64 frameStart;
	Uint64 frameTime;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_ShowCursor(SDL_DISABLE);

	g->Initialize();
	while (g->GetGameState())
	{
		frameStart = SDL_GetTicks();
	
		//Main event
		g->Event();
		g->Die();
		g->Render();
	
		//Stable fps
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}
	g->Close();

	return 0;
}