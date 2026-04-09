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
    cdialect "C11"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "src/pch.c"

    files
    {
        "src/**.h",
        "src/**.c"
    }

    includedirs 
    {
        "include",
        "src",
    }

    filter "system:windows"
        systemversion "latest"
        toolset "msc-v145"

        buildoptions 
        {
            "/utf-8",
            "/TC",
        }

    filter "system:linux"
        links 
        {
            "m"
        }
    
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
