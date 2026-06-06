#pragma once

#include "core/layer.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace core {

class LayerStack {
public:
  LayerStack() = default;

  LayerStack(const LayerStack &) = delete;
  LayerStack(LayerStack &&) = delete;
  auto operator=(const LayerStack &) -> LayerStack & = delete;
  auto operator=(LayerStack &&) -> LayerStack & = delete;

  void PushLayer(std::unique_ptr<Layer> layer) {
    layers_.emplace(layers_.begin() + static_cast<long>(layer_insert_index_),
                    std::move(layer));
    layer_insert_index_++;
  }

  void PushOverlay(std::unique_ptr<Layer> overlay) {
    layers_.emplace_back(std::move(overlay));
  }

  void PopLayer(const Layer *layer) {
    auto it = std::find_if(layers_.begin(), layers_.begin() + static_cast<long>(layer_insert_index_),
                           [layer](const auto &candidate) { return candidate.get() == layer; });

    if (it != layers_.begin() + static_cast<long>(layer_insert_index_)) {
      layers_.erase(it);
      layer_insert_index_--;
    }
  }

  void PopOverlay(const Layer *overlay) {
    auto it = std::find_if(layers_.begin() + static_cast<long>(layer_insert_index_), layers_.end(),
                           [overlay](const auto &candidate) { return candidate.get() == overlay; });

    if (it != layers_.end()) {
      layers_.erase(it);
    }
  }

  auto begin() { return layers_.begin(); }
  auto end() { return layers_.end(); }
  auto begin() const { return layers_.begin(); }
  auto end() const { return layers_.end(); }
  auto rbegin() { return layers_.rbegin(); }
  auto rend() { return layers_.rend(); }
  auto rbegin() const { return layers_.rbegin(); }
  auto rend() const { return layers_.rend(); }

private:
  std::vector<std::unique_ptr<Layer>> layers_;
  std::size_t layer_insert_index_ = 0;
};

} // namespace core
