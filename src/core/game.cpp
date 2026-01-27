#include "game.hpp"
#include "core/fundamentals/direction.hpp"
#include <memory>
#include <utility>

Game::Game(int width, int height, std::unique_ptr<IFoodFactory> foodFactory,
           const TimeContext &timeContext, int tickPerSecond)
    : width(width), height(height), score(0),
      snake(Position(width / 2, height / 2), Direction::Left),
      foodFactory(std::move(foodFactory)), timeContext(timeContext),
      tickInterval(1.0F / static_cast<float>(tickPerSecond)),
      tickAccumulator(0.0F) {
  spawnFood();
}

auto Game::getWidth() const -> const int & { return width; }

auto Game::getHeight() const -> const int & { return height; }

void Game::update() {
  tickAccumulator += timeContext.getDeltaTime();
  handleInput();

  if (tickAccumulator < tickInterval) {
    return;
  }

  checkFoodEaten();
  handleEvents();

  for (auto &food : activeFoods) {
    food->update();
  }
  snake.move();

  tickAccumulator -= tickInterval;
}

auto Game::isRunning() const -> bool {
  const auto &snakeHeadPos = snake.getHead()->pos;

  // Check collision with self
  for (const auto &node : snake) {
    if (node.pos == snakeHeadPos && node != *snake.begin()) {
      return false;
    }
  }

  // Check collision with boundaries
  return snakeHeadPos.x >= 0 && snakeHeadPos.y >= 0 &&
         snakeHeadPos.y < height && snakeHeadPos.x < width;
}

auto Game::getScore() const -> const int & { return score; }

auto Game::getSnake() const -> const Snake & { return snake; }

auto Game::getAciveFoods() const
    -> const std::vector<std::unique_ptr<IFood>> & {
  return activeFoods;
}

auto Game::submitInputEvent(std::unique_ptr<event::Input> inputEvent) -> void {
  pendingInput = std::move(inputEvent);
}

auto Game::handleInput() -> void {
  if (pendingInput) {
    const auto &keyInput = dynamic_cast<event::KeyInput *>(pendingInput.get());

    if (keyInput == nullptr) {
      return;
    }

    switch (keyInput->key_code_) {
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

    pendingInput.reset();
  }
}

void Game::setSnakeDirection(Direction direction) {
  if (isOppositeDirection(std::make_pair(snake.getDirection(), direction))) {
    return;
  }

  snake.setDirection(direction);
}

void Game::checkFoodEaten() {
  const auto &snakeHeadPos = snake.getHead()->pos;

  for (auto it = activeFoods.begin(); it != activeFoods.end(); ++it) {
    if ((*it)->position() == snakeHeadPos) {
      eventQueue.emplace(std::make_unique<FoodEatenEvent>(std::move(*it)));
      activeFoods.erase(it);
      return;
    }
  }
}

void Game::spawnFood() {
  auto newFood = foodFactory->generate();

  // Ensure food does not spawn on the snake
  bool confict = true;
  while (confict) {
    confict = false;
    for (const auto &node : snake) {
      if (node.pos == newFood->position()) {
        confict = true;
        newFood = foodFactory->generate();
        break;
      }
    }
  }

  activeFoods.emplace_back(std::move(newFood));
}

void Game::handleEvents() {
  while (!eventQueue.empty()) {
    const auto &gameEvent = eventQueue.front();
    switch (gameEvent->gameEventType) {
    case GameEventType::FoodEaten: {
      const auto &ateFoodEvent = dynamic_cast<FoodEatenEvent &>(*gameEvent);
      snake.eat(*ateFoodEvent.food);
      score += ateFoodEvent.food->additionalScore();
      eventQueue.emplace(
          std::make_unique<GameEvent>(GameEventType::RequestSpawnFood));
      break;
    }
    case GameEventType::RequestSpawnFood:
      spawnFood();
      break;
    }
    eventQueue.pop();
  }
}

Game::GameEvent::GameEvent(const GameEventType &gameEventType)
    : gameEventType(gameEventType) {}

Game::FoodEatenEvent::FoodEatenEvent(std::unique_ptr<IFood> food)
    : GameEvent(GameEventType::FoodEaten), food(std::move(food)) {}
