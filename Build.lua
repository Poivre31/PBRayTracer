workspace "OrionRayTracer"
   configurations {"Debug", "Release", "Dist"}
   architecture "x64"
   startproject "OrionRayTracer"
   systemversion "latest"
   clangtidy "On"
   buildoptions { "/Zc:__cplusplus" }

include "VegaEngine/Build-Vega.lua"
include "OrionRayTracer/Build-Orion.lua"
include "PBRT/Build-PBRT.lua"
include "vendor/ImGui/Build-ImGui.lua"