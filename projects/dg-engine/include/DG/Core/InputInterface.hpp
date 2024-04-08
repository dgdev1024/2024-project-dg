/** @file DG/Core/InputInterface.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>
#include <DG/Core/InputCodes.hpp>

namespace dg
{

  class InputInterface
  {
  protected:
    InputInterface () = default;

  public:
    virtual ~InputInterface () = default;
    static Unique<InputInterface> make ();

  public:
    virtual Key resolveKeyEnum (I32 keycode) const = 0;
    virtual I32 resolveKeyCode (Key key) const = 0;
    virtual MouseButton resolveMouseButtonEnum (I32 buttonCode) const = 0;
    virtual I32 resolveMouseButtonCode (MouseButton button) const = 0;
    virtual GamepadButton resolveGamepadButtonEnum (I32 buttonCode) const = 0;
    virtual I32 resolveGamepadButtonCode (GamepadButton button) const = 0;
    virtual GamepadAxis resolveGamepadAxisEnum (I32 axisCode) const = 0;
    virtual I32 resolveGamepadAxisCode (GamepadAxis axis) const = 0;

  public:
    virtual bool isKeyDown (Key key) const = 0;
    virtual bool isMouseButtonDown (MouseButton button) const = 0;
    virtual Vector2f getCursorPosition () const = 0;
    virtual bool isGamepadPresent (I32 id = 0) const = 0;
    virtual bool isGamepadButtonDown (GamepadButton button, I32 id = 0) const = 0;
    virtual F32 getGamepadAxis (GamepadAxis axis, I32 id = 0) const = 0;

  };

}
