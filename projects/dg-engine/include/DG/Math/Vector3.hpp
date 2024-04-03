/** @file DG/Math/Vector3.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>

namespace dg
{

  template <typename T>
  struct Vector3
  {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
      "[Vector3] 'T' must be an integer or floating-point number.");

    T x, y, z;

    inline T getLength () const
    {
      return std::sqrt((x * x) + (y * y) + (z * z));
    }

    inline Vector3<T> getNormalized () const
    {
      if (x == 0 && y == 0 && z == 0) { return *this; }
      
      T length = getLength();
      return { x / length, y / length, z / length };
    }

    inline T getDot (const Vector3<T>& rhs) const
    {
      Vector3<T> nlhs = getNormalized(),
                 nrhs = rhs.getNormalized();

      return (nlhs.x * nrhs.x) + (nlhs.y * nrhs.y) + (nlhs.z * nrhs.z);
    }

    inline Vector3<T> getCross (const Vector3<T>& rhs) const
    {
      return {
        (y * rhs.z) - (z * rhs.y),
        (z * rhs.x) - (x * rhs.z),
        (x * rhs.y) - (y * rhs.x)
      };
    }

  };



  template <typename T>
  inline Vector3<T> operator- (const Vector3<T>& lhs)
  {
    return { -lhs.x, -lhs.y, -lhs.z };
  }

  

  template <typename T>
  inline Vector3<T> operator+ (const Vector3<T>& lhs, T rhs)
  {
    return { lhs.x + rhs, lhs.y + rhs, lhs.z + rhs };
  }
  
  template <typename T>
  inline Vector3<T> operator- (const Vector3<T>& lhs, T rhs)
  {
    return { lhs.x - rhs, lhs.y - rhs, lhs.z - rhs };
  }
  
  template <typename T>
  inline Vector3<T> operator* (const Vector3<T>& lhs, T rhs)
  {
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
  }
  
  template <typename T>
  inline Vector3<T> operator/ (const Vector3<T>& lhs, T rhs)
  {
    if (rhs == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Vector3] Attempted division of vector by zero!");
    }

    return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
  }



  template <typename T>
  inline Vector3<T>& operator+= (Vector3<T>& lhs, T rhs)
  {
    lhs.x += rhs;
    lhs.y += rhs;
    lhs.z += rhs;
    return lhs;
  }

  template <typename T>
  inline Vector3<T>& operator-= (Vector3<T>& lhs, T rhs)
  {
    lhs.x -= rhs;
    lhs.y -= rhs;
    lhs.z -= rhs;
    return lhs;
  }

  template <typename T>
  inline Vector3<T>& operator*= (Vector3<T>& lhs, T rhs)
  {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
  }

  template <typename T>
  inline Vector3<T>& operator/= (Vector3<T>& lhs, T rhs)
  {
    if (rhs == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Vector3] Attempted division of vector by zero!");
    }

    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
  }



  template <typename T>
  inline Vector3<T> operator+ (const Vector3<T>& lhs, const Vector3<T>& rhs)
  {
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
  }

  template <typename T>
  inline Vector3<T> operator- (const Vector3<T>& lhs, const Vector3<T>& rhs)
  {
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
  }



  template <typename T>
  inline Vector3<T>& operator+= (Vector3<T>& lhs, const Vector3<T>& rhs)
  {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
  }

  template <typename T>
  inline Vector3<T>& operator-= (Vector3<T>& lhs, const Vector3<T>& rhs)
  {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
  }

  using Vector3i = Vector3<I32>;
  using Vector3u = Vector3<U32>;
  using Vector3f = Vector3<F32>;

}
