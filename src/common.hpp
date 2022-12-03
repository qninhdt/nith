#pragma once

#ifdef _MSC_VER
#ifdef _DEBUG
#define NITH_DEBUG
#endif // !_DEBUG
#endif // !MSVC

#ifdef _WIN32
#ifdef _WIN64
#define NITH_PLATFORM_WINDOWS
#else
#error "x86 Builds are not supported!"
#endif
#endif

#ifdef NITH_DEBUG
#ifdef NITH_PLATFORM_WINDOWS
#define NITH_DEBUGBREAK() __debugbreak()
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#endif

//#ifdef NITH_DEBUG
//#else
//#define NITH_ROOT ""
//#endif

namespace nith {

    static std::string NITH_ROOT = "D:/github/nith/";

    using i8  = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;
    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using f32 = float;
    using f64 = double;

    using iv2 = glm::ivec2;
    using iv3 = glm::ivec3;
    using iv4 = glm::ivec4;
    using uv2 = glm::uvec2;
    using uv3 = glm::uvec3;
    using uv4 = glm::uvec4;
    using v2  = glm::vec2;
    using v3  = glm::vec3;
    using v4  = glm::vec4;
    using mat4 = glm::mat4;

    using size = std::size_t;


}