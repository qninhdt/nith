#pragma once

namespace nith::gl
{
    enum class BufferType
    {
        Vertex = 0,
        Index
    };

    enum class GLDataType
    {
        None = 0,
        Short,
        Ushort,
        Int,
        Uint,
        Float,
        Vec2,
        Vec3,
        Vec4,
        Ivec2,
        Ivec3,
        Ivec4,
    };

    enum class BufferUsageType
    {
        None = 0,
        StaticDraw,
        DynamicDraw
    };

    class Buffer
    {
    public:
        Buffer(const BufferType& type);
        ~Buffer();

        GLuint getId() const { return m_id; }

        template<typename T>
        void setData(const std::vector<T>& data)
        {
            setData(data.data(), data.size());
        }

        void setData(void* data, const u32& size);

        void bind() const
        {
            NITH_CLIENT_ASSERT(m_id != 0, "Buffer is not created");
            glBindBuffer(m_type, m_id);
        }

        void setUsage(const BufferUsageType& usage);

    private:

        void set_data(void* data, const u32& size);

        GLuint m_id;
        GLenum m_type;
        GLenum m_usage;
        u32 m_capacity;
    };

    class VertexBuffer : public Buffer
    {
    public:
        VertexBuffer();
    };

    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(const GLDataType& type);
        GLenum getIndexType() const { return m_indexType; }
    private:
        GLenum m_indexType;
    };

    GLenum ConvertToGLEnum(const GLDataType& type);
    u32 GetGLComponentCount(const GLDataType& type);
    u32 GetGLSize(const GLenum& type);
}