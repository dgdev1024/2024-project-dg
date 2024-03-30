/** @file DGStudio/Application.cpp */

#include <DGStudio/Application.hpp>

namespace dgstudio
{

  Application::Application (
    const dg::ApplicationSpecification& spec
  ) :
    dg::Application { spec }
  {
    DG_INFO("This is a {}.", "log");
  }

  Application::~Application ()
  {
    
  }

}
