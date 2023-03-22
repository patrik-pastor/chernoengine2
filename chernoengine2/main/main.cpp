#include <chernoengine2/core/application.hpp>
#include <chernoengine2/imgui/imgui_layer.hpp>

int main(){
    chernoengine2::Application app;
//    app.PushLayer(new chernoengine2::ExampleLayer);
    app.PushOverlay(new chernoengine2::ImguiLayer);
    app.Run();
}