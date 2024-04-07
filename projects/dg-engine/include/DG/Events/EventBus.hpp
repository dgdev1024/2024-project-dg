/** @file DG/Events/EventBus.hpp */

#pragma once

#include <DG/Events/EventListener.hpp>

namespace dg
{

  class EventBus
  {
  public:
    EventBus (EventListener& topLevelListener);
    ~EventBus ();

    static EventBus& get ();

    inline static Unique<EventBus> make (
      EventListener& topLevelListener
    )
    {
      return std::make_unique<EventBus>(topLevelListener);
    }

    inline void poll ()
    {
      for (auto& event : m_events)
      {
        m_topLevelListener.listenForEvent(*event);
      }

      m_events.clear();
    }

    template <typename T, typename... Us>
    inline void emplace (
      Us&&... eventArgs
    )
    {
      static_assert(std::is_base_of_v<Event, T>, "'T' must derive from 'dg::Event'.");
      m_events.emplace_back(std::make_unique<T>(std::forward<Us>(eventArgs)...));
    }

  private:
    static EventBus* s_instance;
    EventListener& m_topLevelListener;
    Collection<Unique<Event>> m_events;

  };

}
