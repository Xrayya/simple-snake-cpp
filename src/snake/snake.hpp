#pragma once

#include "../core/movable.hpp"
#include "../core/position.hpp"
#include <memory>

struct SnakeNode {
  Position pos;
  std::unique_ptr<SnakeNode> backNode;
  SnakeNode *frontNode = nullptr;

  explicit SnakeNode(Position pos);
};

class Snake : public IMovable {
public:
  int length = 1;

  explicit Snake(Position pos);

  const Position &getHeadPosition() const;
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

private:
  std::unique_ptr<SnakeNode> head;
  SnakeNode *tail;
  Position lastTailPosition;

  void grow();
};
