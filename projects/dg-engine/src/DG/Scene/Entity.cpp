/** @file DG/Scene/Entity.cpp */

#include <DG/Scene/Scene.hpp>
#include <DG/Scene/Entity.hpp>

namespace dg
{

  Entity::Entity (Scene* scene, Handle handle) :
    m_handle { handle },
    m_scene { scene }
  {
    if (m_scene == nullptr) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to create entity with no parent scene!");
    }
  }

}
