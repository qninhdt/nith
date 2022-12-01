#pragma once

#include "client/gl/buffer.hpp"

namespace nith::gl
{
    struct VertexArrayAttribute
    {
        GLDataType dataType;
        bool normalized;

        VertexArrayAttribute(const GLDataType& dataType,
            const bool& normalized = false): 
            dataType(dataType),
            normalized(normalized)
        {}
    };

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        
        void bind() const { glBindVertexArray(m_id); }

        void setBuffer(const VertexBuffer& buffer,
            const std::initializer_list<VertexArrayAttribute>& attributes);

        void setIndex(const IndexBuffer& buffer)
        {
            bind();
            m_indexType = buffer.getIndexType();
            buffer.bind();
        }

        void draw() const;

        void setDrawCount(const u32& count) { m_drawCount = count; }

    private:
        GLuint m_id;
        GLenum m_indexType;
        u32 m_drawCount;
    };   
}