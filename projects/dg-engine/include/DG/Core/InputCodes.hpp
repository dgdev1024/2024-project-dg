/** @file DG/Core/InputCodes.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  enum class Key
  {
    UNKNOWN,
    ESCAPE,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    PRINT_SCREEN,
    INSERT,
    DELETE,
    GRAVE_ACCENT,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    NUM_0,
    MINUS,
    EQUALS,
    BACKSPACE,
    TAB,
    Q, 
    W, 
    E, 
    R, 
    T, 
    Y, 
    U, 
    I, 
    O, 
    P,
    LEFT_BRACKET, 
    RIGHT_BRACKET, 
    BACKSLASH,
    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,
    SEMICOLON,
    APOSTROPHE,
    ENTER,
    LEFT_SHIFT,
    Z,
    X,
    C,
    V,
    B,
    N,
    M,
    COMMA,
    PERIOD,
    SLASH,
    RIGHT_SHIFT,
    LEFT_CONTROL,
    LEFT_SUPER,
    LEFT_ALT,
    SPACE,
    RIGHT_ALT,
    RIGHT_SUPER,
    RIGHT_CONTROL,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PAGE_UP,
    PAGE_DOWN,
    HOME,
    END,
    KP_0,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,
    KP_9,
    KP_DECIMAL,
    KP_ADD,
    KP_SUBTRACT,
    KP_MULTIPLY,
    KP_DIVIDE,
    KP_ENTER,
    CAPS_LOCK,
    SCROLL_LOCK,
    NUM_LOCK
  };

  enum class KeyModifier
  {
    NONE,
    SHIFT,
    CONTROL,
    ALT,
    SUPER
  };

  enum class MouseButton
  {
    UNKNOWN,
    LEFT,
    RIGHT,
    MIDDLE,
    SIDE1,
    SIDE2
  };

  enum class GamepadButton
  {
    UNKNOWN,
    A,
    B,
    X,
    Y,
    LEFT_BUMPER,
    RIGHT_BUMPER,
    BACK,
    START,
    GUIDE,
    LEFT_THUMBSTICK,
    RIGHT_THUMBSTICK,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_RIGHT,
    DPAD_LEFT,

    CROSS = A,
    CIRCLE = B,
    SQUARE = X,
    TRIANGLE = Y,
    SELECT = BACK
  };

  enum class GamepadAxis
  {
    UNKNOWN,
    LEFT_X,
    LEFT_Y,
    RIGHT_X,
    RIGHT_Y,
    LEFT_TRIGGER,
    RIGHT_TRIGGER
  };

}
