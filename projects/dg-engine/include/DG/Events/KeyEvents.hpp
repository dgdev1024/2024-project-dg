/** @file DG/Events/KeyEvents.hpp */

#pragma once

#include <DG/Events/Event.hpp>

namespace dg
{

  class KeyEvent : public Event
  {
  protected:
    KeyEvent (U32 keycode) : m_keycode { keycode } {}

  public:
    inline U32 getKeycode () const { return m_keycode; }

  protected:
    U32 m_keycode = 0;

  };

  class KeyDownEvent : public KeyEvent
  {
    DG_EVENT_IMPL(EventType::KeyDown)

  public:
    KeyDownEvent (U32 keycode) : KeyEvent { keycode } {}

  };

  class KeyUpEvent : public KeyEvent
  {
    DG_EVENT_IMPL(EventType::KeyUp)

  public:
    KeyUpEvent (U32 keycode) : KeyEvent { keycode } {}
    
  };

  class TextInputEvent : public Event
  {
    DG_EVENT_IMPL(EventType::TextInput)

  public:
    TextInputEvent (U32 codepoint) : m_codepoint { codepoint } {}

  public:
    inline U32 getCodepoint () const { return m_codepoint; }

  private:
    U32 m_codepoint = 0;

  };

}
