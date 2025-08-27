#include "Core.h"

void Core::initialize() {
	for (size_t i = 0; i < 4; i++) {
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

		std::stringstream ss_path;
		ss_path << "./src/sprites/core-" << i << ".png";
		std::string path = ss_path.str();

		if (!sprite->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing core: " << error << std::endl;
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
		ss_path << "./src/sprites/core-health-" << i + 1 << ".png";
		std::string path = ss_path.str();

		if (!sprite->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing core: " << error << std::endl;
			GameWindow::window().close();
		}

		sprite->frame.setTexture(sprite->texture);
		sprite->frame.setTexture(sprite->texture);

		sprite->width = sprite->texture.getSize().x;
		sprite->height = sprite->texture.getSize().y;

		sprite->frame.setOrigin(sprite->width / 2.f, 0);

		health_sprites.push_back(sprite);
	}

	for (size_t i = 0; i < 4; i++) {
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

		std::stringstream ss_path;
		ss_path << "./src/sprites/core-damage-" << i + 1 << ".png";
		std::string path = ss_path.str();

		if (!sprite->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing core: " << error << std::endl;
			GameWindow::window().close();
		}

		sprite->frame.setTexture(sprite->texture);


		sprite->width = sprite->texture.getSize().x;
		sprite->height = sprite->texture.getSize().y;

		sprite->frame.setOrigin(sprite->width / 2.f, 0);

		damage_sprites.push_back(sprite);
	}

	sprite = sprites.at(0);
	health_sprite = health_sprites.at(health_sprites.size() - 1);
	x = 400;
}

void Core::destroyed_tick(float delta_time) {
	last_frame_time += delta_time;

	if (last_frame_time >= frame_time) {
		last_frame_time -= frame_time;
		current_sprite++;
		if (current_sprite >= frames) current_sprite = 0;
		sprite = damage_sprites.at(current_sprite);
	}

	draw();
}

void Core::tick(float delta_time) {
	if (_destroyed) return destroyed_tick(delta_time);

	last_frame_time += delta_time;

	if (last_frame_time >= frame_time) {
		last_frame_time -= frame_time;
		current_sprite++;
		if (current_sprite >= frames) current_sprite = 0;
		sprite = sprites.at(current_sprite);
	}

	draw();

	if (health == 3) health_sprite = health_sprites.at(health_sprites.size() - 1);
	else if (health == 2) health_sprite = health_sprites.at(health_sprites.size() - 2);
	else if (health == 1) health_sprite = health_sprites.at(health_sprites.size() - 3);

	draw_health();
}

void Core::draw() {
	sprite->frame.setPosition(x, y);
	GameWindow::window().draw(sprite->frame);
}

void Core::draw_health() {
	health_sprite->frame.setPosition(x, y);
	GameWindow::window().draw(health_sprite->frame);
}

void Core::damage() {
	health--;
	if (health <= 0) {
		health = 3;
		current_sprite--;
		if (health < health_sprites.size()) sprite = health_sprites.at(health);
		else _destroyed = true;
	}
}