#include "game.hpp"
#include "core/fundamentals/direction.hpp"
#include <memory>

Game::Game(int width, int height, std::unique_ptr<IFoodFactory> foodFactory,
           std::unique_ptr<const IInputHandler> inputHandler,
           const TimeContext &timeContext, int tickPerSecond)
    : width(width), height(height), score(0),
      snake(Position(width / 2, height / 2), Direction::Left),
      foodFactory(std::move(foodFactory)),
      inputHandler(std::move(inputHandler)), timeContext(timeContext),
      tickInterval(1.0f / tickPerSecond), tickAccumulator(0.0f) {
  spawnFood();
}

const int &Game::getWidth() const { return width; }

const int &Game::getHeight() const { return height; }

void Game::update() {
  tickAccumulator += timeContext.getDeltaTime();
  listenForInput();

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

bool Game::isRunning() const {
  const auto &snakeHeadPos = snake.getHeadPosition();

  // Check collision with self
  for (const auto &node : const_cast<Snake &>(snake)) {
    if (node.pos == snakeHeadPos &&
        node != *const_cast<Snake &>(snake).begin()) {
      return false;
    }
  }

  // Check collision with boundaries
  if (snakeHeadPos.x < 0 || snakeHeadPos.y < 0 || snakeHeadPos.y >= height ||
      snakeHeadPos.x >= width) {
    return false;
  }

  return true;
}

const int &Game::getScore() const { return score; }

const Snake &Game::getSnake() const { return snake; }

const std::vector<std::unique_ptr<IFood>> &Game::getAciveFoods() const {
  return activeFoods;
}

void Game::listenForInput() {
  auto event = inputHandler->poll();
  if (event->inputType == InputType::Direction) {
    auto directionEvent =
        static_cast<InputEventDirection *>(std::move(event).get());
    setSnakeDirection(directionEvent->direction);
  }
}

void Game::setSnakeDirection(Direction direction) {
  if (isOppositeDirection(snake.direction, direction)) {
    return;
  }

  snake.direction = direction;
}

void Game::checkFoodEaten() {
  const auto &snakeHeadPos = snake.getHeadPosition();

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
      const auto &ateFoodEvent = static_cast<FoodEatenEvent &>(*gameEvent);
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

Game::GameEvent::GameEvent(const GameEventType &gameEventType) {
  eventType = EventType::Game;
  this->gameEventType = gameEventType;
}

Game::FoodEatenEvent::FoodEatenEvent(std::unique_ptr<IFood> food)
    : GameEvent(GameEventType::FoodEaten), food(std::move(food)) {}
