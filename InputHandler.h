#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "EntityManager.h"
#include "GameState.h"
#include "Weight.h"

class InputHandler {
public:
  InputHandler();

  void handleInputs(sf::RenderWindow &window, EntityManager &entityManager);

private:
  void handleMouseClick(sf::Event &event, sf::RenderWindow &window,
                        EntityManager &entityManager);
  void handleKeyPress(sf::Event &event, sf::RenderWindow &window,
                      EntityManager &entityManager);
  void togglePause();

  void placeWeight();

  void handleStartPlacingWeight(sf::RenderWindow &window,
                                EntityManager &entityManager);

  void handleStartPlacingSpring(sf::RenderWindow &window,
                                EntityManager &entityManager);

  void handleFinishPlacingSpring(sf::Vector2f position);

private:
  GameState &m_gameState;
  Weight *m_clickedWeight = nullptr;
  Spring *m_clickedSpring = nullptr;
  bool m_isPlacingWeight = false;
  bool m_isPlacingSpring = false;
  sf::Vector2f getWorldPosition(sf::RenderWindow &window);
};
