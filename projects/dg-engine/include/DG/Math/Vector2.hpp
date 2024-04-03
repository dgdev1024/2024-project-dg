/** @file DG/Math/Vector2.hpp */

#pragma once

#include <DG_Pch.hpp>

namespace dg
{

  template <typename T>
  struct Vector2
  {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
      "[Vector2] 'T' must be an integer or floating-point number.");

    T x, y;

    inline T getLength () const
    {
      return std::sqrt((x * x) + (y * y));
    }

    inline Vector2<T> getNormalized () const
    {
      if (x == 0 && y == 0) { return *this; }
      
      T length = getLength();
      return { x / length, y / length };
    }

    inline T getDot (const Vector2<T>& rhs) const
    {
      Vector2<T> nlhs = getNormalized(),
                 nrhs = rhs.getNormalized();

      return (nlhs.x * nrhs.x) + (nlhs.y * nrhs.y);
    }

  };



  template <typename T>
  inline Vector2<T> operator- (const Vector2<T>& lhs)
  {
    return { -lhs.x, -lhs.y };
  }

  

  template <typename T>
  inline Vector2<T> operator+ (const Vector2<T>& lhs, T rhs)
  {
    return { lhs.x + rhs, lhs.y + rhs };
  }
  
  template <typename T>
  inline Vector2<T> operator- (const Vector2<T>& lhs, T rhs)
  {
    return { lhs.x - rhs, lhs.y - rhs };
  }
  
  template <typename T>
  inline Vector2<T> operator* (const Vector2<T>& lhs, T rhs)
  {
    return { lhs.x * rhs, lhs.y * rhs };
  }
  
  template <typename T>
  inline Vector2<T> operator/ (const Vector2<T>& lhs, T rhs)
  {
    if (rhs == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Vector2] Attempted division of vector by zero!");
    }

    return { lhs.x / rhs, lhs.y / rhs };
  }



  template <typename T>
  inline Vector2<T>& operator+= (Vector2<T>& lhs, T rhs)
  {
    lhs.x += rhs;
    lhs.y += rhs;
    return lhs;
  }

  template <typename T>
  inline Vector2<T>& operator-= (Vector2<T>& lhs, T rhs)
  {
    lhs.x -= rhs;
    lhs.y -= rhs;
    return lhs;
  }

  template <typename T>
  inline Vector2<T>& operator*= (Vector2<T>& lhs, T rhs)
  {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
  }

  template <typename T>
  inline Vector2<T>& operator/= (Vector2<T>& lhs, T rhs)
  {
    if (rhs == 0) {
      DG_ENGINE_THROW(std::invalid_argument,
        "[Vector2] Attempted division of vector by zero!");
    }

    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
  }



  template <typename T>
  inline Vector2<T> operator+ (const Vector2<T>& lhs, const Vector2<T>& rhs)
  {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
  }

  template <typename T>
  inline Vector2<T> operator- (const Vector2<T>& lhs, const Vector2<T>& rhs)
  {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
  }



  template <typename T>
  inline Vector2<T>& operator+= (Vector2<T>& lhs, const Vector2<T>& rhs)
  {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
  }

  template <typename T>
  inline Vector2<T>& operator-= (Vector2<T>& lhs, const Vector2<T>& rhs)
  {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
  }

  using Vector2i = Vector2<I32>;
  using Vector2u = Vector2<U32>;
  using Vector2f = Vector2<F32>;

}
