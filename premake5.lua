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
    kind "SharedLib"
    language "C++"

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

    pchheader "engine_pch.h"
    pchsource "Engine/src/engine_pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
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

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ENGINE_BUILD_DLL",
            "ENGINE_PLATFORM_WINDOWS",
            "WIN32"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        staticruntime "Off"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        staticruntime "Off"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "ENGINE_DIST"
        staticruntime "Off"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "%{IncludeDir.glm}"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ENGINE_PLATFORM_WINDOWS",
            "WIN32"
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        staticruntime "Off"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        staticruntime "Off"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "ENGINE_DIST"
        staticruntime "Off"
        buildoptions "/MD"
        optimize "On"