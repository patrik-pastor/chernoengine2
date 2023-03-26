include_directories(${THIRD_PARTY_DIRECTORY}/imgui)
find_package(spdlog)
add_executable(main
        ${THIRD_PARTY_DIRECTORY}/glad/glad.c

        ${THIRD_PARTY_DIRECTORY}/imgui/imgui.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_draw.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_tables.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_widgets.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_demo.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/backends/imgui_impl_glfw.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/backends/imgui_impl_opengl3.cpp

        ../core/log.cpp
        ../core/window.cpp
        ../core/linux_window.cpp
        ../core/application.cpp
        ../core/layer.cpp
        ../core/layer_stack.cpp
        ../core/input.cpp

        ../events/event.cpp
        ../events/application_event.cpp
        ../events/key_event.cpp
        ../events/mouse_event.cpp

        ../renderer/graphics_context.cpp
        ../renderer/opengl_context.cpp
        ../renderer/renderer.cpp
        ../renderer/renderer_api.cpp
        ../renderer/render_command.cpp
        ../renderer/shader.cpp
        ../renderer/buffer.cpp
        ../renderer/vertex_array.cpp
        ../renderer/orthographic_camera.cpp

        ../opengl/opengl_buffer.cpp
        ../opengl/opengl_vertex_array.cpp
        ../opengl/opengl_renderer_api.cpp
        ../opengl/opengl_shader.cpp

        ../imgui/imgui_layer.cpp

        main.cpp)
target_link_libraries(main PRIVATE spdlog::spdlog glfw)
