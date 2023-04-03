//
// Created by shepherd on 3.4.23.
//

#ifndef CHERNOENGINE2_INSTRUMENTATION_TIMER_HPP
#define CHERNOENGINE2_INSTRUMENTATION_TIMER_HPP

#include <string>
#include <chrono>

namespace chernoengine2 {

class InstrumentationTimer {
public:
    explicit InstrumentationTimer(const std::string& name);

    ~InstrumentationTimer();

private:
    std::string name_;
    std::chrono::system_clock::time_point start_tp_, end_tp_;
};

} // chernoengine2

#endif //CHERNOENGINE2_INSTRUMENTATION_TIMER_HPP
