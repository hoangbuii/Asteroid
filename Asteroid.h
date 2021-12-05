#include "Entity.h"

class Asteroid :public Entity
{
private:
	int x_speed;
	int y_speed;
	double angle;

	int max_HP;
	int current_HP;
public:
	Asteroid();
	~Asteroid();
	void Render(SDL_Renderer* G_Renderer);
	int get_speed_x()
	{
		return x_speed;
	}
	int get_speed_y()
	{
		return y_speed;
	}
	void set_speed_x(int s_x)
	{
		x_speed = s_x;
	}
	void set_speed_y(int s_y)
	{
		y_speed = s_y;
	}
	double get_angle()
	{
		angle += 0.5;
		if (angle == 360)
		{
			angle = 0;
		}
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
	void Attacked(const int& Damage)
	{
		current_HP -= Damage;
	}
};
