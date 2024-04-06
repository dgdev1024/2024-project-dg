project "GLFW"

  kind "StaticLib"
  language "C"
  location "../../generated/glfw"
  targetdir "../../build/bin/glfw/%{cfg.buildcfg}"
  objdir "../../build/obj/glfw/%{cfg.buildcfg}"

  defines { "DG_USING_GLFW" }

  filter { "system:linux" }
    cdialect "gnu17"
    defines { "_GLFW_X11" }
  filter {}

  includedirs { "./include" }
  files { "./src/*.c" }
