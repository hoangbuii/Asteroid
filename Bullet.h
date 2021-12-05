#pragma once

#include "Entity.h"

class Bullet:public Entity
{
private:

	int x_speed;
	int y_speed;
	int velocity;

	double angle;
public:
	Bullet();
	~Bullet();
	void Render(SDL_Renderer* G_Renderer);
	void Fire();
	int get_speed_x()
	{
		return x_speed;
	}
	int get_speed_y()
	{
		return y_speed;
	}
	int get_velocity()
	{
		return velocity;
	}
	void set_velocity(int _velocity)
	{
		velocity = _velocity;
	}
	double get_angle()
	{
		return angle;
	}
	void set_angle(double angle)
	{
		this->angle = angle;
	}
	void Free();
};
