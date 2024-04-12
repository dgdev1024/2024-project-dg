/** @file DG/Graphics/Camera.hpp */

#pragma once

#include <DG_Pch.hpp>
#include <DG/Math/Projections.hpp>
#include <DG/Math/Transforms.hpp>

namespace dg
{

  enum class ProjectionType
  {
    ORTHOGRAPHIC, PERSPECTIVE
  };

  class Camera
  {
  public:
    Camera () = default;
    Camera (const Matrix4f& projection) :
      m_projection { projection }
    {}
    virtual ~Camera () = default;

  public:
    inline const Matrix4f& getProjection () const { return m_projection; }
    inline void setProjection (const Matrix4f& projection) { m_projection = projection; }

  protected:
    virtual void updateProjection () {}

  protected:
    Matrix4f m_projection = Matrix4f::IDENTITY;

  };

}
