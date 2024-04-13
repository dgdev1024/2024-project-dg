/** @file DGStudio/Main.cpp */

#include <DGStudio/Application.hpp>

int main ()
{
  int result = 0;

  try {
    dg::ApplicationSpecification spec;
    spec.windowSpec.title = "DG Studio";
    spec.guiSpec.enabled = true;
    spec.guiSpec.docking = true;
    dgstudio::Application app { spec };
    app.start();
  } catch (std::exception& ex) {
    result = 1;
  }

  return result;
}
