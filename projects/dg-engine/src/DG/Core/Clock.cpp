/** @file DG/Core/Clock.cpp */

#include <DG/Core/Clock.hpp>

namespace dg
{

  Clock::Clock () :
    m_startPoint { std::chrono::high_resolution_clock::now() }
  {

  }

  F32 Clock::getElapsed () const
  {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<F32> elapsed = m_startPoint - now;
    return elapsed.count();
  }

  F32 Clock::restart ()
  {
    auto elapsed = getElapsed();
    m_startPoint = std::chrono::high_resolution_clock::now();
    return elapsed;
  }

}
