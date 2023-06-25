#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.h"
#include "Spring.h"
#include "Weight.h"

class EntityManager {

public:
  static EntityManager &getInstance();
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

private:
  EntityManager();
  EntityManager(const EntityManager &) = delete;
  EntityManager &operator=(const EntityManager &) = delete;
  std::vector<Weight *> m_weights;
  std::vector<Spring *> m_springs;
  GameState &m_gameState;
};
