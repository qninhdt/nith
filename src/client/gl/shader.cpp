#include "client/gl/shader.hpp"

#include "util/file_util.hpp"

namespace nith::gl 
{
    void Shader::loadFromSource(const std::string& vertexSource,
        const std::string& fragmentSource)
    {
        int vertSuccess, fragSuccess, programSuccess; 
        char infoLog[512];

        // create vertex shader
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vertexCSource = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertexCSource, NULL);
        
        // compile vertex shader
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);
        if (!vertSuccess)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            NITH_CLIENT_ERROR("Complie vertex shader {0}", m_name);
            NITH_CLIENT_ERROR("Vertex shader error {0}", infoLog);
        }

        // create fragment shader
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fragmentCSource = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentCSource, NULL);

        // compile fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);
        if (!fragSuccess)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            NITH_CLIENT_ERROR("Complie fragment shader {0}", m_name);
            NITH_CLIENT_ERROR("Fragment shader error {0}", infoLog);
        }

        // create shader program
        m_programId = glCreateProgram();
        glAttachShader(m_programId, vertexShader);
        glAttachShader(m_programId, fragmentShader);

        glLinkProgram(m_programId);
        glGetProgramiv(m_programId, GL_LINK_STATUS, &programSuccess);

        if (!programSuccess || !vertSuccess || !fragSuccess) {
            glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
            NITH_CLIENT_ERROR("Linking shader {0} failed", m_name);
            NITH_CLIENT_ERROR("Shader program error: {0}", infoLog);
        }
        else
        {
            NITH_CLIENT_INFO("Complie shader {0} successfully", m_name);
        }

        // delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::loadFromFile(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexSource, fragmentSource;
        
        if (!util::ReadTextFile(vertexPath, vertexSource))
        {
            NITH_CLIENT_ERROR("Cannot open vertex shader file {0}", vertexPath);
        }

        if (!util::ReadTextFile(fragmentPath, fragmentSource))
        {
            NITH_CLIENT_ERROR("Cannot open fragment shader file {0}", fragmentPath);
        }
     
        if (!vertexSource.empty() && !fragmentSource.empty())
        {
            loadFromSource(vertexSource, fragmentSource);
        }
        else
        {
            NITH_CLIENT_ERROR("Cannot load shader {0}", m_name);
        }
    }

    Shader::~Shader() {
        glDeleteProgram(m_programId);
    }
}