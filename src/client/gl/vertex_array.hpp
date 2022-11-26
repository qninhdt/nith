#pragma once

#include "client/gl/buffer.hpp"

namespace nith::gl
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        
        void create();
        void bind() const;

        void addBuffer(const VertexBuffer& buffer,
            const BufferLayout& layout);

        void setIndex(IndexBuffer* buffer);

        void draw();

        void setDrawCount(const u32& count);

        IndexBuffer* getIndexBuffer();

        //std::vector<VertexBuffer>& getVertexBuffers();

    private:
        GLuint m_id;
        u32 m_drawCount;
        u32 m_attrCount;
        IndexBuffer* m_indexBuffer;
        //std::vector<VertexBuffer> m_vertexBuffers;
    };

    inline void VertexArray::create()
    {
        glGenVertexArrays(1, &m_id);
    }

    inline void VertexArray::bind() const
    {
        glBindVertexArray(m_id);
    }

    inline void VertexArray::setIndex(IndexBuffer* buffer)
    {
        m_indexBuffer = buffer;
        buffer->bind();
    }

    inline IndexBuffer* VertexArray::getIndexBuffer()
    {
        return m_indexBuffer;
    }

    // inline std::vector<VertexBuffer>& VertexArray::getVertexBuffers()
    // {
    //     return m_vertexBuffers;
    // }

    inline void VertexArray::setDrawCount(const u32& count)
    {
        m_drawCount = count;
    }
     
}