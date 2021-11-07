#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//#include <SDL_ttf.h>
#include <FreeImage.h>
#include "Bird.h"
#include "Background.h"
#include "Foreground.h"
#include "Base.h"
#include "Pipe.h"
#include "Coin.h"
#include "TextObject.h"

#include "Menu.h"
#include "Mouse.h"

using namespace std;

class Gameloop
{
private:
	const int SCREEN_WIDTH = 540;
	const int SCREEN_HEIGHT = 720;

	SDL_Window* window; 
	SDL_Surface* screenSurface;
	SDL_Surface* textSurface;
	SDL_Renderer* renderer;

	Background bg;
	Bird b;
	Pipe p1_[3], p2_[3];
	Pipe scoreSpace_[3];
	Coin c_[3];
	Base bs1, bs2;

	Mouse* m = new Mouse;
	enum ButtonNames { REPLAY, EXIT };
	Button* button[2];
	Menu* menu = new Menu;
	SDL_Texture* menuTex;
	SDL_Texture* buttonTex;

	Foreground coin;
	Foreground trophy;

	const char* img_bPath = "Img/bird0.png";
	FREE_IMAGE_FORMAT img_format = FreeImage_GetFileType(img_bPath, 0);
	FIBITMAP* img_b = FreeImage_Load(img_format, img_bPath);
	int b_Src_Width = FreeImage_GetWidth(img_b);
	int b_Src_Height = FreeImage_GetHeight(img_b);

	TTF_Font* scoreFont;
	TTF_Font* scoreOutline;
	TextObject s;
	TextObject s_outline;
	int textWidth;
	int textHeight;
	SDL_Color white = { 250, 250, 250 };
	SDL_Color brown = { 94, 54, 67 };
	bool checkTouch = false;
	bool checkScore = true;
	unsigned int score = 0;
	unsigned int SCORE = 0;
	Foreground scoreTable;
	int tableYpos;
	/*Animation*/
	double speed;
	double a;
	TTF_Font* hsOutline;
	TextObject hs;
	TextObject hs_outline;
	unsigned int highscore;
	int fontSize;

	bool birdDie = false;
	bool checkDie = true;
	bool playing = false;
	bool newGame = false;

	bool touchBase = false;

	bool touchCoin_[3];

	bool gameState;

	Mix_Music* backgroundsound;
	Mix_Chunk* clickSound;
	Mix_Chunk* wingSound;
	Mix_Chunk* pointSound;
	Mix_Music* hitSound;
	Mix_Music* dieSound;
	Mix_Music* swooshingSound;

public:
	Gameloop();
	~Gameloop();
	void Initialize();
	bool GetGameState();
	void NewGame();
	void Event();
	void Update();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void CollisionDetection();
	void Die();
	void Render();
	void Close();
	void set_color(int code);
};