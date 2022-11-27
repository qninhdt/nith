#include "client/gl/vertex_array.hpp"

namespace nith::gl
{
    VertexArray::VertexArray() :
        m_id(0),
        m_drawCount(0),
        m_indexType(0)
    {
        glGenVertexArrays(1, &m_id);
    }

    void VertexArray::draw() const
    {
        NITH_CLIENT_ASSERT(m_drawCount != 0, "Draw count is not set");

        if (m_indexType == 0)
        {
            glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, m_drawCount, m_indexType, 0);
        }
    }


    void VertexArray::setAttributes(const std::initializer_list<VertexArrayAttribute>& attributes)
    {
        u32 offset = 0;
        u32 attrCount = 0;
        u32 stride = 0;

        // compute stride side
        for (auto& attr : attributes)
            // why is this shit so longggggg ?
            stride += GetGLComponentCount(attr.dataType) * GetGLSize(ConvertToGLEnum(attr.dataType));

        for (auto& attr : attributes)
        {
            switch (attr.dataType)
            {
            case GLDataType::Short:
            case GLDataType::Ushort:
            case GLDataType::Int:
            case GLDataType::Uint:
            case GLDataType::Ivec2:
            case GLDataType::Ivec3:
            case GLDataType::Ivec4:
            {
                const u32 count = GetGLComponentCount(attr.dataType);
                const GLenum glType = ConvertToGLEnum(attr.dataType);

                glEnableVertexAttribArray(attrCount);
                glVertexAttribIPointer(attrCount, count, glType,
                    stride, (void*)offset);

                offset += count * GetGLSize(glType);
                attrCount += 1;
                break;
            }
            case GLDataType::Vec2:
            case GLDataType::Vec3:
            case GLDataType::Vec4:
            case GLDataType::Float:
            {
                const u32 count = GetGLComponentCount(attr.dataType);
                const GLenum glType = ConvertToGLEnum(attr.dataType);

                glEnableVertexAttribArray(attrCount);
                glVertexAttribPointer(
                    attrCount,
                    count,
                    glType,
                    attr.normalized ? GL_TRUE : GL_FALSE,
                    stride,
                    (void*)offset
                );

                offset += count * GetGLSize(glType);
                attrCount += 1;
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
