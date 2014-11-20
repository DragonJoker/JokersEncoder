#pragma once

#include <afxwin.h>
#include <TransparentImageCtrl.h>
#include <TransparentListBox.h>
#include <TransparentButton.h>
#include <TransparentDialog.h>
#include <ScalableLayout.h>

#define DEF_DEBUG_OGL 0

namespace Joker
{
	class CJokersEncoderDlg
		: public CTransparentCtrlT< CDialog, eDEFAULT_RENDERER >
	{
	private:
		enum { IDD = IDD_JOKERSENCODER_DIALOG };
		typedef CTransparentCtrlT< CDialog, eDEFAULT_RENDERER > BaseType;
		
	public:
		CJokersEncoderDlg( CWnd * pParent = NULL );
		virtual ~CJokersEncoderDlg();

	protected:
		virtual void DoDataExchange( CDataExchange * pDX );

		virtual BOOL OnInitDialog();
		DECLARE_MESSAGE_MAP()
		afx_msg void OnDestroy();
		afx_msg BOOL OnEraseBkgnd( CDC * pDC );
		afx_msg void OnPaint();
		afx_msg void OnSize( UINT uiType, int cx, int cy );
		afx_msg void OnSizing(  UINT nSide, LPRECT lpRect );
		afx_msg HCURSOR OnQueryDragIcon();
		afx_msg void OnBnClickedFile();
		afx_msg void OnBnClickedFolder();
		afx_msg void OnBnClickedOptions();
		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedCancel();

	private:
		HICON m_hIcon;
		CTransparentButton< eDEFAULT_RENDERER > m_btnOk;
#if !DEF_DEBUG_OGL
		CTransparentListBox< eDEFAULT_RENDERER > m_listFiles;
		CTransparentButton< eDEFAULT_RENDERER > m_btnCancel;
		CTransparentButton< eDEFAULT_RENDERER > m_btnSettings;
		CTransparentButton< eDEFAULT_RENDERER > m_btnAddFile;
		CTransparentButton< eDEFAULT_RENDERER > m_btnAddFolder;
#else
		CButton m_btnCancel;
		CButton m_btnSettings;
		CButton m_btnAddFile;
		CButton m_btnAddFolder;
#endif
		CScalableLayout m_layout;
		CRect m_rcInitialRect;
		CRect m_rcRect;
		bool m_needResize;
	};
}