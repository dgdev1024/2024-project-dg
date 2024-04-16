/** @file DG/Scene/Scene.cpp */

#include <DG/Core/Application.hpp>
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

  Entity Scene::getPrimaryCameraEntity ()
  {
    auto cameraEntities = m_registry.view<CameraComponent>();
    for (const auto& cameraEntity : cameraEntities) {
      if (m_registry.get<CameraComponent>(cameraEntity).isPrimary() == true) {
        return { this, cameraEntity };
      }
    }

    return {};
  }

  void Scene::setPrimaryCameraEntity (const Entity& entity)
  {
    auto cameraEntities = m_registry.view<CameraComponent>();
    for (auto& cameraEntity : cameraEntities) {
      m_registry.get<CameraComponent>(cameraEntity).setPrimary(cameraEntity == entity.getHandle());
    }
  }

  void Scene::fixedUpdate (const F32 timestep)
  {

  }

  void Scene::update ()
  {
    Matrix4f cameraProduct = Matrix4f::IDENTITY;
    findPrimaryCameraMatrix(cameraProduct);

    Renderer& renderer = Application::getRenderer();
    renderer.beginScene2D(cameraProduct);
    {
      auto view = m_registry.view<TransformComponent, QuadComponent>();
      for (const auto& entity : view) {
        const auto& [transform, quad] = view.get<TransformComponent, QuadComponent>(entity);
        renderer.submitQuad2D(transform.transform, RenderSpecification2D {
          .color = quad.color,
          .texture = quad.texture,
          .entityId = static_cast<I32>(entity)
        });
      }
    }
    renderer.endScene2D();
  }

  void Scene::findPrimaryCameraMatrix (Matrix4f& cameraProduct)
  {
    auto cameraEntities = m_registry.view<TransformComponent, CameraComponent>();
    for (const auto& cameraEntity : cameraEntities) {
      const auto& cameraComponent = m_registry.get<CameraComponent>(cameraEntity);
      if (cameraComponent.isPrimary() == true) {
        cameraProduct = cameraComponent.getProjection() *
          m_registry.get<TransformComponent>(cameraEntity).transform.getInverse();
        return;
      }
    }
  }

}
