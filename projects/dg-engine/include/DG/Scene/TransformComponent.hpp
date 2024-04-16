/** @file DG/Scene/TransformComponent.hpp */

#pragma once

#include <DG/Math/Transforms.hpp>

namespace dg
{

  struct TransformComponent
  {
    Matrix4f transform = Matrix4f::IDENTITY;
  };

}
