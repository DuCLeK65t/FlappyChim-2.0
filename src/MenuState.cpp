#include "MenuState.h"

using namespace std;

SDL_Window* win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 540, 720, SDL_WINDOW_SHOWN);
SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
State* menu = new Menu;
State* options = new Options;
State* current = menu;

State::State()
{
	static Mouse* m = new Mouse;
	mouse = m;

	//menuState = true;
}

State::~State()
{

}

Menu::Menu()
{
	background = IMG_LoadTexture(ren, "Img/menu.png");

	// lấy tạo độ của nút cần tải lên
	button[PLAY] = new Button(0, 0);
	button[OPTIONS] = new Button(0, 184);
	button[EXIT] = new Button(0, 368);
	button[SOUND] = new Button(0, 920);

	// lấy tọa độ của nút xuất hiện ở đâu trên cửa sổ
	button[PLAY]->setXY(179, 300);
	button[OPTIONS]->setXY(179, 400);
	button[EXIT]->setXY(179, 500);
	button[SOUND]->setXY(15, 640);
	//menuState = true;
}

Menu::~Menu() {
	SDL_DestroyTexture(background);
	delete button[PLAY];
	delete button[EXIT];
	delete button[OPTIONS];
	delete button[SOUND];
}
void Menu::enter() {
	cout << "Vao trang thai Menu\n";
}
void Menu::update() {
	bool running = true;
	SDL_Event e;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				running = false;
				SDL_Quit();
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (button[PLAY]->selected)
					{
						//menuState = false;
						//ren = NULL;
						//SDL_RenderClear(ren);
						//SDL_RenderPresent(ren);
						break;
					}
					if (button[OPTIONS]->selected)
					{
						running = false;
						current = options;
						break;
					}
					if (button[EXIT]->selected)
					{
						running = false;
						SDL_Quit();
						break;
					}
					if (button[SOUND]->selected)
					{
						running = false;
						cout << "sound off" << endl;
						Mix_PauseMusic();
						current = options;
						break;
					}
				}
			}
			}
		}
		SDL_GetMouseState(&(mouse->cursor.x), &(mouse->cursor.y));

		SDL_RenderCopy(ren, background, NULL, NULL);
		for (Button* n : button) {
			n->checkSelected(mouse);
			n->draw();
		}
		mouse->draw();
		SDL_RenderPresent(ren);
		SDL_RenderClear(ren);
	}
}

//bool Menu::GetMenuState()
//{
//	return menuState;
//}

Options::Options() {
	background = IMG_LoadTexture(ren, "bg.png"); //bg.png
	//vị trí lấy ảnh từ gốc tọa độ.
	button[PLAY] = new Button(0, 0);
	button[BACK] = new Button(0, 552);
	button[SOUND] = new Button(0, 1104);

	// vị trí hiện ảnh từ gốc tọa độ.
	button[PLAY]->setXY(179, 300);
	button[BACK]->setXY(179, 400);
	button[SOUND]->setXY(15, 640);
}
Options::~Options() {
	SDL_DestroyTexture(background);
	delete button[PLAY];
	delete button[BACK];
	delete button[SOUND];
}
void Options::enter() {
	cout << "Vao trang thai Options\n";
}
void Options::update()
{
	bool running = true;
	SDL_Event e;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				running = false;
				SDL_Quit();
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (button[BACK]->selected)
					{
						current = menu;
						running = false;
						break;
					}
					if (button[SOUND]->selected)
					{
						running = false;
						cout << "sound on" << endl;
						Mix_ResumeMusic();
						//current = menu;
						break;
					}
				}
			}
			}
			SDL_GetMouseState(&(mouse->cursor.x), &(mouse->cursor.y));
			SDL_RenderCopy(ren, background, NULL, NULL);
			for (Button* n : button) {
				n->checkSelected(mouse);
				n->draw();
			}
			mouse->draw();
			SDL_RenderPresent(ren);
			SDL_RenderClear(ren);
		}
	}
}

//SDL_Window* win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 540, 720, SDL_WINDOW_SHOWN);
//SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
//State* menu = new Menu;
//State* options = new Options;
//State* current = menu;