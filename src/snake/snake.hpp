#pragma once

#include "../core/movable.hpp"
#include "../core/position.hpp"
#include "../food/food.hpp"
#include "snake_node.hpp"
#include <memory>

class Snake : public IMovable {
public:
  int length = 1;

  explicit Snake(Position pos);

  void move(Direction direction) override;
  int eat(IFood &food);

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

private:
  std::unique_ptr<SnakeNode> head;
  SnakeNode *tail;
  Position lastTailPosition;

  void grow();
};
