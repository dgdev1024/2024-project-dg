/** @file DG/GLFW/GLFWInputInterface.cpp */

#include <DG/Core/Application.hpp>
#include <DG/GLFW/GLFWInputInterface.hpp>

namespace dg
{

  Unique<InputInterface> InputInterface::make ()
  {
    return std::make_unique<GLFW::InputInterfaceImpl>();
  }

}

namespace dg::GLFW
{

  InputInterfaceImpl::InputInterfaceImpl () :
    InputInterface {}
  {
    m_winptr = reinterpret_cast<GLFWwindow*>(Application::getWindow().getPointer());
  }

  InputInterfaceImpl::~InputInterfaceImpl ()
  {
    m_winptr = nullptr;
  }

  Key InputInterfaceImpl::resolveKeyEnum (I32 keycode) const 
  {
    switch (keycode)
    {
      case GLFW_KEY_ESCAPE: return Key::ESCAPE;
      case GLFW_KEY_F1: return Key::F1;
      case GLFW_KEY_F2: return Key::F2;
      case GLFW_KEY_F3: return Key::F3;
      case GLFW_KEY_F4: return Key::F4;
      case GLFW_KEY_F5: return Key::F5;
      case GLFW_KEY_F6: return Key::F6;
      case GLFW_KEY_F7: return Key::F7;
      case GLFW_KEY_F8: return Key::F8;
      case GLFW_KEY_F9: return Key::F9;
      case GLFW_KEY_F10: return Key::F10;
      case GLFW_KEY_F11: return Key::F11;
      case GLFW_KEY_F12: return Key::F12;
      case GLFW_KEY_PRINT_SCREEN: return Key::PRINT_SCREEN;
      case GLFW_KEY_INSERT: return Key::INSERT;
      case GLFW_KEY_DELETE: return Key::DELETE;
      case GLFW_KEY_GRAVE_ACCENT: return Key::GRAVE_ACCENT;
      case GLFW_KEY_1: return Key::NUM_1;
      case GLFW_KEY_2: return Key::NUM_2;
      case GLFW_KEY_3: return Key::NUM_3;
      case GLFW_KEY_4: return Key::NUM_4;
      case GLFW_KEY_5: return Key::NUM_5;
      case GLFW_KEY_6: return Key::NUM_6;
      case GLFW_KEY_7: return Key::NUM_7;
      case GLFW_KEY_8: return Key::NUM_8;
      case GLFW_KEY_9: return Key::NUM_9;
      case GLFW_KEY_0: return Key::NUM_0;
      case GLFW_KEY_MINUS: return Key::MINUS;
      case GLFW_KEY_EQUAL: return Key::EQUALS;
      case GLFW_KEY_BACKSPACE: return Key::BACKSPACE;
      case GLFW_KEY_TAB: return Key::TAB;
      case GLFW_KEY_Q: return Key::Q;
      case GLFW_KEY_W: return Key::W;
      case GLFW_KEY_E: return Key::E;
      case GLFW_KEY_R: return Key::R;
      case GLFW_KEY_T: return Key::T;
      case GLFW_KEY_Y: return Key::Y;
      case GLFW_KEY_U: return Key::U;
      case GLFW_KEY_I: return Key::I;
      case GLFW_KEY_O: return Key::O;
      case GLFW_KEY_P: return Key::P;
      case GLFW_KEY_LEFT_BRACKET: return Key::LEFT_BRACKET;
      case GLFW_KEY_RIGHT_BRACKET: return Key::RIGHT_BRACKET;
      case GLFW_KEY_BACKSLASH: return Key::BACKSLASH;
      case GLFW_KEY_A: return Key::A;
      case GLFW_KEY_S: return Key::S;
      case GLFW_KEY_D: return Key::D;
      case GLFW_KEY_F: return Key::F;
      case GLFW_KEY_G: return Key::G;
      case GLFW_KEY_H: return Key::H;
      case GLFW_KEY_J: return Key::J;
      case GLFW_KEY_K: return Key::K;
      case GLFW_KEY_L: return Key::L;
      case GLFW_KEY_SEMICOLON: return Key::SEMICOLON;
      case GLFW_KEY_APOSTROPHE: return Key::APOSTROPHE;
      case GLFW_KEY_ENTER: return Key::ENTER;
      case GLFW_KEY_LEFT_SHIFT: return Key::LEFT_SHIFT;
      case GLFW_KEY_Z: return Key::Z;
      case GLFW_KEY_X: return Key::X;
      case GLFW_KEY_C: return Key::C;
      case GLFW_KEY_V: return Key::V;
      case GLFW_KEY_B: return Key::B;
      case GLFW_KEY_N: return Key::N;
      case GLFW_KEY_M: return Key::M;
      case GLFW_KEY_COMMA: return Key::COMMA;
      case GLFW_KEY_PERIOD: return Key::PERIOD;
      case GLFW_KEY_SLASH: return Key::SLASH;
      case GLFW_KEY_RIGHT_SHIFT: return Key::RIGHT_SHIFT;
      case GLFW_KEY_LEFT_CONTROL: return Key::LEFT_CONTROL;
      case GLFW_KEY_LEFT_SUPER: return Key::LEFT_SUPER;
      case GLFW_KEY_LEFT_ALT: return Key::LEFT_ALT;
      case GLFW_KEY_SPACE: return Key::SPACE;
      case GLFW_KEY_RIGHT_ALT: return Key::RIGHT_ALT;
      case GLFW_KEY_RIGHT_SUPER: return Key::RIGHT_SUPER;
      case GLFW_KEY_RIGHT_CONTROL: return Key::RIGHT_CONTROL;
      case GLFW_KEY_UP: return Key::UP;
      case GLFW_KEY_DOWN: return Key::DOWN;
      case GLFW_KEY_LEFT: return Key::LEFT;
      case GLFW_KEY_RIGHT: return Key::RIGHT;
      case GLFW_KEY_PAGE_UP: return Key::PAGE_UP;
      case GLFW_KEY_PAGE_DOWN: return Key::PAGE_DOWN;
      case GLFW_KEY_HOME: return Key::HOME;
      case GLFW_KEY_END: return Key::END;
      case GLFW_KEY_KP_0: return Key::KP_0;
      case GLFW_KEY_KP_1: return Key::KP_1;
      case GLFW_KEY_KP_2: return Key::KP_2;
      case GLFW_KEY_KP_3: return Key::KP_3;
      case GLFW_KEY_KP_4: return Key::KP_4;
      case GLFW_KEY_KP_5: return Key::KP_5;
      case GLFW_KEY_KP_6: return Key::KP_6;
      case GLFW_KEY_KP_7: return Key::KP_7;
      case GLFW_KEY_KP_8: return Key::KP_8;
      case GLFW_KEY_KP_9: return Key::KP_9;
      case GLFW_KEY_KP_DECIMAL: return Key::KP_DECIMAL;
      case GLFW_KEY_KP_ADD: return Key::KP_ADD;
      case GLFW_KEY_KP_SUBTRACT: return Key::KP_SUBTRACT;
      case GLFW_KEY_KP_MULTIPLY: return Key::KP_MULTIPLY;
      case GLFW_KEY_KP_DIVIDE: return Key::KP_DIVIDE;
      case GLFW_KEY_KP_ENTER: return Key::KP_ENTER;
      case GLFW_KEY_CAPS_LOCK: return Key::CAPS_LOCK;
      case GLFW_KEY_SCROLL_LOCK: return Key::SCROLL_LOCK;
      case GLFW_KEY_NUM_LOCK: return Key::NUM_LOCK;
      default: return Key::UNKNOWN;
    }
  }

