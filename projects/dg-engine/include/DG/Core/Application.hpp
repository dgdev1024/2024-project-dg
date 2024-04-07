/** @file DG/Core/Application.hpp */

#pragma once

#include <DG_Pch.hpp>
#include <DG/Graphics/Renderer.hpp>
#include <DG/Core/Window.hpp>
#include <DG/Events/EventBus.hpp>

namespace dg
{

  /**
   * @brief The @a `ApplicationSpecification` struct describes properties used
   *        to define the DG Engine's client @a `Application`.
   */
  struct ApplicationSpecification
  {

    WindowSpecification windowSpec;
    
    /**
     * @brief The application's maximum framerate. This is used to determine its
     *        fixed timestep.
     */
    F32 framerate = 60.0f;

  };

  /**
   * @brief The @a `Application` class is the base class for the DG Engine's
   *        client applications.
   */
  class Application : public EventListener
  {
  protected:

    /**
     * @brief Constructs an @a `Application` instance using the given
     *        @a `ApplicationSpecification`.
     * 
     * @param spec  The application's specification. 
     */
    Application (
      const ApplicationSpecification& spec = {}
    );

  public:
    virtual ~Application ();

  public:
    static Application& get ();
    static EventBus& getEventBus ();
    static Window& getWindow ();
    static Renderer& getRenderer ();

  public:

    /**
     * @brief Starts the client application's application loop.
     */
    void start ();

  protected:
    void listenForEvent (Event& ev) override;
    void fixedUpdate ();
    void update ();

  protected:

    /**
     * @brief A pointer to the singleton @a `Application` instance.
     */
    static Application* s_instance;

    /**
     * @brief A pointer to the client application's central event bus.
     */
    Unique<EventBus> m_eventBus = nullptr;

    Unique<Window> m_window = nullptr;

    Unique<Renderer> m_renderer = nullptr;

    bool m_running = true;

    /**
     * @brief The application's fixed timestep. This determines how frequently
     *        the @a `fixedUpdate` method is called.
     */
    F32 m_timestep = 0.0f;

  };

}
