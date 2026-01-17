#pragma once

enum class EventType { Input, Game };

struct Event {
  EventType eventType;
};
