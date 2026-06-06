#pragma once

#include "app_core/input/input_event.hpp"
#include <cstdint>
#include <functional>
#include <utility>

namespace core {

enum class EventType : std::uint8_t {
  None = 0,
  KeyPressed,
  WindowClose,
  GameOver,
};

class Event {
public:
  virtual ~Event() = default;

  bool Handled = false;

  [[nodiscard]] virtual auto GetEventType() const -> EventType = 0;
  [[nodiscard]] virtual auto GetName() const -> const char * = 0;
};

class KeyPressedEvent : public Event {
public:
  explicit KeyPressedEvent(KeyCode keyCode) : key_code_(keyCode) {}

  static auto GetStaticType() -> EventType { return EventType::KeyPressed; }

  [[nodiscard]] auto GetEventType() const -> EventType override {
    return GetStaticType();
  }

  [[nodiscard]] auto GetName() const -> const char * override {
    return "KeyPressedEvent";
  }

  KeyCode key_code_;
};

class WindowCloseEvent : public Event {
public:
  static auto GetStaticType() -> EventType { return EventType::WindowClose; }

  [[nodiscard]] auto GetEventType() const -> EventType override {
    return GetStaticType();
  }

  [[nodiscard]] auto GetName() const -> const char * override {
    return "WindowCloseEvent";
  }
};

class GameOverEvent : public Event {
public:
  static auto GetStaticType() -> EventType { return EventType::GameOver; }

  [[nodiscard]] auto GetEventType() const -> EventType override {
    return GetStaticType();
  }

  [[nodiscard]] auto GetName() const -> const char * override {
    return "GameOverEvent";
  }
};

class EventDispatcher {
public:
  explicit EventDispatcher(Event &event) : event_(event) {}

  template <typename T, typename F> auto Dispatch(const F &func) -> bool {
    if (event_.GetEventType() != T::GetStaticType()) {
      return false;
    }

    event_.Handled = std::invoke(func, static_cast<T &>(event_));
    return true;
  }

private:
  Event &event_;
};

} // namespace core
