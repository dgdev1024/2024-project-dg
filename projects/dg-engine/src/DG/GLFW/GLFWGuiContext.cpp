/** @file DG/GLFW/GLFWGuiContext.cpp */

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>

#if defined(DG_USING_OPENGL)
  #include <imgui_impl_opengl3.h>
#endif

#include <DG/Core/Application.hpp>
#include <DG/GLFW/GLFWGuiContext.hpp>

namespace dg
{

  Unique<GuiContext> GuiContext::make (const GuiContextSpecification& spec)
  {
    return std::make_unique<GLFW::GuiContextImpl>(spec);
  }

}

namespace dg::GLFW
{

  GuiContextImpl::GuiContextImpl (const GuiContextSpecification& spec) :
    GuiContext { spec }
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    if (m_docking == true) {
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }

    if (m_viewport == true) {
      io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    ImGui::StyleColorsDark();  

    #if defined(DG_USING_OPENGL)
      ImGui_ImplGlfw_InitForOpenGL(
        reinterpret_cast<GLFWwindow*>(Application::getWindow().getPointer()),
        true
      );
      ImGui_ImplOpenGL3_Init("#version 450 core");
    #endif
  }

  GuiContextImpl::~GuiContextImpl ()
  {
    #if defined(DG_USING_OPENGL)
      ImGui_ImplOpenGL3_Shutdown();
    #endif

    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void GuiContextImpl::begin ()
  {
    #if defined(DG_USING_OPENGL)
      ImGui_ImplOpenGL3_NewFrame();
    #endif

    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void GuiContextImpl::end ()
  {
    ImGui::Render();

    #if defined(DG_USING_OPENGL)
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if (m_viewport == true) {
        GLFWwindow* context = glfwGetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        glfwMakeContextCurrent(context);
      }
    #endif
  }

}
