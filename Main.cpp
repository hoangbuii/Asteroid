#include "Entity.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "CommonFunc.h"



bool Init()
{
	bool success = true;
	int img_flags = IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Failed to initiate SDL: " << SDL_GetError() << endl;
		success = false;
	}
	if (TTF_Init() < 0)
	{
		cout << "Failed to load SDL_ttf: " << TTF_GetError() << endl;
		success = false;
	}
	if (!(IMG_Init(img_flags) & img_flags))
	{
		cout << "Failed to load SDL_image: " << IMG_GetError() << endl;
		success = false;
	}
	G_Window = SDL_CreateWindow("Astro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (G_Window == NULL)
	{
		cout << "Failed to create window: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		G_Renderer = SDL_CreateRenderer(G_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (G_Renderer == NULL)
		{
			cout << "Failed to create window: " << SDL_GetError() << endl;
			success = false;
		}
	}
	return success;
}

void close()
{
	SDL_DestroyRenderer(G_Renderer);
	G_Renderer = NULL;

	SDL_DestroyWindow(G_Window);
	G_Window = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}


bool Load_Asteroids(vector<Asteroid*>& Asteroid1, const char* file_path, int HP)
{
	bool success = true;
	for (int i = 0; i < 1; i++)
	{
		Asteroid* Asteroid_i = new Asteroid;
		if (!Asteroid_i->Load_Image(file_path, G_Renderer))
		{
			cout << "Image Error: " << endl;
			success = false;
		}
		Asteroid1.push_back(Asteroid_i);
	}

	for (int i = 0; i < Asteroid1.size(); i++)
	{
		Asteroid1[i]->set_X(rand() % 100);
		Asteroid1[i]->set_Y(rand() % 50);
		Asteroid1[i]->set_speed_x(rand() % 4 - 1);
		Asteroid1[i]->set_speed_y(rand() % 4 - 1);
		Asteroid1[i]->set_HP(HP);
	}
	return success;
}

bool Load_Assets()
{
	bool success = true;
	font_32 = TTF_OpenFont("Assets/Retro.ttf", 32);
	font_32_outline = TTF_OpenFont("Assets/Retro.ttf", 32);
	font_24 = TTF_OpenFont("Assets/Retro.ttf", 24);

	fstream high_score_file;
	high_score_file.open("Assets/High_score.txt", ios::in);
	if (!high_score_file.is_open())
	{
		cout << "Can't open high score file!" << endl;
		success = false;
	}
	else
	{
		int line;
		while (!high_score_file.eof())
		{
			high_score_file >> line;
			player_high_score.push_back(line);
		}
	}
	high_score_file.close();

	for (int i = 0; i < player_high_score.size(); i++)
	{
		cout << player_high_score[i] << endl;
	}

	if (!Background_logo.Load_Image("Assets/Background_logo.png", G_Renderer))
	{
		cout << "Background Logo error!" << endl;
		success = false;
	}

	if (!Background_menu.Load_Image("Assets/Background_menu.png", G_Renderer))
	{
		cout << "Background menu error!" << endl;
		success = false;
	}
	if (!Credit.Load_Image("Assets/Credit.png", G_Renderer))
	{
		cout << "Credit background error!" << endl;
		success = false;
	}

	if (!Instructions.Load_Image("Assets/Instructions.png", G_Renderer))
	{
		cout << "Instruction background error!" << endl;
		success = false;
	}


	if (!Arrow_Selected.Load_Image("Assets/Arrow.png", G_Renderer))
	{
		cout << "Arrow selected error!" << endl;
		success = false;
	}

	if (!G_Background.Load_Image("Assets/Background_main.png", G_Renderer))
	{
		cout << "Background Error!" << endl;
		success = false;
	}

	if (!Tung_Beo.Load_Image("Assets/Spaceship.png", G_Renderer))
	{
		cout << "Image Error: " << endl;
		success = false;
	}
	if (!Load_Asteroids(Big_Asteroids, "Assets/Big_Asteroid.png", BIG_ASTEROID_HP))
	{
		success = false;
	}
	if (!Load_Asteroids(Medium_Asteroids, "Assets/Medium_Asteroid.png", MEDIUM_ASTEROID_HP))
	{
		success = false;
	}
	if (!Load_Asteroids(Small_Asteroids, "Assets/Small_Asteroid.png", SMALL_ASTEROID_HP))
	{
		success = false;
	}
	Arrow_Selected.set_X(400);

	Tung_Beo.set_velocity(PLAYER_VELOCITY);
	Tung_Beo.set_Bullet_dmg(PLAYER_BULLET_DAMAGE);
	Tung_Beo.set_HP(PLAYER_HP);
	return success;
}

