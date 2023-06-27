#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#include "EntityManager.h"
#include "InputHandler.h"

InputHandler::InputHandler() : m_gameState(GameState::getInstance()) {}

void InputHandler::handleInputs(sf::RenderWindow &window,
                                EntityManager &entityManager) {

  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
    else if (event.type == sf::Event::MouseButtonPressed) {
      handleMouseClick(event, window, entityManager);
    } else if (event.type == sf::Event::KeyPressed) {
      handleKeyPress(event, window, entityManager);
    } else if (event.type == sf::Event::MouseButtonReleased &&
               event.mouseButton.button == sf::Mouse::Left) {
      // Reset the pressed state of all weights
      if (m_clickedWeight != nullptr) {
        m_clickedWeight->setIsPressed(false);
      }
      m_clickedWeight = nullptr;
      m_isPlacingWeight = false;
    }
  }
}

void InputHandler::handleKeyPress(sf::Event &event, sf::RenderWindow &window,
                                  EntityManager &entityManager) {
  if (event.key.code == sf::Keyboard::Escape) {
    togglePause();
  } else if (event.key.code == sf::Keyboard::W) {

    if (m_isPlacingWeight || m_isPlacingSpring) {
      return;
    }
    // Reset the pressed state of all weights
    if (m_clickedWeight != nullptr) {
      m_clickedWeight->setIsPressed(false);
    }
    m_isPlacingWeight = true;
    handleStartPlacingWeight(window, entityManager);
  } else if (event.key.code == sf::Keyboard::S) {
    if (m_isPlacingSpring) {
      return;
    }
    if (m_clickedWeight != nullptr) {
      m_clickedWeight->setIsPressed(false);
    }
    m_clickedWeight = nullptr;
    handleStartPlacingSpring(window, entityManager);
  }
}

void InputHandler::handleStartPlacingWeight(sf::RenderWindow &window,
                                            EntityManager &entityManager) {
  m_isPlacingSpring = false;
  m_clickedSpring = nullptr;

  // Create a weight at the mouse location
  sf::Vector2f worldPosition = getWorldPosition(window);

  Weight *w = new Weight(worldPosition);
  entityManager.addWeight(w);
  m_clickedWeight = w;
  w->setIsPressed(true);
}

void InputHandler::handleStartPlacingSpring(sf::RenderWindow &window,
                                            EntityManager &entityManager) {
  m_clickedWeight = nullptr;
  m_isPlacingWeight = false;
  m_isPlacingSpring = true;
  sf::Vector2f p1 = getWorldPosition(window);

  Weight *startWeight = entityManager.getWeightFromPosition(p1);
  if (startWeight != nullptr) {
    // the spring starts on a weight
    // need to convert from global coordinates to local coordinates
    p1 = startWeight->globalToLocalCoordinates(p1);
    if (std::isnan(p1.x) || std::isnan(p1.y)) {
      p1 = sf::Vector2f(0.f, 0.f);
    }
  }

  sf::Vector2f p2 = getWorldPosition(window);
  Spring *s = new Spring(p1, p2, startWeight, nullptr);
  m_clickedSpring = s;
  s->setIsBeingPlaced(true);
  entityManager.addSpring(s);
}

void InputHandler::handleMouseClick(sf::Event &event, sf::RenderWindow &window,
                                    EntityManager &entityManager) {
  if (event.mouseButton.button == sf::Mouse::Left) {
    if (m_isPlacingWeight) {
      placeWeight();
      return;
    }

    sf::Vector2f worldPosition = getWorldPosition(window);

    // Handle the mouse click at the world position
    // You can now use the worldPosition to perform further operations
    m_clickedWeight = entityManager.getWeightFromPosition(worldPosition);

    if (m_isPlacingSpring) {
      handleFinishPlacingSpring(worldPosition);
      return;
    }

    if (m_clickedWeight != nullptr) {
      // Weight found at the clicked position
      m_clickedWeight->press(worldPosition);
    }
  }
}

void InputHandler::handleFinishPlacingSpring(sf::Vector2f position) {
  if (m_clickedWeight == nullptr) {
    m_clickedSpring->setEndPoint(position);
  } else {
    m_clickedSpring->setEndPoint(
        m_clickedWeight->globalToLocalCoordinates(position));
    m_clickedSpring->setEndPointWeight(m_clickedWeight);
  }
  m_clickedSpring->setIsBeingPlaced(false);
  m_clickedSpring = nullptr;
  m_isPlacingSpring = false;
  m_clickedWeight = nullptr;
}

void InputHandler::togglePause() {
  GameState &gameState = GameState::getInstance();
  gameState.setPaused(!gameState.isPaused());
}

void InputHandler::placeWeight() {
  m_clickedWeight->setIsPressed(false);
  m_clickedWeight = nullptr;
  m_isPlacingWeight = false;
}

sf::Vector2f InputHandler::getWorldPosition(sf::RenderWindow &window) {
  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
  return window.mapPixelToCoords(mousePosition);
}
