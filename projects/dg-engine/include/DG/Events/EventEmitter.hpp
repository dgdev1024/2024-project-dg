/** @file DG/Events/EventEmitter.hpp */

#pragma once

#include <DG/Core/Application.hpp>
#include <DG/Events/EventBus.hpp>

namespace dg
{

  class EventEmiter
  {
  public:

    template <typename T, typename... Us>
    inline void emitEvent (
      Us&&... eventArgs
    )
    {
      static_assert(std::is_base_of_v<Event, T>, "'T' must derive from 'dg::Event'.");
      Application::getEventBus().emplace<T>(std::forward<Us>(eventArgs)...);
    }

  };

}
