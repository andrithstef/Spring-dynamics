#include <SFML/Graphics.hpp>

#include "EntityManager.h"
#include "InputHandler.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1500.f, 1000.f), "Spring Dynamics");

  EntityManager &entityManager = EntityManager::getInstance();
  InputHandler inputHandler = InputHandler();

  sf::Clock clock;

  while (window.isOpen()) {
    inputHandler.handleInputs(window, entityManager);

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(100, 100, 100));

    entityManager.Update(deltaTime, window);
    entityManager.Show(window);

    window.display();
  }

  return 0;
}
