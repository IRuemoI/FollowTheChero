-- premake5.lua
workspace "Hazel"
   architecture "x64"
   configurations { "Debug", "Release","Dist" }

 outputdir = "%{cfg.buildcfg}-%{cfg.sys}-%{cfg.architecture}"


project "Hazel"
   location "Hazel" --���·��
   kind "SharedLib"  -- =dll
   language "C++"

   targetdir ("bin/"..outputdir.. "/%{prj.name}")
   objdir ("bin-int/"..outputdir.. "/%{prj.name}")

   files
   {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"

   }

   includedirs
   {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
   }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On" --��̬��������ʱ��  ����ʱ����c++�ṩ�ı�׼��Ļ���������dll("/MD")һ���Ƕ�̬����,����ͬ���������ľ�̬��libҲ��������ʱ��("/MT")
      systemversion "10.0"

      defines
      {
         "HZ_BUILD_DLL",
         "HZ_PLATFORM_WINDOWS",
         "_WINDLL"

      }
      postbuildcommands 
      {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox") --copy from to .todir is baed on fromdir
      }
   
   filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"

   filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On" --���������Ż�

   filter "configurations:Dist"
      defines "HZ_DIST"
      optimize "On" --���������Ż�

project "Sandbox"
   location "Sandbox" --���·��
   kind "ConsoleApp"  -- =dll
   language "C++"

   targetdir ("bin/"..outputdir.."/%{prj.name}")
   objdir ("bin-int/"..outputdir.."/%{prj.name}")

   files
   {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
   }
   includedirs
   {
        
        "Hazel/src",
        "Hazel/vendor/spdlog/include"

   }

   links
   {
        "Hazel"
   }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On" --��̬��������ʱ��  ����ʱ����c++�ṩ�ı�׼��Ļ���������dll("/MD")һ���Ƕ�̬����,����ͬ���������ľ�̬��libҲ��������ʱ��("/MT")
      systemversion "10.0"

      defines
      {
         "HZ_PLATFORM_WINDOWS"
      }

   
   filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"

   filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On" --���������Ż�

   filter "configurations:Dist"
      defines "HZ_DIST"
      optimize "On" --��