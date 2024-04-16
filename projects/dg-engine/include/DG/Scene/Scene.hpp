/** @file DG/Scene/Scene.hpp */

#pragma once

#include <DG_Pch.hpp>

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

  private:
    entt::registry m_registry;

  };

}
