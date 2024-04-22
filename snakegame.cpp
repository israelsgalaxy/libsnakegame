#include <algorithm>

#include "snakegame.h"

SnakeGame::SnakeGame(int gridSize) : m_gridSize(gridSize) { AddFood(); }

SnakeGame::MoveResult SnakeGame::MoveSnake(Direction direction) {
  if (!m_bodyPositions.empty()) {
    if ((direction == Direction::Right &&
         m_currentDirection == Direction::Left) ||
        (direction == Direction::Left &&
         m_currentDirection == Direction::Right) ||
        (direction == Direction::Up && m_currentDirection == Direction::Down) ||
        (direction == Direction::Down && m_currentDirection == Direction::Up)) {
      return MoveResult::Grid;
    }
  }

  m_currentDirection = direction;

  if (direction == Direction::Halt) {
    return MoveResult::Grid;
  }

  m_bodyPositions.push_front(m_headPosition);

  switch (direction) {
  case Direction::Left:
    m_headPosition.first =
        (m_headPosition.first == 0 ? m_gridSize : m_headPosition.first) - 1;
    break;
  case Direction::Right:
    m_headPosition.first =
        (m_headPosition.first == m_gridSize - 1 ? -1 : m_headPosition.first) +
        1;
    break;
  case Direction::Up:
    m_headPosition.second =
        (m_headPosition.second == 0 ? m_gridSize : m_headPosition.second) - 1;
    break;
  case Direction::Down:
    m_headPosition.second =
        (m_headPosition.second == m_gridSize - 1 ? -1 : m_headPosition.second) +
        1;
    break;
  }

  if (std::find(m_bodyPositions.begin(), m_bodyPositions.end(),
                m_headPosition) != m_bodyPositions.end()) {
    Reset();
    return MoveResult::Body;
  }

  if (m_headPosition == m_foodPosition) {
    AddFood();
    return MoveResult::Food;
  }

  m_bodyPositions.pop_back();
  return MoveResult::Grid;
}

void SnakeGame::AddFood() {
  std::pair<int, int> newFood{udist(mt), udist(mt)};

  while (m_foodPosition == newFood || m_headPosition == newFood ||
         (std::find(m_bodyPositions.begin(), m_bodyPositions.end(), newFood) !=
          m_bodyPositions.end())) {
    newFood = {udist(mt), udist(mt)};
  }

  m_foodPosition = newFood;
}

void SnakeGame::Reset() {
  m_headPosition = {0, 0};
  m_foodPosition = {0, 0};
  AddFood();
  m_bodyPositions.clear();
  m_currentDirection = Direction::Halt;

  std::seed_seq ss{rd()};
  mt.seed(ss);
}

const std::pair<int, int> &SnakeGame::GetHeadPosition() {
  return m_headPosition;
}

const std::pair<int, int> &SnakeGame::GetFoodPosition() {
  return m_foodPosition;
}

const std::deque<std::pair<int, int>> &SnakeGame::GetBodyPositions() {
  return m_bodyPositions;
}
