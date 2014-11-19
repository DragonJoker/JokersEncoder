#pragma once

#include "TransparentCtrl.h"

#if DEF_USING_OGL
#	include "TransparentDialogOGL.h"
#endif

#if DEF_USING_D2D
#	include "TransparentDialogD2D.h"
#endif

#include "TransparentDialogGDI.h"
