#include "Spring.h"
#include <cmath>
#include <iostream>
#include <limits>

Spring::Spring(float length, float K, const sf::Vector2f &p1,
               const sf::Vector2f &p2, Weight *connectedWeight1,
               Weight *connectedWeight2)
    : m_length(length), m_K(K), m_p1(p1), m_p2(p2),
      m_connectedWeight1(connectedWeight1),
      m_connectedWeight2(connectedWeight2) {}

void Spring::Update(float deltaTime, sf::RenderWindow &window) {
  // calculate the force using hooks law

  // need the current length of the spring
  // get global coordinates of both endpoints
  sf::Vector2f endPoint1 = m_p1;
  if (m_connectedWeight1 != nullptr) {
    // the spring is connected to a weight at m_p1
    // need to convert from local to global coordinates
    endPoint1 = m_connectedWeight1->localToGlobalCoordinates(endPoint1);
  }
  std::cout << "Endpoint1: " << endPoint1.x << endPoint1.y << std::endl;

  sf::Vector2f endPoint2 = m_p2;
  if (m_connectedWeight2 != nullptr) {
    // The spring is connected to a weight at m_p2
    // need to convert from local to global coordinates
    endPoint2 = m_connectedWeight2->localToGlobalCoordinates(endPoint2);
  }
  std::cout << "Endpoint2: " << endPoint2.x << endPoint2.y << std::endl;

  // get the length of this vector
  sf::Vector2f diff = endPoint2 - endPoint1;

  float magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);

  if (std::abs(magnitude - m_length) <= 0.01) {
    // The force is so close to the center, that no torque will happen
    return;
  }

  // use hooks law for calculating foce magnitude
  float force = m_K * (magnitude - m_length);

  sf::Vector2f forceVec = diff / magnitude * force;

    std::cout << "Force: " << force << std::endl;

  if (m_connectedWeight1 != nullptr) {
    m_connectedWeight1->applyForce(forceVec, m_p1, window);
  }

  if (m_connectedWeight2 != nullptr) {
    m_connectedWeight2->applyForce(-forceVec, m_p2, window);
  }
}

void Spring::Show(sf::RenderWindow &window) {

  // Create a vertex array to hold the line
  sf::VertexArray line(sf::Lines, 2);

  // need the current length of the spring
  // get global coordinates of both endpoints
  sf::Vector2f endPoint1 = m_p1;

  if (m_connectedWeight1 != nullptr) {
    // the spring is connected to a weight at m_p1
    // need to convert from local to global coordinates
    endPoint1 = m_connectedWeight1->localToGlobalCoordinates(endPoint1);
  }

  sf::Vector2f endPoint2 = m_p2;
  if (m_connectedWeight2 != nullptr) {
    // The spring is connected to a weight at m_p2
    // need to convert from local to global coordinates
    endPoint2 = m_connectedWeight2->localToGlobalCoordinates(endPoint2);
  }

  line[0].position = endPoint1;
  line[1].position = endPoint2;
  line[0].color = sf::Color::Red;
  line[1].color = sf::Color::Red;

  window.draw(line);
}
