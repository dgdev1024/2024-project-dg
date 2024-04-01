/** @file DG/Events/WindowEvents.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>
#include <DG/Events/Event.hpp>

namespace dg
{

  class WindowCloseEvent : public Event
  {
    DG_EVENT_IMPL(EventType::WindowClose)

  public:
    WindowCloseEvent () {}

  };

  class WindowResizeEvent : public Event
  {
    DG_EVENT_IMPL(EventType::WindowResize)

  public:
    WindowResizeEvent (U32 width, U32 height) :
      m_size { width, height }
    {}

  public:
    inline const Vector2u& getSize () const { return m_size; }
    inline U32 getWidth () const { return m_size.x; }
    inline U32 getHeight () const { return m_size.y; }

  private:
    Vector2u m_size;

  };

  class WindowFocusEvent : public Event
  {
    DG_EVENT_IMPL(EventType::WindowFocus)

  public:
    WindowFocusEvent () {}

  };

  class WindowBlurEvent : public Event
  {
    DG_EVENT_IMPL(EventType::WindowBlur)

  public:
    WindowBlurEvent () {}

  };

}
