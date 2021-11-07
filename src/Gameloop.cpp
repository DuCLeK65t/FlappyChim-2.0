#include "Gameloop.h"

Gameloop::Gameloop()
{
	window = NULL;
	screenSurface = NULL;
	renderer = NULL;

	bg.setSrc(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	bg.setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	bs1.setSrc(0, 0, 720, 120);
	bs2.setSrc(0, 0, 720, 120);

	b.setSrc(0, 0, b_Src_Width, b_Src_Height);
	Bird::Bird(b_Src_Width, b_Src_Height);

	s.setSrc(0, 0, NULL, NULL);
	s_outline.setSrc(0, 0, NULL, NULL);
	hs.setSrc(0, 0, NULL, NULL);
	hs_outline.setSrc(0, 0, NULL, NULL);
	fontSize = 32;
	scoreTable.setSrc(0, 0, 444, 282);
	
	coin.setSrc(0, 160, 80, 80);
	trophy.setSrc(0, 0, 102, 102);

	button[REPLAY] = new Button(0, 736);
	button[EXIT] = new Button(0, 368);

	button[REPLAY]->setXY(80, 470);
	button[EXIT]->setXY(275, 470);
}

Gameloop::~Gameloop()
{
	delete button[REPLAY];
	delete button[EXIT];
}

void Gameloop::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		Close();
	}
	else
	{
		window = SDL_CreateWindow("FlappyBird 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 540, 720, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created!" << endl << "Error: " << SDL_GetError() << endl;
			gameState = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer)
			{
				SDL_ShowCursor(SDL_DISABLE);
				cout << endl;
				set_color(4);
				SetConsoleOutputCP(1252);
				cout << "Team 404 Not Found!" << endl;
				cout << "Copyright ©2021 https://github.com/20021515/FlappyChim-2.0 All rights reserved.\r\n" << endl;
				set_color(10);
				cout << "   __________ ___                                 " << endl;
				cout << "   ___  ____/_  /______ _______ _______ ___  __   " << endl;
				cout << "   __  /___ _  /_  __ `/__  __ \\ _  __ \\ _ \\/ /" << endl;
				cout << "   _  ____/ / / / /_/ / _  /_/ /_  /_/ / __  /    " << endl;
				cout << "   / /     /_/  \\__,_/  / ____/ / ____/   / /    " << endl;
				cout << "  /_/                  /_/     /_/       /_/      " << endl;
				set_color(9);
				cout << "   _______ ____            __ " << endl;
				cout << "   __  __ \\__(_)_ ___ ___ / /" << endl;
				cout << "   _  /_/_/_  /_ `__/  __` /  " << endl;
				cout << "   / /_/ / / / / / _  /_/ /   " << endl;
				cout << "  /_,___/ /_/ /_/   \\__,_/ \n" << endl;
				set_color(15);
				cout << "===============================================" << endl;
				//cout << "Options is to choose character and we will update in next version" << endl;

				gameState = true;
				bg.CreateTexture("Img/bgDay.png", renderer);
				b.CreateTexture(img_bPath, renderer);
				b.CreateTexture1("Img/bird1.png", renderer);
				b.CreateTexture2("Img/bird2.png", renderer);
				bs1.CreateTexture("Img/baseLong.png", renderer);
				bs2.CreateTexture("Img/baseLong.png", renderer);
				for (int i = 0; i < 3; i++)
				{
					p1_[i].CreateTexture("Img/pipeTop.png", renderer);
					p2_[i].CreateTexture("Img/pipeBottom.png", renderer);
					c_[i].CreateTexture("Img/coin.png", renderer);
				}
				scoreSpace_[0].CreateTexture("Img/angry0.png", renderer);
				coin.CreateTexture("Img/coin.png", renderer);
				scoreTable.CreateTexture("Img/score.png", renderer);
				trophy.CreateTexture("Img/trophy.png", renderer);

				m->CreateTexture("Img/mouse0.png", renderer);
				menuTex = IMG_LoadTexture(renderer, "Img/menu.png");
				buttonTex = IMG_LoadTexture(renderer, "Img/ui.png");
			}
		}
	}
	if (Mix_Init(1) == 0)
	{
		cout << "Sound could not initialize! Mix_Error: " << Mix_GetError() << endl;
		Close();
	}
	else
	{
		backgroundsound = Mix_LoadMUS("Audio/ingame.mp3");
		clickSound = Mix_LoadWAV("Audio/mouse_click.wav");
		wingSound = Mix_LoadWAV("Audio/sfx_wing.wav");
		pointSound = Mix_LoadWAV("Audio/sfx_point.wav");
		hitSound = Mix_LoadMUS("Audio/sfx_hit.wav");
		dieSound = Mix_LoadMUS("Audio/sfx_die.wav");
		swooshingSound = Mix_LoadMUS("Audio/sfx_swooshing.wav");
	}
	if (TTF_Init() < 0)
	{
		cout << "Text could not initialize! Text_Error: " << TTF_GetError() << endl;
		Close();
	}
	else
	{
		scoreFont = TTF_OpenFont("TextFont/flappy-bird-font.ttf", fontSize);
		scoreOutline = TTF_OpenFont("TextFont/flappy-bird-font.ttf", fontSize);
		TTF_SetFontOutline(scoreOutline, 10);
		hsOutline = TTF_OpenFont("TextFont/flappy-bird-font.ttf", fontSize);
		TTF_SetFontOutline(hsOutline, 10);
	}
	ifstream file("HighScore.txt");
	if (!file.is_open())
	{
		cout << "Unable to open highscore file!";
		Close();
	}
	else
	{
		file.close();
	}
	/*Start*/
	if (!(menu->Enter(menuTex, buttonTex, m, renderer)))
	{
		gameState = false;
	}
	else
	{
		NewGame();
	}
}

