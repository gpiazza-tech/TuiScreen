workspace "TuiScreen"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "TuiScreen"
    location "."
    kind "StaticLib"
    language "C"
    staticruntime "on"
    toolset "msc-v145"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "src/pch.c"

    files
    {
        "src/**.h",
        "src/**.c"
    }

    includedirs "include"
    
    buildoptions 
    {
        "/utf-8",
        "/TC",
    }

    filter "system:windows"
        systemversion "latest"
        defines "TUI_PLATFORM_WINDOWS"
    
    filter "configurations:Debug"
        defines "PXR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PXR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "PXR_DIST"
        runtime "Release"
        optimize "on"