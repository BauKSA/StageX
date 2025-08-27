#include "UserInterface.h"

void UserInterface::initialize() {
	sprite = std::make_shared<Sprite>();
	font = std::make_shared<Sprite>();

	if (!sprite->texture.loadFromFile("./src/sprites/ui.png")) {
		const std::string error = "Can't initialize sprite in ./src/sprites/ui.png";
		std::cerr << "Error initializing UI: " << error << std::endl;
		GameWindow::window().close();
	}

	sprite->frame.setTexture(sprite->texture);
	sprite->frame.setTexture(sprite->texture);

	sprite->width = sprite->texture.getSize().x;
	sprite->height = sprite->texture.getSize().y;


	sprite->frame.setOrigin(0, 0);
	sprite->frame.setPosition(x, y);

	if (!font->texture.loadFromFile("./src/sprites/numbers.png")) {
		const std::string error = "Can't initialize sprite in ./src/sprites/numbers.png";
		std::cerr << "Error initializing UI: " << error << std::endl;
		GameWindow::window().close();
	}

	font->frame.setTexture(font->texture);
	font->frame.setTexture(font->texture);

	font->width = font->texture.getSize().x;
	font->height = font->texture.getSize().y;


	font->frame.setOrigin(0, 0);
	font->frame.setPosition(x, y);
}

void UserInterface::draw(int lvl, int points) {
	GameWindow::window().draw(sprite->frame);
	draw_dynamics(lvl, points);
}

void UserInterface::draw_number(int number, float x_pos, float y_pos) {
	std::string str = std::to_string(number);

	float x_offset = 0.f;

	for (char c : str) {
		int digit = c - '0';

		int src_x = digit * (12 + 2);
		sf::IntRect rect(src_x, 0, 12, 26);

		font->frame.setTextureRect(rect);
		font->frame.setPosition(x_pos + x_offset, y_pos);

		GameWindow::window().draw(font->frame);

		x_offset += 14;
	}
}

void UserInterface::draw_dynamics(int lvl, int points) {
	draw_number(points, 517, 289);
	draw_number(lvl, 517, 242);
}