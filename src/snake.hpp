#pragma once

#include "direction.hpp"
#include "food.hpp"
#include "movable.hpp"
#include <cstddef>
#include <iterator>
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

  class Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = SnakeNode;
    using difference_type = std::ptrdiff_t;
    using pointer = SnakeNode *;
    using reference = SnakeNode &;

    explicit Iterator(SnakeNode *node) : current(node) {}

    reference operator*() const { return *current; }
    pointer operator->() const { return current; }

    Iterator &operator++() {
      current = current->backNode.get();
      return *this;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }

  private:
    SnakeNode *current;
  };

  Iterator begin() { return Iterator(head.get()); }
  Iterator end() { return Iterator(tail->backNode.get()); }

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
