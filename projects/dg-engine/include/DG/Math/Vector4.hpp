/** @file DG/Math/Vector4.hpp */

#pragma once

#include <DG/Math/Vector3.hpp>

namespace dg
{

  template <typename T>
  struct Vector4
  {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
      "[Vector4] 'T' must be an integer or floating-point number.");

    T x, y, z, w;

    static constexpr Count COMPONENT_COUNT = 4;

    inline const T* getPointer () const
    {
      return &x;
    }

    inline T getLength () const
    {
      return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
    }

    inline Vector4<T> getNormalized () const
    {
      if (x == 0 && y == 0 && z == 0 && w == 0) { return *this; }
      
      T length = getLength();
      return { x / length, y / length, z / length, w / length };
    }

    inline T getDot (const Vector4<T>& rhs) const
    {
      Vector4<T> nlhs = getNormalized(),
                 nrhs = rhs.getNormalized();

      return (nlhs.x * nrhs.x) + (nlhs.y * nrhs.y) + (nlhs.z * nrhs.z) + (nlhs.w * nrhs.w);
    }

    inline Vector3<T> getVector3 () const
    {
      if (w == 0) {
        DG_ENGINE_THROW(std::runtime_error,
          "[Vector4] Attempted division of vector's x, y and z components by zero!");
      }

      return { x / w, y / w, z / w };
    }

  };

  template <typename T>
  std::ostream& operator<< (std::ostream& stream, const Vector4<T>& vector)
  {
    stream << "[ " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << " ]";
    return stream;
  }

  template <typename T>
  inline Vector4<T> operator- (const Vector4<T>& lhs)
  {
    return { -lhs.x, -lhs.y, -lhs.z, -lhs.w };
  }

  

  template <typename T>
  inline Vector4<T> operator+ (const Vector4<T>& lhs, T rhs)
  {
    return { lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs };
  }
  
  template <typename T>
  inline Vector4<T> operator- (const Vector4<T>& lhs, T rhs)
  {
    return { lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs };
  }
  
  template <typename T>
  inline Vector4<T> operator* (const Vector4<T>& lhs, T rhs)
  {
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs };
  }
  
  template <typename T>
  inline Vector4<T> operator/ (const Vector4<T>& lhs, T rhs)
  {
    if (rhs == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Vector4] Attempted division of vector by zero!");
    }

    return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs };
  }



  template <typename T>
  inline Vector4<T>& operator+= (Vector4<T>& lhs, T rhs)
  {
    lhs.x += rhs;
    lhs.y += rhs;
    lhs.z += rhs;
    lhs.w += rhs;
    return lhs;
  }

  template <typename T>
  inline Vector4<T>& operator-= (Vector4<T>& lhs, T rhs)
  {
    lhs.x -= rhs;
    lhs.y -= rhs;
    lhs.z -= rhs;
    lhs.w -= rhs;
    return lhs;
  }

  template <typename T>
  inline Vector4<T>& operator*= (Vector4<T>& lhs, T rhs)
  {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    lhs.w *= rhs;
    return lhs;
  }

  template <typename T>
  inline Vector4<T>& operator/= (Vector4<T>& lhs, T rhs)
  {
    if (rhs == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Vector4] Attempted division of vector by zero!");
    }

    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    lhs.w /= rhs;
    return lhs;
  }



  template <typename T>
  inline Vector4<T> operator+ (const Vector4<T>& lhs, const Vector4<T>& rhs)
  {
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
  }

  template <typename T>
  inline Vector4<T> operator- (const Vector4<T>& lhs, const Vector4<T>& rhs)
  {
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
  }



  template <typename T>
  inline Vector4<T>& operator+= (Vector4<T>& lhs, const Vector4<T>& rhs)
  {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    lhs.w += rhs.w;
    return lhs;
  }

  template <typename T>
  inline Vector4<T>& operator-= (Vector4<T>& lhs, const Vector4<T>& rhs)
  {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    lhs.w -= rhs.w;
    return lhs;
  }

  using Vector4i = Vector4<I32>;
  using Vector4u = Vector4<U32>;
  using Vector4f = Vector4<F32>;

}
