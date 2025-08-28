#include "GameWindow.h"

void GameWindow::pollEvents() {
    if (!GameWindow::window().isOpen()) return;

    sf::Event event;
    while (window().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            GameWindow::window().close();
        }

        for (std::size_t i = 0; i < handlers.size(); ++i) {
            handlers[i](event);
        }
    }
}