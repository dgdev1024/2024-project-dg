/** @file DG/Core/Window.hpp */

#pragma once

#include <DG_Pch.hpp>
#include <DG/Events/EventEmitter.hpp>

namespace dg
{

  struct WindowSpecification
  {
    String title = "DG Engine Application";
    Vector2u size = { 1280, 720 };
  };

  class Window : public EventEmitter
  {
  protected:
    Window (const WindowSpecification& spec) :
      m_title { spec.title },
      m_size { spec.size }
    {}

  public:
    virtual ~Window () = default;

  public:
    static Unique<Window> make (const WindowSpecification& spec = {});

  public:
    virtual void update () = 0;
    virtual void* getPointer () const = 0;

  public:
    inline const String& getTitle () const { return m_title; }
    inline const Vector2u& getSize () const { return m_size; }

    inline void setTitle (const String& title) { m_title = title; onTitleChanged(); }
    inline void setSize (const Vector2u& size) { m_size = size; onSizeChanged(); }

  protected:
    virtual void onTitleChanged () = 0;
    virtual void onSizeChanged () = 0;

  protected:
    String m_title;
    Vector2u m_size;

  };

}
