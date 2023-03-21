//
// Created by shepherd on 9.3.23.
//

#ifndef CHERNOENGINE2_LAYER_STACK_HPP
#define CHERNOENGINE2_LAYER_STACK_HPP

#include <vector>

#include <chernoengine2/core/layer.hpp>

namespace chernoengine2 {

class LayerStack {
public:
    LayerStack() = default;

    void PushLayer(Layer *layer);

    void PushOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin();

    std::vector<Layer *>::iterator end();

    std::vector<Layer *>::const_iterator begin() const;

    std::vector<Layer *>::const_iterator end() const;

private:
    std::vector<Layer *> layers_;
    int layer_insert_index_ = 0;
};

} // chernoengine2

#endif //CHERNOENGINE2_LAYER_STACK_HPP
