/** @file DG/OpenGL/GLFrameBuffer.hpp */

#pragma once

#if !defined(DG_USING_OPENGL)
  #error "Do not #include this file if you are not using OpenGL!"
#endif

#include <DG/Graphics/FrameBuffer.hpp>

namespace dg::OpenGL
{

  class FrameBufferImpl : public FrameBuffer
  {
  public:
    FrameBufferImpl (const FrameBufferSpecification& spec);
    ~FrameBufferImpl ();

  public:
    void bind (FrameBufferBindTarget target = FrameBufferBindTarget::DRAW) const override;
    void unbind (FrameBufferBindTarget target = FrameBufferBindTarget::DRAW) const override;
    U32 getColorHandle (const Index index = 0) const override;
    U32 getDepthHandle () const override;
    void* getColorPointer (const Index index = 0) const override;
    I32 readPixelI32 (const Index index, const Vector2i& position) const override;
    I32 readPixelI32 (const Index index, const Vector2f& position) const override;

  private:
    void onSizeChanged () override;
    void build ();

  private:
    U32 m_handle = 0;
    Collection<U32> m_colorHandles;
    U32 m_depthHandle = 0;

  };

}
