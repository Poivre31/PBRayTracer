project "PBRT"
   kind "None"
   language "C++"
   cppdialect "C++23"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "vendor/**.cpp", "vendor/**.h", "res/shaders/**.frag","res/shaders/**.vert","res/shaders/**.comp", }
   filter { "files:**.vert or **.frag or **.comp" }
      buildaction "None"
   filter {}

   includedirs{
      "../vendor/glfw/include",
      "../vendor/glew/include",
      "../vendor/imgui",
      "../vendor/imgui/backends",
      "../vendor/spdlog/include",
   }

   libdirs{"../vendor/glfw/lib","../vendor/glew/lib"}
   links{"glew32s.lib","glfw3.lib","opengl32.lib"}
   defines{"GLEW_STATIC"}

   targetdir "bin/%{cfg.buildcfg}"
   objdir "obj/%{cfg.buildcfg}" 

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }
      buildoptions { "/utf-8" }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"

   filter {}
   postbuildcommands {
      '{COPYDIR} "%{prj.location}/res" "%{cfg.targetdir}/res"'
   }
