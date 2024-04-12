/** @file DG/Math/Matrix4.hpp */

#pragma once

#include <DG/Math/Matrix3.hpp>
#include <DG/Math/Vector4.hpp>

namespace dg
{

  template <typename T>
  struct Matrix4
  {
    static_assert(std::is_floating_point_v<T>,
      "[Matrix4] 'T' must be a floating-point number.");

    T aa, ba, ca, da,
      ab, bb, cb, db,
      ac, bc, cc, dc,
      ad, bd, cd, dd;

    static constexpr Count ELEMENT_COUNT = 16;
    static constexpr Matrix4<T> IDENTITY = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };

    inline const T* getPointer () const
    {
      return &aa;
    }

    inline Matrix4<T> getTranspose () const
    {
      return {
        aa, ab, ac, ad,
        ba, bb, bc, bd, 
        ca, cb, cc, cd,
        da, db, dc, dd
      };
    }

    inline T getDeterminant () const
    {
      return
        aa * (bb * (cc * dd - cd * dc) - bc * (cb * dd - cd * db) + bd * (cb * dc - cc * db)) -
        ab * (ba * (cc * dd - cd * dc) - bc * (ca * dd - cd * da) + bd * (ca * dc - cc * da)) +
        ac * (ba * (cb * dd - cd * db) - bb * (ca * dd - cd * da) + bd * (ca * db - cb * da)) -
        ad * (ba * (cb * dc - cc * db) - bb * (ca * dc - cc * da) + bc * (ca * db - cb * da));
    }
    
    inline Matrix4<T> getAdjoint () const
    {
      return {
        (bb * (cc * dd - cd * dc) - bc * (cb * dd - cd * db) + bd * (cb * dc - cc * db)),
        -(ab * (cc * dd - cd * dc) - ac * (cb * dd - cd * db) + ad * (cb * dc - cc * db)),
        (ab * (bc * dd - bd * dc) - ac * (bb * dd - bd * db) + ad * (bb * dc - bc * db)),
        -(ab * (bc * cd - bd * cc) - ac * (bb * cd - bd * cb) + ad * (bb * cc - bc * cb)),

        -(ba * (cc * dd - cd * dc) - bc * (ca * dd - cd * da) + bd * (ca * dc - cc * da)),
        (aa * (cc * dd - cd * dc) - ac * (ca * dd - cd * da) + ad * (ca * dc - cc * da)),
        -(aa * (bc * dd - bd * dc) - ac * (ba * dd - bd * da) + ad * (ba * dc - bc * da)),
        (aa * (bc * cd - bd * cc) - ac * (ba * cd - bd * cb) + ad * (ba * cc - bc * cb)),

        (ba * (cb * dd - cd * db) - bb * (ca * dd - cd * da) + bd * (ca * db - cb * da)),
        -(aa * (cb * dd - cd * db) - ab * (ca * dd - cd * da) + ad * (ca * db - cb * da)),
        (aa * (bb * dd - bd * db) - ab * (ba * dd - bd * da) + ad * (ba * db - bb * da)),
        -(aa * (bb * cd - bd * cb) - ab * (ba * cd - bd * ca) + ad * (ba * cb - bb * ca)),

        -(ba * (cb * dc - cc * db) - bb * (ca * dc - cc * da) + bc * (ca * db - cb * da)),
        (aa * (cb * dc - cc * db) - ab * (ca * dc - cc * da) + ac * (ca * db - cb * da)),
        -(aa * (bb * dc - bc * db) - ab * (ba * dc - bc * da) + ac * (ba * db - bb * da)),
        (aa * (bb * cc - bc * cb) - ab * (ba * cc - bc * ca) + ac * (ba * cb - bb * ca)),
      };
    }

    inline Matrix4<T> getInverse () const
    {
      T determinant = getDeterminant();
      if (determinant == 0) { return IDENTITY; }

      return getAdjoint() * (1 / determinant);
    }

