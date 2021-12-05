#include "Bullet.h"

Bullet::Bullet()
{
	Frame.x = 0;
	Frame.y = 0;

	x_speed = 1;
	y_speed = 1;
	velocity = 0;
	angle = 0;
}

Bullet::~Bullet()
{
	Entity::Free();
}

void Bullet::Render(SDL_Renderer* G_Renderer)
{
	SDL_RenderCopy(G_Renderer, Tex, NULL, &Frame);
	//SDL_RenderCopyEx(G_Renderer, Tex, NULL, &Frame, angle, NULL, SDL_FLIP_NONE);
}

void Bullet::Fire()
{
	x_speed = velocity * sin(angle * (2 * 3.14) / 360);
	y_speed = velocity * -cos(angle * (2 * 3.14) / 360);

	Frame.x += x_speed;
	Frame.y += y_speed;

	if (Frame.x + Frame.w < 0)
	{
		Frame.x += 1280;
	}
	if (Frame.x > 1280)
	{
		Frame.x -= 1280;
	}
	if (Frame.y + Frame.h < 0)
	{
		Frame.y += 720;
	}
	if (Frame.y > 720)
	{
		Frame.y -= 720;
	}
}

void Bullet::Free()
{
	Entity::Free();
}