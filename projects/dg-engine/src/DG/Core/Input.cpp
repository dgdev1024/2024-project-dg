/** @file DG/Core/Input.cpp */

#include <DG/Core/Input.hpp>

namespace dg
{

  Unique<InputInterface> Input::s_interface = nullptr;

  void Input::initialize ()
  {
    s_interface = InputInterface::make();
  }

  void Input::shutdown ()
  {
    s_interface.reset();
  }

  Key Input::resolveKeyEnum (I32 keycode)
  {
    return s_interface->resolveKeyEnum(keycode);
  }
  
  I32 Input::resolveKeyCode (Key key)
  {
    return s_interface->resolveKeyCode(key);
  }
  
  MouseButton Input::resolveMouseButtonEnum (I32 buttonCode)
  {
    return s_interface->resolveMouseButtonEnum(buttonCode);
  }
  
  I32 Input::resolveMouseButtonCode (MouseButton button)
  {
    return s_interface->resolveMouseButtonCode(button);
  }
  
  GamepadButton Input::resolveGamepadButtonEnum (I32 buttonCode)
  {
    return s_interface->resolveGamepadButtonEnum(buttonCode);
  }
  
  I32 Input::resolveGamepadButtonCode (GamepadButton button)
  {
    return s_interface->resolveGamepadButtonCode(button);
  }
  
  GamepadAxis Input::resolveGamepadAxisEnum (I32 axisCode)
  {
    return s_interface->resolveGamepadAxisEnum(axisCode);
  }
  
  I32 Input::resolveGamepadAxisCode (GamepadAxis axis)
  {
    return s_interface->resolveGamepadAxisCode(axis);
  }
  
  bool Input::isKeyDown (Key key)
  {
    return s_interface->isKeyDown(key);
  }
  
  bool Input::isMouseButtonDown (MouseButton button)
  {
    return s_interface->isMouseButtonDown(button);
  }
  
  Vector2f Input::getCursorPosition ()
  {
    return s_interface->getCursorPosition();
  }
  
  bool Input::isGamepadPresent (I32 id)
  {
    return s_interface->isGamepadPresent(id);
  }
  
  bool Input::isGamepadButtonDown (GamepadButton button, I32 id)
  {
    return s_interface->isGamepadButtonDown(button, id);
  }
  
  F32 Input::getGamepadAxis (GamepadAxis axis, I32 id)
  {
    return s_interface->getGamepadAxis(axis, id);
  }

}

