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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mkpch.h"
	pchsource "MakeEngine/src/mkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
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
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS",
			"MK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MK_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"MakeEngine/src",
		"MakeEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"MakeEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MK_DIST"
		runtime "Release"
		optimize "on"