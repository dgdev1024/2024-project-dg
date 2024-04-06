-- @file premake5.lua

newoption {
  trigger = "winapi",
  value = "API",
  description = "Choose an API to use for windowing and input",
  allowed = {
    { "glfw",     "GLFW" }
  },
  default = "glfw"
}

newoption {
  trigger = "gfxapi",
  value = "API",
  description = "Choose an API for graphics and rendering",
  allowed = {
    { "glad",     "OpenGL via GLAD" }
  },
  default = "glad"
}

-- Workspace Settings
workspace "project-dg"

  -- Language and Standard
  language "C++"
  cppdialect "gnu++20"

  -- Build Configuration
  location "./generated"
  configurations { "debug", "release", "distribute" }

  -- Build Macros
  filter { "configurations:debug" }
    defines { "DG_DEBUG" }
    symbols "On"
  filter { "configurations:release" }
    defines { "DG_RELEASE" }
    optimize "On"
  filter { "configurations:distribute" }
    defines { "DG_DISTRIBUTE" }
    optimize "On"
  filter {}

  -- Operating System Macros
  filter { "system:linux" }
    defines { "DG_USING_LINUX" }
  filter {}

  -- General Defines


-- External Dependency Build Scripts
if _OPTIONS["winapi"] == "glfw" then
  include "./vendor/glfw"
end

if _OPTIONS["gfxapi"] == "glad" then
  include "./vendor/glad"
end

-- Engine Library
project "dg-engine"

  -- Project Configuration
  kind "StaticLib"
  location "./generated/dg-engine"
  targetdir "./build/bin/dg-engine/%{cfg.buildcfg}"
  objdir "./build/obj/dg-engine/%{cfg.buildcfg}"

  -- Precompiled Header
  pchheader "DG_Pch.hpp"
  pchsource "./projects/dg-engine/src/DG_Pch.cpp"

  -- Include Directories
  includedirs {
    "./vendor/imgui",
    "./vendor/imguizmo",
    "./projects/dg-engine/include"
  }

  -- Source Files
  files {
    "./projects/dg-engine/src/**.cpp",
    "./vendor/imgui/*.cpp",
    "./vendor/imguizmo/*.cpp"
  }

  if _OPTIONS["winapi"] == "glfw" then
    includedirs { 
      "./vendor/glfw/include",
      "./vendor/imgui-glfw"
    }

    files {
      "./vendor/imgui-glfw/*.cpp"
    }
  end

  if _OPTIONS["gfxapi"] == "glad" then
    includedirs { 
      "./vendor/glad/include",
      "./vendor/imgui-opengl"
    }

    files {
      "./vendor/imgui-opengl/*.cpp"
    }
  end

-- Studio Application
project "dg-studio"

  -- Project Configuration
  kind "ConsoleApp"
  location "./generated/dg-studio"
  targetdir "./build/bin/dg-studio/%{cfg.buildcfg}"
  objdir "./build/obj/dg-studio/%{cfg.buildcfg}"

  -- Precompiled Header
  pchheader "DGStudio_Pch.hpp"
  pchsource "./projects/dg-studio/src/DGStudio_Pch.cpp"

  -- Include Directories
  includedirs {
    "./projects/dg-engine/include",
    "./projects/dg-studio/include"
  }

  -- Source Files
  files {
    "./projects/dg-studio/src/**.cpp"
  }

  -- Link Libraries
  libdirs {
    "./build/bin/dg-engine/%{cfg.buildcfg}"
  }

  links {
    "dg-engine"
  }

  if _OPTIONS["winapi"] == "glfw" then
    includedirs { "./vendor/glfw/include" }
    libdirs { "./build/bin/glfw/%{cfg.buildcfg}" }
    links { "GLFW" }
  end

  if _OPTIONS["gfxapi"] == "glad" then
    includedirs { "./vendor/glad/include" }
    libdirs { "./build/bin/glad/%{cfg.buildcfg}" }
    links { "GLAD" }
  end
  