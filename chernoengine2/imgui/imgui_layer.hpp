//
// Created by shepherd on 21.3.23.
//

#ifndef CHERNOENGINE2_IMGUI_LAYER_HPP
#define CHERNOENGINE2_IMGUI_LAYER_HPP

#include <chernoengine2/core/layer.hpp>

namespace chernoengine2 {

class ImguiLayer : public Layer {
public:
    ImguiLayer();

    void OnAttach() override;

    void OnDetach() override;

    void Begin();

    void End();

//    void OnImguiRender() override;
};

} // chernoengine2

#endif //CHERNOENGINE2_IMGUI_LAYER_HPP
