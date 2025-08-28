#include "Player.h"

void Player::initialize() {
	sprite = std::make_shared<Sprite>();

	if (!sprite->texture.loadFromFile("./src/sprites/ship.png")) {
		const std::string error = "Can't initialize sprite in ./src/sprites/ship.png";
		std::cerr << "Error initializing player: " << error << std::endl;
		GameWindow::window().close();
		return;
	}

	sprite->frame.setTexture(sprite->texture);

	sprite->width = sprite->texture.getSize().x;
	sprite->height = sprite->texture.getSize().y;

	x += sprite->width / 2.f;

	sprite->frame.setOrigin(sprite->width / 2.f, 0);
	sprite->frame.setPosition(x, y);

	GameWindow::addHandler(
		[this](const sf::Event& event) {
			this->add_event(event);
		}
	);

	for (size_t i = 0; i < 6; i++) {
		std::shared_ptr<Sprite> spr = std::make_shared<Sprite>();

		std::stringstream ss_path;
		ss_path << "./src/sprites/destroyed-ship-" << i << ".png";
		std::string path = ss_path.str();

		if (!spr->texture.loadFromFile(path)) {
			const std::string error = "Can't initialize sprite in " + path;
			std::cerr << "Error initializing player: " << error << std::endl;
			GameWindow::window().close();
		}

		spr->frame.setTexture(spr->texture);
		spr->frame.setTexture(spr->texture);

		spr->width = spr->texture.getSize().x;
		spr->height = spr->texture.getSize().y;

		spr->frame.setOrigin(spr->width / 2.f, 0);

		destroyed_sprites.push_back(spr);
	}

	if (!destroyed_buffer.loadFromFile("./src/sounds/ship-explosion.wav")) {
		const std::string error = "Can't initialize sound in ./src/sounds/ship-explosion.wav";
		std::cerr << "Error initializing player: " << error << std::endl;
		GameWindow::window().close();
	}

	destroyed_sound.setBuffer(destroyed_buffer);

	current_sprite = sprite;
}

void Player::draw() {
	current_sprite->frame.setPosition(x, y);
	GameWindow::window().draw(current_sprite->frame);
}

void Player::set_movement(Directions dir, bool key_down = true) {
	switch (dir) {
	case Directions::UP:
		UP = key_down;
		break;
	case Directions::DOWN:
		DOWN = key_down;
		break;
	case Directions::RIGHT:
		RIGHT = key_down;
		break;
	case Directions::LEFT:
		LEFT = key_down;
		break;
	default:
		break;
	}
}

void Player::add_event(const sf::Event& event) {
	events.push(event);
}

void Player::event_handler() {
	while (!events.empty()) {
		sf::Event e = events.front();
		events.pop();

		if (e.type == sf::Event::KeyPressed) {
			if (e.key.code == sf::Keyboard::D) {
				set_movement(Directions::RIGHT);
			}
			else if (e.key.code == sf::Keyboard::A) {
				set_movement(Directions::LEFT);
			}

			if (e.key.code == sf::Keyboard::W) {
				set_movement(Directions::UP);
			}
			else if (e.key.code == sf::Keyboard::S) {
				set_movement(Directions::DOWN);
			}
		}
		else if (e.type == sf::Event::KeyReleased) {
			if (e.key.code == sf::Keyboard::D) {
				set_movement(Directions::RIGHT, false);
			}
			
			if (e.key.code == sf::Keyboard::A) {
				set_movement(Directions::LEFT, false);
			}

			if (e.key.code == sf::Keyboard::W) {
				set_movement(Directions::UP, false);
			}
			
			if (e.key.code == sf::Keyboard::S) {
				set_movement(Directions::DOWN, false);
			}
		}
		else if (e.type == sf::Event::JoystickMoved) {
			float pos = e.joystickMove.position;
			sf::Joystick::Axis axis = e.joystickMove.axis;

			if (axis == sf::Joystick::PovX) {
				if (pos > 50) set_movement(Directions::RIGHT);
				else if (pos < -50) set_movement(Directions::LEFT);
				else {
					set_movement(Directions::RIGHT, false);
					set_movement(Directions::LEFT, false);
				}
			}else if (axis == sf::Joystick::PovY) {
				if (pos > 50) set_movement(Directions::UP);
				else if (pos < -50) set_movement(Directions::DOWN);
				else {
					set_movement(Directions::UP, false);
					set_movement(Directions::DOWN, false);
				}
			}
			else if (axis == sf::Joystick::X) {
				if (pos > 50) set_movement(Directions::RIGHT);
				else if (pos < -50) set_movement(Directions::LEFT);
				else {
					set_movement(Directions::RIGHT, false);
					set_movement(Directions::LEFT, false);
				}
			}
			else if (axis == sf::Joystick::Y) {
				if (pos > 50) set_movement(Directions::DOWN);
				else if (pos < -50) set_movement(Directions::UP);
				else {
					set_movement(Directions::UP, false);
					set_movement(Directions::DOWN, false);
				}
			}
		}
	}
}

void Player::move(float delta_time) {
	float dx = 0.f;
	float dy = 0.f;

	if (RIGHT && !LEFT) dx += 1.f;
	if (LEFT && !RIGHT) dx -= 1.f;
	if (UP && !DOWN) dy -= 1.f;
	if (DOWN && !UP) dy += 1.f;

	float length = std::sqrt(dx * dx + dy * dy);
	if (length != 0.f) {
		dx /= length;
		dy /= length;
	}

	float x_pos = x + (dx * speed * delta_time);
	float y_pos = y + (dy * speed * delta_time);

	x_pos = std::clamp(x_pos, 0.f, WIDTH_LIMIT - sprite->width);
	y_pos = std::clamp(y_pos, 0.f, HEIGHT_LIMIT - sprite->height);

	x = x_pos;
	y = y_pos;
}

void Player::tick(float delta_time) {
	if (_destroyed) return destroyed_tick(delta_time);

	event_handler();
	move(delta_time);
	draw();
}

void Player::destroyed_tick(float delta_time) {
	if (destroyed_sprite >= destroyed_sprites.size()) {
		ready_to_start = true;
		return;
	}

	last_frame_time += delta_time;

	if (last_frame_time >= frame_time) {
		last_frame_time -= frame_time;
		destroyed_sprite++;
		if (destroyed_sprite >= destroyed_sprites.size()) return;

		current_sprite = destroyed_sprites.at(destroyed_sprite);
	}

	draw();
}