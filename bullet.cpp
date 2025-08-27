#include "Bullet.h"

void Bullet::initialize() {
	sprite = std::make_shared<Sprite>();

	const std::string path = player ?
		"./src/sprites/player-bullet.png"
		: "./src/sprites/core-bullet.png";

	if (!sprite->texture.loadFromFile(path)) {
		const std::string error = "Can't initialize sprite in " + path;
		std::cerr << "Error initializing bullet: " << error << std::endl;
		GameWindow::window().close();
	}

	sprite->frame.setTexture(sprite->texture);
	sprite->frame.setTexture(sprite->texture);

	sprite->width = sprite->texture.getSize().x;
	sprite->height = sprite->texture.getSize().y;

	x += sprite->width / 2.f;

	sprite->frame.setOrigin(sprite->width / 2.f, 0);
	sprite->frame.setPosition(x, y);
}

void Bullet::tick(float delta_time) {
	if (_destroyed) return;

	if (player) x += speed * delta_time;
	else x -= speed * delta_time;

	draw();
}

void Bullet::draw() {
	sprite->frame.setPosition(x, y);
	GameWindow::window().draw(sprite->frame);
}