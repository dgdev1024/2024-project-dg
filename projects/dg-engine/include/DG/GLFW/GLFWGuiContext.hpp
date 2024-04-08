/** @file DG/GLFW/GLFWGuiContext.hpp */

#pragma once

#if !defined(DG_USING_GLFW)
  #error "Do not #include this file if you are not building with GLFW!"
#endif

#include <DG/Core/GuiContext.hpp>

namespace dg::GLFW
{

  class GuiContextImpl : public GuiContext
  {
  public:
    GuiContextImpl (const GuiContextSpecification& spec);
    ~GuiContextImpl ();

  public:
    void begin () override;
    void end () override;
    
  };  

}
