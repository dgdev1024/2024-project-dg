/** @file DG/Math/Matrix3.hpp */

#pragma once

#include <DG/Math/Matrix2.hpp>
#include <DG/Math/Vector3.hpp>

namespace dg
{

  template <typename T>
  struct Matrix3
  {
    static_assert(std::is_floating_point_v<T>,
      "[Matrix3] 'T' must be a floating-point number.");

    T aa, ba, ca,
      ab, bb, cb,
      ac, bc, cc;

    static constexpr Count ELEMENT_COUNT = 9;
    static constexpr Matrix3<T> IDENTITY = {
      1, 0, 0,
      0, 1, 0,
      0, 0, 1
    };

    inline const T* getPointer () const
    {
      return &aa;
    }

    inline Matrix3<T> getTranspose () const
    {
      return {
        aa, ab, ac,
        ba, bb, bc,
        ca, cb, cc
      };
    }

    inline T getDeterminant () const
    {
      return
        aa * (bb * cc - bc * cb) -
        ab * (ba * cc - bc * ca) +
        ac * (ba * cb - bb * ca);
    }
    
    inline Matrix3<T> getAdjoint () const
    {
      return {
        (bb * cc - bc * cb),
        -(ab * cc - ac * cb),
        (ab * bc - ac * bb),

        -(ba * cc - bc * ca),
        (aa * cc - ac * ca),
        -(aa * bc - ac * ba),
        
        (ba * cb - bb * ca),
        -(aa * cb - ab * ca),
        (aa * bb - ab * ba)
      };
    }

    inline Matrix3<T> getInverse () const
    {
      T determinant = getDeterminant();
      if (determinant == 0) { return IDENTITY; }

      return getAdjoint() * (1 / determinant);
    }

  };


  
  template <typename T>
  inline Matrix3<T> operator+ (const Matrix3<T>& lhs, const Matrix3<T>& rhs)
  {
    return {
      lhs.aa + rhs.aa,
      lhs.ba + rhs.ba,
      lhs.ca + rhs.ca,

      lhs.ab + rhs.ab,
      lhs.bb + rhs.bb,
      lhs.cb + rhs.cb,

      lhs.ac + rhs.ac,
      lhs.bc + rhs.bc,
      lhs.cc + rhs.cc
    };
  }
  
  template <typename T>
  inline Matrix3<T> operator- (const Matrix3<T>& lhs, const Matrix3<T>& rhs)
  {
    return {
      lhs.aa - rhs.aa,
      lhs.ba - rhs.ba,
      lhs.ca - rhs.ca,

      lhs.ab - rhs.ab,
      lhs.bb - rhs.bb,
      lhs.cb - rhs.cb,

      lhs.ac - rhs.ac,
      lhs.bc - rhs.bc,
      lhs.cc - rhs.cc
    };
  }



  template <typename T>
  inline Matrix3<T>& operator+= (Matrix3<T>& lhs, const Matrix3<T>& rhs)
  {
    lhs.aa += rhs.aa;
    lhs.ba += rhs.ba;
    lhs.ca += rhs.ca;

    lhs.ab += rhs.ab;
    lhs.bb += rhs.bb;
    lhs.cb += rhs.cb;

    lhs.ac += rhs.ac;
    lhs.bc += rhs.bc;
    lhs.cc += rhs.cc;

    return lhs;
  }

  template <typename T>
  inline Matrix3<T>& operator-= (Matrix3<T>& lhs, const Matrix3<T>& rhs)
  {
    lhs.aa -= rhs.aa;
    lhs.ba -= rhs.ba;
    lhs.ca -= rhs.ca;

    lhs.ab -= rhs.ab;
    lhs.bb -= rhs.bb;
    lhs.cb -= rhs.cb;

    lhs.ac -= rhs.ac;
    lhs.bc -= rhs.bc;
    lhs.cc -= rhs.cc;

    return lhs;
  }



  template <typename T>
  inline Matrix3<T> operator* (const Matrix3<T>& lhs, T rhs)
  {
    return {
      lhs.aa * rhs.aa,
      lhs.ba * rhs.ba,
      lhs.ca * rhs.ca,

      lhs.ab * rhs.ab,
      lhs.bb * rhs.bb,
      lhs.cb * rhs.cb,

      lhs.ac * rhs.ac,
      lhs.bc * rhs.bc,
      lhs.cc * rhs.cc
    };
  }

  template <typename T>
  inline Matrix3<T>& operator*= (Matrix3<T>& lhs, T rhs)
  {
    lhs.aa *= rhs.aa;
    lhs.ba *= rhs.ba;
    lhs.ca *= rhs.ca;

    lhs.ab *= rhs.ab;
    lhs.bb *= rhs.bb;
    lhs.cb *= rhs.cb;

    lhs.ac *= rhs.ac;
    lhs.bc *= rhs.bc;
    lhs.cc *= rhs.cc;

    return lhs;
  }



  template <typename T>
  inline Matrix3<T> operator* (const Matrix3<T>& lhs, const Matrix3<T>& rhs)
  {
    return {
      lhs.aa * rhs.aa + lhs.ab * rhs.ba + lhs.ac * rhs.ca,
      lhs.aa * rhs.ab + lhs.ab * rhs.bb + lhs.ac * rhs.cb,
      lhs.aa * rhs.ac + lhs.ab * rhs.bc + lhs.ac * rhs.cc,

      lhs.ba * rhs.aa + lhs.bb * rhs.ba + lhs.bc * rhs.ca,
      lhs.ba * rhs.ab + lhs.bb * rhs.bb + lhs.bc * rhs.cb,
      lhs.ba * rhs.ac + lhs.bb * rhs.bc + lhs.bc * rhs.cc,

      lhs.ca * rhs.aa + lhs.cb * rhs.ba + lhs.cc * rhs.ca,
      lhs.ca * rhs.ab + lhs.cb * rhs.bb + lhs.cc * rhs.cb,
      lhs.ca * rhs.ac + lhs.cb * rhs.bc + lhs.cc * rhs.cc
    };
  }

  template <typename T>
  inline Vector3<T> operator* (const Matrix3<T>& lhs, const Vector3<T>& rhs)
  {
    return {
      lhs.aa * rhs.x,
      lhs.bb * rhs.y,
      lhs.cc * rhs.z
    };
  }



  using Matrix3f = Matrix3<F32>;

}
