#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager() : m_weights(), m_springs() {}

void EntityManager::Update(float deltaTime, sf::RenderWindow &window) {
  for (auto &spring : m_springs) {
    spring->Update(deltaTime, window);
  }

  for (auto &weight : m_weights) {
    weight->Update(deltaTime, window);
  }
}

void EntityManager::Show(sf::RenderWindow &window) {

  for (auto spring : m_springs) {
    spring->Show(window);
  }

  for (auto weight : m_weights) {
    weight->Show(window);
  }
}

Weight *EntityManager::getWeightFromPosition(const sf::Vector2f &position) {
  for (auto weight : m_weights) {
    if (weight->overlapsPosition(position)) {
      return weight;
    }
  }
  return nullptr;
}

void EntityManager::addWeight(Weight *w) { m_weights.push_back(w); }

void EntityManager::addSpring(Spring *s) { m_springs.push_back(s); }
