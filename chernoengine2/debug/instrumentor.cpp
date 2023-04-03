//
// Created by shepherd on 3.4.23.
//

#include <chernoengine2/debug/instrumentor.hpp>

#include <sstream>
#include <algorithm>

namespace chernoengine2 {

Instrumentor& Instrumentor::Get() {
    static Instrumentor instance;
    return instance;
}

uint64_t Instrumentor::ConvertThreadIdToLong(const std::thread::id& id) {
    std::stringstream ss;
    ss << id;
    return std::stoul(ss.str());
}

void Instrumentor::WriteHeader() {
    output_stream_ << "{\"otherData\": {}, \"traceEvents\":[{}";
}

void Instrumentor::WriteFooter() {
    output_stream_ << "]}";
}

void Instrumentor::BeginSession(const std::string& filepath) {
    output_stream_.open(filepath);
    WriteHeader();
}

void Instrumentor::EndSession() {
    WriteFooter();
    output_stream_.close();
}

void Instrumentor::WriteProfile(const ProfileResult& result) {
    std::string name = result.name;
    std::replace(name.begin(), name.end(), '"', '\'');

    output_stream_ << ",{";
    output_stream_ << "\"cat\":\"function\",";
    output_stream_ << "\"dur\":" << (result.end - result.start) << ',';
    output_stream_ << "\"name\":\"" << name << "\",";
    output_stream_ << "\"ph\":\"X\",";
    output_stream_ << "\"pid\":0,";
    output_stream_ << "\"tid\":" << ConvertThreadIdToLong(result.thread_id) << ',';
    output_stream_ << "\"ts\":" << result.start;
    output_stream_ << "}";
}


} // chernoengine2