  I32 InputInterfaceImpl::resolveKeyCode (Key key) const 
  {
    switch (key)
    {
      case Key::ESCAPE: return GLFW_KEY_ESCAPE;
      case Key::F1: return GLFW_KEY_F1;
      case Key::F2: return GLFW_KEY_F2;
      case Key::F3: return GLFW_KEY_F3;
      case Key::F4: return GLFW_KEY_F4;
      case Key::F5: return GLFW_KEY_F5;
      case Key::F6: return GLFW_KEY_F6;
      case Key::F7: return GLFW_KEY_F7;
      case Key::F8: return GLFW_KEY_F8;
      case Key::F9: return GLFW_KEY_F9;
      case Key::F10: return GLFW_KEY_F10;
      case Key::F11: return GLFW_KEY_F11;
      case Key::F12: return GLFW_KEY_F12;
      case Key::PRINT_SCREEN: return GLFW_KEY_PRINT_SCREEN;
      case Key::INSERT: return GLFW_KEY_INSERT;
      case Key::DELETE: return GLFW_KEY_DELETE;
      case Key::GRAVE_ACCENT: return GLFW_KEY_GRAVE_ACCENT;
      case Key::NUM_1: return GLFW_KEY_1;
      case Key::NUM_2: return GLFW_KEY_2;
      case Key::NUM_3: return GLFW_KEY_3;
      case Key::NUM_4: return GLFW_KEY_4;
      case Key::NUM_5: return GLFW_KEY_5;
      case Key::NUM_6: return GLFW_KEY_6;
      case Key::NUM_7: return GLFW_KEY_7;
      case Key::NUM_8: return GLFW_KEY_8;
      case Key::NUM_9: return GLFW_KEY_9;
      case Key::NUM_0: return GLFW_KEY_0;
      case Key::MINUS: return GLFW_KEY_MINUS;
      case Key::EQUALS: return GLFW_KEY_EQUAL;
      case Key::BACKSPACE: return GLFW_KEY_BACKSPACE;
      case Key::TAB: return GLFW_KEY_TAB;
      case Key::Q: return GLFW_KEY_Q; 
      case Key::W: return GLFW_KEY_W; 
      case Key::E: return GLFW_KEY_E; 
      case Key::R: return GLFW_KEY_R; 
      case Key::T: return GLFW_KEY_T; 
      case Key::Y: return GLFW_KEY_Y; 
      case Key::U: return GLFW_KEY_U; 
      case Key::I: return GLFW_KEY_I; 
      case Key::O: return GLFW_KEY_O; 
      case Key::P: return GLFW_KEY_P;
      case Key::LEFT_BRACKET: return GLFW_KEY_LEFT_BRACKET; 
      case Key::RIGHT_BRACKET: return GLFW_KEY_RIGHT_BRACKET; 
      case Key::BACKSLASH: return GLFW_KEY_BACKSLASH;
      case Key::A: return GLFW_KEY_A;
      case Key::S: return GLFW_KEY_S;
      case Key::D: return GLFW_KEY_D;
      case Key::F: return GLFW_KEY_F;
      case Key::G: return GLFW_KEY_G;
      case Key::H: return GLFW_KEY_H;
      case Key::J: return GLFW_KEY_J;
      case Key::K: return GLFW_KEY_K;
      case Key::L: return GLFW_KEY_L;
      case Key::SEMICOLON: return GLFW_KEY_SEMICOLON;
      case Key::APOSTROPHE: return GLFW_KEY_APOSTROPHE;
      case Key::ENTER: return GLFW_KEY_ENTER;
      case Key::LEFT_SHIFT: return GLFW_KEY_LEFT_SHIFT;
      case Key::Z: return GLFW_KEY_Z;
      case Key::X: return GLFW_KEY_X;
      case Key::C: return GLFW_KEY_C;
      case Key::V: return GLFW_KEY_V;
      case Key::B: return GLFW_KEY_B;
      case Key::N: return GLFW_KEY_N;
      case Key::M: return GLFW_KEY_M;
      case Key::COMMA: return GLFW_KEY_COMMA;
      case Key::PERIOD: return GLFW_KEY_PERIOD;
      case Key::SLASH: return GLFW_KEY_SLASH;
      case Key::RIGHT_SHIFT: return GLFW_KEY_RIGHT_SHIFT;
      case Key::LEFT_CONTROL: return GLFW_KEY_LEFT_CONTROL;
      case Key::LEFT_SUPER: return GLFW_KEY_LEFT_SUPER;
      case Key::LEFT_ALT: return GLFW_KEY_LEFT_ALT;
      case Key::SPACE: return GLFW_KEY_SPACE;
      case Key::RIGHT_ALT: return GLFW_KEY_RIGHT_ALT;
      case Key::RIGHT_SUPER: return GLFW_KEY_RIGHT_SUPER;
      case Key::RIGHT_CONTROL: return GLFW_KEY_RIGHT_CONTROL;
      case Key::UP: return GLFW_KEY_UP;
      case Key::DOWN: return GLFW_KEY_DOWN;
      case Key::LEFT: return GLFW_KEY_LEFT;
      case Key::RIGHT: return GLFW_KEY_RIGHT;
      case Key::PAGE_UP: return GLFW_KEY_PAGE_UP;
      case Key::PAGE_DOWN: return GLFW_KEY_PAGE_DOWN;
      case Key::HOME: return GLFW_KEY_HOME;
      case Key::END: return GLFW_KEY_END;
      case Key::KP_0: return GLFW_KEY_KP_0;
      case Key::KP_1: return GLFW_KEY_KP_1;
      case Key::KP_2: return GLFW_KEY_KP_2;
      case Key::KP_3: return GLFW_KEY_KP_3;
      case Key::KP_4: return GLFW_KEY_KP_4;
      case Key::KP_5: return GLFW_KEY_KP_5;
      case Key::KP_6: return GLFW_KEY_KP_6;
      case Key::KP_7: return GLFW_KEY_KP_7;
      case Key::KP_8: return GLFW_KEY_KP_8;
      case Key::KP_9: return GLFW_KEY_KP_9;
      case Key::KP_DECIMAL: return GLFW_KEY_KP_DECIMAL;
      case Key::KP_ADD: return GLFW_KEY_KP_ADD;
      case Key::KP_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
      case Key::KP_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
      case Key::KP_DIVIDE: return GLFW_KEY_KP_DIVIDE;
      case Key::KP_ENTER: return GLFW_KEY_KP_ENTER;
      case Key::CAPS_LOCK: return GLFW_KEY_CAPS_LOCK;
      case Key::SCROLL_LOCK: return GLFW_KEY_SCROLL_LOCK;
      case Key::NUM_LOCK: return GLFW_KEY_NUM_LOCK;    
      default: return GLFW_KEY_UNKNOWN;
    }
  }

