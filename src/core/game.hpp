#pragma once

#include "core/event.hpp"
#include "core/fundamentals/time.hpp"
#include "core/input/input.hpp"
#include "food/food_factory.hpp"
#include "snake/snake.hpp"
#include <memory>
#include <queue>
#include <vector>

class Game {
public:
  Game(int width, int height, std::unique_ptr<IFoodFactory> foodFactory,
       std::unique_ptr<const IInputHandler> inputHandler,
       const TimeContext &timeContext, int tickPerSecond);

  const int &getWidth() const;
  const int &getHeight() const;

  void update();
  bool isRunning() const;
  const int &getScore() const;
  const Snake &getSnake() const;
  const std::vector<std::unique_ptr<IFood>> &getAciveFoods() const;

protected:
  int width, height;
  int score;
  Snake snake;
  std::vector<std::unique_ptr<IFood>> activeFoods;
  std::unique_ptr<IFoodFactory> foodFactory;
  std::unique_ptr<const IInputHandler> inputHandler;

  const TimeContext &timeContext;
  float tickInterval;
  float tickAccumulator;

  void listenForInput();
  void handleEvents();
  void setSnakeDirection(Direction direction);
  void spawnFood();
  void checkFoodEaten();

  enum class GameEventType { RequestSpawnFood, FoodEaten };

  class GameEvent : Event {
  public:
    GameEvent(const GameEventType &gameEventType);
    GameEventType gameEventType;
  };

  class FoodEatenEvent : public GameEvent {
  public:
    FoodEatenEvent(std::unique_ptr<IFood> food);
    std::unique_ptr<IFood> food;
  };

  std::queue<std::unique_ptr<GameEvent>> eventQueue;
};
