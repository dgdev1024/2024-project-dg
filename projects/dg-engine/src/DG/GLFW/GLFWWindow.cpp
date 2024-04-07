/** @file DG/GLFW/GLFWWindow.cpp */

#include <DG/Graphics/RenderCommand.hpp>
#include <DG/GLFW/GLFWWindow.hpp>

namespace dg
{

  Unique<Window> Window::make (const WindowSpecification& spec)
  {
    return std::make_unique<GLFW::WindowImpl>(spec);
  }

}

namespace dg::GLFW
{

  static Count s_windowCount = 0;

  static void onError (int code, const char* description)
  {
    DG_ENGINE_ERROR("GLFW Error {}: {}", code, description);
  }

  static void onWindowClose (GLFWwindow* winptr)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    window->emitEvent<WindowCloseEvent>();
  }

  static void onWindowSize (GLFWwindow* winptr, int width, int height)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    window->emitEvent<WindowResizeEvent>(width, height);
  }

  static void onFramebufferSize (GLFWwindow* winptr, int width, int height)
  {
    RenderCommand::setViewport(width, height);
  }

  WindowImpl::WindowImpl (const WindowSpecification& spec) :
    Window { spec }
  {
    if (s_windowCount == 0) {
      glfwSetErrorCallback(onError);
      if (glfwInit() != GLFW_TRUE) {
        DG_ENGINE_THROW(std::runtime_error, "Could not initialize GLFW!");
      }

      #if defined(DG_USING_OPENGL)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      #else
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      #endif
    }

    m_winptr = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
    if (m_winptr == nullptr) {
      DG_ENGINE_THROW(std::runtime_error, "Could not create GLFW window!");
    }

    #if defined(DG_USING_OPENGL)
      glfwMakeContextCurrent(m_winptr);
      glfwSwapInterval(1);
    #endif

    glfwSetWindowUserPointer(m_winptr, this);
    glfwSetWindowCloseCallback(m_winptr, onWindowClose);
    glfwSetWindowSizeCallback(m_winptr, onWindowSize);
    glfwSetFramebufferSizeCallback(m_winptr, onFramebufferSize);

    s_windowCount++;
  }

  WindowImpl::~WindowImpl ()
  {
    glfwDestroyWindow(m_winptr);
    if (--s_windowCount == 0) {
      glfwTerminate();
    }
  }

  void WindowImpl::update ()
  {
    glfwPollEvents();

    #if defined(DG_USING_OPENGL)
      glfwSwapBuffers(m_winptr);
    #endif
  }

  void* WindowImpl::getPointer () const
  {
    return m_winptr;
  }

  void WindowImpl::onTitleChanged ()
  {
    glfwSetWindowTitle(m_winptr, m_title.c_str());
  }

  void WindowImpl::onSizeChanged ()
  {
    glfwSetWindowSize(m_winptr, m_size.x, m_size.y);
  }

}
