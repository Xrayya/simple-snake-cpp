#pragma once

#include "core/fundamentals/event.hpp"
#include "core/fundamentals/time.hpp"
#include "core/input/input_event.hpp"
#include "food/food_factory.hpp"
#include "snake/snake.hpp"
#include <cstdint>
#include <memory>
#include <queue>
#include <vector>

class Game {
public:
  Game(int width, int height, std::unique_ptr<IFoodFactory> foodFactory,
       const TimeContext &timeContext, int tickPerSecond);

  [[nodiscard]] auto getWidth() const -> const int &;
  [[nodiscard]] auto getHeight() const -> const int &;

  void update();
  [[nodiscard]] auto isRunning() const -> bool;
  [[nodiscard]] auto getScore() const -> const int &;
  [[nodiscard]] auto getSnake() const -> const Snake &;
  [[nodiscard]] auto getAciveFoods() const
      -> const std::vector<std::unique_ptr<IFood>> &;

  void submitInputEvent(std::unique_ptr<event::Input> inputEvent);

private:
  int width, height;
  int score;
  Snake snake;
  std::vector<std::unique_ptr<IFood>> activeFoods;
  std::unique_ptr<IFoodFactory> foodFactory;
  std::unique_ptr<event::Input> pendingInput;

  const TimeContext &timeContext;
  float tickInterval;
  float tickAccumulator;

  void handleInput();
  void handleEvents();
  void setSnakeDirection(Direction direction);
  void spawnFood();
  void checkFoodEaten();

  enum class GameEventType : std::uint8_t { RequestSpawnFood, FoodEaten };

  class GameEvent : event::Event {
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
