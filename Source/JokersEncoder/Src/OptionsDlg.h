#pragma once

#include <afxwin.h>
#include <TransparentButton.h>
#include <TransparentDialog.h>

#include "JokersEncoder.h"

namespace Joker
{
	class COptionsDlg
		: public CTransparentCtrlT< CDialog, eDEFAULT_RENDERER >
	{
	private:
		DECLARE_DYNAMIC( COptionsDlg )
		enum { IDD = IDD_OPTIONS_DIALOG };
		typedef CTransparentCtrlT< CDialog, eDEFAULT_RENDERER > BaseType;

	public:
		COptionsDlg( CWnd * pParent = NULL );
		virtual ~COptionsDlg();

	protected:
		virtual void DoDataExchange( CDataExchange * pDX );
		virtual BOOL OnInitDialog();

		DECLARE_MESSAGE_MAP()
		afx_msg void OnDestroy();

	private:
		HICON m_hIcon;
		Joker::CTransparentButton< eDEFAULT_RENDERER > m_buttonOK;
		Joker::CTransparentButton< eDEFAULT_RENDERER > m_buttonCancel;
	};
}
