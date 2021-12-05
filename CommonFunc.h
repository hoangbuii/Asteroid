#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int SPAWN_ASTEROID_TIME = 3000;
const int BIG_ASTEROID_DAMAGE = 4;
const int MEDIUM_ASTEROID_DAMAGE = 2;
const int SMALL_ASTEROID_DAMAGE = 1;

const int BIG_ASTEROID_HP = 9;
const int MEDIUM_ASTEROID_HP = 4;
const int SMALL_ASTEROID_HP = 1;

const int BIG_ASTEROID_SCORE = 9;
const int MEDIUM_ASTEROID_SCORE = 3;
const int SMALL_ASTEROID_SCORE = 1;
const int SURVIVAL_SCORE = 1;

const int PLAYER_HP = 20;
const int PLAYER_BULLET_DAMAGE = 1;
const int PLAYER_VELOCITY = 3;

enum Menu {
	PLAY = 0,
	INSTRUCTION = 1,
	HIGH_SCORE = 2,
	EXIT = 3,
};

vector<Asteroid*> Big_Asteroids;
vector<Asteroid*> Medium_Asteroids;
vector<Asteroid*> Small_Asteroids;

Spaceship Tung_Beo;
Entity G_Background;
Entity Arrow_Selected;
Entity Background_logo;
Entity Background_menu;
Entity Credit;
Entity Instructions;


TTF_Font* font_32;
TTF_Font* font_32_outline;
TTF_Font* font_24;

SDL_Color White = { 255,255,255 };
SDL_Window* G_Window = NULL;
SDL_Renderer* G_Renderer = NULL;
SDL_Event event;



bool game_Running = true;
bool intro = true;
bool main_menu = false;
bool start_game = false;
bool Death_menu = false;
bool Playing = false;
int menu = PLAY;
bool menu_selected = false;

vector<int> player_high_score;





bool Check_Collision(const SDL_Rect& object1, const SDL_Rect& object2)
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

	// Case 2: size object 1 < size object 2
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

void Render_Message(SDL_Renderer* Renderer, float p_x, float p_y, const char* p_Text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* Surface_Message = TTF_RenderText_Blended(font, p_Text, textColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, Surface_Message);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = Surface_Message->w;
	src.h = Surface_Message->h;

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;


	SDL_RenderCopy(Renderer, Message, &src, &dst);
	SDL_FreeSurface(Surface_Message);
	SDL_DestroyTexture(Message);
}

void Render_Center(SDL_Renderer* Renderer, float p_x, float p_y, const char* p_Text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* Surface_Message = TTF_RenderText_Blended(font, p_Text, textColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, Surface_Message);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = Surface_Message->w;
	src.h = Surface_Message->h;

	SDL_Rect dst;
	dst.x = (SCREEN_WIDTH - src.w) / 2 + p_x;
	dst.y = (SCREEN_HEIGHT - src.h) / 2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(Renderer, Message, &src, &dst);
	SDL_FreeSurface(Surface_Message);
	SDL_DestroyTexture(Message);
}

void Render_Logo(SDL_Renderer* Renderer, float p_x, float p_y, const char* file_path)
{
	SDL_Texture* p_Tex = NULL;
	p_Tex = IMG_LoadTexture(Renderer, file_path);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_Tex, NULL, NULL, &src.w, &src.h);
	//Get width and Heigt of Texture

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;
	SDL_RenderCopy(Renderer, p_Tex, &src, &dst);
	SDL_DestroyTexture(p_Tex);
}