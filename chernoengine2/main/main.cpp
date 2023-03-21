#include <chernoengine2/core/application.hpp>

int main(){
    chernoengine2::Application app;
    app.PushLayer(new chernoengine2::ExampleLayer);
    app.Run();
}