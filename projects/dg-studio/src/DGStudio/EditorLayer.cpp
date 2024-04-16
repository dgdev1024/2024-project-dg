/** @file DGStudio/EditorLayer.cpp */

#include <DGStudio/EditorLayer.hpp>

namespace dgstudio
{

  void EditorLayer::onAttach ()
  {

    dg::FrameBufferSpecification framebufferSpec;
    framebufferSpec.attachmentSpec = {
      dg::FrameBufferTextureFormat::COLOR,
      dg::FrameBufferTextureFormat::COLOR_R32I,
      dg::FrameBufferTextureFormat::DEPTH
    };

    m_frameBuffer = dg::FrameBuffer::make(framebufferSpec);
    m_shader = dg::Shader::make("assets/quad2d.glsl");
    m_texture = dg::Texture::make("assets/wall.jpg");

    dg::Renderer& renderer = dg::Application::getRenderer();
    renderer.useFrameBuffer2D(m_frameBuffer);
    renderer.useQuadShader2D(m_shader);

    m_scene = std::make_shared<dg::Scene>();
  }

  void EditorLayer::onDetach ()
  {
    m_scene.reset();
    m_frameBuffer.reset();
    m_shader.reset();
  }

  void EditorLayer::fixedUpdate (const dg::F32 timestep)
  {
    m_scene->fixedUpdate(timestep);
  }

  void EditorLayer::update ()
  {
    m_scene->update();
  }

  void EditorLayer::guiUpdate ()
  {
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    updateMenuBar();
    updateDemoWindow();
    updateSceneWindow();
  }

  /** Update Menu Bar *****************************************************************************/

  void EditorLayer::updateMenuBar ()
  {
    if (ImGui::BeginMainMenuBar()) {
      updateViewMenu();

      ImGui::EndMainMenuBar();
    }
  }

  void EditorLayer::updateViewMenu ()
  {
    if (ImGui::BeginMenu("View")) {
      ImGui::MenuItem("Scene Window", nullptr, &m_showSceneWindow);
      ImGui::MenuItem("ImGui Demo Window", nullptr, &m_showDemoWindow);
      ImGui::EndMenu();
    }
  }

  /** Update Windows ******************************************************************************/

  void EditorLayer::updateDemoWindow ()
  {
    if (m_showDemoWindow == false) { return; }

    ImGui::ShowDemoWindow(&m_showDemoWindow);
  }

  void EditorLayer::updateSceneWindow ()
  {
    if (m_showSceneWindow == false) { return; }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });

    ImGui::Begin("Scene", &m_showSceneWindow);
    ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
    if (m_frameBuffer->setSize(contentRegionAvailable.x, contentRegionAvailable.y) == false) {
      ImGui::Image(m_frameBuffer->getColorPointer(), contentRegionAvailable, { 0, 1 }, { 1, 0 });
    }
    ImGui::End();

    ImGui::PopStyleVar();
  }

}
