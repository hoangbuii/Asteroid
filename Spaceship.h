#pragma once

#include "Entity.h"
#include "Bullet.h"
class Spaceship :public Entity
{
private:
	int velocity;
	int x_velocity;
	int y_velocity;

	double angle;
	double angle_speed;

	vector<Bullet*> Bullets;
	int Shoot;
	bool Lock_shot = false;

	int max_HP;
	int current_HP;
	int Bullet_dmg;
	
	bool Key_LEFT = false, Key_RIGHT = false, Key_UP = false, Key_DOWN = false, key_S = false;
public:
	Spaceship();
	~Spaceship();
	void Render(SDL_Renderer* G_Renderer);
	void Handle_Event(SDL_Event& p_Event);
	void Move(SDL_Renderer* G_Renderer);
	void Reset();
	void set_Bullets(const vector<Bullet*>& bullets) 
	{
		Bullets = bullets; 
	}
	vector<Bullet*> get_Bullets()
	{ 
		return Bullets; 
	}
	void remove_Bullets(int& i);
	int get_velocity()
	{
		return velocity;
	}
	int get_x_velocity()
	{
		return x_velocity;
	}
	int get_y_velocity()
	{
		return y_velocity;
	}
	void set_velocity(int _velocity)
	{
		velocity = _velocity;
	}
	double get_angle()
	{
		return angle;
	}
	void set_HP(int _hp)
	{
		max_HP = _hp;
		current_HP = _hp;
	}
	int get_max_HP()
	{
		return max_HP;
	}
	int get_current_HP()
	{
		return current_HP;
	}
	void Attacked(int& Damage)
	{
		current_HP -= Damage;
	}
	int get_Bullet_dmg()
	{
		return Bullet_dmg;
	}
	void set_Bullet_dmg(int _dmg)
	{
		Bullet_dmg = _dmg;
	}
	void Get_Damage(int _dame)
	{
		current_HP -= _dame;
	}
};