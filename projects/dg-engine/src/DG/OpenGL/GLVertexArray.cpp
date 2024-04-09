/** @file DG/OpenGL/GLVertexArray.cpp */

#include <DG/OpenGL/GLVertexArray.hpp>

namespace dg
{

  Shared<VertexArray> VertexArray::make ()
  {
    return std::make_shared<OpenGL::VertexArrayImpl>();
  }

}

namespace dg::OpenGL
{

  static GLenum resolveGLType (VertexAttributeType type)
  {
    switch (type)
    {
      case VertexAttributeType::Float:     return GL_FLOAT;      
      case VertexAttributeType::Double:    return GL_DOUBLE;       
      case VertexAttributeType::Int:       return GL_INT;    
      case VertexAttributeType::Uint:      return GL_UNSIGNED_INT;     
      case VertexAttributeType::Bool:      return GL_BOOL;    
      case VertexAttributeType::Float2:    return GL_FLOAT;       
      case VertexAttributeType::Double2:   return GL_DOUBLE;        
      case VertexAttributeType::Int2:      return GL_INT;     
      case VertexAttributeType::Uint2:     return GL_UNSIGNED_INT;      
      case VertexAttributeType::Bool2:     return GL_BOOL;     
      case VertexAttributeType::Float3:    return GL_FLOAT;       
      case VertexAttributeType::Double3:   return GL_DOUBLE;        
      case VertexAttributeType::Int3:      return GL_INT;     
      case VertexAttributeType::Uint3:     return GL_UNSIGNED_INT;      
      case VertexAttributeType::Bool3:     return GL_BOOL;     
      case VertexAttributeType::Float4:    return GL_FLOAT;       
      case VertexAttributeType::Double4:   return GL_DOUBLE;        
      case VertexAttributeType::Int4:      return GL_INT;     
      case VertexAttributeType::Uint4:     return GL_UNSIGNED_INT;      
      case VertexAttributeType::Bool4:     return GL_BOOL;     
      case VertexAttributeType::Float3x3:  return GL_FLOAT;         
      case VertexAttributeType::Double3x3: return GL_DOUBLE;          
      case VertexAttributeType::Float4x4:  return GL_FLOAT;         
      case VertexAttributeType::Double4x4: return GL_DOUBLE; 
      default: return 0;        
    }
  }

  VertexArrayImpl::VertexArrayImpl () :
    VertexArray {}
  {
    glGenVertexArrays(1, &m_handle);
  }

  VertexArrayImpl::~VertexArrayImpl ()
  {
    glDeleteVertexArrays(1, &m_handle);
  }

  void VertexArrayImpl::bind () const
  {
    glBindVertexArray(m_handle);
  }

  void VertexArrayImpl::unbind () const
  {
    glBindVertexArray(0);
  }

  void VertexArrayImpl::addVertexBuffer (const Shared<VertexBuffer>& vbo)
  {
    if (vbo == nullptr) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to add null vertex buffer to GL vertex array!");
    }

    const auto& layout = vbo->getLayout();
    if (layout.getAttributes().empty() == true) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to add vertex buffer with no layout to GL vertex array!");
    }

    if (isLayoutDefined() == true) {
      const auto& firstLayout = m_vbos.at(0)->getLayout();
      if (layout.isCompatible(firstLayout) == false) {
        DG_ENGINE_THROW(std::invalid_argument,
          "Attempt to add vertex buffer with incompatible layout to GL vertex array!");
      }
    }

    glBindVertexArray(m_handle);
    vbo->bind();

    Index index = 0;
    for (const auto& attribute : layout) {
      glVertexAttribPointer(
        index,
        attribute.getElementCount(),
        resolveGLType(attribute.type),
        attribute.normalized ? GL_TRUE : GL_FALSE,
        layout.getStride(),
        (const void*) attribute.offset
      );
      glEnableVertexAttribArray(index++);
    }

    m_vbos.push_back(vbo);
  }

  void VertexArrayImpl::setIndexBuffer (const Shared<IndexBuffer>& ibo)
  {
    if (ibo == nullptr) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to assign null index buffer to GL vertex array!");
    }

    glBindVertexArray(m_handle);
    ibo->bind();

    m_ibo = ibo;
  }

}
