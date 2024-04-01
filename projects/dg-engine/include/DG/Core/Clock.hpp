/** @file DG/Core/Clock.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  class Clock
  {
  public:
    Clock ();
    F32 getElapsed () const;
    F32 restart ();

  private:
    std::chrono::high_resolution_clock::time_point m_startPoint;

  };

}
