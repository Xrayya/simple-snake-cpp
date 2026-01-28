#include "game_core/snake.hpp"
#include <ranges>

namespace actor {
SnakeNode::SnakeNode(const Position &pos, const Direction &direction)
    : central_pos_(pos), direction_(direction) {}

auto SnakeNode::operator==(const SnakeNode &other) const -> bool {
  return central_pos_ == other.central_pos_ &&
         back_node_.get() == other.back_node_.get() &&
         front_node_ == other.front_node_;
}

auto SnakeNode::getBackNode() const -> const std::unique_ptr<SnakeNode> & {
  return back_node_;
}

auto SnakeNode::setBackNode(std::unique_ptr<SnakeNode> newBackNode) -> void {
  back_node_ = std::move(newBackNode);
}

auto SnakeNode::getFrontNode() const -> SnakeNode * { return front_node_; }

auto SnakeNode::setFrontNode(SnakeNode *newFrontNode) -> void {
  front_node_ = newFrontNode;
}

auto SnakeNode::getCentralPosition() const -> const Position & {
  return central_pos_;
}

auto SnakeNode::setCentralPosition(const Position &pos) -> void {
  central_pos_ = pos;
}

auto SnakeNode::getOccupiedPositions() const -> std::vector<Position> {
  return {central_pos_};
}

auto SnakeNode::onUpdate() -> void {}

auto SnakeNode::getAdditionalScore() const -> const int & {
  static const int score = 0;
  return score;
}

auto SnakeNode::getEaterSizeEffect() const -> const int & {
  static const int sizeEffect = 1;
  return sizeEffect;
}

auto SnakeNode::onConsume() -> bool { return false; }

auto SnakeNode::getDirection() const -> const Direction & { return direction_; }

auto SnakeNode::setDirection(const Direction &dir) -> void { direction_ = dir; }

auto SnakeNode::onMove() -> void {
  if (front_node_ == nullptr) {
    return;
  }

  central_pos_.x_ = front_node_->central_pos_.x_;
  central_pos_.y_ = front_node_->central_pos_.y_;
}

Snake::Snake(const Position &pos, const Direction &direction)
    : direction_(direction),
      head_(std::make_unique<SnakeNode>(pos, direction_)) {
  switch (direction) {
  case Direction::Up:
    head_->setBackNode(std::make_unique<SnakeNode>(Position(pos.x_, pos.y_ + 1),
                                                   head_->getDirection()));
    break;
  case Direction::Down:
    head_->setBackNode(std::make_unique<SnakeNode>(Position(pos.x_, pos.y_ - 1),
                                                   head_->getDirection()));
    break;
  case Direction::Right:
    head_->setBackNode(std::make_unique<SnakeNode>(Position(pos.x_ - 1, pos.y_),
                                                   head_->getDirection()));
    break;
  case Direction::Left:
    head_->setBackNode(std::make_unique<SnakeNode>(Position(pos.x_ + 1, pos.y_),
                                                   head_->getDirection()));
    break;
  }

  head_->getBackNode()->setFrontNode(head_.get());
  tail_ = head_->getBackNode().get();
}

auto Snake::getLength() const -> const int & { return length_; }

auto Snake::getHead() const -> const std::unique_ptr<SnakeNode> & {
  return head_;
}

auto Snake::getTail() const -> SnakeNode * { return tail_; }

auto Snake::getCentralPosition() const -> const Position & {
  return head_->getCentralPosition();
}

auto Snake::setCentralPosition([[maybe_unused]] const Position &pos) -> void {}

auto Snake::getOccupiedPositions() const -> std::vector<Position> {
  std::vector<Position> positions;
  for (const auto &node : *this) {
    positions.push_back(node.getCentralPosition());
  }
  return positions;
}

auto Snake::onUpdate() -> void {}

auto Snake::canConsume([[maybe_unused]] const Consumable &consumable) const
    -> bool {
  return true;
}

auto Snake::consume(const Consumable &consumable) -> void {
  pending_growth_ += consumable.getEaterSizeEffect();
}

auto Snake::getDirection() const -> const Direction & { return direction_; }

auto Snake::setDirection(const Direction &newDirection) -> void {
  direction_ = newDirection;
}

auto Snake::onMove() -> void {
  if (pending_growth_ > 0) {
    tail_->setBackNode(std::make_unique<SnakeNode>(tail_->getCentralPosition(),
                                                   tail_->getDirection()));
    tail_->getBackNode()->setFrontNode(tail_);
    tail_ = tail_->getBackNode().get();

    pending_growth_--;
    length_++;
  }

  for (auto &node : std::ranges::reverse_view(*this)) {
    node.onMove();
  }

  switch (direction_) {
  case Direction::Up:
    head_->setCentralPosition(Position(head_->getCentralPosition().x_,
                                       head_->getCentralPosition().y_ - 1));
    break;
  case Direction::Down:
    head_->setCentralPosition(Position(head_->getCentralPosition().x_,
                                       head_->getCentralPosition().y_ + 1));
    break;
  case Direction::Left:
    head_->setCentralPosition(Position(head_->getCentralPosition().x_ - 1,
                                       head_->getCentralPosition().y_));
    break;
  case Direction::Right:
    head_->setCentralPosition(Position(head_->getCentralPosition().x_ + 1,
                                       head_->getCentralPosition().y_));
    break;
  }
}

auto Snake::begin() -> Snake::iterator {
  return iterator(
      IteratorConstructorParams<SnakeNode>{.node = head_.get(), .tail = tail_});
}

auto Snake::end() -> Snake::iterator {
  return iterator(IteratorConstructorParams<SnakeNode>{
      .node = tail_->getBackNode().get(), .tail = tail_});
}

auto Snake::rbegin() -> Snake::reverse_iterator {
  return reverse_iterator(end());
}

auto Snake::rend() -> Snake::reverse_iterator {
  return reverse_iterator(begin());
}

auto Snake::begin() const -> Snake::const_iterator {
  return const_iterator(IteratorConstructorParams<const SnakeNode>{
      .node = head_.get(), .tail = tail_});
}

auto Snake::end() const -> Snake::const_iterator {
  return Snake::const_iterator(IteratorConstructorParams<const SnakeNode>{
      .node = tail_->getBackNode().get(), .tail = tail_});
}

auto Snake::rbegin() const -> Snake::reverse_const_iterator {
  return reverse_const_iterator(end());
}

auto Snake::rend() const -> Snake::reverse_const_iterator {
  return reverse_const_iterator(begin());
}
} // namespace actor
