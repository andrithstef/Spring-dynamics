#include "Weight.h"
#include "utils.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
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
  sf::Vector2f globalLocation = localToGlobalCoordinates(location);

  // Create a vertex array to hold the line
  sf::VertexArray line(sf::Lines, 2);
  line[0].position = globalLocation;
  line[1].position = globalLocation + 5.0f * force;
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

  float torque = calculateTorque(diff, force);

  if (std::isnan(torque)) {
    return;
  }

  m_currentTorque += torque;
}

void Weight::Update(float deltaTime, sf::RenderWindow &window) {
  // calculate all forces acting on the weight

  applyForce(sf::Vector2f(0.f, 200.f), m_size / 2.f,
             window); // gravity

  m_angularVelocity +=
      (m_currentTorque / (m_mass * m_size.x * m_size.x / 12)) * deltaTime;
  m_rotation += m_angularVelocity * deltaTime;

  m_velocity += m_currentForce / m_mass * deltaTime;
  m_position += m_velocity * deltaTime;

  m_currentForce = sf::Vector2f(0.f, 0.f);
  m_currentTorque = 0.f;
}

void Weight::show(sf::RenderWindow &window) {
  sf::RectangleShape shape(m_size);
  shape.setPosition(m_position + m_size / 2.f);
  shape.setOrigin(m_size / 2.f);
  shape.setRotation(m_rotation);
  shape.setFillColor(sf::Color::White);

  window.draw(shape);
}

sf::Vector2f Weight::localToGlobalCoordinates(sf::Vector2f local) const {
  // go from local coordinates to global coordinates
  return rotatePoint(local + m_position, m_position + m_size / 2.f,
                     m_rotation * 3.1415 / 180);
}
