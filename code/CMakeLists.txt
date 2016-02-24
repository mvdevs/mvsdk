# Make sure the user is not executing this script directly
if(NOT InMV)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InMV)

add_subdirectory("${SRCDir}/game")
add_subdirectory("${SRCDir}/cgame")
add_subdirectory("${SRCDir}/ui")

# Custom target for building qvm's
file(MAKE_DIRECTORY "${QVMDir}/tmp/game")
file(MAKE_DIRECTORY "${QVMDir}/tmp/cgame")
file(MAKE_DIRECTORY "${QVMDir}/tmp/ui")

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
	WORKING_DIRECTORY
		"${QVMDir}/tmp/game"

	COMMAND $<TARGET_FILE:${ASM}>
		"-vq3" "-v" "-o" "${QVMDir}/jk2mpgame.qvm" ${MVGAMEASMFILES} ${MVGAMEASM}
	WORKING_DIRECTORY
		"${QVMDir}/tmp/game"

	COMMAND $<TARGET_FILE:${LCC}>
		"-DQ3_VM" "-DJK2_CGAME" "-DMISSIONPACK" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${SRCDir}/cgame" "-I${SRCDir}/game" "-I${SRCDir}/ui" ${MVCGAMEVMSOURCES}
	WORKING_DIRECTORY
		"${QVMDir}/tmp/cgame"

	COMMAND $<TARGET_FILE:${ASM}>
		"-vq3" "-v" "-o" "${QVMDir}/cgame.qvm" ${MVCGAMEASMFILES} ${MVCGAMEASM}
	WORKING_DIRECTORY
		"${QVMDir}/tmp/cgame"

	COMMAND $<TARGET_FILE:${LCC}>
		"-DQ3_VM" "-DJK2_UI" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${SRCDir}/cgame" "-I${SRCDir}/game" "-I${SRCDir}/ui" ${MVUIVMSOURCES}
	WORKING_DIRECTORY
		"${QVMDir}/tmp/ui"

	COMMAND $<TARGET_FILE:${ASM}>
		"-vq3" "-v" "-o" "${QVMDir}/ui.qvm" ${MVUIASMFILES} ${MVUIASM}
	WORKING_DIRECTORY
		"${QVMDir}/tmp/ui"

	DEPENDS
		${LCC} ${CPP} ${RCC} ${ASM}
)

set_property(TARGET qvms PROPERTY PROJECT_LABEL "Build QVMs")
