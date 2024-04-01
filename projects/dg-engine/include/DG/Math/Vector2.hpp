/** @file DG/Math/Vector2.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  template <typename T>
  struct Vector2
  {
    T x, y;
  };

  using Vector2i = Vector2<I32>;
  using Vector2u = Vector2<U32>;
  using Vector2f = Vector2<F32>;

}
