#pragma once

#include "game_core/consumable.hpp"
#include "game_core/consumer.hpp"
#include "game_core/direction.hpp"
#include "game_core/movable.hpp"
#include "game_core/position.hpp"
#include <memory>

namespace actor {
class SnakeNode : public Consumable, public Movable {
public:
  SnakeNode(const Position &pos, const Direction &direction);

  auto operator==(const SnakeNode &other) const -> bool;

  [[nodiscard]] auto getBackNode() const -> const std::unique_ptr<SnakeNode> &;
  auto setBackNode(std::unique_ptr<SnakeNode>) -> void;

  [[nodiscard]] auto getFrontNode() const -> SnakeNode *;
  auto setFrontNode(SnakeNode *) -> void;

  [[nodiscard]] auto getCentralPosition() const -> const Position & override;
  auto setCentralPosition(const Position &pos) -> void override;

  [[nodiscard]] auto getOccupiedPositions() const
      -> std::vector<Position> override;

  auto onUpdate() -> void override;

  [[nodiscard]] auto getAdditionalScore() const -> const int & override;

  [[nodiscard]] auto getEaterSizeEffect() const -> const int & override;

  auto onConsume() -> bool override;

  [[nodiscard]] auto getDirection() const -> const Direction & override;
  auto setDirection(const Direction &dir) -> void override;

  auto onMove() -> void override;

private:
  Position central_pos_;
  Direction direction_;
  std::unique_ptr<SnakeNode> back_node_ = nullptr;
  SnakeNode *front_node_ = nullptr;
};

class Snake : public Consumer, public Movable {
  int length_ = 2;
  Direction direction_;
  std::unique_ptr<SnakeNode> head_;
  SnakeNode *tail_;
  int pending_growth_ = 0;

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

    Iterator() : current(nullptr), tail(nullptr) {}

    explicit Iterator(IteratorConstructorParams<T> iterParams)
        : current(iterParams.node), tail(iterParams.tail) {}

    auto operator*() const -> reference { return *current; }
    auto operator->() const -> pointer { return current; }

    auto operator++() -> Iterator & {
      // WARNING: if this break, probabbly because change of SnakeNode structure
      current = current->getBackNode().get();
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
        // WARNING: if this break, probabbly because change of SnakeNode
        // structure
        current = current->getFrontNode();
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
  Snake(const Position &pos, const Direction &direction);

  [[nodiscard]] auto getLength() const -> const int &;

  [[nodiscard]] auto getHead() const -> const std::unique_ptr<SnakeNode> &;

  [[nodiscard]] auto getTail() const -> SnakeNode *;

  [[nodiscard]] auto getCentralPosition() const -> const Position & override;
  auto setCentralPosition(const Position &pos) -> void override;

  [[nodiscard]] auto getOccupiedPositions() const
      -> std::vector<Position> override;

  auto onUpdate() -> void override;

  [[nodiscard]] auto canConsume(const Consumable &consumable) const
      -> bool override;

  auto consume(const Consumable &consumable) -> void override;

  [[nodiscard]] auto getDirection() const -> const Direction & override;
  auto setDirection(const Direction &newDirection) -> void override;

  auto onMove() -> void override;

  using iterator = Iterator<SnakeNode>;

  auto begin() -> iterator;
  auto end() -> iterator;

  using reverse_iterator = std::reverse_iterator<iterator>;

  auto rbegin() -> reverse_iterator;
  auto rend() -> reverse_iterator;

  using const_iterator = Iterator<const SnakeNode>;

  [[nodiscard]] auto begin() const -> const_iterator;
  [[nodiscard]] auto end() const -> const_iterator;

  using reverse_const_iterator = std::reverse_iterator<const_iterator>;

  [[nodiscard]] auto rbegin() const -> reverse_const_iterator;
  [[nodiscard]] auto rend() const -> reverse_const_iterator;
};
} // namespace actor
