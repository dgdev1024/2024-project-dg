/** @file DG/Events/Event.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  enum class EventType
  {
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowBlur,

    KeyDown,
    KeyUp,
    TextInput,

    MouseButtonDown,
    MouseButtonUp,
    MouseMotion,
    Scroll
  };

  class Event
  {
    friend class EventListener;

  protected:
    Event () = default;

  public:
    virtual ~Event () = default;
    
  public:
    virtual EventType getType () const = 0;
    virtual const Char* getName () const = 0;

  public:
    inline bool isHandled () const { return m_handled; }

  protected:
    bool m_handled = false;

  };

  #define DG_EVENT_IMPL(eventType) \
    public: \
      inline EventType getType () const override { return eventType; } \
      inline static EventType getStaticType () { return eventType; } \
      inline const Char* getName () const override { return #eventType; }

}
