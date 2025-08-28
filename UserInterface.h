#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<iostream>
#include<string>

#include "Utils.h"
#include "GameWindow.h"

class UserInterface {
private:
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<Sprite> keyboard_ui;
	std::shared_ptr<Sprite> joystick_ui;
	std::shared_ptr<Sprite> font;
	int x, y;
	
	void draw_number(int number, float x_pos, float y_pos);
	void draw_dynamics(int lvl, int points);
public:
	UserInterface() {
		y = 0;
		x = 500;
	}

	void initialize();

	void draw(int lvl, int points);
};