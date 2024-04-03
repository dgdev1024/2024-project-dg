/** @file DGStudio/Application.cpp */

#include <DGStudio/Application.hpp>

namespace dgstudio
{

  Application::Application (
    const dg::ApplicationSpecification& spec
  ) :
    dg::Application { spec }
  {
    dg::Json json;
    json.loadFromFile("assets/test.json");

    if (json["something"].getType() == dg::JsonDataType::Null) {
      DG_INFO("Something is not all there.");
    }
  }

  Application::~Application ()
  {
    
  }

}
