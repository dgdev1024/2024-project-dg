/** @file DG/Events/KeyEvents.hpp */

#pragma once

#include <DG/Events/Event.hpp>

namespace dg
{

  class KeyEvent : public Event
  {
  protected:
    KeyEvent (I32 keycode, bool ctrl, bool alt, bool shift, bool super) : 
      m_keycode { keycode },
      m_ctrl { ctrl },
      m_alt { alt },
      m_shift { shift },
      m_super { super }
    {}

  public:
    inline I32 getKeycode () const { return m_keycode; }
    inline bool isCtrlDown () const { return m_ctrl; }
    inline bool isAltDown () const { return m_alt; }
    inline bool isShiftDown () const { return m_shift; }
    inline bool isSuperDown () const { return m_super; }

  protected:
    I32 m_keycode = 0;
    bool m_ctrl = false;
    bool m_alt = false;
    bool m_shift = false;
    bool m_super = false;

  };

  class KeyDownEvent : public KeyEvent
  {
    DG_EVENT_IMPL(EventType::KeyDown)

  public:
    KeyDownEvent (I32 keycode, bool ctrl, bool alt, bool shift, bool super) : 
      KeyEvent { keycode, ctrl, alt, shift, super } {}

  };

  class KeyUpEvent : public KeyEvent
  {
    DG_EVENT_IMPL(EventType::KeyUp)

  public:
    KeyUpEvent (I32 keycode, bool ctrl, bool alt, bool shift, bool super) : 
      KeyEvent { keycode, ctrl, alt, shift, super } {}
    
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
