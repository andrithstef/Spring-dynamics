#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Weight {

public:
  Weight(const sf::Vector2f &position);

  void Update(float deltaTime, sf::RenderWindow &window);

  /**
   * Applies force to the weight.
   *
   * This function takes in a force on an object and uses it to update the total
   * force and torque on the weight.
   *
   * @param force The force vector on the weight.
   * @param location The local coordinates of the force.
   */
  void applyForce(const sf::Vector2f &force, const sf::Vector2f &position);

  float getMass();
  float getRotation();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  sf::Vector2f getVelocity();

  /*
   * Calculates the global coordinates for a local point
   */
  sf::Vector2f localToGlobalCoordinates(sf::Vector2f local) const;

  sf::Vector2f globalToLocalCoordinates(sf::Vector2f global) const;

  /*
   * Tells whether the weight overlaps the given position
   */
  bool overlapsPosition(const sf::Vector2f &position);

  void Show(sf::RenderWindow &window);

  void setIsPressed(bool isPressed);
  void press(sf::Vector2f location);

private:
  float getMomentOfInertia();

private:
  float m_mass = 0.1;
  float m_rotation = 0;
  sf::Vector2f m_position; // upper right corner of the weight
  sf::Vector2f m_size = sf::Vector2f(75.f, 75.f);
  sf::Vector2f m_velocity = sf::Vector2f(0.f, 0.f);
  float m_angularVelocity = 0.f;
  sf::Vector2f m_currentForce = sf::Vector2f(0.f, 0.f);
  float m_currentTorque = 0.f;
  bool m_isPressed = false;
  sf::Vector2f m_pressLocation = sf::Vector2f(37.5f, 37.5f);
  float m_drag = 0.5f;
  float m_angularDrag = 0.05f;
};
