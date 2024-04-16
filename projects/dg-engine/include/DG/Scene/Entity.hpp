/** @file DG/Scene/Entity.hpp */

#pragma once

#include <DG_Pch.hpp>
#include <DG/Core/PrettyTypename.hpp>
#include <DG/Scene/Scene.hpp>
#include <DG/Scene/Components.hpp>

namespace dg
{

  class Entity
  {
  public:
    using Handle = entt::entity;

  public:
    Entity ();
    Entity (Scene* scene, Handle handle);

  public:

    template <typename T, typename... Us>
    inline T& addComponent (Us&&... args)
    {
      return m_scene->m_registry.get_or_emplace<T>(m_handle, std::forward<Us>(args)...);
    }

    template <typename... Ts>
    inline bool hasComponents ()
    {
      return m_scene->m_registry.all_of<Ts...>(m_handle);
    }

    inline TransformComponent& getTransformComponent ()
    {
      return m_scene->m_registry.get<TransformComponent>(m_handle);
    }

    inline const TransformComponent& getTransformComponent () const
    {
      return m_scene->m_registry.get<TransformComponent>(m_handle);
    }

    inline TagComponent& getTagComponent ()
    {
      return m_scene->m_registry.get<TagComponent>(m_handle);
    }

    inline const TagComponent& getTagComponent () const
    {
      return m_scene->m_registry.get<TagComponent>(m_handle);
    }

    template <typename T>
    inline T& getComponent ()
    {
      if (hasComponents<T>() == false) {
        DG_ENGINE_THROW(std::out_of_range, "Attempt to get non-existant entity component '{}'!",
          getPrettyTypename<T>());
      }

      return m_scene->m_registry.get<T>(m_handle);
    }

    template <typename T>
    inline const T& getComponent () const
    {
      if (hasComponents<T>() == false) {
        DG_ENGINE_THROW(std::out_of_range, "Attempt to get non-existant entity component '{}'!",
          getPrettyTypename<T>());
      }

      return m_scene->m_registry.get<T>(m_handle);
    }

    template <typename T>
    inline void removeComponent ()
    {
      static_assert(
        std::is_same_v<T, TagComponent> == false &&
        std::is_same_v<T, TransformComponent> == false,
        "[Entity] 'T' is a key component and cannot be removed."
      );

      if (hasComponents<T>() == false) {
        DG_ENGINE_THROW(std::out_of_range, "Attempt to remove non-existant entity component '{}'!",
          getPrettyTypename<T>());
      }

      m_scene->m_registry.remove<T>(m_handle);
    }

  public:
    inline Handle getHandle () const { return m_handle; }
    inline bool isValid () const { return (m_scene != nullptr); }
    inline operator bool () const { return isValid(); }

  private:
    Handle m_handle;
    Scene* m_scene = nullptr;

  };

}
