#pragma once
#include<memory>
#include<iostream>
#include<queue>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>

#include "GameWindow.h"
#include "Utils.h"

class Player {
private:
	std::shared_ptr<Sprite> sprite;
	std::vector<std::shared_ptr<Sprite>> destroyed_sprites;
	std::shared_ptr<Sprite> current_sprite;
	int destroyed_sprite;
	float x, y;
	float speed;
	std::queue<sf::Event> events;
	bool RIGHT, LEFT, UP, DOWN;
	bool _destroyed;
	bool ready_to_start;
	float frame_time;
	float last_frame_time;
	sf::SoundBuffer destroyed_buffer;
	sf::Sound destroyed_sound;

	void destroyed_tick(float delta_time);
public:
	Player() :
		x(64), y(180), speed(300.f),
		RIGHT(false), LEFT(false), UP(false), DOWN(false)
	{
		frame_time = 0.15f;
		last_frame_time = 0;
		_destroyed = false;
		ready_to_start = false;
		destroyed_sprite = 0;
	}

	void initialize();

	void clear_events() {
		while (!events.empty()) events.pop();
	}

	void draw();
	void set_movement(Directions dir, bool key_donw);
	void move(float delta_time);

	void add_event(const sf::Event& event);
	void event_handler();

	void tick(float delta_time);

	void reset() {
		x = 64;
		y = 180;
		_destroyed = false;
		current_sprite = sprite;
		ready_to_start = false;
		last_frame_time = 0;
		destroyed_sprite = 0;
	}

	void destroy() {
		_destroyed = true;
		destroyed_sound.play();
	}

	float get_x()const { return x; }
	float get_y()const { return y; }
	bool destroyed()const { return _destroyed; }
	bool is_ready()const { return ready_to_start; }
};