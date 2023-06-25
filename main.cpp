#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <chrono>
#include <thread>

#include "EntityManager.h"
#include "Spring.h"
#include "Weight.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML Project");

  EntityManager e = EntityManager();

  float mass = 0.1;
  float rotation = 0;
  sf::Vector2f position(500.f, 200.f);
  sf::Vector2f size(75.f, 75.f);
  Weight w = Weight(mass, position, rotation, size);
  e.addWeight(&w);

  sf::Vector2f position_2(900.f, 200.f);
  sf::Vector2f size_2(75.f, 75.f);

  Weight w2 = Weight(mass, position_2, rotation, size_2);
  e.addWeight(&w2);

  float length = 200;
  float K = 1.5;
  sf::Vector2f p1(500.f, 100.f);
  sf::Vector2f p2(37.5f, 37.5f);

  sf::Vector2f po1(75.f, 75.f);
  sf::Vector2f po2(0.f, 75.f);

  // Spring s = Spring(length, K, p1, p2, nullptr, &w);
  // e.addSpring(&s);
  Spring s2 = Spring(length, K, po1, po2, &w, &w2);
  e.addSpring(&s2);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
          sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

          // Handle the mouse click at the world position
          // You can now use the worldPosition to perform further operations

          // Example: Get the weight at the clicked position
          Weight *clickedWeight = e.getWeightFromPosition(worldPosition);
          if (clickedWeight != nullptr) {
            // Weight found at the clicked position
            std::cout << "Clicked on weight : " << clickedWeight << std::endl;
          }
        }
      }
    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(100, 100, 100));

    e.Update(deltaTime, window);
    e.Show(window);

    window.display();
    // std::chrono::seconds sleepDuration(10);
    // std::this_thread::sleep_for(sleepDuration);
  }

  return 0;
}
