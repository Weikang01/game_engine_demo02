project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		staticruntime "On"
        buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		staticruntime "On"
        buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		staticruntime "On"
        buildoptions "/MT"
		optimize "on"