#include "snake.hpp"
#include <memory>

Snake::Snake(Position pos) : head(std::make_unique<SnakeNode>(pos)) {
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

  lastTailPosition = tail->pos;
}

void Snake::grow() {
  tail->backNode = std::make_unique<SnakeNode>(lastTailPosition);
  tail->backNode->frontNode = tail;
  tail = tail->backNode.get();
}

void Snake::move(Direction direction) {
  lastTailPosition.x = tail->pos.x;
  lastTailPosition.y = tail->pos.y;

  auto frontNodePos = &tail->frontNode->pos;
  auto currentNode = tail->frontNode;
  while (currentNode->frontNode != nullptr) {
    tail->pos.x = frontNodePos->x;
    tail->pos.y = frontNodePos->y;
    currentNode = currentNode->frontNode;
  }

  switch (direction) {
  case Up:
    head->pos.y--;
    break;
  case Down:
    head->pos.y++;
    break;
  case Left:
    head->pos.x--;
    break;
  case Right:
    head->pos.x++;
    break;
  }
}

int Snake::eat(IFood &food) {
  grow();
  return food.scoreAddition();
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
