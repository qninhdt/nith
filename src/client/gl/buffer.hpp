#pragma once

namespace nith::gl
{
    enum class BufferType
    {
        Vertex = 0,
        Index
    };

    enum class BufferDataType
    {
        None = 0,
        Short,
        Ushort,
        Int,
        Uint,
        Float,
        Vec2,
        Vec3,
        Vec4
    };

    enum class BufferUsageType
    {
        None = 0,
        StaticDraw,
        DynamicDraw
    };

    struct BufferElement
    {
        BufferDataType dataType;
        bool normalized;
    };

    struct BufferLayout
    {
        u32 stride;
        std::vector<BufferElement> elements;
    };

    class Buffer
    {
    public:
        Buffer(const BufferType& type);
        ~Buffer();

        GLuint getId() const;

        void create();

        template<typename T>
        void setData(const std::vector<T> data);

        template<typename T>
        void setData(T* data, const u32& size);

        void bind() const;

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
        IndexBuffer(const BufferDataType& type);

        GLenum getIndexType() const;

    private:
        GLenum m_indexType;
    };

    inline void Buffer::create()
    {
        glGenBuffers(1, &m_id);
    }

    inline GLuint Buffer::getId() const
    {
        return m_id;
    }

    inline void Buffer::bind() const
    {
        NITH_CLIENT_ASSERT(m_id != 0, "Buffer is not created");
        glBindBuffer(m_type, m_id);
    }

    template<typename T>
    void Buffer::setData(T* data, const u32& size)
    {
        set_data(data, size * sizeof(T));
    }

    inline GLenum IndexBuffer::getIndexType() const
    {
        return m_indexType;
    }

    u32 GetGLDataComponentCount(const BufferDataType& type);

    GLenum ToGLDataType(const BufferDataType& type);

    u32 GetGLDataTypeSize(const GLenum& type);
}