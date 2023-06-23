#include "Weight.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <iostream>
#include <limits>

Weight::Weight(float mass, const sf::Vector2f &position, float rotation,
               const sf::Vector2f &size)
    : m_mass(mass), m_position(position), m_rotation(rotation), m_size(size),
      m_velocity(0.f, 0.f), m_angularVelocity(0.f), m_currentTorque(0.f),
      m_currentForce(sf::Vector2f(0.f, 0.f)) {}

/**
 * Applies force to the weight.
 *
 * This function takes in a force on an object and uses it to update the total
 * force and torque on the weight.
 *
 * @param force The force vector on the weight.
 * @param location The local coordinates of the force.
 */
void Weight::applyForce(const sf::Vector2f &force, const sf::Vector2f &location,
                        sf::RenderWindow &window) {

  // go from local coordinates to global coordinates
  sf::Vector2f globalLocation =
      rotatePoint(location + m_position, m_position + m_size / 2.f,
                  m_rotation * 3.1415 / 180);


  // Create a vertex array to hold the line
  sf::VertexArray line(sf::Lines, 2);
  line[0].position = globalLocation - m_size / 2.f;
  line[1].position = globalLocation - m_size / 2.f + 100.0f * force;
  line[0].color = sf::Color::Blue;
  line[1].color = sf::Color::Blue;

  window.draw(line);

  m_currentForce += force;

  sf::Vector2f diff = globalLocation - (m_position + m_size / 2.f);
  float l = std::sqrt(diff.x * diff.x + diff.y * diff.y);

  if (l <= std::numeric_limits<float>::epsilon()) {
    // The force is so close to the center, that no torque will happen
    return;
  }

  float torque =
      calculateTorque(diff, force);

  m_currentTorque += torque;

    std::cout << m_velocity.y << std::endl;
}

void Weight::Update(float deltaTime, sf::RenderWindow &window) {
  m_currentForce = sf::Vector2f(0.f, 0.f);
  m_currentTorque = 0.f;
  // calculate all forces acting on the weight

  applyForce(sf::Vector2f(10.f, 5.f), sf::Vector2f(0.f, 0.f),
             window); // gravity

  m_angularVelocity += (m_currentTorque / 10) * deltaTime;
  m_rotation += m_angularVelocity * deltaTime;

  m_velocity += m_currentForce / m_mass * deltaTime;
  m_position += m_velocity * deltaTime;
}

void Weight::show(sf::RenderWindow &window) {
  sf::RectangleShape shape(m_size);
  shape.setPosition(m_position);
  shape.setOrigin(m_size / 2.f);
  shape.setRotation(m_rotation);
  shape.setFillColor(sf::Color::White);

  window.draw(shape);
}

sf::Vector2f Weight::rotatePoint(const sf::Vector2f &p,
                                 const sf::Vector2f &origin, float theta) {
  sf::Vector2f translated = p - origin;

  float cosTheta = std::cos(theta);
  float sinTheta = std::sin(theta);

  sf::Vector2f rotated;
  rotated.x = translated.x * cosTheta - translated.y * sinTheta;
  rotated.y = translated.x * sinTheta + translated.y * cosTheta;

  sf::Vector2f result = rotated + origin;
  return result;
}

float Weight::calculateTorque(sf::Vector2f r, sf::Vector2f force) {
    float rMagnitude = std::hypot(r.x, r.y);  // Magnitude of vector r
    float forceMagnitude = std::hypot(force.x, force.y);  // Magnitude of vector F
    
    // Calculate the angle between the vectors r and F
    float angle = std::acos((r.x * force.x + r.y * force.y) / (rMagnitude * forceMagnitude));
    
    // Calculate the sign of the torque based on the orientation of vectors r and F
    float crossProduct = (r.x * force.y) - (r.y * force.x);
    float torque = rMagnitude * forceMagnitude * std::sin(angle) * (crossProduct >= 0 ? 1 : -1);
    return torque;
}
