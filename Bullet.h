#pragma once
#include<memory>
#include<iostream>
#include<string>

#include "GameWindow.h"
#include "Utils.h"

class Bullet {
private:
	std::shared_ptr<Sprite> sprite;
	bool player;
	float x, y;
	float speed;
	bool _destroyed;

public:
	Bullet(int _x, int _y, bool p = true) :
		player(p) {
		x = _x;
		y = _y;
		speed = 500.f;
		_destroyed = false;
	}

	void initialize();

	void tick(float delta_time);
	void draw();

	void destroy() { _destroyed = true; }

	float get_x()const { return x; }
	float get_y()const { return y; }
	bool is_from_player()const { return player; }
	bool destroyed()const { return _destroyed; }
};