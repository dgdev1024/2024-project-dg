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
    void updateMenuBar ();
    void updateViewMenu ();

  private:
    void updateDemoWindow ();
    void updateSceneWindow ();

  private:
    dg::Shared<dg::VertexArray>   m_vao           = nullptr;
    dg::Shared<dg::VertexBuffer>  m_vbo           = nullptr;
    dg::Shared<dg::IndexBuffer>   m_ibo           = nullptr;
    dg::Shared<dg::Shader>        m_shader        = nullptr;
    dg::Shared<dg::Texture>       m_texture       = nullptr;
    dg::Shared<dg::FrameBuffer>   m_frameBuffer   = nullptr;

  private:
    bool  m_showDemoWindow        = true;
    bool  m_showSceneWindow       = true;

  };

}
