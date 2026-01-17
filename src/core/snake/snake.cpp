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

Snake::Iterator::Iterator(SnakeNode *node, SnakeNode *tail)
    : current(node), tail(tail) {}

Snake::Iterator::reference Snake::Iterator::operator*() const {
  return *current;
}

Snake::Iterator::pointer Snake::Iterator::operator->() const { return current; }

Snake::Iterator &Snake::Iterator::operator++() {
  current = current->backNode.get();
  return *this;
}

Snake::Iterator Snake::Iterator::operator++(int) {
  auto tmp = *this;
  ++(*this);
  return tmp;
}

Snake::Iterator &Snake::Iterator::operator--() {
  if (current == nullptr) {
    current = tail;
  } else {
    current = current->frontNode;
  }
  return *this;
}

Snake::Iterator Snake::Iterator::operator--(int) {
  auto tmp = *this;
  --(*this);
  return tmp;
}

bool Snake::Iterator::operator==(const Iterator &other) const {
  return current == other.current;
}

bool Snake::Iterator::operator!=(const Iterator &other) const {
  return current != other.current;
}

Snake::Iterator Snake::begin() { return Snake::Iterator(head.get(), tail); }

Snake::Iterator Snake::end() {
  return Snake::Iterator(tail->backNode.get(), tail);
}

Snake::ReverseIterator Snake::rbegin() { return ReverseIterator(end()); }

Snake::ReverseIterator Snake::rend() { return ReverseIterator(begin()); }
