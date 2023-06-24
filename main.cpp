#include "Spring.h"
#include "Weight.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <chrono>
#include <thread>

int main() {
  sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML Project");

  float mass = 0.1;
  float rotation = 0;
  sf::Vector2f position(501.f, 100.f);
  sf::Vector2f size(75.f, 75.f);
  Weight w = Weight(mass, position, rotation, size);

  float length = 500;
  float K = 1;
  sf::Vector2f p1(900.f, 100.f);
  sf::Vector2f p2(75.f, 0.f);

  sf::Vector2f po1(100.f, 100.f);
  sf::Vector2f po2(0.f, 0.f);

  Spring s2 = Spring(length, K, po1, po2, nullptr, &w);

  Spring s = Spring(length, K, p1, p2, nullptr, &w);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(100, 100, 100));

    s.Update(deltaTime, window);
    s2.Update(deltaTime, window);
    w.Update(deltaTime, window);
    s.Show(window);
    s2.Show(window);
    w.show(window);
    window.display();
    // std::chrono::seconds sleepDuration(1);
    // std::this_thread::sleep_for(sleepDuration);
  }

  return 0;
}
