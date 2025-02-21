workspace "VoxelGame"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Share"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


function CopyPDB()
	return "{COPY} ../bin/" .. outputdir .. "/Engine/Engine.pdb ../bin/" .. outputdir .. "/Game"
end

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
		"Vendor/include/GLFW",
		"Vendor/include/GLM"
	}

	links
	{
		--"winmm",
		--"setupapi",
		--"version",
		--"Imm32",
		"glfw3_mt",
		"opengl32"
	}

	libdirs
	{
		"Vendor/bin/glfw"
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
			"GLFW_STATIC"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "EG_DEBUG"
		optimize "On"
	filter "configurations:Share"
		defines "EG_SHARE"
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
		"Vendor/include/GLM"
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

	-- copy engine dll
	prebuildcommands
	{
		"{COPY} ../bin/" .. outputdir .. "/Engine/Engine.dll ../bin/" .. outputdir .. "/Game"
	}

	filter "configurations:Debug"
		prebuildcommands
		{
			CopyPDB()
		}
	filter "configurations:Release"
		prebuildcommands
		{
			CopyPDB()
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
	filter "configurations:Share"
		defines "APP_SHARE"
		optimize "On"