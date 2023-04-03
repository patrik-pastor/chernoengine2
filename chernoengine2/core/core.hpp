//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_CORE_HPP
#define CHERNOENGINE2_CORE_HPP

#include <memory>
#include <functional>

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define PROFILING 0

namespace chernoengine2 {

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ...Args>
constexpr Scope<T> CreateScope(Args&& ...args){
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ...Args>
constexpr Ref<T> CreateRef(Args&& ...args){
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // chernoengine2

#endif //CHERNOENGINE2_CORE_HPP
