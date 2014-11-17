#pragma once

#include <afxwin.h>
#include <ImageCtrl.h>
#include <TransparentButton.h>

#include "JokersEncoder.h"

class COptionsDlg : public CDialogEx
{
private:
	DECLARE_DYNAMIC( COptionsDlg )

	enum { IDD = IDD_OPTIONS_DIALOG };

	HICON m_hIcon;
	Joker::CTransparentImageCtrl m_staticBackground;
	Joker::CTransparentButton m_buttonOK;
	Joker::CTransparentButton m_buttonCancel;

public:
	COptionsDlg( CWnd * pParent = NULL );
	virtual ~COptionsDlg();

protected:
	virtual void DoDataExchange( CDataExchange * pDX );
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
};
