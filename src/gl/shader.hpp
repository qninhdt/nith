#pragma once

namespace nith::gl
{
    class Shader
    {
    public:

        Shader(const std::string& name): m_name(name) {};

        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(Shader const&) = delete;

        GLuint getUniformLocation(const char* name) const;

        void setInt(const GLuint& location, const i32& value) const;
        void setUint(const GLuint& location, const u32& value) const;
        void setFloat(const GLuint& location, const f32& value) const;
        void setDouble(const GLuint& location, const f64& value) const;
        void setVec2(const GLuint& location, const v2& value) const;
        void setVec3(const GLuint& location, const v3& value) const;
        void setVec4(const GLuint& location, const v4& value) const;
        void setMat4(const GLuint& location, const mat4& value) const;

        bool loadFromFile(const char* vertexPath,const char* fragmentPath, const bool& log = true);

        bool loadFromSource(const std::string& vertexSource,
            const std::string& fragmentSource, const bool& log = true);

        bool reload();

        void use() const;

        std::string getName() const;

    private:
        GLuint m_programId;
        std::string m_vertPath;
        std::string m_fragPath;
        std::string m_name;
    };

    inline GLuint Shader::getUniformLocation(const char* name) const {
        return glGetUniformLocation(m_programId, name);
    }

    inline void Shader::setInt(const GLuint& location, const i32& value) const {
        glUniform1i(location, value);
    }

    inline void Shader::setUint(const GLuint& location, const u32& value) const {
        glUniform1ui(location, value);
    }

    inline void Shader::setFloat(const GLuint& location, const f32& value) const {
        glUniform1f(location, value);
    }

    inline void Shader::setDouble(const GLuint& location, const f64& value) const {
        glUniform1d(location, value);
    }

    inline void Shader::setVec2(const GLuint& location, const v2& value) const {
        glUniform2f(location, value.x, value.y);
    }

    inline void Shader::setVec3(const GLuint& location, const v3& value) const {
        glUniform3f(location, value.x, value.y, value.z);
    }

    inline void Shader::setVec4(const GLuint& location, const v4& value) const {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    inline void Shader::setMat4(const GLuint& location, const mat4& value) const {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    inline void Shader::use() const {
        glUseProgram(m_programId);
    }

    inline std::string Shader::getName() const {
        return m_name;
    }

} // end namespace nith::gl