#pragma once

#include "core/food/food.hpp"
#include "core/fundamentals/direction.hpp"
#include "core/fundamentals/iterator.hpp"
#include "core/fundamentals/movable.hpp"
#include "core/fundamentals/position.hpp"
#include <memory>

struct SnakeNode {
  Position pos;
  std::unique_ptr<SnakeNode> backNode;
  SnakeNode *frontNode = nullptr;

  bool operator==(const SnakeNode &other) const;

  explicit SnakeNode(const Position &pos);
};

class Snake : public IMovable {
public:
  int length = 2;

  explicit Snake(const Position &pos, const Direction &direction);

  const Position &getHeadPosition() const;
  Direction direction;
  void eat(const IFood &food);
  void move() override;

  using SnakeIterator = Iterator<SnakeNode>;

  SnakeIterator begin();
  SnakeIterator end();

  using ReverseSnakeIterator = std::reverse_iterator<SnakeIterator>;

  ReverseSnakeIterator rbegin();
  ReverseSnakeIterator rend();





protected:
  std::unique_ptr<SnakeNode> head;
  SnakeNode *tail;
  int pendingGrowth = 0;
};
