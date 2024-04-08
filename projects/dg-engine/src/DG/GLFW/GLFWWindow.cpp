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

  static void onWindowFocus (GLFWwindow* winptr, int focused)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    if (focused == GLFW_TRUE) {
      window->emitEvent<WindowFocusEvent>();
    } else {
      window->emitEvent<WindowBlurEvent>();
    }
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

  static void onKey (GLFWwindow* winptr, int key, int scan, int action, int mods)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));

    bool  ctrl  = (mods & GLFW_MOD_CONTROL),
          alt   = (mods & GLFW_MOD_ALT),
          shift = (mods & GLFW_MOD_SHIFT),
          super = (mods & GLFW_MOD_SUPER);

    if (action == GLFW_PRESS) {
      window->emitEvent<KeyDownEvent>(key, ctrl, alt, shift, super);
    } else if (action == GLFW_RELEASE) {
      window->emitEvent<KeyUpEvent>(key, ctrl, alt, shift, super);
    }
  }

  static void onChar (GLFWwindow* winptr, unsigned int codepoint)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    window->emitEvent<TextInputEvent>(codepoint);
  }

  static void onMouseButton (GLFWwindow* winptr, int button, int action, int mods)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));

    bool  ctrl  = (mods & GLFW_MOD_CONTROL),
          alt   = (mods & GLFW_MOD_ALT),
          shift = (mods & GLFW_MOD_SHIFT),
          super = (mods & GLFW_MOD_SUPER);

    if (action == GLFW_PRESS) {
      window->emitEvent<MouseButtonDownEvent>(button, ctrl, alt, shift, super);
    } else if (action == GLFW_RELEASE) {
      window->emitEvent<MouseButtonUpEvent>(button, ctrl, alt, shift, super);
    }    
  }

  static void onCursorPos (GLFWwindow* winptr, double x, double y)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    window->emitEvent<MouseMotionEvent>(static_cast<F32>(x), static_cast<F32>(y));
  }

  static void onCursorEnter (GLFWwindow* winptr, int entered)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    if (entered == GLFW_TRUE) {
      window->emitEvent<MouseEnterEvent>();
    } else {
      window->emitEvent<MouseLeaveEvent>();
    }
  }

  static void onScroll (GLFWwindow* winptr, double x, double y)
  {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(winptr));
    window->emitEvent<ScrollEvent>(static_cast<F32>(x), static_cast<F32>(y));
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
    glfwSetWindowFocusCallback(m_winptr, onWindowFocus);
    glfwSetFramebufferSizeCallback(m_winptr, onFramebufferSize);
    glfwSetKeyCallback(m_winptr, onKey);
    glfwSetCharCallback(m_winptr, onChar);
    glfwSetMouseButtonCallback(m_winptr, onMouseButton);
    glfwSetCursorPosCallback(m_winptr, onCursorPos);
    glfwSetCursorEnterCallback(m_winptr, onCursorEnter);
    glfwSetScrollCallback(m_winptr, onScroll);

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
