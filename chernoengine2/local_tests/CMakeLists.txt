find_package(spdlog)
add_executable(logging
        ../core/log.cpp
        logging.cpp)
target_link_libraries(logging PRIVATE spdlog::spdlog)