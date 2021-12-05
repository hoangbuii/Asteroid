#pragma once

#include "Asteroid.h"


Asteroid::Asteroid()
{
	x_speed = 0;
	y_speed = 0;
	angle = 0;
}

Asteroid::~Asteroid()
{
	Entity::Free();
}

void Asteroid::Render(SDL_Renderer* G_Renderer)
{
	Frame.x += x_speed;
	Frame.y += y_speed;

	if (Frame.x + Frame.w < 0)
	{
		Frame.x += 1280 + Frame.w;
	}
	if (Frame.x > 1280)
	{
		Frame.x -= 1280 + Frame.w;
	}
	if (Frame.y + Frame.h < 0)
	{
		Frame.y += 720 + Frame.h;
	}
	if (Frame.y > 720)
	{
		Frame.y -= 720 + Frame.h;
	}
	SDL_RenderCopyEx(G_Renderer, Tex, NULL, &Frame, get_angle(), NULL, SDL_FLIP_NONE);
}