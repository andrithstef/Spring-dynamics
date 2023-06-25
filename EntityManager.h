#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Spring.h"
#include "Weight.h"

class EntityManager {

public:
  EntityManager();

  /*
   * Update all entities stored in the entityManager
   */
  void Update(float deltaTime, sf::RenderWindow &window);

  /*
   * Render all entities stored in the entityManager
   */
  void Show(sf::RenderWindow &window);

  Weight *getWeightFromPosition(const sf::Vector2f &position);

  void addWeight(Weight *w);
  void addSpring(Spring *s);

  void printStatus() {
    std::cout << m_weights.size() << std::endl;
    std::cout << m_springs.size() << std::endl;
  }

private:
  std::vector<Weight *> m_weights;
  std::vector<Spring *> m_springs;
};
