#include <cmath>

#include "Spring.h"

Spring::Spring(sf::Vector2f p1, sf::Vector2f p2, Weight *connectedWeight1,
               Weight *connectedWeight2)
    : m_p1(p1), m_p2(p2), m_connectedWeight1(connectedWeight1),
      m_connectedWeight2(connectedWeight2) {}

void Spring::Update(sf::RenderWindow &window) {
  if (m_isBeingPlaced) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f floatVector(static_cast<float>(mousePosition.x),
                             static_cast<float>(mousePosition.y));
    m_p2 = floatVector;
  }

  // calculate the force using hooks law

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

  // get the length of this vector
  sf::Vector2f diff = endPoint2 - endPoint1;

  float magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);

  if (std::abs(magnitude - m_length) <= 0.01) {
    // The force is so close to the center, that no torque will happen
    return;
  }

  // use hooks law for calculating foce magnitude
  float force = m_K * (magnitude - m_length);

  if (m_connectedWeight1 != nullptr) {

    sf::Vector2f forceVec1 =
        diff / magnitude *
        (force - 0.1f * std::hypot(m_connectedWeight1->getVelocity().x,
                                   m_connectedWeight1->getVelocity().y));
    m_connectedWeight1->applyForce(forceVec1, m_p1);
  }

  if (m_connectedWeight2 != nullptr) {
    sf::Vector2f forceVec2 =
        diff / magnitude *
        (force - 0.1f * std::hypot(m_connectedWeight2->getVelocity().x,
                                   m_connectedWeight2->getVelocity().y));
    m_connectedWeight2->applyForce(-forceVec2, m_p2);
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

  sf::VertexArray wave(sf::LineStrip);

  // Define the properties of the sine wave
  float amplitude = 10.0f; // Amplitude of the wave
  int numPoints = 500;     // Number of points on the curve

  // Calculate the angle between a and b
  float angle =
      std::atan2(endPoint2.y - endPoint1.y, endPoint2.x - endPoint1.x);

  float dist = std::hypot(endPoint1.x - endPoint2.x, endPoint1.y - endPoint2.y);

  for (int i = 0; i <= numPoints; ++i) {
    float t = static_cast<float>(i) / numPoints;
    float x = endPoint1.x + t * (dist);
    float y = endPoint1.y +
              amplitude * std::sin((50 / dist) * M_PI * (x - endPoint1.x));

    // Rotate the point around point a
    sf::Vector2f rotatedPoint;
    rotatedPoint.x = std::cos(angle) * (x - endPoint1.x) -
                     std::sin(angle) * (y - endPoint1.y) + endPoint1.x;
    rotatedPoint.y = std::sin(angle) * (x - endPoint1.x) +
                     std::cos(angle) * (y - endPoint1.y) + endPoint1.y;

    wave.append(sf::Vertex(rotatedPoint, sf::Color(50, 50, 50)));
  }

  window.draw(wave);
}
