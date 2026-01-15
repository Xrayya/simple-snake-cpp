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

  void move(Direction direction) override;
  int eat(IFood &food);

  class Iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = SnakeNode;
    using difference_type = std::ptrdiff_t;
    using pointer = SnakeNode *;
    using reference = SnakeNode &;

    explicit Iterator(SnakeNode *node, SnakeNode *tail)
        : current(node), tail(tail) {}

    reference operator*() const { return *current; }
    pointer operator->() const { return current; }

    Iterator &operator++() {
      current = current->backNode.get();
      return *this;
    }

    Iterator operator++(int) {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }

    Iterator &operator--() {
      if (current == nullptr) {
        current = tail;
      } else {
        current = current->frontNode;
      }
      return *this;
    }

    Iterator operator--(int) {
      auto tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }

  private:
    SnakeNode *current;
    SnakeNode *tail;
  };

  Iterator begin() { return Iterator(head.get(), tail); }
  Iterator end() { return Iterator(tail->backNode.get(), tail); }

  using ReverseIterator = std::reverse_iterator<Iterator>;

  ReverseIterator rbegin() { return ReverseIterator(end()); }
  ReverseIterator rend() { return ReverseIterator(begin()); }

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
