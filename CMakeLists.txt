cmake_minimum_required(VERSION 2.8)

project(CSK)
set(CMAKE_SHARED_LIBRARY_PREFIX "../")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".asi")


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.60.0 COMPONENTS property_tree)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
else()
    set(Boost_USE_STATIC_LIBS OFF)
    find_package(Boost 1.60.0 COMPONENTS property_tree)
	if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
    endif()
endif()


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CSK ${PROJECT_NAME}_LIST)


if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--gc-sections -ffast-math -static")
	add_definitions("-ffunction-sections -fdata-sections -w -municode")
	if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fno-stack-protector")
	elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
	endif()
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--strip-all")
	endif()
endif()

set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_VISIBILITY_PRESET hidden
    C_VISIBILITY_PRESET hidden
)

target_link_libraries(${PROJECT_NAME})

