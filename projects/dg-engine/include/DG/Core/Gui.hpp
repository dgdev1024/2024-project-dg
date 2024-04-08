/** @file DG/Core/Gui.hpp */

#pragma once

#include <DG/Core/GuiContext.hpp>

namespace dg
{

  class Gui
  {
  public:
    static void initialize (const GuiContextSpecification& spec = {});
    static void shutdown ();
    static bool begin ();
    static void end ();

  private:
    static Unique<GuiContext> s_context;

  };

}