void Remove_Asteroid(vector<Asteroid*>& Asteroid1, int& j)
{
	if (j <= Asteroid1.size())
	{
		Asteroid* current_Asteroid = Asteroid1.at(j);
		Asteroid1.erase(Asteroid1.begin() + j);
		if (current_Asteroid != NULL)
		{
			delete current_Asteroid;
			current_Asteroid = NULL;
		}
	}

}

void Render_Asteroid(vector<Asteroid*>& Asteroid1)
{
	for (int i = 0; i < Asteroid1.size(); i++)
	{
		Asteroid1[i]->Render(G_Renderer);
	}
}

void Reset_Game()
{
	int i = 0;
	while (Big_Asteroids.size() > 0)
	{
		Remove_Asteroid(Big_Asteroids, i);
	}

	while (Medium_Asteroids.size() > 0)
	{
		Remove_Asteroid(Medium_Asteroids, i);
	}
	while (Small_Asteroids.size() > 0)
	{
		Remove_Asteroid(Small_Asteroids, i);
	}

	while (Tung_Beo.get_Bullets().size() > 0)
	{
		Tung_Beo.remove_Bullets(i);
	}

	Load_Asteroids(Big_Asteroids, "Assets/Big_Asteroid.png", BIG_ASTEROID_HP);
	Load_Asteroids(Medium_Asteroids, "Assets/Medium_Asteroid.png", MEDIUM_ASTEROID_HP);
	Load_Asteroids(Small_Asteroids, "Assets/Small_Asteroid.png", SMALL_ASTEROID_HP);

	Tung_Beo.Reset();
	Tung_Beo.set_velocity(PLAYER_VELOCITY);
	Tung_Beo.set_Bullet_dmg(PLAYER_BULLET_DAMAGE);
	Tung_Beo.set_HP(PLAYER_HP);
}


