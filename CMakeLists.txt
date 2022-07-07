cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ProjectName MMSnake)
project(${ProjectName} LANGUAGES CXX)

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
endif(NOT DEFINED BUILD_SHARED_LIBS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(vendor/SDL)

add_subdirectory(src)