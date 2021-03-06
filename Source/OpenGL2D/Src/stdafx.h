// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#if !defined( VLD_AVAILABLE )
#	define _CRTDBG_MAP_ALLOC
#	include <stdlib.h>
#	include <crtdbg.h>
#endif

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "OpenGL2DPrerequisites.h"

#if !defined( NDEBUG ) && defined( VLD_AVAILABLE )
#	include <vld.h>
#endif