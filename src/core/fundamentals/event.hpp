#pragma once

namespace event {
struct Event {
  Event() = default;

  Event(const Event &) = default;
  Event(Event &&) = delete;
  auto operator=(const Event &) -> Event & = default;
  auto operator=(Event &&) -> Event & = delete;

  virtual ~Event() = default;
};
} // namespace event
