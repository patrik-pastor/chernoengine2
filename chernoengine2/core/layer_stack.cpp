//
// Created by shepherd on 9.3.23.
//

#include <chernoengine2/core/layer_stack.hpp>

namespace chernoengine2 {

void LayerStack::PushLayer(Layer *layer) {
    layers_.emplace(layers_.begin() + layer_insert_index_, layer);
    layer_insert_index_++;
}

void LayerStack::PushOverlay(Layer *overlay) {
    layers_.emplace_back(overlay);
}

std::vector<Layer *>::iterator LayerStack::begin() {
    return layers_.begin();
}

std::vector<Layer *>::iterator LayerStack::end() {
    return layers_.end();
}

std::vector<Layer *>::const_iterator LayerStack::begin() const {
    return layers_.begin();
}

std::vector<Layer *>::const_iterator LayerStack::end() const {
    return layers_.end();
}

} // chernoengine2