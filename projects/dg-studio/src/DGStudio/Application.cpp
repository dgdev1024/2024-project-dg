/** @file DGStudio/Application.cpp */

#include <DGStudio/Application.hpp>

namespace dgstudio
{

  Application::Application (
    const dg::ApplicationSpecification& spec
  ) :
    dg::Application { spec }
  {
    dg::FileLexer lexer { "./premake5.lua" };
    while (lexer.hasMoreTokens() == true) {
      auto token = lexer.getNextToken();
      DG_INFO("Token: {} = '{}'", token.typeToString(), token.contents);
    }
  }

  Application::~Application ()
  {
    
  }

}
