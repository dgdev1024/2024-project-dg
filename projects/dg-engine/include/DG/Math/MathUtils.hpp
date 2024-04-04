/** @file DG/Math/MathUtils.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  template <typename T>
  constexpr T PI = 3.14159265359;

  template <typename T>
  constexpr T EPSILON = 0.0001;

  template <typename T>
  inline T radians (const T angle)
  {
    return angle * (PI<T> / 180.0);
  }

  template <typename T>
  inline T degrees (const T angle)
  {
    return angle * (180.0 / PI<T>);
  }

  template <typename T>
  inline T clamp (T number, T low, T high)
  {
    if (number < low) { return low; }
    else if (number > high) { return high; }
    else { return number; }
  }

  template <typename T>
  inline bool floatEquals (T lhs, T rhs)
  {
    static_assert(std::is_floating_point_v<T>,
      "[floatEquals] 'T' must be a floating-point number.");

    return ((rhs - EPSILON<T>) < lhs) && (lhs < (rhs + EPSILON<T>));
  }

}
