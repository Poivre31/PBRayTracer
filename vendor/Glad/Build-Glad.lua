workspace "Glad"
   configurations {"Build"}
   architecture "x64"
   startproject "Glad"
   systemversion "latest"

project "Glad"
   kind "StaticLib"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "on"

   files { "**.h", "**.c" }

   includedirs{
      "include"
   }

   targetdir "bin/%{cfg.buildcfg}"
   objdir "obj/%{cfg.buildcfg}" 

   optimize "On"
   symbols "Off"
