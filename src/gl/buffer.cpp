#include "gl/buffer.hpp"

namespace nith::gl
{
    GLenum ConvertToGLEnum(const GLDataType& type)
    {
        switch (type)
        {
        case GLDataType::Short:
            return GL_SHORT;
        case GLDataType::Ushort:
            return GL_UNSIGNED_SHORT;
        case GLDataType::Int:
            return GL_INT;
        case GLDataType::Uint:
            return GL_UNSIGNED_INT;
        case GLDataType::Vec2:
        case GLDataType::Vec3:
        case GLDataType::Vec4:
        case GLDataType::Float:
            return GL_FLOAT;
        default:
            NITH_CLIENT_ASSERT(0, "Buffer data type is invalid");
            return 0;
        }
    }

    u32 GetGLComponentCount(const GLDataType& type)
    {
        switch (type)
        {
        case GLDataType::Short:
        case GLDataType::Ushort:
        case GLDataType::Int:
        case GLDataType::Uint:
        case GLDataType::Float:
            return 1;
        case GLDataType::Vec2:
        case GLDataType::Ivec2:
            return 2;
        case GLDataType::Vec3:
        case GLDataType::Ivec3:
            return 3;
        case GLDataType::Vec4:
        case GLDataType::Ivec4:
            return 4;
        default:
            NITH_CLIENT_ASSERT(0, "Buffer data type is invalid");
            return 0;
        }
    }

    u32 GetGLSize(const GLenum& type)
    {
        switch (type)
        {
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
            return 2;
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_FLOAT:
            return 4;
        default:
            NITH_CLIENT_ASSERT(0, "GL data type is invalid");
            return 0;
        }
    }

    Buffer::Buffer(const BufferType& type):
        m_id(0),
        m_capacity(0),
        m_usage(GL_STATIC_DRAW)
    {
        switch (type)
        {
        case BufferType::Vertex:
            m_type = GL_ARRAY_BUFFER;
            break;
        case BufferType::Index:
            m_type = GL_ELEMENT_ARRAY_BUFFER;
            break;
        default:
            NITH_CORE_ASSERT(0, "Buffer type is invalid");
            m_type = 0;
            break;
        }

        glGenBuffers(1, &m_id);
    }

    void Buffer::setData(void* data, const u32& size)
    {
        bind();
        if (size > m_capacity)
        {
            glBufferData(m_type, size, data, m_usage);
            m_capacity = size;
        }
        else
        {
            glBufferSubData(m_type, 0, size, data);
        }
    }

    void Buffer::setUsage(const BufferUsageType& usage)
    {
        switch (usage)
        {
        case BufferUsageType::StaticDraw:
            m_usage = GL_STATIC_DRAW;
            break;
        case BufferUsageType::DynamicDraw:
            m_usage = GL_DYNAMIC_DRAW;
            break;
        default:
            NITH_CLIENT_ASSERT(0, "Usage type is invalid");
            break;
        }
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &m_id);
    }
    
    VertexBuffer::VertexBuffer():
        Buffer(BufferType::Vertex)
    {}

    IndexBuffer::IndexBuffer(const GLDataType& type):
        Buffer(BufferType::Index),
        m_indexType(ConvertToGLEnum(type))
    {}


}