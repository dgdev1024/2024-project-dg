/** @file DGStudio/Application.hpp */

#pragma once

#include <DGStudio/EditorLayer.hpp>

namespace dgstudio
{

  class Application : public dg::Application
  {
  public:
    
    Application (
      const dg::ApplicationSpecification& spec = {}
    );
    ~Application ();
    
  private:
    EditorLayer m_editorLayer;

  };

}
