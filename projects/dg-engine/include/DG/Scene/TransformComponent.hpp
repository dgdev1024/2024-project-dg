/** @file DG/Scene/TransformComponent.hpp */

#pragma once

#include <DG/Math/Transforms.hpp>

namespace dg
{

  struct TransformComponent
  {
    Matrix4f transform = Matrix4f::IDENTITY;

    inline void applyRotation (F32 angle, const Vector3f& axis, bool degrees = true)
    {
      transform = rotate(transform, (degrees == false) ? angle : radians(angle), axis);
    }

    inline void applyRotation (F32 angle, bool degrees = true)
    {
      applyRotation(angle, { 0.0f, 0.0f, -1.0f }, degrees);
    }

  };

}
