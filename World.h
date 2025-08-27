#pragma once
#include<vector>
#include<memory>
#include<SFML/Graphics.hpp>
#include<queue>
#include <random>
#include <cmath>

#include "Player.h"
#include "CoreShield.h"
#include "Core.h"
#include "Bullet.h"
#include "UserInterface.h"
#include "Fire.h"

class World {
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<CoreShield> shield;
	std::shared_ptr<Core> core;
	std::queue<sf::Event> events;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<Fire>> fires;
	std::unique_ptr<UserInterface> ui;

	int points;
	int lvl;
	bool refreshing;
	float refreshing_time;
	float fire_time;
	float fire_current_time;
	bool first_shoot;
	bool end;

	void check_bullets();
	void check_shield();
	void check_core();
	void check_fires();

	void refresh();
	void reset();
	void game_over();
public:
	World() {
		ui = std::make_unique<UserInterface>();
		ui->initialize();

		refreshing = false;
		refreshing_time = 0.f;
		fire_time = 2.f;
		fire_current_time = 0.f;
		first_shoot = false;
		end = false;

		GameWindow::addHandler(
			[this](const sf::Event& event) {
				add_event(event);
			}
		);

		points = 0;
		lvl = 0;
	}

	static World& instance() {
		static World world;
		return world;
	}

	void tick(float delta_time);

	void add_player(std::shared_ptr<Player> _player) { player = _player; }
	void add_shield(std::shared_ptr<CoreShield> _shield) { shield = _shield; }
	void add_core(std::shared_ptr<Core> _core) { core = _core; }

	void add_event(const sf::Event event) { events.push(event); }
	void event_handler();

	void player_shoot();
	void fire();
};