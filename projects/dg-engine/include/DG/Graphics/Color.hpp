/** @file DG/Graphics/Color.hpp */

#pragma once

#include <DG/Math/Vector4.hpp>
#include <DG/Math/MathUtils.hpp>

namespace dg
{

  namespace Color
  {

    constexpr Vector4f BLACK    = { 0.0f, 0.0f, 0.0f, 1.0f };
    constexpr Vector4f WHITE    = { 1.0f, 1.0f, 1.0f, 1.0f };
    constexpr Vector4f RED      = { 1.0f, 0.0f, 0.0f, 1.0f };
    constexpr Vector4f GREEN    = { 0.0f, 1.0f, 0.0f, 1.0f };
    constexpr Vector4f BLUE     = { 0.0f, 0.0f, 1.0f, 1.0f };

    inline Vector4f fromRGBA8 (I32 red, I32 green, I32 blue, I32 alpha = 255)
    {
      return {
        clamp<I32>(red, 0, 255)     / 255.0f,
        clamp<I32>(green, 0, 255)   / 255.0f,
        clamp<I32>(blue, 0, 255)    / 255.0f,
        clamp<I32>(alpha, 0, 255)   / 255.0f
      };
    }

    inline Vector4f fromRGB5 (I32 red, I32 green, I32 blue)
    {
      return {
        clamp<I32>(red, 0, 31)      / 31.0f,
        clamp<I32>(green, 0, 31)    / 31.0f,
        clamp<I32>(blue, 0, 31)     / 31.0f,
        1.0f
      };
    }

  }

}
