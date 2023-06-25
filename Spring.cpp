#include "Spring.h"
#include <cmath>
#include <iostream>
#include <limits>

Spring::Spring(float length, float K, sf::Vector2f p1, sf::Vector2f p2,
               Weight *connectedWeight1, Weight *connectedWeight2)
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
        (force - 0.01f * std::hypot(m_connectedWeight1->getVelocity().x,
                                    m_connectedWeight1->getVelocity().y));
    m_connectedWeight1->applyForce(forceVec1, m_p1, window);
  }

  if (m_connectedWeight2 != nullptr) {
    sf::Vector2f forceVec2 =
        diff / magnitude *
        (force - 0.01f * std::hypot(m_connectedWeight2->getVelocity().x,
                                    m_connectedWeight2->getVelocity().y));
    m_connectedWeight2->applyForce(-forceVec2, m_p2, window);
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

  // line[0].position = endPoint1;
  // line[1].position = endPoint2;
  // line[0].color = sf::Color::Red;
  // line[1].color = sf::Color::Red;

  // window.draw(line);



    sf::Vector2f a = endPoint1;
    sf::Vector2f b = endPoint2;

    sf::VertexArray wave(sf::LineStrip);
    wave.setPrimitiveType(sf::LineStrip);

    // Define the properties of the sine wave
    float amplitude = 10.0f;   // Amplitude of the wave
    int numPoints = 500;        // Number of points on the curve

    // Calculate the angle between a and b
    float angle = std::atan2(b.y - a.y, b.x - a.x);
    angle = 3.1415f/2.f;
    float dist = std::hypot(a.x-b.x, a.y-b.y);

    for (int i = 0; i <= numPoints; ++i)
    {
        float t = static_cast<float>(i) / numPoints;
        float x = a.x + t * (b.x - a.x);
        float y = a.y + amplitude * std::sin(50/dist * 3.1415 * (x - a.x));

        // Rotate the point around point a
        sf::Vector2f rotatedPoint;
        rotatedPoint.x = std::cos(angle) * (x - a.x) - std::sin(angle) * (y - a.y) + a.x;
        rotatedPoint.y = std::sin(angle) * (x - a.x) + std::cos(angle) * (y - a.y) + a.y;

        wave.append(sf::Vertex(rotatedPoint, sf::Color::Red));
    }

  window.draw(wave);
}
