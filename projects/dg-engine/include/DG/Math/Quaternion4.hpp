/** @file DG/Math/Quaternion4.hpp */

#pragma once

#include <DG/Math/Matrix4.hpp>

namespace dg
{

  template <typename T>
  struct Quaternion4
  {
    static_assert(std::is_floating_point_v<T>,
      "[Quaternion4] 'T' must be a floating-point number.");

    T x, y, z, w;

    Quaternion4 () = default;

    Quaternion4 (T angleInRadians, const Vector3<T>& axis)
    {
      Vector3<T> normalized = axis.getNormalized();

      T halfAngle = angleInRadians / 2;
      T sine = std::sin(halfAngle);
      T cosine = std::cos(halfAngle);

      x = normalized.x * sine;
      y = normalized.y * sine;
      z = normalized.z * sine;
      w = cosine;
    }

    Quaternion4 (T pitch, T yaw, T roll)
    {
      T halfPitch = pitch / 2;
      T halfYaw   = yaw / 2;
      T halfRoll  = roll / 2;

      T pitchSine = std::sin(halfPitch);
      T yawSine   = std::sin(halfYaw);
      T rollSine  = std::sin(halfRoll);
      
      T pitchCosine = std::cos(halfPitch);
      T yawCosine   = std::cos(halfYaw);
      T rollCosine  = std::cos(halfRoll);

      x = rollCosine * pitchSine * yawCosine - rollSine * pitchCosine * yawSine;
      y = rollCosine * pitchCosine * yawSine + rollSine * pitchSine * yawCosine;
      z = rollSine * pitchCosine * yawCosine - rollCosine * pitchSine * yawSine;
      w = rollCosine * pitchCosine * yawCosine + rollSine * pitchSine * yawSine;      
    }

    Quaternion4 (const Vector3<T>& eulerAngles) :
      Quaternion4 { eulerAngles.x, eulerAngles.y, eulerAngles.z }
    {}

    Quaternion4 (T x, T y, T z, T w) :
      x { x }, y { y }, z { z }, w { w } {}

    inline operator Vector4<T> () const
    {
      return { x, y, z, w };
    }

    inline Matrix4<T> toMatrix4 () const
    {
      T xx = x * x;
      T yy = y * y;
      T zz = z * z;
      T xz = x * z;
      T xy = x * y;
      T yz = y * z;
      T wx = w * x;
      T wy = w * y;
      T wz = w * z;

      return {
        1 - 2 * (yy + zz),  2 * (xy - wz),      2 * (xz + wy),      0,
        2 * (xy + wz),      1 - 2 * (xx + zz),  2 * (yz - wx),      0,
        2 * (xz - wy),      2 * (yz + wx),      1 - 2 * (xx + yy),  0,
        0, 0, 0, 1
      };
    }

  };

  using Quaternion4f = Quaternion4<F32>;

}
