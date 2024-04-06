project "GLAD"

  kind "StaticLib"
  language "C"
  location "../../generated/glad"
  targetdir "../../build/bin/glad/%{cfg.buildcfg}"
  objdir "../../build/obj/glad/%{cfg.buildcfg}"

  defines { "DG_USING_OPENGL", "DG_USING_GLAD" }

  includedirs { "./include" }
  files { "./src/*.c" }