bool Gameloop::GetGameState()
{
	return gameState;
}

void Gameloop::NewGame()
{
	if(menu->bgSound())
		Mix_VolumeMusic(8);
	else
		Mix_VolumeMusic(0);

	Mix_PlayMusic(backgroundsound, -1);
	if (checkDie)
	{
		b.Gravity(touchBase, false);
		int xPipe[3] = { 0, 1, 2 };
		for (int i = 0; i < 3; i++)
		{
			p1_[i].setSrc(0, 0, 125, 500);
			p2_[i].setSrc(0, 0, 125, 500);
			Pipe::Pipe(xPipe[i]);
			touchCoin_[i] = false;
			c_[i].eated_[i] = false;
		}
		touchBase = true;
		score = 0;
		SCORE = 0;
		
		playing = false;
		birdDie = false;
		checkDie = false;

		textWidth = 35;
		textHeight = 50;
		coin.setDest(12, 18, 55, 42);
		scoreTable.setDest(0, 0, NULL, NULL);
		trophy.setDest(0, 0, NULL, NULL);
		tableYpos = 600;
		speed = 0;
		a = 0.3;
		s.setDest(73, 13, textWidth, textHeight);
		s_outline.setDest(73, 13, textWidth - 3, textHeight);
	}
}

void Gameloop::Event()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
		if (birdDie)
		{
	case SDL_MOUSEBUTTONDOWN:
	{
		Mix_VolumeChunk(clickSound, 10);
		Mix_PlayChannel(1, clickSound, 0);
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			if (button[REPLAY]->selected)
			{
				NewGame();
				//checkDie = true;
			}
			if (button[EXIT]->selected)
			{
				//checkDie = true;
				if (!(menu->Enter(menuTex, buttonTex, m, renderer)))
					gameState = false;
				else
					NewGame();
			}
		}
		break;
	}
		}
		else
		{
	case SDL_KEYDOWN:
	{
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			if (!b.JumpState() && !birdDie)
			{
				b.Jump();
				//Mix_Chunk* wingSound = Mix_LoadWAV("Audio/sfx_wing.wav");
				Mix_VolumeChunk(wingSound, 20);
				Mix_PlayChannel(1, wingSound, 0);
			}
			if (!checkDie)
			{
				playing = true;
				birdDie = false;
				touchBase = false;
			}
		}
		break;
	}
	case SDL_QUIT:
	{
		gameState = false;
		break;
	}
		}
	default:
	{
		Update();
		CollisionDetection();
		if (checkTouch && checkScore)
		{
			score += 1;
			SCORE = score / 2;
			if (score % 2 == 0)
			{
				Mix_VolumeChunk(pointSound, 15);
				Mix_PlayChannel(2, pointSound, 0);
				if (SCORE >= 10)
				{
					s.setDest(70, 13, textWidth * 2, textHeight);
					s_outline.setDest(70, 13, textWidth * 2 - 6, textHeight);
				}
				if (SCORE >= 100)
				{
					s.setDest(70, 13, textWidth * 3, textHeight);
					s_outline.setDest(70, 13, textWidth * 3 - 4, textHeight);
				}
			}
			checkScore = false;
		}
		break;
	}
	}
}