int main(int argc, char* argv[])
{
	srand(time(NULL));
	if (!Init())
	{
		cout << "FATAL ERROR!!" << endl;
		close();
		return 1;
	}

	if (!Load_Assets())
	{
		cout << "Can't load game asset!" << endl;
		close();
		return 1;
	}

	int open_game_time = SDL_GetTicks();
	int current_opengame_time = SDL_GetTicks();

	while (intro)
	{
		current_opengame_time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				intro = false;
				game_Running = false;
			}
		}
		if (current_opengame_time - open_game_time > 2500)
		{
			intro = false;
			game_Running = true;
			main_menu = true;
		}

		SDL_RenderClear(G_Renderer);
		Background_logo.Render(G_Renderer);
		SDL_RenderPresent(G_Renderer);
	}





	while (game_Running)
	{
		//load menu renderer
		while (main_menu)
		{
			SDL_RenderClear(G_Renderer);
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					main_menu = false;
					start_game = false;
					game_Running = false;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						if (!menu_selected)menu--;
						break;
					case SDLK_DOWN:
						if (!menu_selected)menu++;
						break;
					case SDLK_s:
						menu_selected = true;
						break;
					case SDLK_y:
						menu_selected = false;
					default:
						break;
					}
				}
			}
			if (menu > EXIT)menu = PLAY;
			if (menu < PLAY)menu = EXIT;
			if (menu_selected == false)
			{
				Background_menu.Render(G_Renderer);
				Arrow_Selected.set_Y(240 + menu * 100);
				Arrow_Selected.Render(G_Renderer);
			}
			else
			{
				switch (menu)
				{
				case PLAY:
					main_menu = false;
					start_game = true;
					menu_selected = false;
					break;
				case INSTRUCTION:
					Instructions.Render(G_Renderer);
					break;
				case HIGH_SCORE:
					for (int i = 0; i < 5 /*player_high_score.size()*/; i++)
					{
						string top_score = to_string(player_high_score[i]);
						string show_top_score = "PLAYER " + to_string(i + 1) + ":       " + top_score;
						Render_Message(G_Renderer, 515, 200 + i * 50, show_top_score.c_str(), font_24, White);
					}
					break;
				case EXIT:
					main_menu = false;
					start_game = false;
					game_Running = false;
					break;
				default:
					break;
				}

			}
			SDL_RenderPresent(G_Renderer);
		}


		//load start game renderer
		while (start_game)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					start_game = false;
					game_Running = false;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						Playing = true;
						start_game = false;
					}
				}
			}
			SDL_RenderClear(G_Renderer);
			Render_Center(G_Renderer, 0, sin(SDL_GetTicks() / 100) * 2 - 4, "CLICK TO START", font_24, White);
			SDL_RenderPresent(G_Renderer);
		}

		int start_game_time = SDL_GetTicks();

		int time_new_asteroid = SDL_GetTicks();

		int current_time = SDL_GetTicks();

		int player_score = 0;


		//load playing renderer
		while (Playing)
		{
			SDL_RenderClear(G_Renderer);
			G_Background.Render(G_Renderer);
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					Playing = false;
					game_Running = false;
				}
				Tung_Beo.Handle_Event(event);
			}

			Tung_Beo.Move(G_Renderer);

			//Collision between bullets and asteroids
			for (int i = 0; i < Tung_Beo.get_Bullets().size(); i++)
			{
				bool bullet_removed = false;
				for (int big = 0; big < Big_Asteroids.size(); big++) //Collison between Bullets and Big Asteroids
				{
					if (Check_Collision(Tung_Beo.get_Bullets()[i]->Get_Rect(), Big_Asteroids[big]->Get_Rect()))
					{
						Tung_Beo.remove_Bullets(i);
						bullet_removed = true;
						Big_Asteroids[big]->Attacked(Tung_Beo.get_Bullet_dmg());
						if (Big_Asteroids[big]->get_current_HP() <= 0)
						{
							player_score += BIG_ASTEROID_SCORE;
							for (int spawn = 0; spawn < 2; spawn++)
							{
								Asteroid* current_Asteroid = new Asteroid;
								if (!current_Asteroid->Load_Image("Assets/Medium_Asteroid.png", G_Renderer))
								{
									cout << "Image Error: " << endl;
									Playing = false;
									break;
								}
								else
								{
									current_Asteroid->set_X(Big_Asteroids[big]->get_X() + rand() % 300 - 150);
									current_Asteroid->set_Y(Big_Asteroids[big]->get_Y() + rand() % 300 - 150);
									current_Asteroid->set_speed_x(rand() % 4 - 1);
									current_Asteroid->set_speed_y(rand() % 4 - 1);
									current_Asteroid->set_HP(MEDIUM_ASTEROID_HP);
								}
								Medium_Asteroids.push_back(current_Asteroid);
							}
							Remove_Asteroid(Big_Asteroids, big);
						}
						break;
					}
				}

				//check if bullet is removed
				if (bullet_removed)
				{
					continue;
				}

				for (int med = 0; med < Medium_Asteroids.size(); med++) //Collison between Bullets and Medium Asteroids
				{
					if (Check_Collision(Tung_Beo.get_Bullets()[i]->Get_Rect(), Medium_Asteroids[med]->Get_Rect()))
					{
						Tung_Beo.remove_Bullets(i);
						bullet_removed = true;
						Medium_Asteroids[med]->Attacked(Tung_Beo.get_Bullet_dmg());
						if (Medium_Asteroids[med]->get_current_HP() <= 0)
						{
							player_score += MEDIUM_ASTEROID_SCORE;
							for (int spawn = 0; spawn < 2; spawn++)
							{
								Asteroid* current_Asteroid = new Asteroid;
								if (!current_Asteroid->Load_Image("Assets/Small_Asteroid.png", G_Renderer))
								{
									cout << "Image Error: " << endl;
									Playing = false;
								}
								else
								{
									current_Asteroid->set_X(Medium_Asteroids[med]->get_X() + rand() % 300 - 150);
									current_Asteroid->set_Y(Medium_Asteroids[med]->get_Y() + rand() % 300 - 150);
									current_Asteroid->set_speed_x(rand() % 4 - 1);
									current_Asteroid->set_speed_y(rand() % 4 - 1);
									current_Asteroid->set_HP(SMALL_ASTEROID_HP);
								}
								Small_Asteroids.push_back(current_Asteroid);
							}
							Remove_Asteroid(Medium_Asteroids, med);
						}
						break;
					}
				}
				if (bullet_removed)
				{
					continue;
				}
				for (int small = 0; small < Small_Asteroids.size(); small++) //Collison between Bullets and Small Asteroids
				{
					if (Check_Collision(Tung_Beo.get_Bullets()[i]->Get_Rect(), Small_Asteroids[small]->Get_Rect()))
					{
						Tung_Beo.remove_Bullets(i);
						bullet_removed = true;
						Small_Asteroids[small]->Attacked(Tung_Beo.get_Bullet_dmg());
						if (Small_Asteroids[small]->get_current_HP() <= 0)
						{
							player_score += SMALL_ASTEROID_SCORE;
							Remove_Asteroid(Small_Asteroids, small);
						}
						break;
					}
				}
			}

			//Collison between Bullets and Player's Sprite
			for (int i = 0; i < Tung_Beo.get_Bullets().size(); i++)
			{
				if (Check_Collision(Tung_Beo.get_Bullets()[i]->Get_Rect(), Tung_Beo.Get_Rect()))
				{
					Tung_Beo.remove_Bullets(i);
					Tung_Beo.Get_Damage(Tung_Beo.get_Bullet_dmg());
					if (Tung_Beo.get_current_HP() <= 0)
					{
						Playing = false;
						Death_menu = true;
					}
					break;
				}
			}

			//Collison between Player's Sprite and Big Asteroids
			for (int big = 0; big < Big_Asteroids.size(); big++)
			{
				if (Check_Collision(Tung_Beo.Get_Rect(), Big_Asteroids[big]->Get_Rect()))
				{
					player_score += BIG_ASTEROID_SCORE;
					//spaceship take damage
					Tung_Beo.Get_Damage(BIG_ASTEROID_DAMAGE);

					//add 3 new smaller asteroid
					for (int spawn = 0; spawn < 2; spawn++)
					{
						Asteroid* current_Asteroid = new Asteroid;
						if (!current_Asteroid->Load_Image("Assets/Medium_Asteroid.png", G_Renderer))
						{
							cout << "Image Error: " << endl;
							Playing = false;
							break;
						}
						else
						{
							current_Asteroid->set_X(Big_Asteroids[big]->get_X() + rand() % 300 - 150);
							current_Asteroid->set_Y(Big_Asteroids[big]->get_Y() + rand() % 300 - 150);
							current_Asteroid->set_speed_x(rand() % 4 - 1);
							current_Asteroid->set_speed_y(rand() % 4 - 1);
							current_Asteroid->set_HP(MEDIUM_ASTEROID_HP);
						}
						Medium_Asteroids.push_back(current_Asteroid);
					}

					Remove_Asteroid(Big_Asteroids, big);
					if (Tung_Beo.get_current_HP() <= 0)
					{
						Playing = false;
						Death_menu = true;

					}
					break;
				}
			}

			//Collison between Player's Sprite and Medium Asteroids
			for (int med = 0; med < Medium_Asteroids.size(); med++)
			{
				if (Check_Collision(Tung_Beo.Get_Rect(), Medium_Asteroids[med]->Get_Rect()))
				{
					player_score += MEDIUM_ASTEROID_SCORE;
					Tung_Beo.Get_Damage(MEDIUM_ASTEROID_DAMAGE);

					//add 3 new smaller asteroid
					for (int spawn = 0; spawn < 2; spawn++)
					{
						Asteroid* current_Asteroid = new Asteroid;
						if (!current_Asteroid->Load_Image("Assets/Small_Asteroid.png", G_Renderer))
						{
							Playing = false;
							break;
						}
						else
						{
							current_Asteroid->set_X(Medium_Asteroids[med]->get_X() + rand() % 300 - 150);
							current_Asteroid->set_Y(Medium_Asteroids[med]->get_Y() + rand() % 300 - 150);
							current_Asteroid->set_speed_x(rand() % 4 - 1);
							current_Asteroid->set_speed_y(rand() % 4 - 1);
							current_Asteroid->set_HP(SMALL_ASTEROID_HP);
						}
						Small_Asteroids.push_back(current_Asteroid);
					}

					Remove_Asteroid(Medium_Asteroids, med);

					if (Tung_Beo.get_current_HP() <= 0)
					{
						Playing = false;
						Death_menu = true;
					}
					break;
				}
			}

			//Collison between Player Sprite and Small Asteroids
			for (int small = 0; small < Small_Asteroids.size(); small++)
			{

				if (Check_Collision(Tung_Beo.Get_Rect(), Small_Asteroids[small]->Get_Rect()))
				{
					player_score += SMALL_ASTEROID_SCORE;
					Tung_Beo.Get_Damage(SMALL_ASTEROID_DAMAGE);

					Remove_Asteroid(Small_Asteroids, small);
					if (Tung_Beo.get_current_HP() <= 0)
					{
						Playing = false;
						Death_menu = true;
					}
					break;
				}
			}

			//Add new asteroid
			current_time = SDL_GetTicks();
			if (current_time - time_new_asteroid > SPAWN_ASTEROID_TIME)
			{
				player_score += SURVIVAL_SCORE;
				time_new_asteroid = SDL_GetTicks();
				int i = rand() % 3;
				switch (i)
				{

				case 0:
				{
					Asteroid* Asteroid_i = new Asteroid;
					if (!Asteroid_i->Load_Image("Assets/Big_Asteroid.png", G_Renderer))
					{
						cout << "Image Error: " << endl;
						Playing = false;
						break;
					}
					Asteroid_i->set_X(rand() % 1000);
					Asteroid_i->set_Y(rand() % 50 - 50);
					Asteroid_i->set_speed_x(rand() % 4 - 2);
					Asteroid_i->set_speed_y(rand() % 4 - 2);
					Asteroid_i->set_HP(BIG_ASTEROID_HP);
					Big_Asteroids.push_back(Asteroid_i);
					break;
				}
				case 1:
				{
					Asteroid* Asteroid_i = new Asteroid;
					if (!Asteroid_i->Load_Image("Assets/Medium_Asteroid.png", G_Renderer))
					{
						cout << "Image Error: " << endl;
						Playing = false;
					}
					Asteroid_i->set_X(rand() % 100);
					Asteroid_i->set_Y(rand() % 50);
					Asteroid_i->set_speed_x(rand() % 4 - 1);
					Asteroid_i->set_speed_y(rand() % 4 - 1);
					Asteroid_i->set_HP(MEDIUM_ASTEROID_HP);
					Medium_Asteroids.push_back(Asteroid_i);
					break;
				}
				case 2:
				{
					Asteroid* Asteroid_i = new Asteroid;
					if (!Asteroid_i->Load_Image("Assets/Small_Asteroid.png", G_Renderer))
					{
						cout << "Image Error: " << endl;
						Playing = false;
					}
					Asteroid_i->set_X(rand() % 100);
					Asteroid_i->set_Y(rand() % 50);
					Asteroid_i->set_speed_x(rand() % 4 - 1);
					Asteroid_i->set_speed_y(rand() % 4 - 1);
					Asteroid_i->set_HP(SMALL_ASTEROID_HP);
					Small_Asteroids.push_back(Asteroid_i);
					break;
				}
				}
			}

			const string current_hp = to_string(Tung_Beo.get_current_HP());

			//render hp number
			Render_Message(G_Renderer, 1210, 50, current_hp.c_str(), font_24, White);

			//render HP 
			SDL_Rect fillRect = { 900, 50, 300 * Tung_Beo.get_current_HP() / Tung_Beo.get_max_HP(), 20 };
			SDL_SetRenderDrawColor(G_Renderer, 128, 128, 128, 255);
			SDL_RenderFillRect(G_Renderer, &fillRect);

			//render HP border
			SDL_Rect outlineRect = { 900, 50, 300, 20 };
			SDL_SetRenderDrawColor(G_Renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(G_Renderer, &outlineRect);

			//black raw renderer
			SDL_SetRenderDrawColor(G_Renderer, 0, 0, 0, 255);

			string currentScore = "SCORE: " + to_string(player_score);
			Render_Message(G_Renderer, 900, 100, currentScore.c_str(), font_24, White);

			Render_Asteroid(Big_Asteroids);
			Render_Asteroid(Medium_Asteroids);
			Render_Asteroid(Small_Asteroids);
			Tung_Beo.Render(G_Renderer);
			SDL_RenderPresent(G_Renderer);
		}

		int death_start_time = SDL_GetTicks();
		int death_current_time = SDL_GetTicks();


		//add high score to text
		//score string
		string player_total_score = "YOUR SCORE: " + to_string(player_score);

		int player_top = 0;
		for (player_top = 0; player_top < 5; player_top++)
		{
			if (player_score > player_high_score[player_top])
			{
				if (player_top == 4)
				{
					player_high_score[4] = player_score;
				}
				else
				{
					for (int i = player_high_score.size() - 1; i > player_top; i--)
					{
						player_high_score[i] = player_high_score[i - 1];
					}
					player_high_score[player_top] = player_score;
				}
				break;
			}
			if (player_top == 4)player_top++;
		}

		if (player_top < 5)
		{
			fstream score_file;
			score_file.open("Assets/High_score.txt", ios::out);
			for (int i = 0; i < player_high_score.size(); i++)
			{
				score_file << player_high_score[i] << endl;
			}
			score_file.close();
		}

		while (Death_menu)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					Death_menu = false;
					game_Running = false;
				}
			}
			death_current_time = SDL_GetTicks();
			if (death_current_time - death_start_time < 3000)
			{
				SDL_RenderClear(G_Renderer);
				//render score string
				Render_Message(G_Renderer, 527, 400 + sin(SDL_GetTicks() / 100) * 2, player_total_score.c_str(), font_24, White);
				//render dead message
				Render_Center(G_Renderer, 0, sin(SDL_GetTicks() / 100) * 2 - 4, "YOU ARE DEAD!", font_32, White);
				SDL_RenderPresent(G_Renderer);
			}
			else
			{
				if (death_current_time - death_start_time < 6000)
				{
					SDL_RenderClear(G_Renderer);
					Render_Logo(G_Renderer, 0, 0, "Assets/Credit.png");
					SDL_RenderPresent(G_Renderer);
				}
				else
				{
					Death_menu = false;
					main_menu = true;
					Reset_Game();
				}
			}
		}

	}
	close();
	return 0;
}