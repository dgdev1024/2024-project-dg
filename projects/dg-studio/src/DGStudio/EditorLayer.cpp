/** @file DGStudio/EditorLayer.cpp */

#include <DGStudio/EditorLayer.hpp>

namespace dgstudio
{

  struct Vertex
  {
    dg::Vector3f position;
    dg::Vector2f texCoords;
  };

  void EditorLayer::onAttach ()
  {
    dg::Collection<Vertex> vertices = {
      { {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f } },
      { {  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f } },
      { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f } },
      { { -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f } }
    };

    dg::Collection<dg::U32> indices = {
      0, 1, 3, 1, 2, 3
    };

    dg::FrameBufferSpecification framebufferSpec;
    framebufferSpec.attachmentSpec = {
      dg::FrameBufferTextureFormat::COLOR,
      dg::FrameBufferTextureFormat::DEPTH
    };

    m_frameBuffer = dg::FrameBuffer::make(framebufferSpec);
    m_vao = dg::VertexArray::make();
    m_vbo = dg::VertexBuffer::makeFrom<Vertex>(vertices);
    m_ibo = dg::IndexBuffer::make(indices);
    m_shader = dg::Shader::make("assets/quad2d.glsl");
    m_texture = dg::Texture::make("assets/wall.jpg");
    m_vbo->setLayout({
      { "in_Position", dg::VertexAttributeType::Float3 },
      { "in_TexCoords", dg::VertexAttributeType::Float2 },
      { "in_Color", dg::VertexAttributeType::Float4 },
      { "in_TexIndex", dg::VertexAttributeType::Float },
      { "in_EntityId", dg::VertexAttributeType::Float }
    });
    m_vao->addVertexBuffer(m_vbo);
    m_vao->setIndexBuffer(m_ibo);

    m_shader->setInteger("uni_Texture", 0);

    auto& renderer = dg::Application::getRenderer();
    renderer.useQuadShader2D(m_shader);
    renderer.useFrameBuffer2D(m_frameBuffer);
  }

  void EditorLayer::onDetach ()
  {
    m_texture.reset();
    m_shader.reset();
    m_vao.reset();
    m_vbo.reset();
    m_ibo.reset();
    m_frameBuffer.reset();
  }

  void EditorLayer::update ()
  {
    auto& renderer = dg::Application::getRenderer();
    renderer.beginScene2D(dg::Matrix4f::IDENTITY);
    renderer.submitQuad2D({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, { .texture = m_texture });
    renderer.endScene2D();
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
