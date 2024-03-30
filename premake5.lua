-- @file premake5.lua

-- Workspace Settings
workspace "project-dg"

  -- Language and Standard
  language "C++"
  cppdialect "C++20"

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


-- Engine Library
project "dg-engine"

  -- Project Configuration
  kind "StaticLib"
  location "./generated/dg-engine"
  targetdir "./build/bin/dg-engine/%{cfg.buildcfg}"
  objdir "./build/obj/dg-engine/%{cfg.buildcfg}"

  -- Precompiled Header
  pchheader "DGPch.hpp"
  pchsource "./projects/dg-engine/src/DGPch.cpp"

  -- Include Directories
  includedirs {
    "./projects/dg-engine/include"
  }

  -- Source Files
  files {
    "./projects/dg-engine/src/**.cpp"
  }

-- Studio Application
project "dg-studio"

  -- Project Configuration
  kind "ConsoleApp"
  location "./generated/dg-studio"
  targetdir "./build/bin/dg-studio/%{cfg.buildcfg}"
  objdir "./build/obj/dg-studio/%{cfg.buildcfg}"

  -- Precompiled Header
  pchheader "DGStudioPch.hpp"
  pchsource "./projects/dg-studio/src/DGStudioPch.cpp"

  -- Include Directories
  includedirs {
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
  