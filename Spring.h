#pragma once
#include "Weight.h"
#include <SFML/Graphics.hpp>

class Spring {

public:
  Spring(float length, float K, sf::Vector2f p1, sf::Vector2f p2,
         Weight *connectedWeight1, Weight *connectedWeight2);

  void Update(float deltaTime, sf::RenderWindow &window);

  void Show(sf::RenderWindow &window);

private:
  float m_length; // the relaxed length of the spring
  float m_K;      // elasticity of the spring

  // The connection points are in global coordinates
  sf::Vector2f m_p1; // connection point 1
  sf::Vector2f m_p2; // connection point 2

  Weight *m_connectedWeight1;
  Weight *m_connectedWeight2;
};
