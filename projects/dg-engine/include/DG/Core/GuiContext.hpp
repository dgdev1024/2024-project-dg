/** @file DG/Core/GuiContext.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  struct GuiContextSpecification
  {
    bool enabled = false;
    bool docking = false;
    bool viewport = false;
  };

  class GuiContext
  {
  protected:
    GuiContext (const GuiContextSpecification& spec) :
      m_enabled { spec.enabled },
      m_docking { spec.docking },
      m_viewport { spec.viewport }
    {}

  public:
    virtual ~GuiContext () = default;
    static Unique<GuiContext> make (const GuiContextSpecification& spec = {});

  public:
    virtual void begin () = 0;
    virtual void end () = 0;

  public:
    inline bool isEnabled () const { return m_enabled; }

  protected:
    bool m_enabled = false;
    bool m_docking = false;
    bool m_viewport = false;

  };

}
