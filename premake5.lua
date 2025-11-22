workspace "VoxelGame"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


function CopyPDB(folderName)
	return "{COPY} ../bin/" .. outputdir .. "/Engine/Engine.pdb ../bin/" .. outputdir .. "/" .. folderName
end

project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/VENDOR/**.h",
		"%{prj.name}/VENDOR/**.cpp"
	}

	-- Imgui src is directly included in the project --
	includedirs
	{
		"Engine/src",
		"Vendor/include/GLFW",
		"Vendor/include/GLEW",
		"Vendor/include/GLM",
		"Vendor/include/SPDLOG"
	}

	links
	{
		"Engine"
	}

	dependson 
	{
		"Engine"
	}

	libdirs
	{
		"bin/" .. outputdir .. "/Engine/Engine.lib"
	}

	--imgui src should not add my pch
	filter "files:Engine/src/Vendor/**.cpp"
		flags {"NoPCH"}


	filter "configurations:Debug"
		prebuildcommands
		{
			CopyPDB("Editor")
		}
	filter "configurations:Release"
		prebuildcommands
		{
			CopyPDB("Editor")
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
			"EDTR_DEBUG",
			"ENGINE_PLATFORM_WINDOWS",
			"FMT_USE_UTF8=1"
		}

	filter "configurations:Debug"
		defines "EDITOR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EDITOR_DEBUG"
		optimize "On"

	filter "configurations:Dist"
		defines "EDTR_DIST"
		optimize "On"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")
	debugdir ("bin/" .. outputdir .. "/Game")

	pchheader "egpch.h"
	pchsource "%{prj.name}/src/egpch.cpp"	

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Engine/src",
		"Vendor/include/SPDLOG",
		"Vendor/include/GLFW",
		"Vendor/include/GLM",
		"Vendor/include/GLEW",
	}

	links
	{
		"glfw3_mt",
		"opengl32",
		"glew32s"
	}

	libdirs
	{
		"Vendor/bin/glfw",
		"Vendor/bin/glew",
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
			"GLFW_STATIC",
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "EG_DEBUG"
		optimize "On"
	filter "configurations:Dist"
		defines "EG_DIST"
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
		"Vendor/include/GLFW",
		"Vendor/include/GLM",
		"Vendor/include/GLEW",
	}

	links
	{
		"Engine"
	}

	dependson
	{
		"Engine"
	}

	libdirs
	{
		"bin/" .. outputdir .. "/Engine/Engine.lib"
	}

	filter "configurations:Debug"
		prebuildcommands
		{
			CopyPDB("Game")
		}
	filter "configurations:Release"
		prebuildcommands
		{
			CopyPDB("Game")
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
		defines "APP_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "APP_DEBUG"
		optimize "On"
	filter "configurations:Dist"
		defines "APP_DIST"
		optimize "On"