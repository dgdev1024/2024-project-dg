/** @file DGStudio/Application.cpp */

#include <DGStudio/Application.hpp>

namespace dgstudio
{

  Application::Application (
    const dg::ApplicationSpecification& spec
  ) :
    dg::Application { spec }
  {
    dg::RenderCommand::setClearColor(dg::Color::BLUE);

    getLayerStack().attachLayer(m_editorLayer);
  }

  Application::~Application ()
  {
    getLayerStack().detachLayer(m_editorLayer);
  }

}
