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
  explicit Snake(Position pos)
      : head(std::make_unique<SnakeNode>(pos)), tail(head.get()),
        lastTailPosition(pos) {}

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
