/** @file DGStudio/Application.cpp */

#include <DGStudio/Application.hpp>

namespace dgstudio
{

  Application::Application (
    const dg::ApplicationSpecification& spec
  ) :
    dg::Application { spec }
  {
    dg::Vector4f position = { 0.0f, 2.0f, 0.0f, 1.0f };
    DG_INFO("Original Position: {}", position);
    
    dg::Matrix4f transform = dg::rotate(dg::Matrix4f::IDENTITY, dg::radians(90.0f), 
      { 0.0f, 0.0f, -1.0f });

    position = transform * position;
    DG_INFO("Rotated Position: {}", position);
  }

  Application::~Application ()
  {
    
  }

}
