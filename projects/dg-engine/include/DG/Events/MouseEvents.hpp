/** @file DG/Events/MouseEvents.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>
#include <DG/Events/Event.hpp>

namespace dg
{

  class MouseButtonEvent : public Event
  {
  protected:
    MouseButtonEvent (U32 buttonCode) : m_buttonCode { buttonCode } {}

  public:
    inline U32 getButtonCode () const { return m_buttonCode; }

  protected:
    U32 m_buttonCode = 0;

  };

  class MouseButtonDownEvent : public MouseButtonEvent
  {
    DG_EVENT_IMPL(EventType::MouseButtonDown)

  public:
    MouseButtonDownEvent (U32 buttonCode) : MouseButtonEvent { buttonCode } {}

  };

  class MouseButtonUpEvent : public MouseButtonEvent
  {
    DG_EVENT_IMPL(EventType::MouseButtonUp)

  public:
    MouseButtonUpEvent (U32 buttonCode) : MouseButtonEvent { buttonCode } {}

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
