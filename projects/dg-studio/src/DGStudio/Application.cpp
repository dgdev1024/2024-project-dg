/** @file DGStudio/Application.cpp */

#include <DGStudio/Application.hpp>

namespace dgstudio
{

  Application::Application (
    const dg::ApplicationSpecification& spec
  ) :
    dg::Application { spec }
  {
    // dg::Matrix4f matrix = dg::perspective(0.f, 800.f, 0.f, 600.f, 0.1f, 100.f);

    // DG_INFO("{} {} {} {}", matrix.aa, matrix.ba, matrix.ca, matrix.da);
    // DG_INFO("{} {} {} {}", matrix.ab, matrix.bb, matrix.cb, matrix.db);
    // DG_INFO("{} {} {} {}", matrix.ac, matrix.bc, matrix.cc, matrix.dc);
    // DG_INFO("{} {} {} {}", matrix.ad, matrix.bd, matrix.cd, matrix.dd);
  }

  Application::~Application ()
  {
    
  }

}
