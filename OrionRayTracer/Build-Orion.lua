project "OrionRayTracer"
   language "C++"
   cppdialect "C++23"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "obj/"

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
      -- "../vendor/gsl",
      "../VegaEngine/src",
   }

   libdirs{
      "../vendor/GLFW/lib",
      "../vendor/Glad/lib",
   }

   links{
      "ImGui",
      "Glad.lib",
      "glfw3_mt.lib",
      "opengl32.lib",
      "VegaEngine"
   }

   buildoptions { "/utf-8" }

   postbuildcommands {
      '{COPYDIR} "%{prj.location}/res" "%{cfg.targetdir}/res"'
   } 

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
      kind "WindowedApp"
      defines { "DIST" }
      optimize "On"
      symbols "Off"

