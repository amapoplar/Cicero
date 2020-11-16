workspace "Cicero"

    architecture "x64"
    configurations { 
        "Debug", 
        "Release"
    }
    
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


    --Include directories relative to root folder

    includeDirs = {}
    includeDirs["sfml"]= "Cicero/vendor/sfml/include"

    project "Cicero"

        location "Cicero"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"

        targetdir("bin/"..outputdir.."/%{prj.name}")
        objdir("bin-int/"..outputdir.."/%{prj.name}")
        
        pchheader "cicpch.h"
        pchsource "Cicero/src/cicpch.cpp"

    
        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"

        }

        includedirs{
            "%{prj.name}/src",
            "%{includeDirs.sfml}"
        }

        links{
        }

        filter "system:windows"
            systemversion "latest"
            defines{
                "CIC_PLATFORM_WINDOWS",
                "CIC_BUILD_DLL",
                "SFML_STATIC"
            }


        filter "configurations:Debug"
            defines "CIC_DEBUG"
            buildoptions "/MDd"
            symbols "On"

        filter "configurations:Release"
            defines "CIC_RELEASE"
            buildoptions "/MD"
            optimize "On"

    project "ChessApp"
        location "ChessApp"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"


        targetdir("bin/"..outputdir.."/%{prj.name}")
        objdir("bin-int/"..outputdir.."/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
    
        includedirs{
            "Cicero/src",
            "%{includeDirs.sfml}"
        }
        libdirs{
            "Cicero/vendor/sfml/lib"
        }

        links{
            "Cicero",
            "opengl32.lib",
            "winmm.lib",
            "gdi32.lib",
            "freetype.lib"
        }

    
        filter "system:windows"
            systemversion "latest"
            defines{
               "CIC_PLATFORM_WINDOWS",
               "SFML_STATIC"
            }
    
        filter "configurations:Debug"
            defines "CIC_DEBUG"
            buildoptions "/MDd"
            symbols "On"
            links{
                "sfml-graphics-s-d.lib",
                "sfml-window-s-d.lib",
                "sfml-system-s-d.lib"
            }
    
        filter "configurations:Release"
            defines "CIC_RELEASE"
            buildoptions "/MD"
            optimize "On"
            links{
                "sfml-graphics-s.lib",
                "sfml-window-s.lib",
                "sfml-system-s.lib"
            }