  MouseButton InputInterfaceImpl::resolveMouseButtonEnum (I32 buttonCode) const
  {
    switch (buttonCode)
    {
      case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::LEFT;
      case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::RIGHT;
      case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::MIDDLE;
      case GLFW_MOUSE_BUTTON_4: return MouseButton::SIDE1;
      case GLFW_MOUSE_BUTTON_5: return MouseButton::SIDE2;
      default: return MouseButton::UNKNOWN;
    }
  }

  I32 InputInterfaceImpl::resolveMouseButtonCode (MouseButton button) const
  {
    switch (button)
    {
      case MouseButton::LEFT:   return GLFW_MOUSE_BUTTON_LEFT;
      case MouseButton::RIGHT:  return GLFW_MOUSE_BUTTON_RIGHT;
      case MouseButton::MIDDLE: return GLFW_MOUSE_BUTTON_MIDDLE;
      case MouseButton::SIDE1:  return GLFW_MOUSE_BUTTON_4;
      case MouseButton::SIDE2:  return GLFW_MOUSE_BUTTON_5;
      default: return -1;
    }
  }  

  GamepadButton InputInterfaceImpl::resolveGamepadButtonEnum (I32 buttonCode) const
  {
    switch (buttonCode)
    {
      case GLFW_GAMEPAD_BUTTON_A: return GamepadButton::A;
      case GLFW_GAMEPAD_BUTTON_B: return GamepadButton::B;
      case GLFW_GAMEPAD_BUTTON_X: return GamepadButton::X;
      case GLFW_GAMEPAD_BUTTON_Y: return GamepadButton::Y;
      case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: return GamepadButton::LEFT_BUMPER;
      case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: return GamepadButton::RIGHT_BUMPER;
      case GLFW_GAMEPAD_BUTTON_BACK: return GamepadButton::BACK;
      case GLFW_GAMEPAD_BUTTON_START: return GamepadButton::START;
      case GLFW_GAMEPAD_BUTTON_GUIDE: return GamepadButton::GUIDE;
      case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: return GamepadButton::LEFT_THUMBSTICK;
      case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: return GamepadButton::RIGHT_THUMBSTICK;
      case GLFW_GAMEPAD_BUTTON_DPAD_UP: return GamepadButton::DPAD_UP;
      case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: return GamepadButton::DPAD_DOWN;
      case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: return GamepadButton::DPAD_RIGHT;
      case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: return GamepadButton::DPAD_LEFT;
      default: return GamepadButton::UNKNOWN;
    }
  }

