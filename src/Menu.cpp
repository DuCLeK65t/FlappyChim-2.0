#include "Menu.h"

Menu::Menu()
{
	bg.setSrc(0, 0, 540, 720);
	bg.setDest(0, 0, 540, 720);
	h.setDest(70, 320, 400, 80);

	sound = true;

	// lấy tọa độ của nút cần tải lên
	button[PLAY] = new Button(0, 0);
	//button[OPTIONS] = new Button(0, 184);
	button[QUIT] = new Button(0, 920);
	button[HELP] = new Button(0, 1450);
	button[SOUND] = new Button(0, 1104);

	// lấy tọa độ của nút xuất hiện ở đâu trên cửa sổ
	button[PLAY]->setXY(179, 380);
	//button[OPTIONS]->setXY(179, 400);
	button[QUIT]->setXY(179, 480);
	button[HELP]->setXY(-125, 632);
	button[SOUND]->setXY(450, 650);
}

Menu::~Menu()
{
	delete button[PLAY];
	//delete button[OPTIONS];
	delete button[QUIT];
	delete button[HELP];
	delete button[SOUND];
}

bool Menu::Enter(SDL_Texture* menu, SDL_Texture* menuButton, Mouse* m, SDL_Renderer* ren)
{
	bg.CreateTexture("Img/menu2.png", ren);
	h.CreateTexture("Img/prompt.png", ren);

	Mix_Music* backgroundsound = Mix_LoadMUS("Audio/8_bit_rainy_city_lofi.mp3");
	Mix_Chunk* clickSound = Mix_LoadWAV("Audio/mouse_click.wav");

	Mix_VolumeMusic(8);
	Mix_PlayMusic(backgroundsound, -1);
	bool newGame;
	SDL_Event e;
	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_MOUSEBUTTONDOWN:
			{
				Mix_VolumeChunk(clickSound, 10);
				Mix_PlayChannel(1, clickSound, 0);
				break;
			}
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (button[PLAY]->selected)
					{
						return true;
					}
					//if (button[OPTIONS]->selected)
					//{
					//	/*Choose Bird*/
					//}
					if (button[QUIT]->selected)
					{
						SDL_DestroyRenderer(ren);
						ren = NULL;
						Mix_FreeMusic(backgroundsound);
						Mix_FreeChunk(clickSound);

						return false;
					}
					if (button[HELP]->selected)	//How to play
					{
						int i = 0;
						while (i <= 2500)
						{
							SDL_RenderClear(ren);
							bg.Render(ren);
							h.Render(ren);
							SDL_RenderPresent(ren);
							i++;
						}
						//SDL_RenderClear(ren);
					}
					if (button[SOUND]->selected)
					{
						if (sound)
						{
							button[SOUND] = new Button(0, 1288);
							button[SOUND]->setXY(450, 650);
							sound = false;
						}
						else
						{
							button[SOUND] = new Button(0, 1104);
							button[SOUND]->setXY(450, 650);
							sound = true;
						}
					}
				}
				break;
			}
		}
		SDL_GetMouseState(&(m->cursor.x), &(m->cursor.y));
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, menu, NULL, NULL);
		for (Button* b : button) 
		{
			b->CheckSelected(m);
			b->Render(ren, menuButton);
		}
		m->Render(ren);
		SDL_RenderPresent(ren);

		if (sound)
			Mix_VolumeMusic(10);
		else
			Mix_VolumeMusic(0);
	}
}

bool Menu::bgSound()
{
	return sound;
}