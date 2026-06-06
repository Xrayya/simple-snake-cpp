#pragma once

#include "core/event.hpp"
#include "core/layer_stack.hpp"
#include "game_core/time.hpp"
#include <memory>
#include <vector>

namespace core {

class Application {
public:
  Application() : time_context_(std::make_shared<TimeContext>()) {}

  Application(const Application &) = delete;
  Application(Application &&) = delete;
  auto operator=(const Application &) -> Application & = delete;
  auto operator=(Application &&) -> Application & = delete;

  void PushLayer(std::unique_ptr<Layer> layer) {
    layer->SetEventCallback(
        [this](std::unique_ptr<Event> event) { QueueEvent(std::move(event)); });
    layer_stack_.PushLayer(std::move(layer));
  }

  void PushOverlay(std::unique_ptr<Layer> overlay) {
    overlay->SetEventCallback(
        [this](std::unique_ptr<Event> event) { QueueEvent(std::move(event)); });
    layer_stack_.PushOverlay(std::move(overlay));
  }

  void Run() {
    time_context_->resetTime();

    while (running_) {
      time_context_->update();
      const float delta_time = time_context_->getDeltaTime();

      for (auto &layer : layer_stack_) {
        layer->OnUpdate(delta_time);
      }

      DispatchQueuedEvents();

      for (auto &layer : layer_stack_) {
        layer->OnRender();
      }
    }
  }

  void Close() { running_ = false; }

  [[nodiscard]] auto GetTimeContext() const -> const std::shared_ptr<TimeContext> & {
    return time_context_;
  }

private:
  void QueueEvent(std::unique_ptr<Event> event) {
    pending_events_.emplace_back(std::move(event));
  }

  void DispatchQueuedEvents() {
    for (auto &event : pending_events_) {
      DispatchEvent(*event);
    }

    pending_events_.clear();
  }

  void DispatchEvent(Event &event) {
    for (auto it = layer_stack_.rbegin(); it != layer_stack_.rend(); ++it) {
      (*it)->OnEvent(event);

      if (event.Handled) {
        return;
      }
    }

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        [this](WindowCloseEvent &) {
          running_ = false;
          return true;
        });
    dispatcher.Dispatch<GameOverEvent>(
        [this](GameOverEvent &) {
          running_ = false;
          return true;
        });
  }

  bool running_ = true;
  LayerStack layer_stack_;
  std::shared_ptr<TimeContext> time_context_;
  std::vector<std::unique_ptr<Event>> pending_events_;
};

} // namespace core