  I32 InputInterfaceImpl::resolveGamepadButtonCode (GamepadButton button) const
  {
    switch (button)
    {
      case GamepadButton::A: return GLFW_GAMEPAD_BUTTON_A;
      case GamepadButton::B: return GLFW_GAMEPAD_BUTTON_B;
      case GamepadButton::X: return GLFW_GAMEPAD_BUTTON_X;
      case GamepadButton::Y: return GLFW_GAMEPAD_BUTTON_Y;
      case GamepadButton::LEFT_BUMPER: return GLFW_GAMEPAD_BUTTON_LEFT_BUMPER;
      case GamepadButton::RIGHT_BUMPER: return GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER;
      case GamepadButton::BACK: return GLFW_GAMEPAD_BUTTON_BACK;
      case GamepadButton::START: return GLFW_GAMEPAD_BUTTON_START;
      case GamepadButton::GUIDE: return GLFW_GAMEPAD_BUTTON_GUIDE;
      case GamepadButton::LEFT_THUMBSTICK: return GLFW_GAMEPAD_BUTTON_LEFT_THUMB;
      case GamepadButton::RIGHT_THUMBSTICK: return GLFW_GAMEPAD_BUTTON_RIGHT_THUMB;
      case GamepadButton::DPAD_UP: return GLFW_GAMEPAD_BUTTON_DPAD_UP;
      case GamepadButton::DPAD_DOWN: return GLFW_GAMEPAD_BUTTON_DPAD_DOWN;
      case GamepadButton::DPAD_RIGHT: return GLFW_GAMEPAD_BUTTON_DPAD_RIGHT;
      case GamepadButton::DPAD_LEFT: return GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
      default: return -1;
    }
  }

