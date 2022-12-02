cmake_minimum_required (VERSION 3.23)

project (nith VERSION 1.0)

set(NITH_CLIENT_SOURCES
    "src/gl/shader.cpp"
    "src/gl/vertex_array.cpp"
    "src/gl/buffer.cpp"
    "src/renderer/mesh.cpp"
    "src/renderer/cube_mesh.cpp"
    "src/nith_client_main.cpp"
    "src/application.cpp"
    "src/window.cpp"
    "src/io/input.cpp"
    "src/systems/camera_system.cpp"
    "src/systems/cube_system.cpp"
    "src/loaders/shader_loader.cpp"
)
 
set(NITH_UTIL_SOURCES
    "src/util/file_util.cpp"
)

add_executable (nith
    "src/log.cpp"
    
    ${NITH_CLIENT_SOURCES}
    ${NITH_UTIL_SOURCES}
 )

add_subdirectory(third_party)

target_include_directories(nith PRIVATE src)

find_package(glad CONFIG REQUIRED)
target_link_libraries(nith PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(nith PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(nith PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(nith PRIVATE imgui::imgui)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(nith PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

find_package(eventpp CONFIG REQUIRED)
target_link_libraries(nith PRIVATE eventpp::eventpp)

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(nith PRIVATE EnTT::EnTT)

target_precompile_headers(nith PRIVATE "src/nithpch.hpp")

if (MSVC AND WIN32 AND NOT MSVC_VERSION VERSION_LESS 142)
    target_link_options(nith PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL>)
    target_compile_options(nith PRIVATE $<$<CONFIG:Debug>:/Zi>)

endif()

set_property(TARGET nith PROPERTY CXX_STANDARD 20)
