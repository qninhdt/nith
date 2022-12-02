#pragma once

#include "gl/shader.hpp"

namespace nith
{
    class ShaderLoader
    {
    public:
        static const std::string ShaderFolderPath;

        static void Init();

        static void LoadAll();

        static void Load(const std::string& name);

        static void Reload(const std::string& name);

        static void ReloadAll();

        static void Destroy();

        static gl::Shader& Get(const std::string& name) {
            return *s_shaders[name];
        }

    private:
        static std::unordered_map<std::string, gl::Shader*> s_shaders;
        static std::unordered_set<std::string> s_shaderNames;
    };
}