  GamepadAxis InputInterfaceImpl::resolveGamepadAxisEnum (I32 axisCode) const
  {
    switch (axisCode)
    {
      case GLFW_GAMEPAD_AXIS_LEFT_X: return GamepadAxis::LEFT_X;
      case GLFW_GAMEPAD_AXIS_LEFT_Y: return GamepadAxis::LEFT_Y;
      case GLFW_GAMEPAD_AXIS_RIGHT_X: return GamepadAxis::RIGHT_X;
      case GLFW_GAMEPAD_AXIS_RIGHT_Y: return GamepadAxis::RIGHT_Y;
      case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER: return GamepadAxis::LEFT_TRIGGER;
      case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER: return GamepadAxis::RIGHT_TRIGGER;
      default: return GamepadAxis::UNKNOWN;
    }
  }

  I32 InputInterfaceImpl::resolveGamepadAxisCode (GamepadAxis axis) const
  {
    switch (axis)
    {
      case GamepadAxis::LEFT_X: return GLFW_GAMEPAD_AXIS_LEFT_X;
      case GamepadAxis::LEFT_Y: return GLFW_GAMEPAD_AXIS_LEFT_Y;
      case GamepadAxis::RIGHT_X: return GLFW_GAMEPAD_AXIS_RIGHT_X;
      case GamepadAxis::RIGHT_Y: return GLFW_GAMEPAD_AXIS_RIGHT_Y;
      case GamepadAxis::LEFT_TRIGGER: return GLFW_GAMEPAD_AXIS_LEFT_TRIGGER;
      case GamepadAxis::RIGHT_TRIGGER: return GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
      default: return -1;
    }
  }

  bool InputInterfaceImpl::isKeyDown (Key key) const
  {
    return glfwGetKey(m_winptr, resolveKeyCode(key)) == GLFW_PRESS;
  }

  bool InputInterfaceImpl::isMouseButtonDown (MouseButton button) const
  {
    return glfwGetMouseButton(m_winptr, resolveMouseButtonCode(button)) == GLFW_PRESS;
  }

  Vector2f InputInterfaceImpl::getCursorPosition () const
  {
    double x, y;
    glfwGetCursorPos(m_winptr, &x, &y);
    return { static_cast<F32>(x), static_cast<F32>(y) };
  }

  bool InputInterfaceImpl::isGamepadPresent (I32 id) const
  {
    return glfwJoystickIsGamepad(id) == GLFW_TRUE;
  }

  bool InputInterfaceImpl::isGamepadButtonDown (GamepadButton button, I32 id) const
  {
    GLFWgamepadstate state;
    if (glfwGetGamepadState(id, &state) == GLFW_TRUE) {
      return state.buttons[resolveGamepadButtonCode(button)] == GLFW_PRESS;
    }

    return false;
  }

  F32 InputInterfaceImpl::getGamepadAxis (GamepadAxis axis, I32 id) const
  {
    GLFWgamepadstate state;
    if (glfwGetGamepadState(id, &state) == GLFW_TRUE) {
      return state.axes[resolveGamepadAxisCode(axis)];
    }

    return 0.0f;
  }
  
}
