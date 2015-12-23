# Make sure the user is not executing this script directly
if(NOT InMV)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InMV)

add_subdirectory("${SRCDir}/ui")
add_subdirectory("${SRCDir}/game")
add_subdirectory("${SRCDir}/cgame")