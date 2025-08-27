#include "Fire.h"

void Fire::initialize() {
	for (size_t i = 0; i < 5; i++) {
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

		std::stringstream ss_path;
		ss_path << "./src/sprites/fire-" << i << ".png";
		std::string path = ss_path.str();

		if (!sprite->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing fire: " << error << std::endl;
			GameWindow::window().close();
		}

		sprite->frame.setTexture(sprite->texture);
		sprite->frame.setTexture(sprite->texture);

		sprite->width = sprite->texture.getSize().x;
		sprite->height = sprite->texture.getSize().y;

		sprite->frame.setOrigin(sprite->width / 2.f, 0);

		sprites.push_back(sprite);
	}

	sprite = sprites.at(0);
}

void Fire::draw() {
	sprite->frame.setPosition(x, y);
	GameWindow::window().draw(sprite->frame);
}

void Fire::tick(float delta_time) {
	if (_destroyed) return;

	if (!animation_end) {
		last_frame_time += delta_time;

		if (last_frame_time >= frame_time) {
			last_frame_time -= frame_time;
			current_sprite++;
			if (current_sprite >= sprites.size() - 1) {
				animation_end = true;
				current_sprite--;
			}

			sprite = sprites.at(current_sprite);
		}
	}

	x -= speed * delta_time;

	draw();
}