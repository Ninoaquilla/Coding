#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <variant>

int main() {
    sf::RenderWindow window(sf::VideoMode{600, 400}, "Tes SFML");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (const auto* e = std::get_if<sf::Event::Closed>(&event)) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
