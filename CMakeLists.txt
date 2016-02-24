if(WIN32)
	cmake_minimum_required(VERSION 3.1.0) # assembler stuff
else()
	cmake_minimum_required(VERSION 2.8.8)
endif()

if(POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD) # debian wheezy still uses 2.8.9
endif()
if(POLICY CMP0042)
	cmake_policy(SET CMP0042 OLD)
endif()

# For checks in subdirectories
set(InMV TRUE)

# Paths
set(SRCDir "${CMAKE_SOURCE_DIR}/code")

# Custom CMake Modules
#list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/tools")

# Project name & version
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
set(ProjectName "JK2MV SDK" CACHE STRING "Project Name")
project(${ProjectName})
set(ProjectURL "https://jk2mv.org")

#include(GetGitRevisionDescription)
#git_describe(MV_VERSION --tags)
#message(STATUS "${ProjectName} Version: ${MV_VERSION}")

# Languages
if (WIN32)
	enable_language(C CXX)
else()
	enable_language(C CXX)
endif()

# Architecture
set(CMAKE_OSX_ARCHITECTURES "i386" "x86_64") # always building both on osx

if(CMAKE_SIZEOF_VOID_P MATCHES "8")
	set(ARCH_BITS 64)
	if(WIN32)
		set(Architecture "x64")
		set(WIN64 TRUE)
	elseif(APPLE)
		set(Architecture "universal")
	else()
		set(Architecture "amd64")
	endif()

	if(NOT APPLE)
		set(GlobalDefines ${GlobalDefines} "_M_X64")
	endif()
else()
	set(ARCH_BITS 32)
	if(WIN32)
		set(Architecture "x86")
		set(WIN64 FALSE)
	elseif(APPLE)
		set(Architecture "universal")
	else()
		set(Architecture "i386")
	endif()

	if(NOT APPLE)
		set(GlobalDefines ${GlobalDefines} "_M_IX86")
	endif()
endif()

message(STATUS "Architecture is ${Architecture}")

# Binary names
if(NOT APPLE)
	set(MVGAME "jk2mpgame_${Architecture}")
	set(MVCGAME "cgame_${Architecture}")
	set(MVUI "ui_${Architecture}")
else()
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/out/install")

	set(MVGAME "jk2mpgame")
	set(MVCGAME "cgame")
	set(MVUI "ui")
endif()

# OSX install target is more like a finalization step
if(APPLE)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/out/bundle")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Global Defines
set(GlobalDefines ${GlobalDefines} "_JK2")
set(GlobalDefines ${GlobalDefines} "DLL_ONLY")
set(GlobalDefines ${GlobalDefines} "MISSIONPACK")
set(GlobalDefines ${GlobalDefines} "GAME_EXPORTS")

# Specific Defines
set(DebugDefines "DEBUG")
set(ReleaseDefines "NDEBUG")
set(ReleaseDefines ${ReleaseDefines} "FINAL_BUILD")

if(NOT MSVC)
	# CMake already defines _DEBUG for MSVC.
	set(DebugDefines ${DebugDefines} "_DEBUG")
endif()

if(MSVC)
	set(GlobalDefines ${GlobalDefines} "_CRT_SECURE_NO_WARNINGS")

	# Multithreaded
	set(CMAKE_CXX_FLAGS_RELEASE "/MT" CACHE TYPE INTERNAL FORCE)
	set(CMAKE_C_FLAGS_RELEASE "/MT" CACHE TYPE INTERNAL FORCE)

	# Platform
	set(GlobalDefines ${GlobalDefines} "UNICODE" "_UNICODE")

	# Optimization
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MP") # multiprocessor compilation
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /Oi /Ot /Ob2 /fp:fast") # maximize speed
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /Ot /Ob2 /fp:fast")

	if(WIN64)
		set(GlobalDefines ${GlobalDefines} "WIN64")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE2")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")

		set(CMAKE_ASM_MASM_FLAGS "${CMAKE_ASM_MASM_FLAGS} /safeseh") # safe exception handler
	endif()
elseif ((("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")) AND NOT WIN32)
	if(APPLE)
		set(GlobalDefines ${GlobalDefines} "MACOS_X")
	endif()

	# Additional flags for debug configuration
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")

	# we need sse optimizations in debug configuration, too because of the inline assembler which is sse code
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")

	# Optimization
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

	if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfpmath=sse -fexpensive-optimizations")

		# Link only libs actually needed
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wl,--as-needed,-s")

		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
	elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")

		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-comment -Wno-reorder -Wunused-value -Wswitch")
	endif()

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfpmath=sse -fexpensive-optimizations")

		# Link only libs actually needed
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wl,--as-needed,-s")

		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")

		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")

		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-deprecated-writable-strings -Wno-reorder -Wunused-value -Wswitch")
	endif()
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

# mv_setup.h preparation - Not used, yet
# set(MVGLOBALIncludeDirs ${MVGLOBALIncludeDirs} ${CMAKE_BINARY_DIR})
# configure_file("${SRCDir}/mv_setup.h.in" "${CMAKE_BINARY_DIR}/mv_setup.h" @ONLY)

set(QVMDir "${CMAKE_BINARY_DIR}/out/qvm")

# Binary names
set(LCC "q3lcc")
set(CPP "q3cpp")
set(RCC "q3rcc")
set(ASM "q3asm")

add_subdirectory("tools")

add_subdirectory(${SRCDir})
