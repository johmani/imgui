project "imgui"
    language "C++"
    cppdialect "C++latest"
    implibdir "%{cfg.objdir}"
    objdir (IntermediatesOutputDir)

    ProjectKind("SharedLib")
    filter "kind:SharedLib"
        targetdir (binOutputDir)
    filter "kind:StaticLib"
        targetdir (libOutputDir)
    filter {}

    files {

        "*.h",
        "*.cpp",

        "ImExtensions/*.h",
        "ImExtensions/*.cpp",

        "*.lua",
    }

    includedirs {
        "."
    }

    removefiles{

        "imgui_demo.cpp",
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
        symbols "On"

    filter "configurations:Dist"
        runtime "Release"
        symbols "Off"