bool Gameloop::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}
	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}
	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}
	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 > size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}
	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}
	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}
	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

void Gameloop::CollisionDetection()
{
	/*Up pipe*/
	if (CheckCollision((&b)->getDest(), (&p1_[0])->getDest()) ||
		CheckCollision((&b)->getDest(), (&p1_[1])->getDest()) ||
		CheckCollision((&b)->getDest(), (&p1_[2])->getDest()))
	{
		birdDie = true;
	}
	/*Down pipe*/
	if (CheckCollision((&b)->getDest(), (&p2_[0])->getDest()) ||
		CheckCollision((&b)->getDest(), (&p2_[1])->getDest()) ||
		CheckCollision((&b)->getDest(), (&p2_[2])->getDest()))
	{
		birdDie = true;
	}
	/*Base*/
	if (CheckCollision((&b)->getDest(), (&bs1)->getDest()) ||
		CheckCollision((&b)->getDest(), (&bs2)->getDest()))
	{
		birdDie = true;
		touchBase = true;
	}
	/*Score*/
	if (CheckCollision((&b)->getDest(), (&scoreSpace_[0])->getDest()) ||
		CheckCollision((&b)->getDest(), (&scoreSpace_[1])->getDest()) ||
		CheckCollision((&b)->getDest(), (&scoreSpace_[2])->getDest()))
	{
		checkTouch = true;
		if (CheckCollision((&b)->getDest(), (&scoreSpace_[0])->getDest()))
			touchCoin_[0] = true;
		else if (CheckCollision((&b)->getDest(), (&scoreSpace_[1])->getDest()))
			touchCoin_[1] = true;
		else if (CheckCollision((&b)->getDest(), (&scoreSpace_[2])->getDest()))
			touchCoin_[2] = true;
	}
	else
	{
		checkTouch = false;
		checkScore = true;
		for (int i = 0; i < 3; i++)
		{
			touchCoin_[i] = false;
		}
	}
}

void Gameloop::Update()
{
	b.Gravity(touchBase, playing);
	bs1.BaseUpdate1(birdDie);
	bs2.BaseUpdate2(birdDie);
	p1_[0].PipeUpdate1(0, birdDie);
	p1_[1].PipeUpdate1(1, birdDie);
	p1_[2].PipeUpdate1(2, birdDie);
	p2_[0].PipeUpdate2(0);
	p2_[1].PipeUpdate2(1);
	p2_[2].PipeUpdate2(2);
	scoreSpace_[0].SpaceScore(0);
	scoreSpace_[1].SpaceScore(1);
	scoreSpace_[2].SpaceScore(2);
	c_[0].CoinUpdate(0, touchCoin_[0]);
	c_[1].CoinUpdate(1, touchCoin_[1]);
	c_[2].CoinUpdate(2, touchCoin_[2]);

	s.WriteText(to_string(SCORE), scoreFont, brown, renderer);
	s_outline.WriteText(to_string(SCORE), scoreOutline, white, renderer);
	SDL_GetMouseState(&(m->cursor.x), &(m->cursor.y));
}

