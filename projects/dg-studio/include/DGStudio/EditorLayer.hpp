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
    void fixedUpdate (const dg::F32 timestep) override;
    void update () override;
    void guiUpdate () override;

  private:
    void updateMenuBar ();
    void updateViewMenu ();

  private:
    void updateDemoWindow ();
    void updateSceneWindow ();

  private:
    dg::Shared<dg::Texture>       m_texture       = nullptr;
    dg::Shared<dg::Shader>        m_shader        = nullptr;
    dg::Shared<dg::FrameBuffer>   m_frameBuffer   = nullptr;
    dg::Shared<dg::Scene>         m_scene         = nullptr;

  private:
    bool  m_showDemoWindow        = true;
    bool  m_showSceneWindow       = true;

  };

}
