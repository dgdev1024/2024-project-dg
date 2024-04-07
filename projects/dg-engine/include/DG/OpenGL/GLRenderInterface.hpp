/** @file DG/OpenGL/GLRenderInterface.hpp */

#pragma once

#if !defined(DG_USING_OPENGL)
  #error "Do not #include this file if not building with an OpenGL rendering library!"
#endif

#include <DG/Graphics/RenderInterface.hpp>

namespace dg::OpenGL
{

  class RenderInterfaceImpl : public RenderInterface
  {
  public:
    RenderInterfaceImpl ();
    ~RenderInterfaceImpl ();

    void clear () override;
    void setClearColor (const Vector4f& color) override;
    void setViewport (I32 x, I32 y, I32 width, I32 height) override;
    void setViewport (I32 width, I32 height) override;

  };

}
