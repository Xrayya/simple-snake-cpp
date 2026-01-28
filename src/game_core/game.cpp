#include "game_core/game.hpp"
#include "game_core/consumable.hpp"
#include "game_core/layout.hpp"
#include <memory>

Game::Game(const Layout &layout, std::unique_ptr<IFoodFactory> foodFactory,
           std::shared_ptr<TimeContext> timeContext, const int &tickPerSecond)
    : layout_(layout), score_(0),
      snake_(Position(layout_.width_ / 2, layout_.height_ / 2),
             Direction::Left),
      food_factory_(std::move(foodFactory)),
      time_context_(std::move(timeContext)),
      tick_interval_(1.0F / static_cast<float>(tickPerSecond)),
      tick_accumulator_(0.0F) {
  spawnFood();
}

auto Game::getLayout() const -> const Layout & { return layout_; }

auto Game::update() -> void {
  tick_accumulator_ += time_context_->getDeltaTime();
  handleInput();

  if (tick_accumulator_ < tick_interval_) {
    return;
  }

  checkFoodEaten();
  handleEvents();

  for (auto &food : active_foods_) {
    food->onUpdate();
  }
  snake_.onMove();

  tick_accumulator_ -= tick_interval_;
}

auto Game::isRunning() const -> bool {
  const auto &snake_head_pos = snake_.getHead()->getCentralPosition();

  // Check collision with self
  for (const auto &node : snake_) {
    if (node.getCentralPosition() == snake_head_pos &&
        node != *snake_.begin()) {
      return false;
    }
  }

  // Check collision with boundaries
  return snake_head_pos.x_ >= 0 && snake_head_pos.y_ >= 0 &&
         snake_head_pos.y_ < layout_.height_ &&
         snake_head_pos.x_ < layout_.width_;
}

auto Game::getScore() const -> const int & { return score_; }

auto Game::getSnake() const -> const actor::Snake & { return snake_; }

auto Game::getAciveFoods() const
    -> const std::vector<std::unique_ptr<actor::Consumable>> & {
  return active_foods_;
}

auto Game::submitInputEvent(std::unique_ptr<event::Input> inputEvent) -> void {
  pending_input_ = std::move(inputEvent);
}

auto Game::handleInput() -> void {
  if (pending_input_) {
    const auto &key_input =
        dynamic_cast<event::KeyInput *>(pending_input_.get());

    if (key_input == nullptr) {
      return;
    }

    switch (key_input->key_code_) {
    case KeyCode::W:
    case KeyCode::ArrowUp:
      setSnakeDirection(Direction::Up);
      break;
    case KeyCode::S:
    case KeyCode::ArrowDown:
      setSnakeDirection(Direction::Down);
      break;
    case KeyCode::A:
    case KeyCode::ArrowLeft:
      setSnakeDirection(Direction::Left);
      break;
    case KeyCode::D:
    case KeyCode::ArrowRight:
      setSnakeDirection(Direction::Right);
      break;
    default:
      break;
    }

    pending_input_.reset();
  }
}

auto Game::setSnakeDirection(Direction direction) -> void {
  if (isOppositeDirection(std::make_pair(snake_.getDirection(), direction))) {
    return;
  }

  snake_.setDirection(direction);
}

auto Game::checkFoodEaten() -> void {
  const auto &snake_head_pos = snake_.getHead()->getCentralPosition();

  for (auto it = active_foods_.begin(); it != active_foods_.end(); ++it) {
    if ((*it)->getCentralPosition() == snake_head_pos) {
      event_queue_.emplace(std::make_unique<FoodEatenEvent>(std::move(*it)));
      active_foods_.erase(it);
      return;
    }
  }
}

auto Game::spawnFood() -> void {
  auto new_food = food_factory_->generate();

  // Ensure food does not spawn on the snake
  bool confict = true;
  while (confict) {
    confict = false;
    for (const auto &node : snake_) {
      if (node.getCentralPosition() == new_food->getCentralPosition()) {
        confict = true;
        new_food = food_factory_->generate();
        break;
      }
    }
  }

  active_foods_.emplace_back(std::move(new_food));
}

auto Game::handleEvents() -> void {
  while (!event_queue_.empty()) {
    const auto &gameE_event = event_queue_.front();
    switch (gameE_event->game_event_type_) {
    case GameEventType::FoodEaten: {
      const auto &consumable_eaten_event =
          dynamic_cast<FoodEatenEvent &>(*gameE_event);
      snake_.consume(*consumable_eaten_event.food);
      score_ += consumable_eaten_event.food->getAdditionalScore();
      event_queue_.emplace(
          std::make_unique<GameEvent>(GameEventType::RequestSpawnFood));
      break;
    }
    case GameEventType::RequestSpawnFood:
      spawnFood();
      break;
    }
    event_queue_.pop();
  }
}

Game::GameEvent::GameEvent(const GameEventType &gameEventType)
    : game_event_type_(gameEventType) {}

Game::FoodEatenEvent::FoodEatenEvent(std::unique_ptr<actor::Consumable> food)
    : GameEvent(GameEventType::FoodEaten), food(std::move(food)) {}
