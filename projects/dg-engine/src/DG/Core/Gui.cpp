/** @file DG/Core/Gui.cpp */

#include <DG/Core/Gui.hpp>

namespace dg
{

  Unique<GuiContext> Gui::s_context = nullptr;

  void Gui::initialize (const GuiContextSpecification& spec)
  {
    s_context = GuiContext::make(spec);
  }

  void Gui::shutdown ()
  {
    s_context.reset();
  }

  bool Gui::begin ()
  {
    if (s_context == nullptr || s_context->isEnabled() == false) {
      return false;
    }

    s_context->begin();
    return true;
  }

  void Gui::end ()
  {
    if (s_context->isEnabled() == true) {
      s_context->end();
    }
  }

}
