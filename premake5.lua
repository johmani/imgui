project "ImGui"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/ThirdParty/%{prj.name}")
	objdir ("%{wks.location}/Binaries/Intermediates/" .. outputdir .. "/ThirdParty/%{prj.name}")

	files
	{
		"*.h",
		"*.cpp"
	}

	postbuildcommands 
	{
        "{COPY} %{cfg.buildtarget.directory}/*.dll %{wks.location}/Binaries/" .. outputdir .. "/VisionEditor",
        "{COPY} %{cfg.buildtarget.directory}/*.dll %{wks.location}/Binaries/" .. outputdir .. "/Runtime",
        "{COPY} %{cfg.buildtarget.directory}/*.dll %{wks.location}/Binaries/" .. outputdir .. "/SandBox"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "off"
