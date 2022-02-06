workspace "Hotline"
	configurations { "Debug", "Release" }
	platforms { "x86_64" }
	cppdialect "C++20"

project "Hotline"
	kind "ConsoleApp" -- WindowedApp
	language "C++"
	location "hotline"
	targetdir "bin/%{cfg.buildcfg}"

	-- set up files
	files { "hotline/src/**.c", "hotline/src/**.cpp", "hotline/src/**.h", "hotline/src/**.hpp", "hotline/src/**.inl", "vendor/glad/src/gl.c" }
	
	-- set include paths
	includedirs { "hotline/src", "vendor/stb", "vendor/glad/include", "vendor/glm", "vendor/entt/src" }

	-- set defines
	defines { "B2_USER_SETTINGS", "GLFW_INCLUDE_NONE", "_CRT_SECURE_NO_WARNINGS" }

	-- link dependencies
	filter "action: not vs*"
		links { "box2d", "glfw3" }

	-- set up configurations
	filter "configurations:Release"
		optimize "Speed"
		runtime "Release"
	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"
	
	-- set up platforms
	filter "platforms:x86"
        architecture "x86"
    filter "platforms:x86_64"
        architecture "x86_64"
