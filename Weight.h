#include <SFML/Graphics.hpp>
#include <vector>

class Weight {

public:
  Weight(float mass, const sf::Vector2f &position, float rotation,
         const sf::Vector2f &size);

  void Update(float deltaTime, sf::RenderWindow &window);
  // void connectSpring(sf::Vector2f connectionPoint);
  // void disconnectSpring();
  void applyForce(const sf::Vector2f &force, const sf::Vector2f &position,
                  sf::RenderWindow &window);

  float getMass();
  float getRotation();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  float calculateTorque(sf::Vector2f r, sf::Vector2f force);

  void show(sf::RenderWindow &window);

private:
  sf::Vector2f rotatePoint(const sf::Vector2f &p, const sf::Vector2f &origin,
                           float theta);

private:
  float m_mass;
  float m_rotation;
  sf::Vector2f m_position; // upper right corner of the weight
  sf::Vector2f m_size;
  sf::Vector2f m_velocity;
  float m_angularVelocity;
  sf::Vector2f m_currentForce;
  float m_currentTorque;
  std::vector<int> connectedSprings;
};
