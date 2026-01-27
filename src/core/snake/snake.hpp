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

  auto operator==(const SnakeNode &other) const -> bool;

  explicit SnakeNode(const Position &pos);
};

class Snake : public IMovable {
  int length = 2;
  Direction direction;
  std::unique_ptr<SnakeNode> head;
  SnakeNode *tail;
  int pendingGrowth = 0;

  template <typename T> struct IteratorConstructorParams {
    T *node;
    T *tail;
  };

  template <typename T> class Iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit Iterator(IteratorConstructorParams<T> iterParams)
        : current(iterParams.node), tail(iterParams.tail) {}

    auto operator*() const -> reference { return *current; }
    auto operator->() const -> pointer { return current; }

    auto operator++() -> Iterator & {
      current = current->backNode.get();
      return *this;
    }
    auto operator++(int) -> Iterator {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }

    auto operator--() -> Iterator & {
      if (current == nullptr) {
        current = tail;
      } else {
        current = current->frontNode;
      }
      return *this;
    }
    auto operator--(int) -> Iterator {
      auto tmp = *this;
      --(*this);
      return tmp;
    }

    auto operator==(const Iterator &other) const -> bool {
      return current == other.current;
    }
    auto operator!=(const Iterator &other) const -> bool {
      return current != other.current;
    }

  private:
    T *current;
    T *tail;
  };

public:
  explicit Snake(const Position &pos, const Direction &direction);

  [[nodiscard]] auto getLength() const -> int;

  auto setDirection(const Direction &newDirection) -> void;
  [[nodiscard]] auto getDirection() const -> Direction;

  [[nodiscard]] auto getHead() const -> const std::unique_ptr<SnakeNode> &;
  auto setHead(std::unique_ptr<SnakeNode>) -> void;

  [[nodiscard]] auto getTail() const -> SnakeNode *;
  auto setTail(SnakeNode *) -> void;

  auto eat(const IFood &food) -> void;
  auto move() -> void override;

  using SnakeIterator = Iterator<SnakeNode>;

  auto begin() -> SnakeIterator;
  auto end() -> SnakeIterator;

  using ReverseSnakeIterator = std::reverse_iterator<SnakeIterator>;

  auto rbegin() -> ReverseSnakeIterator;
  auto rend() -> ReverseSnakeIterator;

  using ConstSnakeIterator = Iterator<const SnakeNode>;

  [[nodiscard]] auto begin() const -> ConstSnakeIterator;
  [[nodiscard]] auto end() const -> ConstSnakeIterator;

  using ConstReverseSnakeIterator = std::reverse_iterator<ConstSnakeIterator>;

  [[nodiscard]] auto rbegin() const -> ConstReverseSnakeIterator;
  [[nodiscard]] auto rend() const -> ConstReverseSnakeIterator;
};
