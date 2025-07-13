workspace "HelloWorld"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "HelloWorld"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "HelloWorld/Build-HelloWorld.lua"