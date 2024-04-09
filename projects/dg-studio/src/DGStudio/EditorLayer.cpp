/** @file DGStudio/EditorLayer.cpp */

#include <DGStudio/EditorLayer.hpp>

namespace dgstudio
{

  void EditorLayer::onAttach ()
  {
    dg::Collection<dg::Vector3f> vertices = {
      {  0.5f,  0.5f, 0.0f },
      {  0.5f, -0.5f, 0.0f },
      { -0.5f, -0.5f, 0.0f },
      { -0.5f,  0.5f, 0.0f }
    };

    dg::Collection<dg::U32> indices = {
      0, 1, 3, 1, 2, 3
    };

    m_vao = dg::VertexArray::make();
    m_vbo = dg::VertexBuffer::makeFrom<dg::Vector3f>(vertices);
    m_ibo = dg::IndexBuffer::make(indices);
    m_shader = dg::Shader::make("assets/basic.glsl");
    m_vbo->setLayout({
      { "in_Position", dg::VertexAttributeType::Float3 }
    });
    m_vao->addVertexBuffer(m_vbo);
    m_vao->setIndexBuffer(m_ibo);

    if (m_shader->setVector4f("uni_FragColor", { 0.0f, 1.0f, 1.0f, 1.0f }) == false) {
      DG_THROW(std::runtime_error, "Uniform not found!");
    }
  }

  void EditorLayer::onDetach ()
  {
    m_shader.reset();
    m_vao.reset();
    m_vbo.reset();
    m_ibo.reset();
  }

  void EditorLayer::update ()
  {
    m_shader->bind();
    dg::RenderCommand::drawIndexed(m_vao);
  }

  void EditorLayer::guiUpdate ()
  {
    ImGui::ShowDemoWindow();
  }

}
