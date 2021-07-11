# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

if (${CMAKE_SOURCE_DIR} STREQUAL {CMAKE_BINARY_DIR})
  message (FATAL_ERROR "In-source build is not allowed, please create a separate build folder.")
endif()

if (NOT DEFINED RCBUILD_VERSION_MAJOR)
	set (rcbuild_version_major 0)
endif ()

if (NOT DEFINED RCBUILD_VERSION_MINOR)
	set (rcbuild_version_minor 0)
endif ()

if (NOT DEFINED RCBUILD_VERSION_PATCH)
	set (rcbuild_version_patch 1)
endif ()
	
list (APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list (APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message (STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file (DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()

include (${CMAKE_BINARY_DIR}/conan_paths.cmake)
include (ExternalProject)

find_package (CCache)

if (CCache_FOUND)
  message ("Detected ccache. Using ccache for faster recompilation")
  option (RCBUILD_CCACHE_COMPILATION "using ccache for faster recompilation" ON)
  if (RCBUILD_CCACHE_COMPILATION)
    set_property (GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCache_EXECUTABLE}")
  endif ()
endif ()

project (rcbuild
	VERSION ${rcbuild_version_major}.${rcbuild_version_minor}.${rcbuild_version_patch}
	LANGUAGES CXX)

option (COMPILE_COMMANDS "cmake export compile commands" OFF)
option (CODE_COVERAGE    "Enable code coverage for the project" OFF)
option (ENABLE_TEST      "Enable Unit-Testing for the project" OFF)
option (TOML11_TEST "Enable testing for TOML11" OFF)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)


# Baseline settings
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message (STATUS "Setting build type to 'Debug' as none was specified.")
  set (CMAKE_BUILD_TYPE Debug
	CACHE STRING "Choose the type of build" FORCE)

  set_property (CACHE CMAKE_BUILD_TYPE
		PROPERTY STRINGS
      "Debug"
      "Release"
      "RelWithDebInfo")
endif ()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

##################################
#    Configuration options
##################################
if (COMPILE_COMMANDS)
	set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if (TOML11_TEST)
    set (toml11_BUILD_TEST ON CACHE BOOL "" FORCE)
endif ()

if (ENABLE_TEST)
  find_package (Boost 1.48
    COMPONENTS unit_test_framework
    REQUIRED system)
  enable_testing()
endif ()

set (BUILD_SHARED_LIBS ON)

##################################
#    Platform agnostic options
##################################
if (MSVC)
	# message (FATAL_ERROR "Compiling this project using MSVC is not supported. Please download MinGW64.")
	message (WARNING "Compiling using MSVC")
endif ()

if (NOT MSVC)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  else ()
    message (FATAL_ERROR "Detected unsupported platform architecture: x86. Terminating")
  endif ()
endif ()

# Include sub-projects.
add_subdirectory ("src")
