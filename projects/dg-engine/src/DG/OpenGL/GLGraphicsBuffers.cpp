/** @file DG/OpenGL/GLGraphicsBuffers.cpp */

#include <DG/OpenGL/GLGraphicsBuffers.hpp>

namespace dg
{

  Shared<VertexBuffer> VertexBuffer::make (const void* data, const Size size, bool dynamic)
  {
    return std::make_shared<OpenGL::VertexBufferImpl>(data, size, dynamic);
  }

  Shared<VertexBuffer> VertexBuffer::allocate (const Size size)
  {
    return std::make_shared<OpenGL::VertexBufferImpl>(size);
  }

  Shared<IndexBuffer> IndexBuffer::make (const Collection<U32>& indices, bool dynamic)
  {
    return std::make_shared<OpenGL::IndexBufferImpl>(indices, dynamic);
  }

  Shared<IndexBuffer> IndexBuffer::allocate (const Count count)
  {
    return std::make_shared<OpenGL::IndexBufferImpl>(count);
  }

}

namespace dg::OpenGL
{

  VertexBufferImpl::VertexBufferImpl (const void* data, const Size size, bool dynamic) :
    VertexBuffer {}
  {
    if (data == nullptr || size == 0) {
      DG_ENGINE_THROW(std::invalid_argument, 
        "Attempt to create GL vertex buffer with null data or zero size!");
    }

    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, (dynamic == true) ? GL_DYNAMIC_DRAW :
      GL_STATIC_DRAW);

    m_dynamic = dynamic;
    m_byteSize = size;
  }

  VertexBufferImpl::VertexBufferImpl (const Size size) :
    VertexBuffer {}
  {
    if (size == 0) {
      DG_ENGINE_THROW(std::invalid_argument, 
        "Attempt to allocate GL vertex buffer with zero size!");
    }

    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    m_dynamic = true;
    m_byteSize = size;
  }

  VertexBufferImpl::~VertexBufferImpl ()
  {
    glDeleteBuffers(1, &m_handle);
  }

  void VertexBufferImpl::bind () const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  }

  void VertexBufferImpl::unbind () const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }



  IndexBufferImpl::IndexBufferImpl (const Collection<U32>& indices, bool dynamic) :
    IndexBuffer {}
  {
    if (indices.empty() == true) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to create GL index buffer with no index data!");
    }

    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(U32), indices.data(),
      (dynamic == true) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    
    m_dynamic = dynamic;
    m_indexCount = indices.size();
  }

  IndexBufferImpl::IndexBufferImpl (const Count count) :
    IndexBuffer {}
  {
    if (count == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to create GL index buffer with zero index count!");
    }

    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(U32), nullptr, GL_DYNAMIC_DRAW);

    m_dynamic = true;
    m_indexCount = count;
  }

  IndexBufferImpl::~IndexBufferImpl ()
  {
    glDeleteBuffers(1, &m_handle);
  }

  void IndexBufferImpl::bind () const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
  }

  void IndexBufferImpl::unbind () const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

}
