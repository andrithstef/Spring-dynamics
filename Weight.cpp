#include <SFML/Graphics.hpp>
#include <cmath>
#include <limits>

#include "GameState.h"
#include "Weight.h"
#include "utils.h"

Weight::Weight(const sf::Vector2f &position) {
  m_position = position - m_size / 2.f;
}

void Weight::applyForce(const sf::Vector2f &force,
                        const sf::Vector2f &location) {

  // go from local coordinates to global coordinates
  sf::Vector2f globalLocation = localToGlobalCoordinates(location);

  // Create a vertex array to hold the line
  // sf::VertexArray line(sf::Lines, 2);
  // line[0].position = globalLocation;
  // line[1].position = globalLocation + 5.0f * force;
  // line[0].color = sf::Color::Blue;
  // line[1].color = sf::Color::Blue;

  // window.draw(line);

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
  if (m_isPressed) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f floatVector(static_cast<float>(mousePosition.x),
                             static_cast<float>(mousePosition.y));
    m_position = floatVector - m_pressLocation;
    return;
  }

  applyForce(sf::Vector2f(0.f, 100.f), m_size / 2.f); // gravity

  // a  = t/I
  // WHERE:
  //  a = angular velocity
  //  t = torque
  //  I = moment of inertia
  // Also introduce some angular drag so the system loses some energy with time
  m_angularVelocity += (m_currentTorque / getMomentOfInertia() -
                        m_angularDrag * m_angularVelocity) *
                       deltaTime;
  m_rotation += m_angularVelocity * deltaTime;

  // F = ma
  //  So dv = F/m * dt
  //  Also introduce drag so that the system loses energy over time
  m_velocity += (m_currentForce / m_mass - m_drag * m_velocity) * deltaTime;
  m_position += m_velocity * deltaTime;

  float maxX = window.getSize().x;
  float maxY = window.getSize().y;
  if (m_position.x <= 0.f || m_position.x + m_size.x >= maxX) {
    m_velocity.x *= -1.f;
    if (m_position.x <= 0.f) {
      m_position.x = 0.f;
    } else {
      m_position.x = maxX - m_size.x;
    }
  }

  if (m_position.y <= 0.f || m_position.y + m_size.y >= maxY) {
    m_velocity.y *= -1.f;
    if (m_position.y <= 0.f) {
      m_position.y = 0.f;
    } else {
      m_position.y = maxY - m_size.y;
    }
  }

  float maxSpeed = 5000;
  float speed = std::hypot(m_velocity.x, m_velocity.y);
  if (speed >= maxSpeed) {
    m_velocity = m_velocity / speed * maxSpeed;
  }

  // reset all forces and torques
  m_currentForce = sf::Vector2f(0.f, 0.f);
  m_currentTorque = 0.f;
}

void Weight::Show(sf::RenderWindow &window) {
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
                     m_rotation * M_PI / 180);
}

sf::Vector2f Weight::globalToLocalCoordinates(sf::Vector2f global) const {
  // Go from global coordinates to local coordinates

  // Undo the rotation by applying the inverse rotation
  global =
      rotatePoint(global, m_position + m_size / 2.f, -m_rotation * M_PI / 180);

  // Undo the translation by subtracting the position
  sf::Vector2f local = global - m_position;

  return local;
}

bool Weight::overlapsPosition(const sf::Vector2f &position) {
  if (position.x < m_position.x || position.x > m_position.x + m_size.x) {
    return false;
  }
  if (position.y < m_position.y || position.y > m_position.y + m_size.y) {
    return false;
  }
  return true;
}

sf::Vector2f Weight::getVelocity() { return m_velocity; }

float Weight::getMomentOfInertia() {
  return (m_mass * m_size.x * m_size.x / 12);
}

void Weight::setIsPressed(bool isPressed) { m_isPressed = isPressed; }

sf::Vector2f Weight::getPosition() { return m_position; }

void Weight::press(sf::Vector2f location) {
  m_isPressed = true;
  m_pressLocation = location - m_position;
}

sf::Vector2f Weight::getSize() { return m_size; }
