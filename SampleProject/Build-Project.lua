project "Project"
   language "C++"
   cppdialect "C++23"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "obj/"

   enablemodules "On"
   buildstlmodules "On"

   files {
      "**.h",
      "**.cpp",
      "**.ixx",
      "**.comp",
      "**.frag",
      "**.vert"
   }


   includedirs{
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

   prebuildcommands {
      '{COPYDIR} "../VegaEngine/res" "%{prj.location}/res/defaults"',
      '{COPYDIR} "%{prj.location}/res" "%{cfg.targetdir}/res"'
   } 

   staticruntime "On"

   filter { "configurations:Debug" }
      kind "ConsoleApp"
      defines { "CONSOLE" }

      defines { "DEBUG" }
      optimize "Off"
      symbols "On"

   filter { "configurations:Release" }
      kind "ConsoleApp"
      defines { "CONSOLE" }

      defines { "RELEASE" }
      optimize "On"
      symbols "On"

   filter { "configurations:Dist" }
      kind "WindowedApp"
      defines { "WINDOWS" }

      defines { "DIST" }
      optimize "On"
      symbols "Off"

