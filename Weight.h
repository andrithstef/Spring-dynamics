#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Weight {

public:
  Weight(float mass, const sf::Vector2f &position, float rotation,
         const sf::Vector2f &size);

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
  void applyForce(const sf::Vector2f &force, const sf::Vector2f &position,
                  sf::RenderWindow &window);

  float getMass();
  float getRotation();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  sf::Vector2f getVelocity();

  /*
   * Calculates the global coordinates for a local point
   */
  sf::Vector2f localToGlobalCoordinates(sf::Vector2f local) const;

  /*
   * Tells whether the weight overlaps the given position
   */
  bool overlapsPosition(const sf::Vector2f &position);

  void Show(sf::RenderWindow &window);

private:
  float m_mass;
  float m_rotation;
  sf::Vector2f m_position; // upper right corner of the weight
  sf::Vector2f m_size;
  sf::Vector2f m_velocity;
  float m_angularVelocity;
  sf::Vector2f m_currentForce;
  float m_currentTorque;
};
