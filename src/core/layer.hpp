#pragma once

#include "core/event.hpp"
#include <functional>
#include <memory>
#include <string>

namespace core {

class Layer {
public:
  explicit Layer(std::string debugName = "Layer")
      : debug_name_(std::move(debugName)) {}
  virtual ~Layer() = default;

  virtual void OnEvent(Event &event) = 0;
  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnRender() = 0;

  using EventCallbackFn = std::function<void(std::unique_ptr<Event>)>;

  void SetEventCallback(EventCallbackFn callback) {
    event_callback_ = std::move(callback);
  }

  [[nodiscard]] auto GetName() const -> const std::string & { return debug_name_; }

protected:
  void SubmitEvent(std::unique_ptr<Event> event) const {
    if (event_callback_) {
      event_callback_(std::move(event));
    }
  }

private:
  std::string debug_name_;
  EventCallbackFn event_callback_;
};

} // namespace core
