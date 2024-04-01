/** @file DG/Core/Application.cpp */

#include <DG/Core/Logging.hpp>
#include <DG/Core/Application.hpp>

namespace dg
{

  /** Singleton Instnace ******************************************************/

  Application* Application::s_instance = nullptr;

  /** Constructor and Destructor **********************************************/

  Application::Application (
    const ApplicationSpecification& spec
  ) :
    m_timestep  { 1.0f / spec.framerate }
  {
    if (s_instance != nullptr) {
      DG_ENGINE_THROW(std::runtime_error, "Singleton application instance already exists!");
    } else {
      s_instance = this;
    }

    Logging::initialize();
    m_eventBus  = EventBus::make(*this);
  }

  Application::~Application ()
  {
    m_eventBus.reset();
    s_instance = nullptr;
  }

  /** Singleton Retrieval *****************************************************/

  Application& Application::get () 
  {
    assert(s_instance != nullptr);
    return *s_instance;
  }

  EventBus& Application::getEventBus ()
  {
    assert(s_instance != nullptr);
    return *s_instance->m_eventBus;
  }

  /** Start Application Loop **************************************************/

  void Application::start ()
  {
    
  }

  /** Application Loop Methods ************************************************/

  void Application::listenForEvent (Event& ev)
  {

    onEvent<WindowCloseEvent>(ev, [&] (WindowCloseEvent&)
    {
      m_running = false;
      return true;
    });

  }

  void Application::fixedUpdate ()
  {

  }

  void Application::update ()
  {

  }

}
