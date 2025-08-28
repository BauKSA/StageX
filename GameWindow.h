#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<functional>
#include<iostream>

#include "Utils.h"

using EventHandler = std::function<void(const sf::Event&)>;

class GameWindow {
private:
	static inline std::vector<EventHandler> handlers{};

	static void connect_joystick() {
		if (sf::Joystick::isConnected(0)) joystick = true;
		else joystick = false;
	}
public:
	inline static bool joystick = false;

	static sf::RenderWindow& window() {
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		static sf::RenderWindow window;

		GameWindow::connect_joystick();

		if (!window.isOpen()) {
			window.create(
				desktop,
				"Stagex",
				sf::Style::Fullscreen
			);

			float window_ratio = static_cast<float>(desktop.width) / desktop.height;
			float target_ratio = static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT;

			sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

			if (window_ratio > target_ratio) {
				float width = SCREEN_HEIGHT * window_ratio;
				view.setViewport(sf::FloatRect((1.f - target_ratio / window_ratio) / 2.f, 0.f, target_ratio / window_ratio, 1.f));
			}
			else if (window_ratio < target_ratio) {
				float height = SCREEN_WIDTH / window_ratio;
				view.setViewport(sf::FloatRect(0.f, (1.f - window_ratio / target_ratio) / 2.f, 1.f, window_ratio / target_ratio));
			}

			window.setView(view);

			window.setFramerateLimit(FRAME_RATE);
			window.setVerticalSyncEnabled(true);
			window.setMouseCursorVisible(false);
		}

		return window;
	}

	static void pollEvents();
    static void addHandler(EventHandler h) { handlers.push_back(h); }
	static bool joystick_connected() { return joystick; }
};