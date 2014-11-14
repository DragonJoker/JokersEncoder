cmake_minimum_required( VERSION 2.8 )

#--------------------------------------------------------------------------------------------------
#	Initial configurations
#--------------------------------------------------------------------------------------------------
# Set project name, used in folders and in workspace creation
set( ProjectName "JokersEncoder" )

# Used to look for external modules
set( CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/CMake"
    "${CMAKE_SOURCE_DIR}/CMake/Modules"
)

include( DateUtils )
get_date( JE_TODAY JE_DAY JE_MONTH JE_YEAR )

# Set project version numbers
set( VERSION_MAJOR	1			)
set( VERSION_MINOR	0			)
set( VERSION_BUILD	0			)
set( VERSION_YEAR	${JE_YEAR}	)

option( PROJECTS_USE_PRECOMPILED_HEADERS "Use precompiled headers" TRUE )
option( PROJECTS_PACKAGE_WIX "Build WiX setup" TRUE )

# Experimental Precompiled headers support for GCC
include( PCHSupport )
# Force Unicode projects (MBCS is past :P)
add_definitions( -DUNICODE -D_UNICODE )

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Set only Debug and Release configuration types" FORCE )

# Enable CTest
enable_testing()
    
# Declare the project
project( ${ProjectName} )
	
if ( MSVC )
	include( Project )
	include( CompilerVersion )
	include( UnitTest )
	include( CompilationFlags )
	include( AStyleUtils )
	
	#--------------------------------------------------------------------------------------------------
	# Looking for needed libraries
	#--------------------------------------------------------------------------------------------------
	find_package( Doxygen )
	find_package( VLD )
	
	#--------------------------------------------------------------------------------------------------
	# Adding include dirs to include search path
	#--------------------------------------------------------------------------------------------------
	if( VLD_FOUND )
		include_directories( ${VLD_INCLUDE_DIR} )
		message( STATUS "+ Found Visual Leak Detector" )
	endif ()
	if( DOXYGEN_FOUND )
		message( STATUS "+ Found Doxygen" )
	endif ()
	
	#--------------------------------------------------------------------------------------------------
	# Adding few library dirs to link search path
	#--------------------------------------------------------------------------------------------------
	if( VLD_FOUND )
		link_directories( ${VLD_LIBRARY_DIR} )
	endif()
	link_directories( ${PROJECTS_BINARIES_OUTPUT_DIR}/lib )
	link_directories( ${CMAKE_SOURCE_DIR}/../Lib/strmbase )
	
	#--------------------------------------------------------------------------------------------------
	# We remove the existing /Zm flag to replace it by /Zm300
	#--------------------------------------------------------------------------------------------------
	string( REGEX REPLACE ".*(/Zm[0-9]+).*" "\\1" ZmFlag ${CMAKE_CXX_FLAGS} )
	if( (NOT "${ZmFlag}" STREQUAL "") AND (NOT "${CMAKE_CXX_FLAGS}" STREQUAL "${ZmFlag}") )
	    string( REPLACE ${ZmFlag} "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} )
	endif()
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm300" )
	# We remove the existing /Zm flag to replace it by /Zm300
	string( REGEX REPLACE ".*(/Zm[0-9]+).*" "\\1" ZmFlag ${CMAKE_C_FLAGS} )
	if( (NOT "${ZmFlag}" STREQUAL "") AND (NOT "${CMAKE_C_FLAGS}" STREQUAL "${ZmFlag}") )
	    string( REPLACE ${ZmFlag} "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS} )
	endif()
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zm300" )
	
	#--------------------------------------------------------------------------------------------------
	# If VLD found, we tell it to the compiler
	#--------------------------------------------------------------------------------------------------
	if( VLD_FOUND )
		set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVLD_AVAILABLE")
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -DVLD_AVAILABLE")
		msg_debug( "Using Visual Leak Detector to check for Memory leaks" )
	endif()
	
	msg_debug( "CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
	msg_debug( "CMAKE_C_FLAGS    : ${CMAKE_C_FLAGS}" )
	msg_debug( "CMAKE_CXX_FLAGS  : ${CMAKE_CXX_FLAGS}" )
    
	SET( JE_MIN_DEPENDENCIES )
	
	add_subdirectory( OpenGL2D )
	add_subdirectory( JokersGraphics )
	add_subdirectory( JokersEncoder )
	
	#--------------------------------------------------------------------------------------------------
	# Prepare WiX installer
	#--------------------------------------------------------------------------------------------------
	if ( "${PROJECTS_PACKAGE_WIX}" STREQUAL "ON" )
		file( MAKE_DIRECTORY "${PROJECTS_SETUP_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}" )
		set( CPACK_PACKAGE_NAME "JokersEncoder" )
		set( CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BUILD}" )
		set( CPACK_PACKAGE_FILE_NAME "Castor3D-${CPACK_PACKAGE_VERSION}-${PROJECTS_PLATFORM}" )
		set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Jokers Encoder" )
		set( CPACK_PACKAGE_DESCRIPTION "Application used to reencode videos" )
		set( CPACK_PACKAGE_RELEASE 1 )
		set( CPACK_PACKAGE_CONTACT "dragonjoker59@hotmail.com" )
		set( CPACK_PACKAGE_VENDOR "DragonJoker" )
		set( CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}" )
		set( CPACK_OUTPUT_FILE_PREFIX "${PROJECTS_SETUP_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}" )
		set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/../LGPL.txt" )
	endif ()
	if ( ${PROJECTS_PACKAGE_WIX} )
		set( CPACK_GENERATOR "WIX" )
		set( CPACK_WIX_UPGRADE_GUID "6B17505B-A8B5-4EEC-8978-1BF24715A8A1" )
		set( CPACK_WIX_PRODUCT_GUID "02ACFE05-CFCE-4E1D-85DA-59A068DDCF70" )
		set( CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/../install/castor.ico" )
		set( CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/../install/dialog.bmp" )
		set( CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/../install/banner.bmp" )
		set( CPACK_WIX_PROGRAM_MENU_FOLDER "JokersEncoder" )
		set( CPACK_WIX_CULTURES "fr-FR;en-EN" )
		include( CPack )
	endif()
else()
	MESSAGE( SEND_ERROR "This project needs Visual Studio" )
endif()
