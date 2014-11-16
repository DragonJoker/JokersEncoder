project( OpenGL2D )

find_package( OpenGL )
find_package( GLM )

if( GLM_FOUND )
	include_directories( ${GLM_INCLUDE_DIR} )
	message( STATUS "+ Found GLM" )
endif()

if( OPENGL_FOUND )
	message( STATUS "+ Found OpenGL" )
endif()

if( OPENGL_FOUND AND GLM_FOUND )
	set( OpenGlLibraries "" )
	foreach( Lib ${OPENGL_gl_LIBRARY} )
		if( OpenGlLibraries )
			set( OpenGlLibraries "${OpenGlLibraries}|${Lib}" )
		else()
			set( OpenGlLibraries "${Lib}" )
		endif()
	endforeach()
	
	set( GL_VERSION_MAJOR	1 )
	set( GL_VERSION_MINOR	0 )
	set( GL_VERSION_BUILD	0 )
	
	include_directories(
		${CMAKE_CURRENT_BINARY_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/Src
		${CMAKE_CURRENT_SOURCE_DIR}/Src
	)
	
	add_target(
		OpenGL2D
		dll
		"${JE_MIN_DEPENDENCIES}"
		"${OpenGlLibraries}"
		"stdafx.h"
		"stdafx.cpp"
	)

	set( JE_MIN_DEPENDENCIES
		${JE_MIN_DEPENDENCIES}
		OpenGL2D
	)
	
	add_target_astyle( OpenGL2D ".h;.hpp;.inl;.cpp" )
endif()