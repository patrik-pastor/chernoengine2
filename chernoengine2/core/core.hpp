//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_CORE_HPP
#define CHERNOENGINE2_CORE_HPP

#include <functional>

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif //CHERNOENGINE2_CORE_HPP
