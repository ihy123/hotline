cmake_minimum_required(VERSION 3.22)

# Meta information
set(HOTLINE_NAME                "Hotline")
set(HOTLINE_VERSION_MAJOR       "0")
set(HOTLINE_VERSION_MINOR       "0")
set(HOTLINE_VERSION_PATCH       "0")
set(HOTLINE_VERSION             "${HOTLINE_VERSION_MAJOR}.${HOTLINE_VERSION_MINOR}.${HOTLINE_VERSION_PATCH}")
set(HOTLINE_NAME_VERSION        "${HOTLINE_NAME} v${HOTLINE_VERSION}")

# define configurations
set(HOTLINE_CONFIGURATION_TYPES Release)
get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(multi_config)
    set(CMAKE_CONFIGURATION_TYPES ${HOTLINE_CONFIGURATION_TYPES})
else()
    set(CMAKE_BUILD_TYPE Release)
#    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type of the project (one of: ${HOTLINE_CONFIGURATION_TYPES})")
#    if(NOT CMAKE_BUILD_TYPE IN_LIST HOTLINE_CONFIGURATION_TYPES)
#        message(FATAL_ERROR
#        "Invalid build type '${CMAKE_BUILD_TYPE}'.
#        CMAKE_BUILD_TYPE must be any one of the possible values:
#        ${HOTLINE_CONFIGURATION_TYPES}")
#    endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
project(${HOTLINE_NAME} C CXX)

# sources
set(src ${CMAKE_SOURCE_DIR}/hotline/src)
file(GLOB_RECURSE HOTLINE_SOURCES ${src}/*.cpp ${src}/*.c ${src}/*.hpp ${src}/*.h ${src}/*.inl)
list(APPEND HOTLINE_SOURCES ${CMAKE_SOURCE_DIR}/vendor/glad/src/gl.c)
add_executable(${HOTLINE_NAME} ${HOTLINE_SOURCES})

# set include directories
target_include_directories(${HOTLINE_NAME} PRIVATE
	${src}
	${CMAKE_SOURCE_DIR}/vendor/stb
	${CMAKE_SOURCE_DIR}/vendor/glm
	${CMAKE_SOURCE_DIR}/vendor/entt/src
    ${CMAKE_SOURCE_DIR}/vendor/glad/include)

# set output directories
set_target_properties(${HOTLINE_NAME} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# set compile definitions
target_compile_definitions(${HOTLINE_NAME} PRIVATE
	B2_USER_SETTINGS
	GLFW_INCLUDE_NONE
	_CRT_SECURE_NO_WARNINGS
	$<$<CONFIG:Release>:GLM_FORCE_SSE2>)


# link dependencies
# we should not explicitly link libraries when using visual studio
# because vcpkg will do this automatically
find_package(box2d REQUIRED)
find_package(glfw3 REQUIRED)
#if((NOT MSVC) OR (${BUILDING_WITH_AUTO_SCRIPT}))
target_link_libraries(${HOTLINE_NAME} PRIVATE box2d::box2d)
target_link_libraries(${HOTLINE_NAME} PRIVATE glfw)
#endif()



#set(GLFW_SOURCES_PATH ${CMAKE_SOURCE_DIR}/vendor/glfw)
#set(BOX2D_SOURCES_PATH ${CMAKE_SOURCE_DIR}/vendor/box2d)
#
#add_subdirectory(${GLFW_SOURCES_PATH})
#target_include_directories(${HOTLINE_NAME} PRIVATE ${GLFW_SOURCES_PATH}/include)
#target_link_libraries(${HOTLINE_NAME} PRIVATE glfw ${GLFW_LIBRARIES})
#
#add_subdirectory(${BOX2D_SOURCES_PATH})
#target_include_directories(${HOTLINE_NAME} PRIVATE ${BOX2D_SOURCES_PATH}/include)
#target_link_libraries(${HOTLINE_NAME} PRIVATE box2d)


# copy resources to binary directory
file(COPY ${CMAKE_SOURCE_DIR}/hotline/res DESTINATION ${CMAKE_SOURCE_DIR}/bin/Release)
