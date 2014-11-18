#pragma once

#include "Colour.h"

namespace Joker
{
	template< typename T, eRENDERER R > class CTransparentCtrlT;
}

#if DEF_USING_OGL
#	include "TransparentCtrlOGL.h"
#endif

#if DEF_USING_D2D
#	include "TransparentCtrlD2D.h"
#endif

#include "TransparentCtrlGDI.h"