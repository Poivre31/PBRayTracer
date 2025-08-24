project "ImGui"
   architecture "x64"
   kind "StaticLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "on"

   files { 
      "imconfig.h",
      "imgui.h",
      "imgui.cpp",
      "imgui_demo.cpp",
      "imgui_draw.cpp",
      "imgui_internal.h",
      "imgui_tables.cpp",
      "imgui_widgets.cpp",
      "imstb_rectpack.h",
      "imstb_textedit.h",
      "imstb_truetype.h",

      "backends/imgui_impl_opengl3.cpp",
      "backends/imgui_impl_opengl3.h",
      "backends/imgui_impl_opengl3_loader.h",
      "backends/imgui_impl_glfw.h",
      "backends/imgui_impl_glfw.cpp",

      "misc/cpp/imgui_stdlib.h",
      "misc/cpp/imgui_stdlib.cpp",
   }

   includedirs {
      "./",
      "backends/",
      "misc/cpp/",
      "../glfw/include",
   }

   targetdir "bin/%{cfg.buildcfg}"
   objdir "obj/%{cfg.buildcfg}" 

   optimize "On"
   symbols "Off"
