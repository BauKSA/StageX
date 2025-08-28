#include "World.h"

void World::initialize_sound() {
	if (!player_shoot_buffer.loadFromFile("./src/sounds/ship-shoot.wav")) {
		const std::string error = "Can't initialize sound in ./src/sounds/ship-shoot.wav";
		std::cerr << "Error initializing world: " << error << std::endl;
		GameWindow::window().close();
	}

	player_shoot_sound.setBuffer(player_shoot_buffer);

	if (!damage_buffer.loadFromFile("./src/sounds/damage.wav")) {
		const std::string error = "Can't initialize sound in ./src/sounds/damage.wav";
		std::cerr << "Error initializing world: " << error << std::endl;
		GameWindow::window().close();
	}

	damage_sound.setBuffer(damage_buffer);
}

void World::event_handler() {
	if (!player) return;
	if (refreshing) return;

	while (!events.empty()) {
		sf::Event e = events.front();
		events.pop();

		if (e.type == sf::Event::KeyReleased) {
			if (e.key.code == sf::Keyboard::K) {
				if (!end) return player_shoot();

				if (player->is_ready()) {
					player->reset();
					core->reset_speed();
					points = 0;
					lvl = 0;
					end = false;
				}
			}
			else if (e.key.code == sf::Keyboard::Escape) {
				GameWindow::window().close();
			}
		}else if(e.type == sf::Event::JoystickButtonReleased) {
			if (e.joystickButton.button == 0) {
				if (!end) return player_shoot();
				if (player->is_ready()) {
					player->reset();
					core->reset_speed();
					points = 0;
					lvl = 0;
					end = false;
				}
			}
			else if (e.joystickButton.button == 7) {
				GameWindow::window().close();
			}
		}
	}
}

void World::player_shoot() {
	player_shoot_sound.play();

	if (!first_shoot) first_shoot = true;
	
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(player->get_x() + 10, player->get_y() + 14);
	bullet->initialize();

	bullets.push_back(bullet);
}

void World::tick(float delta_time) {
	ui->draw(lvl, points);
	event_handler();

	if (end) return;

	if (refreshing) {
		refreshing_time += delta_time;
		if (refreshing_time >= 1.5f) reset();
		return;
	}


	fire_current_time += delta_time;
	if (fire_current_time >= fire_time) {
		fire_current_time = 0;
		fire();
	}

	for (size_t i = 0; i < fires.size(); i++) {
		fires.at(i)->tick(delta_time);
	}

	for (size_t i = 0; i < bullets.size(); i++) {
		bullets.at(i)->tick(delta_time);
	}

	if (shield) check_shield();
	if (core) check_core();

	check_fires();
	check_bullets();
}

void World::reset() {
	if (core) core->reset();
	if (shield) shield->reset();
	if (player) player->clear_events();

	while (!events.empty()) events.pop();

	refreshing = false;
	refreshing_time = 0;
}

void World::refresh() {
	bullets.clear();
	fires.clear();

	refreshing = true;
	lvl++;
	points += 4;

	if (fire_time > 0.1) fire_time -= 0.25f;
	if (fire_time == 0) fire_time = 0.1;
}

void World::check_bullets() {
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[](const std::shared_ptr<Bullet>& b) {
				return b->destroyed();
			}),
		bullets.end());
}

void World::check_fires() {
	for (size_t i = 0; i < fires.size(); i++) {
		Fire& f = *(fires.at(i).get());

		if (f.get_x() <= -64) f.destroy();


		for (size_t j = 0; j < bullets.size(); j++) {
			Bullet& b = *(bullets.at(j).get());
			
			const int margin = 32;

			if (std::abs(b.get_x() - f.get_x()) > margin) continue;
			if (b.get_y() + 4 >= f.get_y() + 4 && b.get_y() <= f.get_y() + 60) {
				b.destroy();
			}
		}

		if (!player) continue;

		const int margin = 12;

		if (std::abs(player->get_x() - f.get_x()) > margin) continue;
		if (player->get_y() + 32 >= f.get_y() + 4 && player->get_y() <= f.get_y() + 60) {
			game_over();
		}
	}

	fires.erase(
		std::remove_if(fires.begin(), fires.end(),
			[](const std::shared_ptr<Fire>& f) {
				return f->destroyed();
			}),
		fires.end());
}

void World::check_shield() {
	if (!shield || shield->destroyed()) return;

	for (size_t i = 0; i < bullets.size(); i++) {
		if (!bullets.at(i)->is_from_player()) continue;
		int x = bullets.at(i)->get_x();
		if (x >= shield->get_x() - 100) {
			bullets.at(i)->destroy();
			shield->damage();
			damage_sound.play();
			points++;
		}
	}
}

void World::check_core() {
	if (!core) return;

	if (core->destroyed()) {
		if (!refreshing) return refresh();
		else return;
	}

	for (size_t i = 0; i < bullets.size(); i++) {
		if (!bullets.at(i)->is_from_player()) continue;
		int x = bullets.at(i)->get_x();
		int y = bullets.at(i)->get_y();
		if (x >= core->get_x() + 50) {
			if (y + 8 >= core->get_y() + 152 && y <= core->get_y() + 208) {
				bullets.at(i)->destroy();
				core->damage();
				damage_sound.play();
				points += 2;
			}
			else {
				bullets.at(i)->destroy();
			}
		}
	}
}

void World::fire() {
	if (!first_shoot) return;

	std::random_device rd;
	std::mt19937 gen(rd());

	int min = 0;
	int max = 296;

	std::uniform_int_distribution<> prob(1, 100);
	std::uniform_int_distribution<> range(0, 296);

	int y_pos;
	int p = prob(gen);

	if (p < 40) y_pos = player->get_y() - 16;
	else y_pos = range(gen);

	std::uniform_int_distribution<> distrib(min, max);


	std::shared_ptr<Fire> f = std::make_shared<Fire>(y_pos);
	f->initialize();
	fires.push_back(f);
}

void World::game_over() {
	reset();
	end = true;
	bullets.clear();
	fires.clear();
	player->destroy();
	refreshing = false;
	refreshing_time = 0.f;
	fire_time = 2.f;
	fire_current_time = 0.f;
	first_shoot = false;
}