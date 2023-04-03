//
// Created by shepherd on 3.4.23.
//

#ifndef CHERNOENGINE2_INSTRUMENTOR_HPP
#define CHERNOENGINE2_INSTRUMENTOR_HPP

#include <string>
#include <fstream>
#include <thread>

#include <chernoengine2/core/core.hpp>
#include <chernoengine2/debug/instrumentation_timer.hpp>

namespace chernoengine2 {

struct ProfileResult {
    std::string name;
    // https://stackoverflow.com/questions/52292391/convert-high-resolution-clocktime-point-to-time-t-with-vc141
    uint64_t start, end;
    std::thread::id thread_id;
};

class Instrumentor {
public:
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    Instrumentor(const Instrumentor&) = delete;

    void operator=(const Instrumentor&) = delete;

    static Instrumentor& Get();

    void BeginSession(const std::string& filepath = "assets/tracing/chrome_tracing.json");

    void EndSession();

    void WriteProfile(const ProfileResult& result);

private:
    Instrumentor() = default;

    static uint64_t ConvertThreadIdToLong(const std::thread::id& id);

    void WriteHeader();

    void WriteFooter();

    std::ofstream output_stream_;
};

#if PROFILING
#define PROFILE_BEGIN_SESSION(filepath) chernoengine2::Instrumentor::Get().BeginSession(filepath)
#define PROFILE_END_SESSION() chernoengine2::Instrumentor::Get().EndSession()
#define PROFILE_SCOPE(name) chernoengine2::InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
#define PROFILE_BEGIN_SESSION(filepath)
#define PROFILE_END_SESSION()
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

} // chernoengine2

#endif //CHERNOENGINE2_INSTRUMENTOR_HPP
