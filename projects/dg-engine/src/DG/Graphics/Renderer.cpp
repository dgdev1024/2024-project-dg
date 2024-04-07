/** @file DG/Graphics/Renderer.cpp */

#include <DG/Graphics/RenderCommand.hpp>
#include <DG/Graphics/Renderer.hpp>

namespace dg
{

  Renderer::Renderer ()
  {
    RenderCommand::initialize();
  }

  Renderer::~Renderer ()
  {
    RenderCommand::shutdown();
  }

  Unique<Renderer> Renderer::make ()
  {
    return std::make_unique<Renderer>();
  }

}
