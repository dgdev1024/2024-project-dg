/** @file DG/Scene/CameraComponent.hpp */

#pragma once

#include <DG/Graphics/Camera.hpp>

namespace dg
{

  class CameraComponent : public Camera
  {
    friend class Scene;

  public:
    CameraComponent () : Camera {} { updateProjection(); }
    ~CameraComponent () = default;

  public:
    inline bool isPrimary () const { return m_primary; }
    inline ProjectionType getProjectionType () const { return m_projectionType; }
    inline const CameraFrustum& getOrthographicFrustum () const { return m_orthographicFrustum; }
    inline const CameraFrustum& getPerspectiveFrustum () const { return m_perspectiveFrustum; }
    inline F32 getAspectRatio () const { return m_aspectRatio; }

    inline void setProjectionType (const ProjectionType type) 
      { m_projectionType = type; updateProjection(); }
    inline void setOrthographicFrustum (const CameraFrustum& frustum) 
      { m_orthographicFrustum = frustum; updateProjection(); }
    inline void setOrthographicFrustum (F32 size, F32 near, F32 far)
      { setOrthographicFrustum({ size, near, far }); }
    inline void setPerspectiveFrustum (const CameraFrustum& frustum) 
      { m_perspectiveFrustum = frustum; updateProjection(); }
    inline void setPerspectiveFrustum (F32 fov, F32 near, F32 far)
      { setPerspectiveFrustum({ fov, near, far }); }
    inline void setAspectRatio (F32 aspectRatio)
      { m_aspectRatio = aspectRatio; updateProjection(); }

  private:
    inline void updateProjection () override
    {
      if (m_projectionType == ProjectionType::ORTHOGRAPHIC) {
        m_projection = orthographic(
          m_orthographicFrustum.size,
          m_aspectRatio,
          m_orthographicFrustum.near,
          m_orthographicFrustum.far
        );
      } else {
        m_projection = perspective(
          radians(m_perspectiveFrustum.size), 
          m_aspectRatio, 
          m_perspectiveFrustum.near,
          m_perspectiveFrustum.far
        );
      }
    }

    inline void setPrimary (bool primary) { m_primary = primary; }

  private:
    ProjectionType m_projectionType = ProjectionType::ORTHOGRAPHIC;
    CameraFrustum m_orthographicFrustum = { 10.0f, -1.0f, 1.0f };
    CameraFrustum m_perspectiveFrustum = { 45.0f, 0.1f, 100.0f };
    F32 m_aspectRatio = 0.0f;
    bool m_primary = false;

  };

}
