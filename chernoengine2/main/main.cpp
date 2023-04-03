#include <chernoengine2/core/application.hpp>
#include <chernoengine2/main/example_layers/first_example.hpp>
#include <chernoengine2/main/example_layers/second_example.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

int main(){
    chernoengine2::Application app;

    PROFILE_BEGIN_SESSION("assets/tracing/profile_startup.json");
//    app.PushLayer(new chernoengine2::FirstExample);
    app.PushLayer(new chernoengine2::SecondExample);
    PROFILE_END_SESSION();

    PROFILE_BEGIN_SESSION("assets/tracing/profile_runtime.json");
    app.Run();
    PROFILE_END_SESSION();
}