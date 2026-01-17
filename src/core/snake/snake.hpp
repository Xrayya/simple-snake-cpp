#pragma once

#include "core/food/food.hpp"
#include "core/fundamentals/direction.hpp"
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

  class Iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = SnakeNode;
    using difference_type = std::ptrdiff_t;
    using pointer = SnakeNode *;
    using reference = SnakeNode &;

    explicit Iterator(SnakeNode *node, SnakeNode *tail);

    reference operator*() const;
    pointer operator->() const;

    Iterator &operator++();
    Iterator operator++(int);

    Iterator &operator--();
    Iterator operator--(int);

    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;

  private:
    SnakeNode *current;
    SnakeNode *tail;
  };

  Iterator begin();
  Iterator end();

  using ReverseIterator = std::reverse_iterator<Iterator>;

  ReverseIterator rbegin();
  ReverseIterator rend();

protected:
  std::unique_ptr<SnakeNode> head;
  SnakeNode *tail;
  int pendingGrowth = 0;
};
