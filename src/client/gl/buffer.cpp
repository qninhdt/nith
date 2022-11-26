#include "client/gl/buffer.hpp"

namespace nith::gl
{
    GLenum ToGLDataType(const BufferDataType& type)
    {
        switch (type)
        {
        case BufferDataType::Short:
            return GL_SHORT;
        case BufferDataType::Ushort:
            return GL_UNSIGNED_SHORT;
        case BufferDataType::Int:
            return GL_INT;
        case BufferDataType::Uint:
            return GL_UNSIGNED_INT;
        case BufferDataType::Vec2:
        case BufferDataType::Vec3:
        case BufferDataType::Vec4:
        case BufferDataType::Float:
            return GL_FLOAT;
        default:
            NITH_CLIENT_ASSERT(0, "Buffer data type is invalid");
            return 0;
        }
    }

    u32 GetGLDataComponentCount(const BufferDataType& type)
    {
        switch (type)
        {
        case BufferDataType::Short:
        case BufferDataType::Ushort:
        case BufferDataType::Int:
        case BufferDataType::Uint:
        case BufferDataType::Float:
            return 1;
        case BufferDataType::Vec2:
            return 2;
        case BufferDataType::Vec3:
            return 3;
        case BufferDataType::Vec4:
            return 4;
        default:
            NITH_CLIENT_ASSERT(0, "Buffer data type is invalid");
            return 0;
        }
    }

    u32 GetGLDataTypeSize(const GLenum& type)
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
    }

    void Buffer::set_data(void* data, const u32& size)
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
        if (m_id != 0)
        {
            glDeleteBuffers(1, &m_id);
        }
    }
    
    VertexBuffer::VertexBuffer():
        Buffer(BufferType::Vertex)
    {}

    IndexBuffer::IndexBuffer(const BufferDataType& type):
        Buffer(BufferType::Index),
        m_indexType(ToGLDataType(type))
    {}


}