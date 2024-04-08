/** @file DG/Core/Input.hpp */

#pragma once

#include <DG/Core/InputInterface.hpp>

namespace dg
{

  class Input
  {
  public:
    static void initialize ();
    static void shutdown ();

  public:
    static Key resolveKeyEnum (I32 keycode);
    static I32 resolveKeyCode (Key key);
    static MouseButton resolveMouseButtonEnum (I32 buttonCode);
    static I32 resolveMouseButtonCode (MouseButton button);
    static GamepadButton resolveGamepadButtonEnum (I32 buttonCode);
    static I32 resolveGamepadButtonCode (GamepadButton button);
    static GamepadAxis resolveGamepadAxisEnum (I32 axisCode);
    static I32 resolveGamepadAxisCode (GamepadAxis axis);

  public:
    static bool isKeyDown (Key key);
    static bool isMouseButtonDown (MouseButton button);
    static Vector2f getCursorPosition ();
    static bool isGamepadPresent (I32 id = 0);
    static bool isGamepadButtonDown (GamepadButton button, I32 id = 0);
    static F32 getGamepadAxis (GamepadAxis axis, I32 id = 0);

  private:
    static Unique<InputInterface> s_interface;

  };

}
