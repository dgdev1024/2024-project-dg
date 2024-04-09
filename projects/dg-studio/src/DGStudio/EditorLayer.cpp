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
    m_vbo->setLayout({
      { "in_Position", dg::VertexAttributeType::Float3 }
    });
    m_vao->addVertexBuffer(m_vbo);
    m_vao->setIndexBuffer(m_ibo);
  }

  void EditorLayer::onDetach ()
  {
    m_vao.reset();
    m_vbo.reset();
    m_ibo.reset();
  }

  void EditorLayer::update ()
  {
    dg::RenderCommand::drawIndexed(m_vao);
  }

  void EditorLayer::guiUpdate ()
  {
    ImGui::ShowDemoWindow();
  }

}
