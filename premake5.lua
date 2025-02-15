workspace "VoxelGame"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Vendor/include/SPDLOG"
	}

	libdirs
	{
		"Vendor/bin"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		characterset ("Unicode")

		buildoptions
		{
			"/utf-8"
		}

		defines
		{
			"ENGINE_PLATFORM_WINDOWS",
			"ENGINE_BUILD_DLL",
			"_WINDLL",
			"FMT_USE_UTF8=1"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "EG_RELEASE"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/src",
		"Vendor/include/SPDLOG"
	}

	links
	{
		"Engine"
	}

	postbuildcommands
	{
		"{COPY} ../bin/" .. outputdir .. "/Engine/Engine.dll ../bin/" .. outputdir .. "/Game"
	}

	libdirs
	{
		"bin/" .. outputdir .. "/Engine/Engine.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		characterset ("Unicode")

		buildoptions
		{
			"/utf-8"
		}

		defines
		{
			"ENGINE_PLATFORM_WINDOWS",
			"FMT_USE_UTF8=1"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "EG_RELEASE"
		optimize "On"