#include "loaders/shader_loader.hpp"
#include "util/file_util.hpp"
#include "io/input.hpp"

namespace nith
{
    std::unordered_map<std::string, gl::Shader*> ShaderLoader::s_shaders;
    std::unordered_set<std::string> ShaderLoader::s_shaderNames;
    const std::string ShaderLoader::ShaderFolderPath = NITH_ROOT + "assets/shaders/";
    
    void ShaderLoader::Init()
    {
        // reload all shaders when press R key
        io::Input::GetEventDispatcher().addEventListener<io::KeyPressedEvent>(
            [&](const io::KeyPressedEvent& event)
            {
                if (event.getKeyCode() == io::KeyCode::F2 && !event.isRepeat())
                {
                    ReloadAll();
                }
            }
        );
    }

    void ShaderLoader::Load(const std::string& name)
    {
        gl::Shader* shader = new gl::Shader(name);
        shader->loadFromFile(
            (ShaderFolderPath + name + ".vert").c_str(),
            (ShaderFolderPath + name + ".frag").c_str()
        );
        s_shaders[name] = shader;
    }

    void ShaderLoader::LoadAll()
    {
        for (auto& entry : std::filesystem::directory_iterator(ShaderFolderPath))
        {
            std::string fileName = entry.path().stem().string();
            s_shaderNames.insert(fileName);
        }

        for (auto& name : s_shaderNames) Load(name);
    }

    void ShaderLoader::Reload(const std::string& name)
    {
        s_shaders[name]->reload();
    }

    void ShaderLoader::ReloadAll()
    {
        u32 count = 0;
        for (auto& name : s_shaderNames)
        {
            count += s_shaders[name]->reload();
        }
        
        if (count == s_shaders.size())
        {
            NITH_CLIENT_INFO("Reload shaders complete");
        }
        else
        {
            NITH_CLIENT_ERROR("Fail to reload some shaders");
        }
    }

    void ShaderLoader::Destroy()
    {
        for (auto& [name, shader] : s_shaders)
        {
            delete shader;
        }
    }
}