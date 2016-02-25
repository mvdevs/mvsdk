cmake_minimum_required(VERSION 3.0)

# For checks in subdirectories
set(InMV TRUE)

# Paths
set(SRCDir "${CMAKE_SOURCE_DIR}/code")
set(QVMDir "${CMAKE_BINARY_DIR}/out/qvm")

# Custom CMake Modules
#list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/tools")

# Project name & version
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
set(ProjectName "JK2MV SDK" CACHE STRING "Project Name")
project(${ProjectName})
set(ProjectURL "https://jk2mv.org")

# Languages
enable_language(C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Customizable options
option(BuildQVMs "Whether to create targets for building QVM files" ON)

# Architecture
set(CMAKE_OSX_ARCHITECTURES "i386" "x86_64") # always building both on osx

if(WIN32)
	set(X86 ON)
	if(CMAKE_SIZEOF_VOID_P MATCHES "8")
		set(Architecture "x64")
		set(WIN64 TRUE)
		set(GlobalDefines ${GlobalDefines} "_M_X64")
	else()
		set(Architecture "x86")
		set(WIN64 FALSE)
		set(GlobalDefines ${GlobalDefines} "_M_IX86")
	endif()
elseif(APPLE)
	set(X86 ON)
	set(Architecture "universal")
else()
	set(X86 OFF)

	if(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
		set(Architecture "arm")
		set(ARM ON)
	elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^i.86$")
		set(X86 ON)
		set(Architecture "i386")
	elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^x86.64$")
		set(X86 ON)
		set(Architecture "amd64")
	else()
		set(Architecture "${CMAKE_SYSTEM_PROCESSOR}")
	endif()
endif()

message(STATUS "Architecture is ${Architecture}")

# Binary names
if(NOT APPLE)
	set(MVGAME "jk2mpgame_${Architecture}")
	set(MVCGAME "cgame_${Architecture}")
	set(MVUI "ui_${Architecture}")
else()
	set(MVGAME "jk2mpgame")
	set(MVCGAME "cgame")
	set(MVUI "ui")
endif()

set(LCC "q3lcc")
set(CPP "q3cpp")
set(RCC "q3rcc")
set(ASM "q3asm")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

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
elseif (("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"))
	if(APPLE)
		set(GlobalDefines ${GlobalDefines} "MACOS_X")
	endif()

	# Additional flags for debug configuration
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")

	# we need sse optimizations in debug configuration, too because of the inline assembler which is sse code
	if(X86)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
	endif()

	# Optimization
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

	if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		if(X86)
			set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfpmath=sse -fexpensive-optimizations")
		endif()

		# Link only libs actually needed
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wl,--as-needed,-s")

		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
	elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")

		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-comment -Wno-reorder -Wunused-value -Wswitch")
	endif()

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		if(X86)
			set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfpmath=sse -fexpensive-optimizations")
		endif()

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

if(BuildQVMs)
	add_subdirectory("tools")
endif()

add_subdirectory(${SRCDir})
