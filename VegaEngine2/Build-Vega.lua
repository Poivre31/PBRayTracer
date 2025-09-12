project "VegaEngine2"
   language "C++"
   cppdialect "C++23"
   targetdir "bin/%{cfg.buildcfg}"
   objdir "obj/%{cfg.buildcfg}"

   enablemodules "On"
   buildstlmodules "On"

   files {
      "**.h",
      "**.cpp",
      "**.ixx",
   }

   includedirs{
      "../vendor/GLFW/include",
      "../vendor/Glad/include",
      "../vendor/ImGui",
      "../vendor/ImGui/backends",
      "../vendor/ImGui/misc/cpp",
      -- "../vendor/gsl",
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
      kind "ConsoleApp"
      defines { "DEBUG" }
      optimize "Off"
      symbols "On"

   filter { "configurations:Release" }
      kind "ConsoleApp"
      defines { "RELEASE" }
      optimize "On"
      symbols "On"

   filter { "configurations:Dist" }
      kind "ConsoleApp"
      defines { "DIST" }
      optimize "On"
      symbols "Off"