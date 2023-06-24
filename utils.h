#pragma once

#include <SFML/Graphics.hpp>


sf::Vector2f rotatePoint(const sf::Vector2f &p, const sf::Vector2f &origin,
                         float theta);

/**
 * Calculates the torque magnitude based on the force vector and the radius vector.
 * 
 * @param r The radius vector from the center of mass to the point of application of the force.
 * @param force The force vector applied to the object.
 * @return The torque magnitude calculated based on the cross product of r and force.
 */
float calculateTorque(sf::Vector2f r, sf::Vector2f force);
