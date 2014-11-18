#pragma once

#ifndef __AFXWIN_H__
#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"

class CJokersEncoderApp : public CWinApp
{
public:
	CJokersEncoderApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CJokersEncoderApp theApp;