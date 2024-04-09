/** @file DG/Graphics/RenderCommand.hpp */

#pragma once

#include <DG/Graphics/RenderInterface.hpp>

namespace dg
{

  class RenderCommand
  {
  public:
    static void initialize ();
    static void shutdown ();
    static void clear ();
    static void setClearColor (const Vector4f& color);
    static void setViewport (I32 x, I32 y, I32 width, I32 height);
    static void setViewport (I32 width, I32 height);
    static void drawIndexed (const Shared<VertexArray>& vao, Count indexCount = 0);

  private:
    static Unique<RenderInterface> s_interface;

  };

}
