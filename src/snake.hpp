#pragma once

#include "direction.hpp"
#include "food.hpp"
#include "movable.hpp"
#include <memory>

class SnakeNode {
public:
  Position pos;
  std::unique_ptr<SnakeNode> backNode;
  SnakeNode *frontNode = nullptr;

  explicit SnakeNode(Position pos) : pos(pos) {}
};

class Snake : public IMovable {
public:
  int length = 1;

  explicit Snake(Position pos)
      : head(std::make_unique<SnakeNode>(pos)), lastTailPosition(pos) {
    switch (direction) {
    case Up:
      head->backNode = std::make_unique<SnakeNode>(Position(pos.x, pos.y + 1));
      break;
    case Down:
      head->backNode = std::make_unique<SnakeNode>(Position(pos.x, pos.y - 1));
      break;
    case Right:
      head->backNode = std::make_unique<SnakeNode>(Position(pos.x - 1, pos.y));
      break;
    case Left:
      head->backNode = std::make_unique<SnakeNode>(Position(pos.x + 1, pos.y));
      break;
    }

    head->backNode->frontNode = head.get();
    tail = head->backNode.get();
  }

  void move(Direction direction) override;
  int eat(IFood &food);

private:
  std::unique_ptr<SnakeNode> head;
  SnakeNode *tail;
  Position lastTailPosition;

  void grow() {
    tail->backNode = std::make_unique<SnakeNode>(lastTailPosition);
    tail->backNode->frontNode = tail;
    tail = tail->backNode.get();
  }
};
