#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<functional>

#include "Utils.h"

using EventHandler = std::function<void(const sf::Event&)>;

class GameWindow {
private:
	static inline std::vector<EventHandler> handlers{};
public:
	static sf::RenderWindow& window() {
		static sf::RenderWindow window(
			sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
			"Stagex"
			//sf::Style::Fullscreen
		);

		window.setFramerateLimit(FRAME_RATE);
		window.setVerticalSyncEnabled(true);
		window.setMouseCursorVisible(false);

		return window;
	}

	static void pollEvents();
    static void addHandler(EventHandler h) { handlers.push_back(h); }
};