/** @file DG/Math/Matrix2.hpp */

#pragma once

#include <DG/Math/Vector2.hpp>

namespace dg
{

  template <typename T>
  struct Matrix2
  {
    static_assert(std::is_floating_point_v<T>,
      "[Matrix2] 'T' must be a floating-point number.");

    T aa, ba,
      ab, bb;

    static constexpr Count ELEMENT_COUNT = 4;
    static constexpr Matrix2<T> IDENTITY = {
      1, 0,
      0, 1
    };

    inline const T* getPointer () const
    {
      return &aa;
    }

    inline Matrix2<T> getTranspose () const
    {
      return {
        aa, ab,
        ba, bb
      };
    }

    inline T getDeterminant () const
    {
      return (aa * bb) - (ab * ba);
    }
    
    inline Matrix2<T> getAdjoint () const
    {
      return {
        bb, -ba,
        -ab, aa
      };
    }

    inline Matrix2<T> getInverse () const
    {
      T determinant = getDeterminant();
      if (determinant == 0) { return IDENTITY; }

      return getAdjoint() * (1 / determinant);
    }

  };


  
  template <typename T>
  inline Matrix2<T> operator+ (const Matrix2<T>& lhs, const Matrix2<T>& rhs)
  {
    return {
      lhs.aa + rhs.aa,
      lhs.ba + rhs.ba,

      lhs.ab + rhs.ab,
      lhs.bb + rhs.bb
    };
  }
  
  template <typename T>
  inline Matrix2<T> operator- (const Matrix2<T>& lhs, const Matrix2<T>& rhs)
  {
    return {
      lhs.aa - rhs.aa,
      lhs.ba - rhs.ba,

      lhs.ab - rhs.ab,
      lhs.bb - rhs.bb
    };
  }



  template <typename T>
  inline Matrix2<T>& operator+= (Matrix2<T>& lhs, const Matrix2<T>& rhs)
  {
    lhs.aa += rhs.aa;
    lhs.ba += rhs.ba;

    lhs.ab += rhs.ab;
    lhs.bb += rhs.bb;

    return lhs;
  }

  template <typename T>
  inline Matrix2<T>& operator-= (Matrix2<T>& lhs, const Matrix2<T>& rhs)
  {
    lhs.aa -= rhs.aa;
    lhs.ba -= rhs.ba;

    lhs.ab -= rhs.ab;
    lhs.bb -= rhs.bb;

    return lhs;
  }



  template <typename T>
  inline Matrix2<T> operator* (const Matrix2<T>& lhs, T rhs)
  {
    return {
      lhs.aa * rhs,
      lhs.ba * rhs,

      lhs.ab * rhs,
      lhs.bb * rhs
    };
  }

  template <typename T>
  inline Matrix2<T>& operator*= (Matrix2<T>& lhs, T rhs)
  {
    lhs.aa *= rhs;
    lhs.ba *= rhs;

    lhs.ab *= rhs;
    lhs.bb *= rhs;

    return lhs;
  }



  template <typename T>
  inline Matrix2<T> operator* (const Matrix2<T>& lhs, const Matrix2<T>& rhs)
  {
    return {
      lhs.aa * rhs.aa + lhs.ba * rhs.ab, 
      lhs.ab * rhs.aa + lhs.bb * rhs.ab,
      
      lhs.aa * rhs.ba + lhs.ba * rhs.bb, 
      lhs.ab * rhs.ba + lhs.bb * rhs.bb
    };
  }

  template <typename T>
  inline Vector2<T> operator* (const Matrix2<T>& lhs, const Vector2<T>& rhs)
  {
    return {
      lhs.aa * rhs.x + lhs.ba * rhs.y,
      lhs.ab * rhs.x + lhs.bb * rhs.y
    };
  }



  using Matrix2f = Matrix2<F32>;

}
