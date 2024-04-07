/** @file DG/Graphics/Renderer.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  class Renderer
  {
  public:
    Renderer ();
    ~Renderer ();

  public:
    static Unique<Renderer> make ();

  };

}
