/** @file DGStudio/EditorLayer.hpp */

#include <DGStudio_Pch.hpp>

namespace dgstudio
{

  class EditorLayer : public dg::Layer
  {
  public:
    EditorLayer () = default;
    ~EditorLayer () = default;

    void guiUpdate () override;

  };

}
