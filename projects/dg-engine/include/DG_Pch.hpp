/** @file DG_Pch.hpp */

#ifndef DG_PCH_HPP
#define DG_PCH_HPP

#if defined(DG_USING_OPENGL)
  #if defined(DG_USING_GLAD)
    #include <glad/glad.h>
  #endif
#endif

#if defined(DG_USING_GLFW)
  #include <GLFW/glfw3.h>
#endif

#include <DG/Common.hpp>
#include <DG/Core/Logging.hpp>

#endif
