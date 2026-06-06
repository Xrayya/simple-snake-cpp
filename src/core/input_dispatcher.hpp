#pragma once

#include "core/event.hpp"
#include <memory>
#include <functional>

namespace core {

/**
 * InputDispatcher polls Raylib input and creates events.
 * 
 * This is NOT a layer—it's a SOURCE of events.
 * 
 * Usage:
 *   InputDispatcher input;
 *   input.SetEventCallback([&app](auto event) {
 *       app.SubmitEvent(std::move(event));
 *   });
 *   
 *   while (running) {
 *       input.Poll();  // Check OS input, emit events
 *       app.Update();  // Layers receive events
 *   }
 */
class InputDispatcher {
public:
  using EventCallback = std::function<void(std::unique_ptr<Event>)>;

  InputDispatcher() = default;
  ~InputDispatcher() = default;

  InputDispatcher(const InputDispatcher &) = delete;
  InputDispatcher(InputDispatcher &&) = delete;
  auto operator=(const InputDispatcher &) -> InputDispatcher & = delete;
  auto operator=(InputDispatcher &&) -> InputDispatcher & = delete;

  /**
   * Set the callback that receives events when input is detected.
   * Typically called by Application to route events through the layer system.
   */
  void SetEventCallback(EventCallback callback) {
    event_callback_ = callback;
  }

  /**
   * Poll Raylib input and emit events.
   * Call this once per frame before processing layers.
   */
  void Poll();

private:
  EventCallback event_callback_;

  void EmitEvent(std::unique_ptr<Event> event) {
    if (event_callback_) {
      event_callback_(std::move(event));
    }
  }
};

} // namespace core
