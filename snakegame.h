#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <deque>
#include <random>
#include <utility>

class SnakeGame {
public:
  SnakeGame(int gridSize);

  enum class Direction { Left, Right, Up, Down, Halt };
  enum class MoveResult { Food, Body, Grid };

  MoveResult MoveSnake(Direction direction);
  const std::pair<int, int> &GetHeadPosition();
  const std::pair<int, int> &GetFoodPosition();
  const std::deque<std::pair<int, int>> &GetBodyPositions();
  void Reset();

private:
  int m_gridSize;
  std::pair<int, int> m_headPosition{0, 0};
  std::pair<int, int> m_foodPosition{0, 0};
  std::deque<std::pair<int, int>> m_bodyPositions;
  Direction m_currentDirection = Direction::Halt;

  std::random_device rd;
  std::seed_seq ss{rd()};
  std::mt19937 mt{ss};
  std::uniform_int_distribution<int> udist{0, m_gridSize - 1};

  void AddFood();
};
#endif