workspace "MakeEngine"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MakeEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "MakeEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "MakeEngine/vendor/imgui"


group "Dependencies"
	include "MakeEngine/vendor/GLFW"
	include "MakeEngine/vendor/Glad"
	include "MakeEngine/vendor/ImGui"
group ""



project "MakeEngine"
	location "MakeEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mkpch.h"
	pchsource "MakeEngine/src/mkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS",
			"MK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MakeEngine/vendor/spdlog/include",
		"MakeEngine/src"
	}

	links
	{
		"MakeEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
		buildoptions "/MD"
		optimize "On"