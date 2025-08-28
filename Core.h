#pragma once
#include<vector>
#include<memory>
#include<string>
#include<sstream>
#include<iostream>

#include "GameWindow.h"
#include "Utils.h"

class Core {
private:
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::vector<std::shared_ptr<Sprite>> damage_sprites;
	std::vector<std::shared_ptr<Sprite>> health_sprites;
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<Sprite> health_sprite;
	int frames;
	int health;
	float x, y;
	int current_sprite;
	float last_frame_time;
	float frame_time;
	bool _destroyed;
	bool up;
	float speed;

	void initialize();
	void destroyed_tick(float delta_time);
public:
	Core() {
		_destroyed = false;
		frames = 4;
		x = 450;
		y = 0.f;
		current_sprite = 0;
		frame_time = 0.15f;
		last_frame_time = 0;
		health = 3;
		up = true;
		speed = 50.f;
		initialize();
	}


	void tick(float delta_time);
	void draw();
	void draw_health();
	void damage();

	void reset() {
		health = 3;
		current_sprite = sprites.size() - 1;
		health_sprite = health_sprites.at(health_sprites.size() - 1);
		_destroyed = false;
		speed += 10.f;
	}

	void reset_speed() { speed = 50.f; }

	int get_health()const { return health; }
	float get_x()const { return x; }
	float get_y()const { return y; }
	bool destroyed()const { return _destroyed; }
};