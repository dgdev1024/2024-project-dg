/** @file DG/GLFW/GLFWWindow.hpp */

#pragma once

#if !defined(DG_USING_GLFW)
  #error "Do not #include this file if not building with GLFW!"
#endif

#include <DG/Core/Window.hpp>

namespace dg::GLFW
{

  class WindowImpl : public Window
  {
  public:
    WindowImpl (const WindowSpecification& spec);
    ~WindowImpl ();

  public:
    void update () override;
    void* getPointer () const override;

  private:
    void onTitleChanged () override;
    void onSizeChanged () override;

  private:
    GLFWwindow* m_winptr = nullptr;

  };

}
