#include "client/gl/vertex_array.hpp"

namespace nith::gl
{
    VertexArray::VertexArray() :
        m_id(0),
        m_drawCount(0),
        m_attrCount(0),
        m_indexBuffer(nullptr)
    {

    }

    void VertexArray::draw()
    {
        NITH_CLIENT_ASSERT(m_drawCount != 0, "Draw count is not set");

        bind();
        if (m_indexBuffer->getId() == 0)
        {
            glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, m_drawCount,
                m_indexBuffer->getIndexType(), 0);
        }
    }


    void VertexArray::addBuffer(const VertexBuffer& buffer,
        const BufferLayout& layout)
    {
        u32 offset = 0;

        buffer.bind();

        for (auto& element : layout.elements)
        {
            switch (element.dataType)
            {
            case BufferDataType::Short:
            case BufferDataType::Ushort:
            case BufferDataType::Int:
            case BufferDataType::Uint:
            {
                const u32 count = GetGLDataComponentCount(element.dataType);
                const GLenum type = ToGLDataType(element.dataType);

                glEnableVertexAttribArray(m_attrCount);
                glVertexAttribIPointer(m_attrCount, count, type,
                    layout.stride, (void*) offset);

                offset += count * GetGLDataTypeSize(type);
                m_attrCount += 1;
                break;
            }
            case BufferDataType::Vec2:
            case BufferDataType::Vec3:
            case BufferDataType::Vec4:
            case BufferDataType::Float:
            {
                const u32 count = GetGLDataComponentCount(element.dataType);
                const GLenum type = ToGLDataType(element.dataType);

                glEnableVertexAttribArray(m_attrCount);
                glVertexAttribPointer(
                    m_attrCount,
                    count,
                    type,
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.stride,
                    (void*)offset
                );

                offset += count * GetGLDataTypeSize(type);
                m_attrCount += 1;
                break;
            }
            default:
                NITH_CLIENT_ASSERT(0, "GL data type is invalid");
                return;
            }
        }
    }

    VertexArray::~VertexArray()
    {
        if (m_id != 0)
        {
            glDeleteVertexArrays(1, &m_id);
        }
    }
}
