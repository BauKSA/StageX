#include "GameWindow.h"

void GameWindow::pollEvents() {
    sf::Event event;
    while (window().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window().close();
        }

        for (std::size_t i = 0; i < handlers.size(); ++i) {
            handlers[i](event);
        }
    }
}