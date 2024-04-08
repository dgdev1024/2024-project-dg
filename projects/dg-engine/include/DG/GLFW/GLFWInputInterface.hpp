/** @file DG/GLFW/GLFWInputInterface.hpp */

#pragma once

#if !defined(DG_USING_GLFW)
  #error "Do not #include this file if you are not building with GLFW!"
#endif

#include <DG/Core/InputInterface.hpp>

namespace dg::GLFW
{

  class InputInterfaceImpl : public InputInterface
  {
  public:
    InputInterfaceImpl ();
    ~InputInterfaceImpl ();

  public:
    Key resolveKeyEnum (I32 keycode) const override;
    I32 resolveKeyCode (Key key) const override;
    MouseButton resolveMouseButtonEnum (I32 buttonCode) const override;
    I32 resolveMouseButtonCode (MouseButton button) const override;
    GamepadButton resolveGamepadButtonEnum (I32 buttonCode) const override;
    I32 resolveGamepadButtonCode (GamepadButton button) const override;
    GamepadAxis resolveGamepadAxisEnum (I32 axisCode) const override;
    I32 resolveGamepadAxisCode (GamepadAxis axis) const override;

  public:
    bool isKeyDown (Key key) const override;
    bool isMouseButtonDown (MouseButton button) const override;
    Vector2f getCursorPosition () const override;
    bool isGamepadPresent (I32 id = 0) const override;
    bool isGamepadButtonDown (GamepadButton button, I32 id = 0) const override;
    F32 getGamepadAxis (GamepadAxis axis, I32 id = 0) const override;

  private:
    GLFWwindow* m_winptr = nullptr;

  };

}
