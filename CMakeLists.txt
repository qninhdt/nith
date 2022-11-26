cmake_minimum_required (VERSION 3.23)

project (nith VERSION 1.0)

set(NITH_CLIENT_SOURCES
    "src/client/gl/shader.cpp"
    "src/client/nith_client_main.cpp"
    "src/client/application.cpp"
    "src/client/window.cpp"
    "src/client/window_event.cpp"
    "src/client/io/input_event.cpp"
    "src/client/io/input.cpp"
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

target_precompile_headers(nith PRIVATE "src/nithpch.hpp")

if (MSVC AND WIN32 AND NOT MSVC_VERSION VERSION_LESS 142)
    target_link_options(nith PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL>)
    target_compile_options(nith PRIVATE $<$<CONFIG:Debug>:/Zi>)

endif()

set_property(TARGET nith PROPERTY CXX_STANDARD 20)
