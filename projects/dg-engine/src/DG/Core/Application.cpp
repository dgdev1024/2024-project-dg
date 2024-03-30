/** @file DG/Core/Application.cpp */

#include <DG/Core/Application.hpp>

namespace dg
{

  /** Constructor and Destructor **********************************************/

  Application::Application (
    const ApplicationSpecification& spec
  ) :
    m_timestep  { 1.0f / spec.framerate }
  {
    
  }

  Application::~Application ()
  {

  }

  /** Start Application Loop **************************************************/

  void Application::start ()
  {
    
  }

}
