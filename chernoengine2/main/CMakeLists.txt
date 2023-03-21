find_package(spdlog)
add_executable(main
        ${THIRD_PARTY_DIRECTORY}/glad/glad.c

        ../core/log.cpp
        ../core/window.cpp
        ../core/linux_window.cpp
        ../core/application.cpp
        ../core/layer.cpp
        ../core/layer_stack.cpp

        ../events/event.cpp
        ../events/application_event.cpp
        ../events/key_event.cpp
        ../events/mouse_event.cpp

        ../renderer/graphics_context.cpp
        ../renderer/opengl_context.cpp

        main.cpp)
target_link_libraries(main PRIVATE spdlog::spdlog glfw)
