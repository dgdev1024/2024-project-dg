/** @file DG/Scene/QuadComponent.hpp */

#pragma once

#include <DG/Graphics/Color.hpp>
#include <DG/Graphics/Texture.hpp>

namespace dg
{

  struct QuadComponent
  {
    Vector4f color = Color::WHITE;
    Shared<Texture> texture = nullptr;
  };

}
