#pragma once

#include <afxwin.h>
#include <ImageCtrl.h>
#include <TransparentListBox.h>
#include <TransparentButton.h>
#include <ScalableLayout.h>

namespace Joker
{
	class CJokersEncoderDlg : public CDialogEx
	{
	private:
		enum { IDD = IDD_JOKERSENCODER_DIALOG };
		
	public:
		CJokersEncoderDlg( CWnd * pParent = NULL );

	protected:
		virtual void DoDataExchange( CDataExchange * pDX );

		virtual BOOL OnInitDialog();
		DECLARE_MESSAGE_MAP()
		afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
		afx_msg void OnPaint();
		afx_msg void OnSizing(  UINT nSide, LPRECT lpRect );
		afx_msg void OnSize( UINT uiType, int cx, int cy );
		afx_msg HCURSOR OnQueryDragIcon();
		afx_msg HBRUSH OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID );
		afx_msg BOOL OnEraseBkgnd( CDC * pDC );
		afx_msg void OnBnClickedFile();
		afx_msg void OnBnClickedFolder();
		afx_msg void OnBnClickedOptions();
		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedCancel();

	private:
		HICON m_hIcon;
		CTransparentListBox m_listFiles;
		CTransparentImageCtrl m_staticBackground;
		CTransparentButton m_btnOk;
		CTransparentButton m_btnCancel;
		CTransparentButton m_btnSettings;
		CTransparentButton m_btnAddFile;
		CTransparentButton m_btnAddFolder;
		CScalableLayout m_layout;
		CRect m_rcRect;
	};
}