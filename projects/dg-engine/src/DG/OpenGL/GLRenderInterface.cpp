/** @file DG/OpenGL/GLRenderInterface.cpp */

#include <DG/OpenGL/GLRenderInterface.hpp>

namespace dg
{

  Unique<RenderInterface> RenderInterface::make ()
  {
    return std::make_unique<OpenGL::RenderInterfaceImpl>();
  }

}

namespace dg::OpenGL
{

  RenderInterfaceImpl::RenderInterfaceImpl () :
    RenderInterface {}
  {
    #if defined(DG_USING_GLAD)
      auto result = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
      if (result == 0) {
        DG_ENGINE_THROW(std::runtime_error, "Could not initialize the GLAD GL loader!");
      }
    #else
      #error "You must #define DG_USING_GLAD or DG_USING_GLEW to use this render interface!"
    #endif

    #if defined(DG_USING_GLFW)

    #endif
  }

  RenderInterfaceImpl::~RenderInterfaceImpl ()
  {

  }

  void RenderInterfaceImpl::clear ()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void RenderInterfaceImpl::setClearColor (const Vector4f& color)
  {
    glClearColor(color.x, color.y, color.z, color.w);
  }

  void RenderInterfaceImpl::setViewport (I32 x, I32 y, I32 width, I32 height)
  {
    glViewport(x, y, width, height);
  }

  void RenderInterfaceImpl::setViewport (I32 width, I32 height)
  {
    glViewport(0, 0, width, height);
  }

  void RenderInterfaceImpl::drawIndexed (const Shared<VertexArray>& vao, Count indexCount)
  {
    if (vao == nullptr) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to render null GL vertex array object!");
    }
    
    const auto& ibo = vao->getIndexBuffer();
    if (ibo == nullptr) {
      DG_ENGINE_THROW(std::invalid_argument,
        "Attempt to render GL vertex array with no index buffer bound!");
    }

    vao->bind();
    glDrawElements(GL_TRIANGLES, ibo->getIndexCount(), GL_UNSIGNED_INT, 0);
  }

}
