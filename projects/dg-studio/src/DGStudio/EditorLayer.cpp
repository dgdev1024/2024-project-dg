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

    m_vao = dg::VertexArray::make();
    m_vbo = dg::VertexBuffer::makeFrom<Vertex>(vertices);
    m_ibo = dg::IndexBuffer::make(indices);
    m_shader = dg::Shader::make("assets/basic_texture.glsl");
    m_texture = dg::Texture::make("assets/wall.jpg");
    m_vbo->setLayout({
      { "in_Position", dg::VertexAttributeType::Float3 },
      { "in_TexCoords", dg::VertexAttributeType::Float2 }
    });
    m_vao->addVertexBuffer(m_vbo);
    m_vao->setIndexBuffer(m_ibo);

    m_shader->setInteger("uni_Texture", 0);
  }

  void EditorLayer::onDetach ()
  {
    m_texture.reset();
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
