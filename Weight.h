#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Weight {

public:
  Weight(float mass, const sf::Vector2f &position, float rotation,
         const sf::Vector2f &size);

  void Update(float deltaTime, sf::RenderWindow &window);
  void applyForce(const sf::Vector2f &force, const sf::Vector2f &position,
                  sf::RenderWindow &window);

  float getMass();
  float getRotation();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();

  /*
   * Calculates the global coordinates for a local point
   */
  sf::Vector2f localToGlobalCoordinates(sf::Vector2f local) const;

  void show(sf::RenderWindow &window);

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
