#pragma once

#include "Logger.h"
#include "Image.h"
#include "TransparentCtrl.h"

namespace Joker
{
	class CImage;

    template< eRENDERER Renderer >
	class CTransparentImageCtrl
		: public CTransparentCtrlT< CStatic, Renderer >
	{
	public:
		typedef CTransparentCtrlT< CStatic, Renderer > BaseType;

	public:
		CTransparentImageCtrl();
		~CTransparentImageCtrl();

		void SetImage( CString const & p_csImageFilePath );
		void SetImage( UINT uiResourceId );
		void SetBkColor( COLORREF clrColour );
		void DrawGDI( HDC hDC );

		inline Joker::ImagePtr GetImage()const
		{
			return m_pImage;
		}

	protected:
		void DoDrawBackground( CRect const & rcRect );

		DECLARE_MESSAGE_MAP();
		afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
		afx_msg BOOL OnEraseBkgnd( CDC * pDC );
		afx_msg	void OnPaint();
		afx_msg HBRUSH OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiCtlId );

	private:
		Joker::ImagePtr m_pImage;
		COLORREF m_crColour;
		CTransparentBrush m_brush;
	};
}

#include "TransparentImageCtrl.inl"
