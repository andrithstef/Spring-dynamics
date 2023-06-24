#include "utils.h"

#include <cmath>

/**
 * Rotates a 2D point around a given origin by a specified angle.
 * 
 * @param p The point to be rotated.
 * @param origin The origin point around which the rotation occurs.
 * @param theta The angle of rotation in radians.
 * @return The rotated point after applying the specified rotation.
 */
sf::Vector2f rotatePoint(const sf::Vector2f &p,
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

float calculateTorque(sf::Vector2f r, sf::Vector2f force) {
  float rMagnitude = std::hypot(r.x, r.y);             // Magnitude of vector r
  float forceMagnitude = std::hypot(force.x, force.y); // Magnitude of vector F

  // Calculate the angle between the vectors r and F
  float angle = std::acos((r.x * force.x + r.y * force.y) /
                          (rMagnitude * forceMagnitude));

  // Calculate the sign of the torque based on the orientation of vectors r and
  // F
  float crossProduct = (r.x * force.y) - (r.y * force.x);
  float torque = rMagnitude * forceMagnitude * std::sin(angle) *
                 (crossProduct >= 0 ? 1 : -1);
  return torque;
}
