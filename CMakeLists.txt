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

include (ExternalProject)

project (rcbuild
	VERSION ${rcbuild_version_major}.${rcbuild_version_minor}.${rcbuild_version_patch}
	LANGUAGES CXX)

option (COMPILE_COMMANDS "cmake export compile commands" ON)
option (CODE_COVERAGE    "Enable code coverage for the project" OFF)
option (ENABLE_TEST      "Enable Unit-Testing for the project" OFF)
option (TOML11_TEST "Enable testing for TOML11" OFF)
option (GIT2_TEST "Enable testing for libgit2" OFF)

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
set (CMAKE_AUTOMOC ON)

if (COMPILE_COMMANDS)
	set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if (TOML11_TEST)
  set (toml11_BUILD_TEST ON CACHE BOOL "" FORCE)
endif ()

if (GIT2_TEST)
  set (BUILD_CLAR ON CACHE BOOL "" FORCE)
endif ()

## libgit2 options
set (BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set (USE_HTTPS ON CACHE BOOL "" FORCE)
set (USE_BUNDLED_ZLIB ON CACHE BOOL "" FORCE)
set (THREADSAFE OFF CACHE BOOL "" FORCE)

if (ENABLE_TEST)
  find_package (Boost 1.48
    COMPONENTS unit_test_framework
    REQUIRED system)
  enable_testing()
endif ()

set (BUILD_SHARED_LIBS ON)

include (CheckCXXCompilerFlag)

if (NOT MSVC)
  check_cxx_compiler_flag (-fno-builtin HAVE_FNO_BUILTIN)
  check_cxx_compiler_flag (-fstack-protector-strong HAS_STACK_PROTECTOR_STRONG)

  if (HAVE_FNO_BUILTIN)
    add_compile_options (-fno-builtin)
  endif ()

  if (HAS_STACK_PROTECTOR_STRONG)
    add_compile_options (-fstack-protector-strong)
    link_libraries (-fstack-protector-strong)
  endif ()
endif ()
# additional compiler options

if (NOT MSVC)
  add_compile_options (-Wstrict-overflow=2)
  add_compile_options (-Wno-dev)
endif ()

##################################
#    Platform agnostic options
##################################
if (MSVC)
  message ("Compiling this project using MSVC")
endif ()

if (NOT MSVC)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  else ()
    message (FATAL_ERROR "Detected unsupported platform architecture: x86. Terminating")
  endif ()
endif ()

# Include sub-projects.
add_subdirectory ("src")
