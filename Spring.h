#pragma once
#include "Weight.h"
#include <SFML/Graphics.hpp>

class Spring {

public:
  Spring(sf::Vector2f p1, sf::Vector2f p2, Weight *connectedWeight1,
         Weight *connectedWeight2);

  void Update(float deltaTime, sf::RenderWindow &window);

  void Show(sf::RenderWindow &window);

  void setIsBeingPlaced(bool isBeingPlaced) { m_isBeingPlaced = isBeingPlaced; }
  void setEndPointWeight(Weight *w) { m_connectedWeight2 = w; }

  void setEndPoint(sf::Vector2f p2) { m_p2 = p2; }

private:
  float m_length = 200.f; // the relaxed length of the spring
  float m_K = 1.5f;       // elasticity of the spring

  // The connection points are in global coordinates
  sf::Vector2f m_p1; // connection point 1
  sf::Vector2f m_p2; // connection point 2

  Weight *m_connectedWeight1;
  Weight *m_connectedWeight2;

  bool m_isBeingPlaced = false;
};
