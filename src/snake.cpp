#include "snake.hpp"
#include "direction.hpp"

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
