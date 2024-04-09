/** @file DG/Graphics/RenderInterface.hpp */

#pragma once

#include <DG/Graphics/Color.hpp>
#include <DG/Graphics/VertexArray.hpp>

namespace dg
{

  class RenderInterface
  {
  protected:
    RenderInterface () = default;
    
  public:
    virtual ~RenderInterface () = default;

  public:
    static Unique<RenderInterface> make ();

  public:
    virtual void clear () = 0;
    virtual void setClearColor (const Vector4f& color) = 0;
    virtual void setViewport (I32 x, I32 y, I32 width, I32 height) = 0;
    virtual void setViewport (I32 width, I32 height) = 0;
    virtual void drawIndexed (const Shared<VertexArray>& vao, Count indexCount = 0) = 0;

  };  

}
