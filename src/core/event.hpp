#pragma once

enum class EventType { Input, Game };

struct Event {
  virtual ~Event() = default;
  EventType eventType;
};
