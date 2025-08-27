#include<memory>
#include <SFML/System.hpp>

#include "GameWindow.h"
#include "Player.h"
#include "CoreShield.h"
#include "Core.h"
#include "World.h"

int main() {
	sf::RenderWindow& window = GameWindow::window();

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->initialize();

	std::shared_ptr<CoreShield> core_shield = std::make_shared<CoreShield>();
	core_shield->initialize();

	std::shared_ptr<Core> core = std::make_shared<Core>();

	World& world = World::instance();
	world.add_player(player);
	world.add_shield(core_shield);
	world.add_core(core);

	sf::Clock clock;
	
	while (window.isOpen()) {
		float delta_time = clock.restart().asSeconds();

		window.clear();
		GameWindow::pollEvents();

		player->tick(delta_time);
		core_shield->tick();
		core->tick(delta_time);
		world.tick(delta_time);

		window.display();
	}

	return 0;
}