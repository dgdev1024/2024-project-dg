/** @file DG/Scene/Scene.hpp */

#pragma once

#include <DG_Pch.hpp>
#include <DG/Math/Matrix4.hpp>

namespace dg
{

  class Entity;

  class Scene
  {
    friend class Entity;

  public:
    Scene ();
    ~Scene ();

  public:
    Entity createEntity (const String& tag = "Untitled Entity");
    Entity getPrimaryCameraEntity ();
    void setPrimaryCameraEntity (const Entity& entity);
    virtual void fixedUpdate (const F32 timestep);
    virtual void update ();

  private:
    void findPrimaryCameraMatrix (Matrix4f& cameraProduct);

  private:
    entt::registry m_registry;

  };

}
