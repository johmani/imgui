project "imgui"
	kind "SharedLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "Off"

	targetdir (binOutputDir)
    objdir (IntermediatesOutputDir)

	files
	{
		"*.h",
		"*.cpp",
		"*.cppm",
		"*.lua",
	}

    includedirs
    {
        
    }

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
		symbols "Off"
