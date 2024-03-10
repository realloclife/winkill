workspace "winkill"
	configurations { "Debug", "Release" }
	architecture "x64"

project "winkill"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++latest"
	targetdir "bin/%{cfg.buildcfg}"

files { "src/**.cxx" }

filter "configurations:Debug"
	defines { "DEBUG" }
	symbols "On"
	optimize "Off"

filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "Speed"
	flags { "LinkTimeOptimization" }

filter {}
