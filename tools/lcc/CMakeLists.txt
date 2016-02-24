# Make sure the user is not executing this script directly
if(NOT InMV)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InMV)

set(LCCFiles
	"bytecode.c"
	"lcc.c"
)

add_executable(${LCC} ${LCCFiles})
set_target_properties(${LCC} PROPERTIES PROJECT_LABEL "q3lcc")
set_property(TARGET ${LCC} PROPERTY FOLDER "Tools")
