file(GLOB_RECURSE "${ProjectName}_sources" RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
list(REMOVE_ITEM ${ProjectName}_sources pch.h)
message(STATUS "${ProjectName}_sources: ${${ProjectName}_sources}")

add_executable(${ProjectName} ${${ProjectName}_sources})
target_include_directories(${ProjectName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(supportsIPO)
	set_target_properties(${ProjectName} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif(supportsIPO)

target_precompile_headers(${ProjectName} PRIVATE pch.h)

target_link_libraries(${ProjectName}
	SDL2-static)

if(MSVC)
	target_compile_options(${ProjectName} PRIVATE
		"$<$<COMPILE_LANGUAGE:CXX>:/Wall;/MP;/Oi;/GL;$<$<CONFIG:RELEASE>:/Ot;/GR->>")
	set_target_properties(${ProjectName} PROPERTIES MSVC_RUNTIME_LIBRARY
		"MultiThreaded$<$<CONFIG:Debug>:Debug>")

	# Disable exceptions: https://cmake.org/pipermail/cmake/2010-December/041641.html
	if(CMAKE_CXX_FLAGS MATCHES "/EHsc ")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif(CMAKE_CXX_FLAGS MATCHES "/EHsc ")

	if(CMAKE_CXX_FLAGS MATCHES "/EHsc$")
		string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif(CMAKE_CXX_FLAGS MATCHES "/EHsc$")

	set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectName})
endif(MSVC)