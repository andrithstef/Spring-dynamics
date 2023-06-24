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
  sf::Vector2f position(500.f, 200.f);
  sf::Vector2f size(75.f, 75.f);
  Weight w = Weight(mass, position, rotation, size);

    sf::Vector2f position_2(500.f, 300.f);
    sf::Vector2f size_2(75.f, 75.f);

    Weight w2 = Weight(mass, position_2, rotation, size_2);

  float length = 50;
  float K = 1.5;
  sf::Vector2f p1(500.f, 100.f);
  sf::Vector2f p2(0.f, 0.f);

  sf::Vector2f po1(75.f, 75.f);
  sf::Vector2f po2(75.f, 75.f);


  Spring s = Spring(length, K, p1, p2, nullptr, &w);
  Spring s2 = Spring(length, K, po1, po2, &w, &w2);

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
    w2.Update(deltaTime, window);
    s.Show(window);
    s2.Show(window);
    w.show(window);
    w2.show(window);
    window.display();
    // std::chrono::seconds sleepDuration(1);
    // std::this_thread::sleep_for(sleepDuration);
  }

  return 0;
}
