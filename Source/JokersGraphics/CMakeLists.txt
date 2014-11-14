project( JokersGraphics )

set( JG_VERSION_MAJOR	1 )
set( JG_VERSION_MINOR	0 )
set( JG_VERSION_BUILD	0 )

set( CMAKE_MFC_FLAG 2 )

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/Src
	${CMAKE_SOURCE_DIR}/OpenGL2D/Src
)

add_target(
	JokersGraphics
	dll
	"${JE_MIN_DEPENDENCIES}"
	"OpenGL2D;DWrite.lib"
	"stdafx.h"
	"stdafx.cpp"
)

set( JE_MIN_DEPENDENCIES
	${JE_MIN_DEPENDENCIES}
	JokersGraphics
)

add_target_compilation_flags( JokersGraphics "-D_AFXDLL" )
add_target_astyle( JokersGraphics ".h;.hpp;.inl;.cpp" )
