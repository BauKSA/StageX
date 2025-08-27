#include "CoreShield.h"

void CoreShield::initialize() {
	for (size_t i = 0; i < 5; i++) {
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

		std::stringstream ss_path;
		ss_path << "./src/sprites/core-shield-" << i << ".png";
		std::string path = ss_path.str();

		if (!sprite->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing core-shield: " << error << std::endl;
			GameWindow::window().close();
		}

		sprite->frame.setTexture(sprite->texture);

		sprite->width = sprite->texture.getSize().x;
		sprite->height = sprite->texture.getSize().y;

		sprite->frame.setOrigin(sprite->width / 2.f, 0);

		sprites.push_back(sprite);
	}

	for (size_t i = 0; i < 3; i++) {
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

		std::stringstream ss_path;
		ss_path << "./src/sprites/shield-health-" << i + 1 << ".png";
		std::string path = ss_path.str();

		if (!sprite->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing core-shield: " << error << std::endl;
			GameWindow::window().close();
		}

		sprite->frame.setTexture(sprite->texture);
		sprite->frame.setTexture(sprite->texture);

		sprite->width = sprite->texture.getSize().x;
		sprite->height = sprite->texture.getSize().y;

		sprite->frame.setOrigin(sprite->width / 2.f, 0);

		health_sprites.push_back(sprite);
	}

	sprite = sprites.at(sprites.size() - 1);
	current_sprite = sprites.size() - 1;
	health_sprite = health_sprites.at(health_sprites.size() - 1);
}

void CoreShield::draw() {
	sprite->frame.setPosition(x, y);

	GameWindow::window().draw(sprite->frame);
}

void CoreShield::draw_health() {
	health_sprite->frame.setPosition(x, y);
	GameWindow::window().draw(health_sprite->frame);
}

void CoreShield::tick() {
	if (_destroyed) return;
	draw();

	if (health == 3) health_sprite = health_sprites.at(health_sprites.size() - 1);
	else if (health == 2) health_sprite = health_sprites.at(health_sprites.size() - 2);
	else if(health == 1) health_sprite = health_sprites.at(health_sprites.size() - 3);

	draw_health();
}

void CoreShield::damage() {
	health--;
	if (health <= 0) {
		health = 3;
		current_sprite--;
		if (current_sprite < sprites.size()) sprite = sprites.at(current_sprite);
		else _destroyed = true;
	}
}