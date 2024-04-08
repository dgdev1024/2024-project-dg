/** @file DG/Events/MouseEvents.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>
#include <DG/Events/Event.hpp>

namespace dg
{

  class MouseButtonEvent : public Event
  {
  protected:
    MouseButtonEvent (U32 buttonCode, bool ctrl, bool alt, bool shift, bool super) : 
      m_buttonCode { buttonCode },
      m_ctrl { ctrl },
      m_alt { alt },
      m_shift { shift },
      m_super { super }
    {}

  public:
    inline U32 getButtonCode () const { return m_buttonCode; }
    inline bool isCtrlDown () const { return m_ctrl; }
    inline bool isAltDown () const { return m_alt; }
    inline bool isShiftDown () const { return m_shift; }
    inline bool isSuperDown () const { return m_super; }

  protected:
    U32 m_buttonCode = 0;
    bool m_ctrl = false;
    bool m_alt = false;
    bool m_shift = false;
    bool m_super = false;

  };

  class MouseButtonDownEvent : public MouseButtonEvent
  {
    DG_EVENT_IMPL(EventType::MouseButtonDown)

  public:
    MouseButtonDownEvent (U32 buttonCode, bool ctrl, bool alt, bool shift, bool super) : 
      MouseButtonEvent { buttonCode, ctrl, alt, shift, super } {}

  };

  class MouseButtonUpEvent : public MouseButtonEvent
  {
    DG_EVENT_IMPL(EventType::MouseButtonUp)

  public:
    MouseButtonUpEvent (U32 buttonCode, bool ctrl, bool alt, bool shift, bool super) : 
      MouseButtonEvent { buttonCode, ctrl, alt, shift, super } {}

  };

  class MouseMotionEvent : public Event
  {
    DG_EVENT_IMPL(EventType::MouseMotion)

  public:
    MouseMotionEvent (F32 x, F32 y) : m_position { x, y } {}

  public:
    inline const Vector2f& getPosition () const { return m_position; }
    inline F32 getX () const { return m_position.x; }
    inline F32 getY () const { return m_position.y; }

  private:
    Vector2f m_position;

  };

  class MouseEnterEvent : public Event
  {
    DG_EVENT_IMPL(EventType::MouseEnter)

  public:
    MouseEnterEvent () {}

  };  

  class MouseLeaveEvent : public Event
  {
    DG_EVENT_IMPL(EventType::MouseLeave)

  public:
    MouseLeaveEvent () {}

  };  

  class ScrollEvent : public Event
  {
    DG_EVENT_IMPL(EventType::Scroll)

  public:
    ScrollEvent (F32 x, F32 y) : m_offset { x, y } {}

  public:
    inline const Vector2f& getOffset () const { return m_offset; }
    inline F32 getHorizontal () const { return m_offset.x; }
    inline F32 getVertical () const { return m_offset.y; }

  private:
    Vector2f m_offset;

  };

}
