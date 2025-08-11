project "HelloWorld"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "vendor/**.cpp", "vendor/**.h", "res/shaders/**.frag","res/shaders/**.vert","res/shaders/**.comp", }
   filter { "files:**.vert or **.frag or **.comp" }
      buildaction "None"
   filter {}

   includedirs{
      "../vendor/GLFW/include",
      "../vendor/GLEW/include",
      "../vendor/ImGui",
      "../vendor/ImGui/backends",
  }
   libdirs{"../vendor/GLFW/lib","../vendor/GLEW/lib"}
   links{"glew32s.lib","glfw3.lib","opengl32.lib"}
   defines{"GLEW_STATIC"}

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

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

postbuildcommands {
   "{COPY} %{wks.location}/shaders %{cfg.targetdir}/shaders"
}