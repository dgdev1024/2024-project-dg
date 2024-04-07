/** @file DG/Events/EventBus.cpp */

#include <DG/Events/EventBus.hpp>

namespace dg
{

  EventBus* EventBus::s_instance = nullptr;

  EventBus::EventBus (EventListener& topLevelListener) :
    m_topLevelListener { topLevelListener }
  {
    if (s_instance != nullptr) {
      DG_ENGINE_THROW(std::runtime_error, "Singleton event bus instance already exists!");
    } else {
      s_instance = this;
    }
  }

  EventBus::~EventBus ()
  {
    s_instance = nullptr;
  }

  EventBus& EventBus::get ()
  {
    assert(s_instance != nullptr);
    return *s_instance;
  }

}
