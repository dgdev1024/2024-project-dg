/** @file DG/OpenGL/GLGraphicsBuffers.hpp */

#pragma once

#if !defined(DG_USING_OPENGL)
  #error "Do not #include this file if not using OpenGL!"
#endif

#include <DG/Graphics/GraphicsBuffers.hpp>

namespace dg::OpenGL
{

  class VertexBufferImpl : public VertexBuffer
  {
  public:
    VertexBufferImpl (const void* data, const Size size, bool dynamic = false);
    VertexBufferImpl (const Size size);
    ~VertexBufferImpl ();

  public:
    void bind () const override;
    void unbind () const override;
    void upload (const void* data, const Size size) override;

  private:
    U32 m_handle = 0;

  };

  class IndexBufferImpl : public IndexBuffer
  {
  public:
    IndexBufferImpl (const Collection<U32>& indices, bool dynamic = false);
    IndexBufferImpl (const Count count);
    ~IndexBufferImpl ();

  public:
    void bind () const override;
    void unbind () const override;

  private:
    U32 m_handle = 0;

  };

}
