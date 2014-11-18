#include "stdafx.h"

#include "DrawerGDI.h"

namespace Joker
{
	CDrawer< eRENDERER_GDI >::CDrawer()
		:	CDrawerDC()
		,	m_hDcSaved( NULL )
	{
	}

	CDrawer< eRENDERER_GDI >::CDrawer( HDC hDC, CRect const & rcRect, BOOL bOwn )
		:	CDrawerDC( hDC, rcRect, bOwn )
		,	m_hDcSaved( NULL )
	{
	}

	CDrawer< eRENDERER_GDI >::CDrawer( CDrawer const & drawer )
		:	CDrawerDC( drawer )
		,	m_hDcSaved( NULL )
	{
	}

	CDrawer< eRENDERER_GDI >::~CDrawer()
	{
	}

	void CDrawer< eRENDERER_GDI >::BeginDraw( HDC hDC, CRect const & rcRect, BOOL bOwn )
	{
		DoSetDC( hDC, rcRect, bOwn );
	}

	void CDrawer< eRENDERER_GDI >::EndDraw()
	{
		DoReleaseDC();
	}

	void CDrawer< eRENDERER_GDI >::CreateBackbuffer( CRect const & rcRect )
	{
		ASSERT( m_hDcSaved == NULL );
		m_rcBack = rcRect;
		m_hDcSaved = m_hDC;
		m_hDC = ::CreateCompatibleDC( m_hDcSaved );
		m_hBitmap = ::CreateCompatibleBitmap( m_hDcSaved, rcRect.Width(), rcRect.Height() );
		::SetStretchBltMode( m_hDC, HALFTONE );
		::SetBrushOrgEx( m_hDC, rcRect.left, rcRect.top, NULL );
		SelectObject( m_hDC, m_hBitmap );
		::SetBkMode( m_hDC, TRANSPARENT );
	}

	void CDrawer< eRENDERER_GDI >::Finalise()
	{
		if ( m_hDcSaved )
		{
			BLENDFUNCTION blendFunction;
			blendFunction.AlphaFormat = AC_SRC_ALPHA;
			blendFunction.BlendOp = AC_SRC_OVER;
			blendFunction.SourceConstantAlpha = 255;
			blendFunction.BlendFlags = 0;

			::AlphaBlend( m_hDcSaved, m_rcRect.left, m_rcRect.top, m_rcRect.right, m_rcRect.bottom,
						  m_hDC, m_rcBack.left, m_rcBack.top, m_rcBack.right, m_rcBack.bottom,
						  blendFunction );
			//		::BitBlt( m_hDcSaved, rcRect.left, rcRect.top, m_rcBack.Width(), m_rcBack.Height(), m_hDC, m_rcBack.left, m_rcBack.top, SRCCOPY );
			::DeleteDC( m_hDC );
			::DeleteObject( m_hBitmap );
			m_hDC = m_hDcSaved;
			m_hDcSaved = NULL;
		}
		else
		{
			ASSERT( FALSE );
		}
	}

	void CDrawer< eRENDERER_GDI >::DrawLine( int iPenHeight, COLORREF cPenColour, CPoint const & ptOrign, CPoint const & ptDest, int iPenStyle )
	{
		HPEN hPen = DoCreateCustomPen( iPenHeight, cPenColour, 1, iPenStyle );
		HPEN hOldPen = HPEN( ::SelectObject( m_hDC, hPen ) );

		DrawLine( ptOrign, ptDest, 1 );

		::SelectObject( m_hDC, hOldPen );
		::DeleteObject( hPen );
	}

	void CDrawer< eRENDERER_GDI >::DrawLine( CPoint const & ptOrign, CPoint const & ptDest, double dRatio )
	{
		::MoveToEx( m_hDC, int( ptOrign.x * dRatio ), int( ptOrign.y * dRatio ), NULL );
		::LineTo( m_hDC, int( ptDest.x * dRatio ), int( ptDest.y * dRatio ) );
	}

