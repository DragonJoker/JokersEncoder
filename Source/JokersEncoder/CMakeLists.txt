project( JokersEncoder )

set( JE_VERSION_MAJOR	1 )
set( JE_VERSION_MINOR	0 )
set( JE_VERSION_BUILD	0 )

set( CMAKE_MFC_FLAG 2 )

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/Src
	${CMAKE_CURRENT_SOURCE_DIR}/Src/Win32
	${CMAKE_SOURCE_DIR}/JokersGraphics/Src
	${CMAKE_SOURCE_DIR}/OpenGL2D/Src
	${CMAKE_SOURCE_DIR}/../Lib/strmbase
)

add_target(
	JokersEncoder
	bin
	"${JE_MIN_DEPENDENCIES}"
	"JokersGraphics"
	"stdafx.h"
	"stdafx.cpp"
)

add_target_compilation_flags( JokersEncoder "-D_AFXDLL" )
add_target_astyle( JokersEncoder ".h;.hpp;.inl;.cpp" )