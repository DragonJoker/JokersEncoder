#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#include <afx.h>
#include <afxwin.h>

#include <atlimage.h>

#include <cstring>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <mutex>

#include "JokersGraphicsPrerequisites.h"

#if !defined( NDEBUG ) && defined( VLD_AVAILABLE )
#	include <vld.h>
#endif
