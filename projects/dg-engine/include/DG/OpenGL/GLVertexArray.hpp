/** @file DG/OpenGL/GLVertexArray.hpp */

#pragma once

#if !defined(DG_USING_OPENGL)
  #error "Do not #include this file if you are not using OpenGL!"
#endif

#include <DG/Graphics/VertexArray.hpp>

namespace dg::OpenGL
{

  class VertexArrayImpl : public VertexArray
  {
  public:
    VertexArrayImpl ();
    ~VertexArrayImpl ();

  public:
    void bind () const override;
    void unbind () const override;
    void addVertexBuffer (const Shared<VertexBuffer>& vbo) override;
    void setIndexBuffer (const Shared<IndexBuffer>& ibo) override;

  private:
    U32 m_handle = 0;

  };

}
