/** @file DGStudio/Application.hpp */

#pragma once

#include <DGStudio_Pch.hpp>

namespace dgstudio
{

  class Application : public dg::Application
  {
  public:
    
    Application (
      const dg::ApplicationSpecification& spec = {}
    );
    ~Application ();
    
  };

}
