cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(StickTheStick LANGUAGES C CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

include(CheckIPOSupported)
check_ipo_supported(RESULT supportsIPO OUTPUT error)
if(supportsIPO)
	message(STATUS "IPO / LTO is supported")
else()
	message(STATUS "IPO / LTO is not supported: <${error}>")
endif()

if(NOT DEFINED BUILD_SHARED_LIBS)
	set(BUILD_SHARED_LIBS OFF)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(vendor/Glad2)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/GLFW)

add_subdirectory(vendor/fmt EXCLUDE_FROM_ALL)

add_subdirectory(src)