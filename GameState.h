#pragma once

#include <SFML/Graphics/Rect.hpp>
class GameState {
private:
  bool m_paused;

public:
  static GameState &getInstance() {
    static GameState instance;
    return instance;
  }

  bool isPaused() const { return m_paused; }

  void setPaused(bool value) { m_paused = value; }


private:
  GameState() : m_paused(false) {}
  GameState(const GameState &) = delete;
  GameState &operator=(const GameState &) = delete;
};
