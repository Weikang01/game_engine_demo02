workspace "game_engine"
    architecture ("x86")

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Engine/vendor/imgui"
IncludeDir["glm"] = "Engine/vendor/glm"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/imgui"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

    pchheader "engine_pch.h"
    pchsource "Engine/src/engine_pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
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
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "action:vs*"
        disablewarnings 
        {
            "6031",
            "26812",
            "26495",
            "26451",
            "26498"
        }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ENGINE_BUILD_DLL",
            "ENGINE_PLATFORM_WINDOWS",
            "WIN32"
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "ENGINE_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Engine/src",
        "Engine/vendor/spdlog/include",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "ENGINE_PLATFORM_WINDOWS",
            "WIN32"
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ENGINE_DIST"
        optimize "On"