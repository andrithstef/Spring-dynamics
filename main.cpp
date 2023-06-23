#include "Weight.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Project");

  float mass = 0.5;
  float rotation = 0;
  sf::Vector2f position(100.f, 100.f);
  sf::Vector2f size(100.f, 100.f);
  Weight w = Weight(mass, position, rotation, size);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float deltaTime = clock.restart().asSeconds();

    window.clear();
    w.Update(deltaTime, window);
    w.show(window);
    window.display();
  }

  return 0;
}
