#pragma once

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using namespace std;


class Entity
{
protected:
	SDL_Texture* Tex;
	SDL_Rect Frame;
public:
	Entity();
	bool Load_Image(const char* file_path,SDL_Renderer* G_Renderer);
	void Render(SDL_Renderer* G_Renderer);
	SDL_Rect Get_Rect() 
	{
		return Frame;
	}
	void Free();

	int get_X()
	{
		return Frame.x;
	}
	int get_Y()
	{
		return Frame.y;
	}
	int get_width()
	{
		return Frame.w;
	}
	int get_height()
	{
		return Frame.h;
	}
	void set_X(int _x)
	{
		Frame.x = _x;
	}
	void set_Y(int _y)
	{
		Frame.y = _y;
	}
};

