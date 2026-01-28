#pragma once

#include "app_core/input/input_event.hpp"
#include "game_core/consumable.hpp"
#include "game_core/food_factory.hpp"
#include "game_core/layout.hpp"
#include "game_core/snake.hpp"
#include "game_core/time.hpp"
#include <cstdint>
#include <memory>
#include <queue>
#include <vector>

class Game {
public:
  Game(const Layout &layout, std::unique_ptr<IFoodFactory> foodFactory,
       std::shared_ptr<TimeContext> timeContext, const int &tickPerSecond);

  [[nodiscard]] auto getLayout() const -> const Layout &;

  void update();
  [[nodiscard]] auto isRunning() const -> bool;
  [[nodiscard]] auto getScore() const -> const int &;
  [[nodiscard]] auto getSnake() const -> const actor::Snake &;
  [[nodiscard]] auto getAciveFoods() const
      -> const std::vector<std::unique_ptr<actor::Consumable>> &;

  void submitInputEvent(std::unique_ptr<event::Input> inputEvent);

private:
  Layout layout_;
  int score_;
  actor::Snake snake_;
  std::vector<std::unique_ptr<actor::Consumable>> active_foods_;
  std::unique_ptr<IFoodFactory> food_factory_;
  std::unique_ptr<event::Input> pending_input_;

  std::shared_ptr<TimeContext> time_context_;
  float tick_interval_;
  float tick_accumulator_;

  auto handleInput() -> void;
  auto handleEvents() -> void;
  auto setSnakeDirection(Direction direction) -> void;
  auto spawnFood() -> void;
  auto checkFoodEaten() -> void;

  enum class GameEventType : std::uint8_t { RequestSpawnFood, FoodEaten };

  class GameEvent : event::Event {
  public:
    GameEvent(const GameEventType &gameEventType);
    GameEventType game_event_type_;
  };

  class FoodEatenEvent : public GameEvent {
  public:
    FoodEatenEvent(std::unique_ptr<actor::Consumable> food);
    std::unique_ptr<actor::Consumable> food;
  };

  std::queue<std::unique_ptr<GameEvent>> event_queue_;
};
