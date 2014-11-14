#pragma once

#include "Logger.h"
#include "Image.h"

namespace Joker
{
	class CImage;

	class JGRA_API CImageCtrl
		: public CStatic
	{
	private:
		Joker::ImagePtr	m_pImage;
		COLORREF		m_crColour;
		HBRUSH			m_hBrush;

	public:
		CImageCtrl();
		~CImageCtrl();

		void SetImage		( CString const & p_csImageFilePath );
		void SetImage		( UINT uiResourceId );
		void SetBkColor		( COLORREF clrColour );
		void DrawGDI		( HDC hDC );

		inline Joker::ImagePtr	GetImage	()const { return m_pImage; }

	protected:
		DECLARE_MESSAGE_MAP();
		afx_msg int		OnCreate( LPCREATESTRUCT lpCreateStruct );
		afx_msg BOOL	OnEraseBkgnd( CDC * pDC );
		afx_msg	void	OnPaint();
		afx_msg HBRUSH	OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiCtlId );
	};
}