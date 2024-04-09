/** @file DGStudio/EditorLayer.hpp */

#include <DGStudio_Pch.hpp>

namespace dgstudio
{

  class EditorLayer : public dg::Layer
  {
  public:
    EditorLayer () = default;
    ~EditorLayer () = default;

    void onAttach () override;
    void onDetach () override;
    void update () override;
    void guiUpdate () override;

  private:
    dg::Shared<dg::VertexArray>   m_vao = nullptr;
    dg::Shared<dg::VertexBuffer>  m_vbo = nullptr;
    dg::Shared<dg::IndexBuffer>   m_ibo = nullptr;
    dg::Shared<dg::Shader>        m_shader = nullptr;

  };

}
