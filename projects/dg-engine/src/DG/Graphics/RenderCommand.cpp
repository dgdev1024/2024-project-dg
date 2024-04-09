/** @file DG/Graphics/RenderCommand.cpp */

#include <DG/Graphics/RenderCommand.hpp>

namespace dg
{

  Unique<RenderInterface> RenderCommand::s_interface = nullptr;

  void RenderCommand::initialize ()
  {
    s_interface = RenderInterface::make();
  }

  void RenderCommand::shutdown ()
  {
    s_interface.reset();
  }

  void RenderCommand::clear ()
  {
    s_interface->clear();
  }

  void RenderCommand::setClearColor (const Vector4f& color)
  {
    s_interface->setClearColor(color);
  }

  void RenderCommand::setViewport (I32 x, I32 y, I32 width, I32 height)
  {
    s_interface->setViewport(x, y, width, height);
  }

  void RenderCommand::setViewport (I32 width, I32 height)
  {
    s_interface->setViewport(width, height);
  }

  void RenderCommand::drawIndexed (const Shared<VertexArray>& vao, Count indexCount)
  {
    s_interface->drawIndexed(vao, indexCount);
  }

}
