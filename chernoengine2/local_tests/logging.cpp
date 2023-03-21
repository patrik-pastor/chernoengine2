//
// Created by shepherd on 20.3.23.
//

#include <iostream>

#include <chernoengine2/core/log.hpp>

class Foo {
public:
    explicit Foo(const std::string& name) : name_(name) {}

    std::string ToString() const { return name_; }

private:
    std::string name_;
};

class Bar : public Foo {
public:
    explicit Bar(const std::string& name) : Foo(name) {}
};


template<typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<Foo, T>, char>> :
        fmt::formatter<std::string> {
    template<typename FormatCtx>
    auto format(const Foo& f, FormatCtx& ctx) const {
        return fmt::formatter<std::string>::format(f.ToString(), ctx);
    }
};

int main(){
//    chernoengine2::Log::Init();
//    LOG_APP_WARN("Initialized Log!");
//    LOG_APP_INFO("Hello!");
//    LOG_CORE_CRITICAL("some error");

    Bar f("mr. Bar");
    spdlog::info("user defined type: {}", f.ToString());
}