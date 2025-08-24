project "VegaEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   targetdir "bin/%{cfg.buildcfg}"
   objdir "obj/%{cfg.buildcfg}"

   files {
      "**.h",
       "**.cpp",
   }

   includedirs{
      "../vendor/GLFW/include",
      "../vendor/spdlog/include",
      "../vendor/Glad/include",
      "../vendor/ImGui",
      "../vendor/ImGui/backends",
      "../vendor/ImGui/misc/cpp",
      "src",
   }

   libdirs{
      "../vendor/GLFW/lib",
      "../vendor/Glad/lib",
   }

   links{
      "ImGui",
      "Glad.lib",
      "glfw3_mt.lib",
      "opengl32.lib"
   }

   buildoptions { "/utf-8" }

   staticruntime "On"

   filter { "configurations:Debug" }
      defines { "DEBUG" }
      optimize "Off"
      symbols "On"

   filter { "configurations:Release" }
      defines { "RELEASE" }
      optimize "On"
      symbols "On"

   filter { "configurations:Dist" }
      defines { "DIST" }
      optimize "On"
      symbols "Off"