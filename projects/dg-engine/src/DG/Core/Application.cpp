/** @file DG/Core/Application.cpp */

#include <DG/Graphics/RenderCommand.hpp>
#include <DG/Core/Input.hpp>
#include <DG/Core/Clock.hpp>
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
    m_window    = Window::make(spec.windowSpec);
    m_renderer  = Renderer::make();
    Input::initialize();

    if (spec.guiSpec.enabled == true) {
      Gui::initialize(spec.guiSpec);
    }
  }

  Application::~Application ()
  {
    Gui::shutdown();
    Input::shutdown();
    m_renderer.reset();
    m_window.reset();
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

  Window& Application::getWindow ()
  {
    assert(s_instance != nullptr);
    return *s_instance->m_window;
  }

  Renderer& Application::getRenderer ()
  {
    assert(s_instance != nullptr);
    return *s_instance->m_renderer;
  }

  /** Start Application Loop **************************************************/

  void Application::start ()
  {
    Clock lagClock;
    F32 lagTime = 0.0f, elapsedTime = 0.0f;

    while (m_running == true)
    {
      elapsedTime = lagClock.restart();
      lagTime += elapsedTime;

      m_eventBus->poll();
      while (lagTime >= m_timestep)
      {
        lagTime -= m_timestep;
        fixedUpdate();
      }

      update();
    }
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
    RenderCommand::clear();

    if (Gui::begin() == true) {

      Gui::end();
    }

    m_window->update();
  }

}
