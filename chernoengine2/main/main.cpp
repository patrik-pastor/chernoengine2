#include <chernoengine2/core/application.hpp>
#include <chernoengine2/main/example_layers/first_example.hpp>
#include <chernoengine2/main/example_layers/second_example.hpp>

int main(){
    chernoengine2::Application app;
//    app.PushLayer(new chernoengine2::FirstExample);
    app.PushLayer(new chernoengine2::SecondExample);
    app.Run();
}