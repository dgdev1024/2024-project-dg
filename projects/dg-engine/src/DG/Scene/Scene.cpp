/** @file DG/Scene/Scene.cpp */

#include <DG/Scene/Entity.hpp>
#include <DG/Scene/Scene.hpp>

namespace dg
{

  Scene::Scene () :
    m_registry {}
  {

  }

  Scene::~Scene ()
  {
    m_registry.clear();
  }

  Entity Scene::createEntity (const String& tag)
  {
    Entity::Handle handle = m_registry.create();
    m_registry.emplace<TransformComponent>(handle);
    m_registry.emplace<TagComponent>(handle, tag);

    return { this, handle };
  }

}
