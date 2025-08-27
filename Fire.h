#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<sstream>

#include "GameWindow.h"
#include "Utils.h"

class Fire {
private:
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Sprite> sprite;
	int current_sprite;
	bool animation_end;
	int x, y;
	bool _destroyed;
	float last_frame_time;
	float frame_time;
	float speed;

public:
	Fire(int _y) {
		x = 400;
		y = _y;
		animation_end = false;
		_destroyed = false;
		last_frame_time = 0;
		frame_time = 0.1f;
		speed = 50.f;
		speed = 175.f;
		current_sprite = 0;
	}

	void initialize();

	void tick(float delta_time);
	void draw();

	void destroy() { _destroyed = true; }

	float get_x()const { return x; }
	float get_y()const { return y; }
	bool destroyed()const { return _destroyed; }
};