	void CDrawer< eRENDERER_GDI >::DrawRect( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CRect const & rcRect, double dRatio )
	{
		HBRUSH hBrush;

		if ( cBrushColour == eCOLOUR_TRUE_TRANSPARENT )
		{
			hBrush = HBRUSH( ::GetStockObject( HOLLOW_BRUSH ) );
		}
		else
		{
			hBrush = ::CreateSolidBrush( cBrushColour );
		}

		HPEN hPen = DoCreateCustomPen( iPenHeight, cPenColour, 1 );
		HPEN hOldPen = NULL;

		if ( iPenHeight != 0 )
		{
			hOldPen = HPEN( SelectObject( m_hDC, hPen ) );
		}

		CRect rcTmpRect( int( rcRect.left * dRatio ), int( rcRect.top * dRatio ), int( rcRect.right * dRatio ), int( rcRect.bottom * dRatio ) );

		::FillRect( m_hDC, rcTmpRect, hBrush );

		if ( hOldPen )
		{
			::MoveToEx(	m_hDC,	rcTmpRect.left,					rcTmpRect.top, NULL	);
			::LineTo(	m_hDC,	rcTmpRect.right - iPenHeight,	rcTmpRect.top	);
			::LineTo(	m_hDC,	rcTmpRect.right - iPenHeight,	rcTmpRect.bottom - iPenHeight	);
			::LineTo(	m_hDC,	rcTmpRect.left,					rcTmpRect.bottom - iPenHeight	);
			::LineTo(	m_hDC,	rcTmpRect.left,					rcTmpRect.top	);
		}

		if ( hOldPen )
		{
			::SelectObject( m_hDC, hOldPen );
		}

		::DeleteObject( hPen );
		::DeleteObject( hBrush );
	}

	void CDrawer< eRENDERER_GDI >::DrawVoidRect( int iPenHeight, COLORREF cPenColour, CRect const & rcRect, double dRatio )
	{
		HPEN hPen = DoCreateCustomPen( iPenHeight, cPenColour, 1 );
		HPEN hOldPen = HPEN( ::SelectObject( m_hDC, hPen ) );

		CRect rcTmpRect( int( rcRect.left * dRatio ), int( rcRect.top * dRatio ), int( rcRect.right * dRatio ), int( rcRect.bottom * dRatio ) );

		::MoveToEx(	m_hDC, rcTmpRect.left,					rcTmpRect.top, NULL	);
		::LineTo(	m_hDC, rcTmpRect.right - iPenHeight,	rcTmpRect.top	);
		::LineTo(	m_hDC, rcTmpRect.right - iPenHeight,	rcTmpRect.bottom - iPenHeight	);
		::LineTo(	m_hDC, rcTmpRect.left,					rcTmpRect.bottom - iPenHeight	);
		::LineTo(	m_hDC, rcTmpRect.left,					rcTmpRect.top	);

		::SelectObject( m_hDC, hOldPen );
		::DeleteObject( hPen );
	}

	LONG CDrawer< eRENDERER_GDI >::DrawText( String const & strText, LPRECT pRect, UINT uiFormat, double dRatio )
	{
		CRect rcTextRect( pRect );
		rcTextRect.left		= LONG( dRatio * rcTextRect.left	);
		rcTextRect.right	= LONG( dRatio * rcTextRect.right	);
		rcTextRect.top		= LONG( dRatio * rcTextRect.top	);
		rcTextRect.bottom	= LONG( dRatio * rcTextRect.bottom	);

#if defined( _UNICODE )
		LONG lReturn = ::DrawTextW( m_hDC, strText.c_str(), strText.size(), rcTextRect, uiFormat );
#else
		LONG lReturn = ::DrawTextA( m_hDC, strText.c_str(), strText.size(), rcTextRect, uiFormat );
#endif

		pRect->left		= LONG( rcTextRect.left		/ dRatio );
		pRect->right	= LONG( rcTextRect.right	/ dRatio );
		pRect->top		= LONG( rcTextRect.top		/ dRatio );
		pRect->bottom	= LONG( rcTextRect.bottom	/ dRatio );

		return lReturn;
	}

	void CDrawer< eRENDERER_GDI >::SetFont( CFont & ca2iFont )
	{
		DoSetFont( ca2iFont );
		ca2iFont.Select( m_hDC );
	}

	void CDrawer< eRENDERER_GDI >::UnsetFont( CFont & ca2iFont )
	{
		DoUnsetFont();
		ca2iFont.Deselect( m_hDC );
	}

	COLORREF CDrawer< eRENDERER_GDI >::SetForegroundColour( COLORREF crColour )
	{
		DoSetForegroundColour( crColour );
		return ::SetTextColor( m_hDC, crColour );
	}

	COLORREF CDrawer< eRENDERER_GDI >::SetBackgroundColour( COLORREF crColour )
	{
		DoSetBackgroundColour( crColour );
		return ::SetBkColor( m_hDC, crColour );
	}

