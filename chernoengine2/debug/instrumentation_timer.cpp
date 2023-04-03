//
// Created by shepherd on 3.4.23.
//

#include <chernoengine2/debug/instrumentation_timer.hpp>

#include <iostream>

#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

InstrumentationTimer::InstrumentationTimer(const std::string& name) : name_(name), start_tp_(std::chrono::system_clock::now()) {}

InstrumentationTimer::~InstrumentationTimer() {
    end_tp_ = std::chrono::system_clock::now();

    uint64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(start_tp_).time_since_epoch().count();
    uint64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(end_tp_).time_since_epoch().count();

    Instrumentor::Get().WriteProfile({name_, start, end, std::this_thread::get_id()});
}

} // chernoengine2