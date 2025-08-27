#pragma once
#include<memory>
#include<vector>
#include <iostream>
#include <sstream>

#include "GameWindow.h"
#include "Utils.h"

class CoreShield {
private:
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Sprite> sprite;
	std::vector<std::shared_ptr<Sprite>> health_sprites;
	std::shared_ptr<Sprite> health_sprite;
	int current_sprite;
	int x, y;
	int health;
	bool _destroyed;

public:
	CoreShield() {
		y = 0;
		health = 3;
		_destroyed = false;
		current_sprite = 0;
		x = 500;
	}

	void initialize();

	void draw();
	void draw_health();
	void tick();
	void damage();

	void reset() {
		health = 3;
		current_sprite = sprites.size() - 1;
		sprite = sprites.at(sprites.size() - 1);
		health_sprite = health_sprites.at(health_sprites.size() - 1);
		_destroyed = false;
	}

	int get_health()const { return health; }
	float get_x()const { return x; }
	float get_y()const { return y; }
	bool destroyed()const { return _destroyed; }
};