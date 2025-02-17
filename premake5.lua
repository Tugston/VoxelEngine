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
	debugdir ("bin/" .. outputdir .. "/Game")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/src",
		"Vendor/include/SPDLOG",
		"Vendor/include/SDL2"
	}

	links
	{
		"winmm",
		"setupapi",
		"version",
		"Imm32",
		"SDL2-static",
		"SDL2main"
	}

	libdirs
	{
		"Vendor/bin/sdl2"
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
			"FMT_USE_UTF8=1",
			"SDL_MAIN_HANDLED"
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
		"Vendor/include/SPDLOG",
		"Vendor/include/SDL2"
	}

	links
	{
		"Engine"
	}

	libdirs
	{
		"bin/" .. outputdir .. "/Engine/Engine.lib"
	}

	filter "configurations:Debug"
		postbuildcommands
		{
			"{COPY} ../bin/" .. outputdir .. "/Engine/Engine.dll ../bin/" .. outputdir .. "/Game",
			"{COPY} ../bin/" .. outputdir .. "/Engine/Engine.pdb ../bin/" .. outputdir .. "/Game"
		}
	filter "configurations:Release"
		postbuildcommands
		{
			"{COPY} ../bin/" .. outputdir .. "/Engine/Engine.dll ../bin/" .. outputdir .. "/Game"
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