	void CDrawer< eRENDERER_GDI >::BitBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, DWORD dwRop )
	{
		::BitBlt( m_hDC, xDest, yDest, cxDest, cyDest, *static_cast< CDrawerDC * >( pDrawer ),  xOrigin, yOrigin, dwRop );
	}

	void CDrawer< eRENDERER_GDI >::StretchBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP )
	{
		::StretchBlt( m_hDC, xDest, yDest, cxDest, cyDest, *static_cast< CDrawerDC * >( pDrawer ), xOrigin, yOrigin, cxOrigin, cyOrigin, dwROP );
	}

	void CDrawer< eRENDERER_GDI >::TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent )
	{
		::TransparentBlt( m_hDC, xDest, yDest, cxDest, cyDest, *static_cast< CDrawerDC * >( pDrawer ), xOrigin, yOrigin, cxOrigin, cyOrigin, crTransparent );
	}

	void CDrawer< eRENDERER_GDI >::StretchBlt( CRect const & rcDest, DWORD dwROP, double dRatio )
	{
		m_pImage->StretchBlt( m_hDC, rcDest, dwROP, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::StretchBlt( int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio )
	{
		m_pImage->StretchBlt( m_hDC, xDest, yDest, cxDest, cyDest, dwROP, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::StretchBlt( CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio )
	{
		m_pImage->StretchBlt( m_hDC, rcDest, rcOrigin, dwROP, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::StretchBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio )
	{
		m_pImage->StretchBlt( m_hDC, xDest, yDest, cxDest, cyDest, xOrigin, yOrigin, cxOrigin, cyOrigin, dwROP, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::TransparentBlt( CRect const & rcDest, COLORREF crTransparent, double dRatio )
	{
		m_pImage->TransparentBlt( m_hDC, rcDest, crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio )
	{
		m_pImage->TransparentBlt( m_hDC, xDest, yDest, cxDest, cyDest, crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::TransparentBlt( CRect const & rcDest, CRect const & rcOrigin, COLORREF crTransparent, double dRatio )
	{
		m_pImage->TransparentBlt( m_hDC, rcDest, rcOrigin, crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio )
	{
		m_pImage->TransparentBlt( m_hDC, xDest, yDest, cxDest, cyDest, xOrigin, yOrigin, cxOrigin, cyOrigin, crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::AlphaBlend( CRect const & rcDest, double dRatio )
	{
		m_pImage->AlphaBlend( m_hDC, rcDest, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::AlphaBlend( CRect const & rcDest, CRect const & rcSource, double dRatio )
	{
		m_pImage->AlphaBlend( m_hDC, rcDest, rcSource, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, double dRatio )
	{
		m_pImage->AlphaBlend( m_hDC, xDest, yDest, cxDest, cyDest, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio )
	{
		m_pImage->AlphaBlend( m_hDC, xDest, yDest, cxDest, cyDest, xOrigin, yOrigin, cxOrigin, cyOrigin, dRatio );
	}

	void CDrawer< eRENDERER_GDI >::FillRect( RECT const * pRect, HBRUSH hBrush )
	{
		::FillRect( m_hDC, pRect, hBrush );
	}

	void CDrawer< eRENDERER_GDI >::Ellipse( int left, int top, int right, int bottom )
	{
		::Ellipse( m_hDC, left, top, right, bottom );
	}

	CDrawerBase * CDrawer< eRENDERER_GDI >::CreateCompatibleDrawer()
	{
		HDC hDC = ::CreateCompatibleDC( m_hDC );
		return new CDrawer< eRENDERER_GDI >( hDC, m_rcRect, TRUE );
	}

	HBITMAP CDrawer< eRENDERER_GDI >::CreateCompatibleBitmap( int iWidth, int iHeight )
	{
		return ::CreateCompatibleBitmap( m_hDC, iWidth, iHeight );
	}

	HPEN CDrawer< eRENDERER_GDI >::DoCreateCustomPen( int iSize, COLORREF cColour, double dRatio, int iPenStyle )
	{
		LOGPEN lpLogPen;
		memset( & lpLogPen, 0, sizeof( lpLogPen ) );
		lpLogPen.lopnColor = cColour;
		lpLogPen.lopnWidth = CPoint( LONG( iSize * dRatio ), LONG( iSize * dRatio ) );
		lpLogPen.lopnStyle = iPenStyle;
		return ::CreatePenIndirect( & lpLogPen );
	}
}