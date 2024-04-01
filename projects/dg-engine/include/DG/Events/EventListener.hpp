/** @file DG/Events/EventListener.hpp */

#pragma once

#include <DG/Events/WindowEvents.hpp>
#include <DG/Events/KeyEvents.hpp>
#include <DG/Events/MouseEvents.hpp>

namespace dg
{

  class EventListener
  {
  public:
  
    virtual void listenForEvent (
      Event& ev
    ) = 0;

  protected:
    
    template <typename T>
    inline void onEvent (
      Event& ev,
      const Function<bool, T&>& handler
    )
    {
      static_assert(std::is_base_of_v<Event, T>, "'T' must derive from 'dg::Event'.");
      if (
        ev.getType() == T::getStaticType() &&
        ev.isHandled() == false &&
        handler != nullptr
      ) {
        ev.m_handled = handler(static_cast<T&>(ev));
      }
    }

  };

}
