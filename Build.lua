workspace "PBRT"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "PBRT"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "PBRT/Build-PBRT.lua"