    inline Matrix3<T> getNormal () const
    {
      Matrix3<T> upperLeft = {
        aa, ba, ca,
        ab, bb, cb,
        ac, bc, cc
      };

      return upperLeft.getInverse().getTranspose();
    }

  };


  
  template <typename T>
  inline Matrix4<T> operator+ (const Matrix4<T>& lhs, const Matrix4<T>& rhs)
  {
    return {
      lhs.aa + rhs.aa,
      lhs.ba + rhs.ba,
      lhs.ca + rhs.ca,
      lhs.da + rhs.da,

      lhs.ab + rhs.ab,
      lhs.bb + rhs.bb,
      lhs.cb + rhs.cb,
      lhs.db + rhs.db,

      lhs.ac + rhs.ac,
      lhs.bc + rhs.bc,
      lhs.cc + rhs.cc,
      lhs.dc + rhs.dc,

      lhs.ad + rhs.ad,
      lhs.bd + rhs.bd,
      lhs.cd + rhs.cd,
      lhs.dd + rhs.dd
    };
  }
  
  template <typename T>
  inline Matrix4<T> operator- (const Matrix4<T>& lhs, const Matrix4<T>& rhs)
  {
    return {
      lhs.aa - rhs.aa,
      lhs.ba - rhs.ba,
      lhs.ca - rhs.ca,
      lhs.da - rhs.da,

      lhs.ab - rhs.ab,
      lhs.bb - rhs.bb,
      lhs.cb - rhs.cb,
      lhs.db - rhs.db,

      lhs.ac - rhs.ac,
      lhs.bc - rhs.bc,
      lhs.cc - rhs.cc,
      lhs.dc - rhs.dc,

      lhs.ad - rhs.ad,
      lhs.bd - rhs.bd,
      lhs.cd - rhs.cd,
      lhs.dd - rhs.dd
    };
  }



  template <typename T>
  inline Matrix4<T>& operator+= (Matrix4<T>& lhs, const Matrix4<T>& rhs)
  {
    lhs.aa += rhs.aa;
    lhs.ba += rhs.ba;
    lhs.ca += rhs.ca;
    lhs.da += rhs.da;

    lhs.ab += rhs.ab;
    lhs.bb += rhs.bb;
    lhs.cb += rhs.cb;
    lhs.db += rhs.db;

    lhs.ac += rhs.ac;
    lhs.bc += rhs.bc;
    lhs.cc += rhs.cc;
    lhs.dc += rhs.dc;

    lhs.ad += rhs.ad;
    lhs.bd += rhs.bd;
    lhs.cd += rhs.cd;
    lhs.dd += rhs.dd;

    return lhs;
  }

  template <typename T>
  inline Matrix4<T>& operator-= (Matrix4<T>& lhs, const Matrix4<T>& rhs)
  {
    lhs.aa -= rhs.aa;
    lhs.ba -= rhs.ba;
    lhs.ca -= rhs.ca;
    lhs.da -= rhs.da;

    lhs.ab -= rhs.ab;
    lhs.bb -= rhs.bb;
    lhs.cb -= rhs.cb;
    lhs.db -= rhs.db;

    lhs.ac -= rhs.ac;
    lhs.bc -= rhs.bc;
    lhs.cc -= rhs.cc;
    lhs.dc -= rhs.dc;

    lhs.ad -= rhs.ad;
    lhs.bd -= rhs.bd;
    lhs.cd -= rhs.cd;
    lhs.dd -= rhs.dd;

    return lhs;
  }



  template <typename T>
  inline Matrix4<T> operator* (const Matrix4<T>& lhs, T rhs)
  {
    return {
      lhs.aa * rhs,
      lhs.ba * rhs,
      lhs.ca * rhs,
      lhs.da * rhs,

      lhs.ab * rhs,
      lhs.bb * rhs,
      lhs.cb * rhs,
      lhs.db * rhs,

      lhs.ac * rhs,
      lhs.bc * rhs,
      lhs.cc * rhs,
      lhs.dc * rhs,

      lhs.ad * rhs,
      lhs.bd * rhs,
      lhs.cd * rhs,
      lhs.dd * rhs
    };
  }

  template <typename T>
  inline Matrix4<T>& operator*= (Matrix4<T>& lhs, T rhs)
  {
    lhs.aa *= rhs;
    lhs.ba *= rhs;
    lhs.ca *= rhs;
    lhs.da *= rhs;

    lhs.ab *= rhs;
    lhs.bb *= rhs;
    lhs.cb *= rhs;
    lhs.db *= rhs;

    lhs.ac *= rhs;
    lhs.bc *= rhs;
    lhs.cc *= rhs;
    lhs.dc *= rhs;

    lhs.ad *= rhs;
    lhs.bd *= rhs;
    lhs.cd *= rhs;
    lhs.dd *= rhs;

    return lhs;
  }



  template <typename T>
  inline Matrix4<T> operator* (const Matrix4<T>& lhs, const Matrix4<T>& rhs)
  {
    // return {
    //   lhs.aa * rhs.aa + lhs.ab * rhs.ba + lhs.ac * rhs.ca + lhs.ad * rhs.da,
    //   lhs.aa * rhs.ab + lhs.ab * rhs.bb + lhs.ac * rhs.cb + lhs.ad * rhs.db,
    //   lhs.aa * rhs.ac + lhs.ab * rhs.bc + lhs.ac * rhs.cc + lhs.ad * rhs.dc,
    //   lhs.aa * rhs.ad + lhs.ab * rhs.bd + lhs.ac * rhs.cd + lhs.ad * rhs.dd,

    //   lhs.ba * rhs.aa + lhs.bb * rhs.ba + lhs.bc * rhs.ca + lhs.bd * rhs.da,
    //   lhs.ba * rhs.ab + lhs.bb * rhs.bb + lhs.bc * rhs.cb + lhs.bd * rhs.db,
    //   lhs.ba * rhs.ac + lhs.bb * rhs.bc + lhs.bc * rhs.cc + lhs.bd * rhs.dc,
    //   lhs.ba * rhs.ad + lhs.bb * rhs.bd + lhs.bc * rhs.cd + lhs.bd * rhs.dd,

    //   lhs.ca * rhs.aa + lhs.cb * rhs.ba + lhs.cc * rhs.ca + lhs.cd * rhs.da,
    //   lhs.ca * rhs.ab + lhs.cb * rhs.bb + lhs.cc * rhs.cb + lhs.cd * rhs.db,
    //   lhs.ca * rhs.ac + lhs.cb * rhs.bc + lhs.cc * rhs.cc + lhs.cd * rhs.dc,
    //   lhs.ca * rhs.ad + lhs.cb * rhs.bd + lhs.cc * rhs.cd + lhs.cd * rhs.dd,

    //   lhs.da * rhs.aa + lhs.db * rhs.ba + lhs.dc * rhs.ca + lhs.dd * rhs.da,
    //   lhs.da * rhs.ab + lhs.db * rhs.bb + lhs.dc * rhs.cb + lhs.dd * rhs.db,
    //   lhs.da * rhs.ac + lhs.db * rhs.bc + lhs.dc * rhs.cc + lhs.dd * rhs.dc,
    //   lhs.da * rhs.ad + lhs.db * rhs.bd + lhs.dc * rhs.cd + lhs.dd * rhs.dd
    // };

    return {
      lhs.aa * rhs.aa + lhs.ba * rhs.ab + lhs.ca * rhs.ac + lhs.da * rhs.ad,
      lhs.aa * rhs.ba + lhs.ba * rhs.bb + lhs.ca * rhs.bc + lhs.da * rhs.bd,
      lhs.aa * rhs.ca + lhs.ba * rhs.cb + lhs.ca * rhs.cc + lhs.da * rhs.cd,
      lhs.aa * rhs.da + lhs.ba * rhs.db + lhs.ca * rhs.dc + lhs.da * rhs.dd,

      lhs.ab * rhs.aa + lhs.bb * rhs.ab + lhs.cb * rhs.ac + lhs.db * rhs.ad,
      lhs.ab * rhs.ba + lhs.bb * rhs.bb + lhs.cb * rhs.bc + lhs.db * rhs.bd,
      lhs.ab * rhs.ca + lhs.bb * rhs.cb + lhs.cb * rhs.cc + lhs.db * rhs.cd,
      lhs.ab * rhs.da + lhs.bb * rhs.db + lhs.cb * rhs.dc + lhs.db * rhs.dd,

      lhs.ac * rhs.aa + lhs.bc * rhs.ab + lhs.cc * rhs.ac + lhs.dc * rhs.ad,
      lhs.ac * rhs.ba + lhs.bc * rhs.bb + lhs.cc * rhs.bc + lhs.dc * rhs.bd,
      lhs.ac * rhs.ca + lhs.bc * rhs.cb + lhs.cc * rhs.cc + lhs.dc * rhs.cd,
      lhs.ac * rhs.da + lhs.bc * rhs.db + lhs.cc * rhs.dc + lhs.dc * rhs.dd,

      lhs.ad * rhs.aa + lhs.bd * rhs.ab + lhs.cd * rhs.ac + lhs.dd * rhs.ad,
      lhs.ad * rhs.ba + lhs.bd * rhs.bb + lhs.cd * rhs.bc + lhs.dd * rhs.bd,
      lhs.ad * rhs.ca + lhs.bd * rhs.cb + lhs.cd * rhs.cc + lhs.dd * rhs.cd,
      lhs.ad * rhs.da + lhs.bd * rhs.db + lhs.cd * rhs.dc + lhs.dd * rhs.dd
    };
  }

  template <typename T>
  inline Vector4<T> operator* (const Matrix4<T>& lhs, const Vector4<T>& rhs)
  {
    return {
      lhs.aa * rhs.x + lhs.ba * rhs.y + lhs.ca * rhs.z + lhs.da * rhs.w,
      lhs.ab * rhs.x + lhs.bb * rhs.y + lhs.cb * rhs.z + lhs.db * rhs.w,
      lhs.ac * rhs.x + lhs.bc * rhs.y + lhs.cc * rhs.z + lhs.dc * rhs.w,
      lhs.ad * rhs.x + lhs.bd * rhs.y + lhs.cd * rhs.z + lhs.dd * rhs.w
    };
  }

  using Matrix4f = Matrix4<F32>;
  using Matrix4d = Matrix4<F64>;

}
