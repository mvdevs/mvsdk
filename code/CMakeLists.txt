# Make sure the user is not executing this script directly
if(NOT InMVSDK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InMVSDK)

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
		file(TO_NATIVE_PATH "${FILE}" FILE_NATIVE)
		set(MVGAMEVMSOURCES_NATIVE ${MVGAMEVMSOURCES_NATIVE} ${FILE_NATIVE})

		get_filename_component(FILE ${FILE} NAME_WE)
		set(MVGAMEASMFILES ${MVGAMEASMFILES} "${FILE}.asm")
	endforeach()

	foreach(FILE ${MVCGAMEVMSOURCES})
		file(TO_NATIVE_PATH "${FILE}" FILE_NATIVE)
		set(MVCGAMEVMSOURCES_NATIVE ${MVCGAMEVMSOURCES_NATIVE} ${FILE_NATIVE})

		get_filename_component(FILE ${FILE} NAME_WE)
		set(MVCGAMEASMFILES ${MVCGAMEASMFILES} "${FILE}.asm")
	endforeach()

	foreach(FILE ${MVUIVMSOURCES})
		file(TO_NATIVE_PATH "${FILE}" FILE_NATIVE)
		set(MVUIVMSOURCES_NATIVE ${MVUIVMSOURCES_NATIVE} ${FILE_NATIVE})

		get_filename_component(FILE ${FILE} NAME_WE)
		set(MVUIASMFILES ${MVUIASMFILES} "${FILE}.asm")
	endforeach()

	file(RELATIVE_PATH MVSDK_CGAME_PATH "${QVMDir}/tmp" "${SRCDir}/cgame")
	file(TO_NATIVE_PATH "${MVSDK_CGAME_PATH}" MVSDK_CGAME_PATH)
	
	file(RELATIVE_PATH MVSDK_GAME_PATH "${QVMDir}/tmp" "${SRCDir}/game")
	file(TO_NATIVE_PATH "${MVSDK_GAME_PATH}" MVSDK_GAME_PATH)
	
	file(RELATIVE_PATH MVSDK_UI_PATH "${QVMDir}/tmp" "${SRCDir}/ui")
	file(TO_NATIVE_PATH "${MVSDK_UI_PATH}" MVSDK_UI_PATH)
	
	file(RELATIVE_PATH MVSDK_BIN_PATH "${QVMDir}/tmp" "${CMAKE_BINARY_DIR}")
	file(TO_NATIVE_PATH "${MVSDK_BIN_PATH}" MVSDK_BIN_PATH)
	
	add_custom_target(qvms
		COMMAND $<TARGET_FILE:${LCC}>
			"-DQ3_VM" "-DJK2_GAME" "-DMISSIONPACK" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${MVSDK_GAME_PATH}" "-I${MVSDK_UI_PATH}" "-I${MVSDK_BIN_PATH}" ${MVGAMEVMSOURCES_NATIVE}

		COMMAND $<TARGET_FILE:${ASM}>
			"-vq3" "-v" "-o" "${QVMDir}/jk2mpgame.qvm" ${MVGAMEASMFILES} ${MVGAMEASM}

		COMMAND $<TARGET_FILE:${LCC}>
			"-DQ3_VM" "-DJK2_CGAME" "-DMISSIONPACK" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${MVSDK_CGAME_PATH}" "-I${MVSDK_GAME_PATH}" "-I${MVSDK_UI_PATH}" "-I${MVSDK_BIN_PATH}" ${MVCGAMEVMSOURCES_NATIVE}

		COMMAND $<TARGET_FILE:${ASM}>
			"-vq3" "-v" "-o" "${QVMDir}/cgame.qvm" ${MVCGAMEASMFILES} ${MVCGAMEASM}

		COMMAND $<TARGET_FILE:${LCC}>
			"-DQ3_VM" "-DJK2_UI" "-S" "-Wf-target=bytecode" "-Wf-g" "-I${SRCDir}/cgame" "-I${MVSDK_GAME_PATH}" "-I${MVSDK_UI_PATH}" "-I${MVSDK_BIN_PATH}" ${MVUIVMSOURCES_NATIVE}

		COMMAND $<TARGET_FILE:${ASM}>
			"-vq3" "-v" "-o" "${QVMDir}/ui.qvm" ${MVUIASMFILES} ${MVUIASM}

		WORKING_DIRECTORY
			"${QVMDir}/tmp"

		DEPENDS
			${LCC} ${CPP} ${RCC} ${ASM}
	)

	set_property(TARGET qvms PROPERTY PROJECT_LABEL "Build QVMs")
endif()
