#include "snake.hpp"
#include "core/fundamentals/direction.hpp"
#include "core/fundamentals/position.hpp"
#include <memory>

SnakeNode::SnakeNode(const Position &pos) : pos(pos) {}

auto SnakeNode::operator==(const SnakeNode &other) const -> bool {
  return pos == other.pos && backNode.get() == other.backNode.get() &&
         frontNode == other.frontNode;
}

Snake::Snake(const Position &pos, const Direction &direction)
    : direction(direction), head(std::make_unique<SnakeNode>(pos)) {
  switch (direction) {
  case Direction::Up:
    head->backNode = std::make_unique<SnakeNode>(Position(pos.x, pos.y + 1));
    break;
  case Direction::Down:
    head->backNode = std::make_unique<SnakeNode>(Position(pos.x, pos.y - 1));
    break;
  case Direction::Right:
    head->backNode = std::make_unique<SnakeNode>(Position(pos.x - 1, pos.y));
    break;
  case Direction::Left:
    head->backNode = std::make_unique<SnakeNode>(Position(pos.x + 1, pos.y));
    break;
  }

  head->backNode->frontNode = head.get();
  tail = head->backNode.get();
}

auto Snake::getLength() const -> int { return length; }

auto Snake::setDirection(const Direction &newDirection) -> void {
  direction = newDirection;
}

auto Snake::getDirection() const -> Direction { return direction; }

auto Snake::getHead() const -> const std::unique_ptr<SnakeNode> & {
  return head;
}

auto Snake::setHead(std::unique_ptr<SnakeNode> newHead) -> void {
  head = std::move(newHead);
}

auto Snake::getTail() const -> SnakeNode * { return tail; }

auto Snake::setTail(SnakeNode *newTail) -> void { tail = newTail; }

void Snake::eat(const IFood &food) { pendingGrowth += food.eaterSizeEffect(); }

void Snake::move() {
  const auto tailPos = tail->pos;

  for (auto i = this->rbegin(); i != this->rend(); ++i) {
    auto &node = *i;
    if (node.frontNode != nullptr) {
      node.pos.x = node.frontNode->pos.x;
      node.pos.y = node.frontNode->pos.y;
    }
  }

  switch (direction) {
  case Direction::Up:
    head->pos.y--;
    break;
  case Direction::Down:
    head->pos.y++;
    break;
  case Direction::Left:
    head->pos.x--;
    break;
  case Direction::Right:
    head->pos.x++;
    break;
  }

  if (pendingGrowth > 0) {
    tail->backNode = std::make_unique<SnakeNode>(tailPos);
    tail->backNode->frontNode = tail;
    tail = tail->backNode.get();

    pendingGrowth--;
    length++;
  }
}

auto Snake::begin() -> Snake::SnakeIterator {
  return Snake::SnakeIterator(
      IteratorConstructorParams<SnakeNode>{.node = head.get(), .tail = tail});
}

auto Snake::end() -> Snake::SnakeIterator {
  return Snake::SnakeIterator(IteratorConstructorParams<SnakeNode>{
      .node = tail->backNode.get(), .tail = tail});
}

auto Snake::rbegin() -> Snake::ReverseSnakeIterator {
  return ReverseSnakeIterator(end());
}

auto Snake::rend() -> Snake::ReverseSnakeIterator {
  return ReverseSnakeIterator(begin());
}

auto Snake::begin() const -> Snake::ConstSnakeIterator {
  return ConstSnakeIterator(IteratorConstructorParams<const SnakeNode>{
      .node = head.get(), .tail = tail});
}

auto Snake::end() const -> Snake::ConstSnakeIterator {
  return Snake::ConstSnakeIterator(IteratorConstructorParams<const SnakeNode>{
      .node = tail->backNode.get(), .tail = tail});
}

auto Snake::rbegin() const -> Snake::ConstReverseSnakeIterator {
  return ConstReverseSnakeIterator(end());
}

auto Snake::rend() const -> Snake::ConstReverseSnakeIterator {
  return ConstReverseSnakeIterator(begin());
}
