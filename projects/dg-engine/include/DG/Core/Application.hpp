/** @file DG/Core/Application.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  /**
   * @brief The @a `ApplicationSpecification` struct describes properties used
   *        to define the DG Engine's client @a `Application`.
   */
  struct ApplicationSpecification
  {
    
    /**
     * @brief The application's maximum framerate. This is used to determine its
     *        fixed timestep.
     */
    float framerate = 60.0f;

  };

  /**
   * @brief The @a `Application` class is the base class for the DG Engine's
   *        client applications.
   */
  class Application
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

    /**
     * @brief Starts the client application's application loop.
     */
    void start ();

  protected:

    /**
     * @brief The application's fixed timestep. This determines how frequently
     *        the @a `fixedUpdate` method is called.
     */
    float m_timestep = 0.0f;

  };

}
