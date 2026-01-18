#include "snake.hpp"
#include "core/fundamentals/direction.hpp"
#include "core/fundamentals/position.hpp"
#include <memory>

SnakeNode::SnakeNode(const Position &pos) : pos(pos) {}

bool SnakeNode::operator==(const SnakeNode &other) const {
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

const Position &Snake::getHeadPosition() const { return head.get()->pos; }

void Snake::eat(const IFood &food) { pendingGrowth += food.eaterSizeEffect(); }

void Snake::move() {
  const auto tailPos = tail->pos;

  for (auto i = this->rbegin(); i != this->rend(); ++i) {
    auto &node = *i;
    if (node.frontNode) {
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

Snake::SnakeIterator Snake::begin() {
  return Snake::SnakeIterator(head.get(), tail);
}

Snake::SnakeIterator Snake::end() {
  return Snake::SnakeIterator(tail->backNode.get(), tail);
}

Snake::ReverseSnakeIterator Snake::rbegin() {
  return ReverseSnakeIterator(end());
}

Snake::ReverseSnakeIterator Snake::rend() {
  return ReverseSnakeIterator(begin());
}

Snake::ConstSnakeIterator Snake::begin() const {
  return Snake::ConstSnakeIterator(head.get(), tail);
}

Snake::ConstSnakeIterator Snake::end() const {
  return Snake::ConstSnakeIterator(tail->backNode.get(), tail);
}

Snake::ConstReverseSnakeIterator Snake::rbegin() const {
  return ConstReverseSnakeIterator(end());
}

Snake::ConstReverseSnakeIterator Snake::rend() const {
  return ConstReverseSnakeIterator(begin());
}
