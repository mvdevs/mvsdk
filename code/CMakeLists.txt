# Make sure the user is not executing this script directly
if(NOT InMV)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InMV)

# mv_setup.h preparation
set(MVGLOBALIncludeDirs ${MVGLOBALIncludeDirs} ${CMAKE_BINARY_DIR})
configure_file("mv_setup.h.in" "${CMAKE_BINARY_DIR}/mv_setup.h" @ONLY)

add_subdirectory("${SRCDir}/game")
add_subdirectory("${SRCDir}/cgame")
add_subdirectory("${SRCDir}/ui")

if(BuildQVMs)
	# Custom target for building qvm's
	file(MAKE_DIRECTORY "${QVMDir}/tmp")

	foreach(FILE ${MVGAMEVMSOURCES})
		get_filename_component(FILE ${FILE} NAME_WE)
		
		set(MVGAMEASMFILES ${MVGAMEASMFILES} "${FILE}.asm")
	endforeach()

	foreach(FILE ${MVCGAMEVMSOURCES})
		get_filename_component(FILE ${FILE} NAME_WE)
		
		set(MVCGAMEASMFILES ${MVCGAMEASMFILES} "${FILE}.asm")
	endforeach()

	foreach(FILE ${MVUIVMSOURCES})
		get_filename_component(FILE ${FILE} NAME_WE)
		
		set(MVUIASMFILES ${MVUIASMFILES} "${FILE}.asm")
	endforeach()

	add_custom_target(qvms
		COMMAND $<TARGET_FILE:${LCC}>
			"-DQ3_VM" "-DJK2_GAME" "-DMISSIONPACK" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${SRCDir}/cgame" "-I${SRCDir}/game" "-I${SRCDir}/ui" ${MVGAMEVMSOURCES}

		COMMAND $<TARGET_FILE:${ASM}>
			"-vq3" "-v" "-o" "${QVMDir}/jk2mpgame.qvm" ${MVGAMEASMFILES} ${MVGAMEASM}

		COMMAND $<TARGET_FILE:${LCC}>
			"-DQ3_VM" "-DJK2_CGAME" "-DMISSIONPACK" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${SRCDir}/cgame" "-I${SRCDir}/game" "-I${SRCDir}/ui" ${MVCGAMEVMSOURCES}

		COMMAND $<TARGET_FILE:${ASM}>
			"-vq3" "-v" "-o" "${QVMDir}/cgame.qvm" ${MVCGAMEASMFILES} ${MVCGAMEASM}

		COMMAND $<TARGET_FILE:${LCC}>
			"-DQ3_VM" "-DJK2_UI" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${SRCDir}/cgame" "-I${SRCDir}/game" "-I${SRCDir}/ui" ${MVUIVMSOURCES}

		COMMAND $<TARGET_FILE:${ASM}>
			"-vq3" "-v" "-o" "${QVMDir}/ui.qvm" ${MVUIASMFILES} ${MVUIASM}

		WORKING_DIRECTORY
			"${QVMDir}/tmp"

		DEPENDS
			${LCC} ${CPP} ${RCC} ${ASM}
	)

	set_property(TARGET qvms PROPERTY PROJECT_LABEL "Build QVMs")
endif()
