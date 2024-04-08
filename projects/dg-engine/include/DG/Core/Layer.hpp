/** @file DG/Core/Layer.hpp */

#pragma once

#include <DG/Events/EventListener.hpp>

namespace dg
{

  class Layer : public EventListener
  {
  protected:
    Layer (bool overlay = false) : m_overlay { overlay } {}

  public:
    virtual ~Layer () = default;

  public:
    virtual void onAttach () {}
    virtual void onDetach () {}
    virtual void listenForEvent (Event&) override {}
    virtual void fixedUpdate (const F32) {}
    virtual void update () {}
    virtual void guiUpdate () {}

  public:
    inline bool isOverlay () const { return m_overlay; }

  protected:
    bool m_overlay = false;

  };

}