void Gameloop::Die()
{
	if (birdDie && !checkDie)
	{
		coin.setDest(0, 0, NULL, NULL);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Mix_VolumeMusic(20);
		Mix_PlayMusic(hitSound, 0);
		SDL_Delay(500);
		//Mix_Music* dieSound = Mix_LoadMUS("Audio/ainsley_harriott_and_his_spicy_meatconverttoaudio.mp3");
		Mix_PlayMusic(dieSound, 0);
		SDL_Delay(500);

		while (tableYpos > (SCREEN_HEIGHT - 282) / 3)
		{
			s.setDest(0, 0, NULL, NULL);
			s_outline.setDest(0, 0, NULL, NULL);

			Mix_VolumeMusic(25);
			Mix_PlayMusic(swooshingSound, 0);
			tableYpos -= speed / 5;
			speed += a / 4;
			scoreTable.setDest((SCREEN_WIDTH - 444) / 2, tableYpos, 438, 290);

			Render();
		}

		ifstream read("HighScore.txt");
		read >> highscore;
		read.close();
		if (SCORE > highscore)
		{
			highscore = SCORE;

			//102 119
			float i = 0, j = 0;
			while (j <= 100)
			{
				i += 3.0 / 7;
				j += 0.5;
				trophy.setDest(330, 335, (int)i, (int)j);

				Render();
			}

			ofstream file("HighScore.txt");
			file << SCORE;
			file.close();
		}
		textWidth = 47;
		textHeight = 67;
		if (SCORE >= 100)
		{
			s.setDest(120, 255, textWidth * 3, textHeight);
			s_outline.setDest(120, 255, textWidth * 3 - 5, textHeight);
		}
		else if (SCORE >= 10)
		{
			s.setDest(145, 255, textWidth * 2, textHeight);
			s_outline.setDest(145, 255, textWidth * 2 - 5, textHeight);
		}
		else
		{
			s.setDest(170, 255, textWidth, textHeight);
			s_outline.setDest(170, 255, textWidth - 5, textHeight);
		}

		textWidth /= 1.55;
		textHeight /= 1.55;
		if (highscore >= 100)
		{
			hs.setDest(323, 235, textWidth * 3, textHeight);
			hs_outline.setDest(323, 235, textWidth * 3 - 5, textHeight);
		}
		else if (highscore >= 10)
		{
			hs.setDest(340, 235, textWidth * 2, textHeight);
			hs_outline.setDest(340, 235, textWidth * 2 - 3, textHeight);
		}
		else
		{
			hs.setDest(353, 235, textWidth, textHeight);
			hs_outline.setDest(353, 235, textWidth - 3, textHeight);
		}
		hs.WriteText(to_string(highscore), scoreFont, brown, renderer);
		hs_outline.WriteText(to_string(highscore), hsOutline, white, renderer);

		checkDie = true;
	}
}

void Gameloop::Render()
{
	SDL_RenderClear(renderer);
	bg.Render(renderer);
	p1_[0].Render(renderer);
	p1_[1].Render(renderer);
	p1_[2].Render(renderer);
	p2_[0].Render(renderer);
	p2_[1].Render(renderer);
	p2_[2].Render(renderer);
	c_[0].Render(renderer);
	c_[1].Render(renderer);
	c_[2].Render(renderer);
	b.Render(renderer);
	bs1.Render(renderer);
	bs2.Render(renderer);

	//scoreSpace_[0].Render(renderer);	//test spaceScore
	
	if (birdDie)
	{
		for (Button* b : button)
		{
			b->CheckSelected(m);
			b->Render(renderer, buttonTex);
		}
		scoreTable.Render(renderer, 0);
		s_outline.Render(renderer);
		s.Render(renderer);
		hs_outline.Render(renderer);
		hs.Render(renderer);
		trophy.Render(renderer, 10);

		m->Render(renderer);
	}
	else
	{
		coin.Render(renderer, 0);
		s_outline.Render(renderer);
		s.Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Gameloop::Close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Gameloop::set_color(int code)
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, code);
}