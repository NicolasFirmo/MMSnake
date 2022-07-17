string(TOLOWER ${PROJECT_NAME} ExecutableName)

file(GLOB_RECURSE "${ExecutableName}_SOURCES" RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
list(REMOVE_ITEM ${ExecutableName}_SOURCES pch.h)
message(STATUS "${ExecutableName}_SOURCES: ${${ExecutableName}_SOURCES}")

add_executable(${ExecutableName} ${${ExecutableName}_SOURCES})
target_compile_definitions(${ExecutableName} PRIVATE DEBUG=$<IF:$<CONFIG:Debug>,1,0>)

target_include_directories(${ExecutableName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(supportsIPO)
	set_target_properties(${ExecutableName} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif(supportsIPO)

target_precompile_headers(${ExecutableName} PRIVATE pch.h)

target_link_libraries(${ExecutableName}
	SDL2main
	SDL2-static
	fmt::fmt)

if(MSVC)
	target_compile_options(${ExecutableName} PRIVATE
		"$<$<COMPILE_LANGUAGE:CXX>:/Wall;/MP;/Oi;/GL;$<$<CONFIG:RELEASE>:/Ot;/GR->>")
	set_target_properties(${ExecutableName} PROPERTIES MSVC_RUNTIME_LIBRARY
		"MultiThreaded$<$<CONFIG:Debug>:Debug>")

	# Disable exceptions: https://cmake.org/pipermail/cmake/2010-December/041641.html
	if(CMAKE_CXX_FLAGS MATCHES "/EHsc ")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif(CMAKE_CXX_FLAGS MATCHES "/EHsc ")

	if(CMAKE_CXX_FLAGS MATCHES "/EHsc$")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif(CMAKE_CXX_FLAGS MATCHES "/EHsc$")

	set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ExecutableName})
endif(MSVC)