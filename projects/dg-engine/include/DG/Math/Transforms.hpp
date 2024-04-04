/** @file DG/Math/Transforms.hpp */

#pragma once

#include <DG/Math/Matrix4.hpp>
#include <DG/Math/Quaternion4.hpp>

namespace dg
{

  template <typename T>
  inline Matrix4<T> translate (const Matrix4<T>& matrix, const Vector3<T>& vector)
  {
    Matrix4<T> translation = Matrix4<T>::IDENTITY;
    translation.da = vector.x;
    translation.db = vector.y;
    translation.dc = vector.z;

    return translation * matrix;
  }

  template <typename T>
  inline Matrix4<T> rotate (const Matrix4<T>& matrix, const T& angle, const Vector3<T>& axis)
  {
    Quaternion4<T> quat { angle, axis };
    return quat.toMatrix4() * matrix;
  }

  template <typename T>
  inline Matrix4<T> scale (const Matrix4<T>& matrix, const Vector3<T>& vector)
  {
    Matrix4<T> scaling = Matrix4<T>::IDENTITY;
    scaling.aa = vector.x;
    scaling.bb = vector.y;
    scaling.cc = vector.z;

    return scaling * matrix;
  }

}
