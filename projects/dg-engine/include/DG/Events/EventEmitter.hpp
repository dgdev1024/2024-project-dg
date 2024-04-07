/** @file DG/Events/EventEmitter.hpp */

#pragma once

#include <DG/Events/EventBus.hpp>

namespace dg
{

  class EventEmitter
  {
  public:

    template <typename T, typename... Us>
    inline void emitEvent (
      Us&&... eventArgs
    )
    {
      static_assert(std::is_base_of_v<Event, T>, "'T' must derive from 'dg::Event'.");
      EventBus::get().emplace<T>(std::forward<Us>(eventArgs)...);
    }

  };

}
