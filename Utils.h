#pragma once
#include<SFML/Graphics.hpp>

constexpr unsigned int SCREEN_WIDTH = 640;
constexpr unsigned int SCREEN_HEIGHT = 360;
constexpr float WIDTH_LIMIT = 380;
constexpr float HEIGHT_LIMIT = 360;

constexpr float FRAME_RATE = 1.f / 30.f;

enum class Directions {
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4
};

enum class Collision {
	NONE = 0,
	RIGHT = 1,
	LEFT = 2,
	UP = 3,
	DOWN = 4
};

struct Sprite {
	int width;
	int height;
	sf::Texture texture;
	sf::Sprite frame;
};