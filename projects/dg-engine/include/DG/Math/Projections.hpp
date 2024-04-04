/** @file DG/Math/Projections.hpp */

#pragma once

#include <DG/Math/Matrix4.hpp>

namespace dg
{

  template <typename T>
  inline Matrix4<T> orthographic (const T left, const T right, const T bottom, const T top,
    const T near, const T far)
  {
    return {
      2 / (right - left),
      0,
      0,
      0,

      0,
      2 / (top - bottom),
      0,
      0,

      0,
      0,
      -2 / (far - near),
      0,

      -(right + left) / (right - left),
      -(top + bottom) / (top - bottom),
      -(far + near) / (far - near),
      1
    };
  }

  template <typename T>
  inline Matrix4<T> orthographic (const T size, const T aspectRatio, const T near, const T far)
  {
    return orthographic<T>(
      -size * aspectRatio * 0.5,
       size * aspectRatio * 0.5,
      -size * 0.5,
       size * 0.5,
      near,
      far
    );
  }

  template <typename T>
  inline Matrix4<T> perspective (const T fieldOfView, const T aspectRatio, const T near,
    const T far)
  {
    T cotHalfFov = 1 / std::tan(fieldOfView / 2);

    return {
      cotHalfFov / aspectRatio,
      0,
      0,
      0,

      0,
      cotHalfFov,
      0,
      0,

      0,
      0,
      (far + near) / (near - far),
      -1,

      0,
      0,
      (2 * far * near) / (near - far),
      0
    };
  }

}
