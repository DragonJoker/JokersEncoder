#include "stdafx.h"

#include "BitmapDC.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#undef DrawText

namespace Joker
{
	namespace
	{
		int WINAPI DrawText( HDC hdc, LPCTSTR lpchText, int cchText, LPRECT lprc, UINT format)
		{
#if defined( _UNICODE )
			return ::DrawTextW( hdc, lpchText, cchText, lprc, format );
#else
			return ::DrawTextA( hdc, lpchText, cchText, lprc, format );
#endif
		}
	}

	CBitmapDC::CBitmapDC( HDC hDC )
		:	m_hBaseDC		( hDC )
		,	m_hDC			( NULL )
		,	m_hBitmap		( NULL )
		,	m_bOwnBitmap	( true )
	{
		m_hDC = ::CreateCompatibleDC( m_hBaseDC );
	}

	CBitmapDC::~CBitmapDC()
	{
		Release();
	}

	CBitmapDC::CBitmapDC( CBitmapDC const & bmpDC )
		:	m_hBaseDC		( bmpDC )
		,	m_hDC			( NULL )
		,	m_hBitmap		( NULL )
		,	m_bOwnBitmap	( true )
	{
		m_hDC = ::CreateCompatibleDC( m_hBaseDC );
	}

	CBitmapDC & CBitmapDC::operator =( CBitmapDC const & bmpDC )
	{
		Release();
		m_hBaseDC = bmpDC;
		m_hDC = ::CreateCompatibleDC( m_hBaseDC );
		return * this;
	}

	void CBitmapDC::Release()
	{
		ReleaseBitmap();

		if ( m_hDC )
		{
			::DeleteDC( m_hDC );
			m_hDC = NULL;
		}
	}

	void CBitmapDC::Attach( HBITMAP hBitmap )
	{
		ReleaseBitmap();
		m_hBitmap = hBitmap;
		SelectBitmap();
		m_bOwnBitmap = false;
	}

	HBITMAP	CBitmapDC::Detach()
	{
		HBITMAP hReturn = NULL;

		if ( ! m_bOwnBitmap )
		{
			hReturn = m_hBitmap;
			m_hBitmap = NULL;
			m_bOwnBitmap = true;
		}

		return hReturn;
	}

	void CBitmapDC::CreateBitmap( CRect const & rcRect )
	{
		ReleaseBitmap();
		m_hBitmap =  ::CreateCompatibleBitmap( m_hBaseDC, rcRect.Width(), rcRect.Height() );
		SelectBitmap();
		m_bOwnBitmap = true;
	}

	void CBitmapDC::FillSolidRect( CColour clColour, CRect rcRect )
	{
		HBRUSH hBrush = ::CreateSolidBrush( clColour.ToBGR() );
		::FillRect( m_hDC, rcRect, hBrush );
		::DeleteObject( hBrush );
	}

	void CBitmapDC::DrawSolidText( HFONT hFont, LOGFONT logFont, CColour clColour, CString const & csText, CRect rcRect, DWORD dwStyle )
	{
		HFONT hOldFont = HFONT( ::SelectObject( m_hDC, hFont ) );
		COLORREF crOldTextColor = ::SetTextColor( m_hDC, clColour.ToBGR() );
		DrawText( m_hDC, csText, csText.GetLength(), rcRect, dwStyle );
		::SetTextColor( m_hDC, crOldTextColor );
		::SelectObject( m_hDC, hOldFont );
	}

	void CBitmapDC::FrameRect( CRect const & rcRect, CColour clColour, int iWidth, UINT uiStyle )
	{
		LOGPEN lpLogPen;
		memset( & lpLogPen, 0, sizeof( lpLogPen ) );
		lpLogPen.lopnColor = clColour.ToBGR();
		lpLogPen.lopnWidth = CPoint( iWidth, iWidth );
		lpLogPen.lopnStyle = uiStyle;
		HPEN hPen = ::CreatePenIndirect( & lpLogPen );
		HPEN hOldPen = HPEN( SelectObject( m_hDC, hPen ) );
		::MoveToEx( m_hDC,	rcRect.left,			rcRect.top, NULL );
		::LineTo( m_hDC,	rcRect.right - iWidth,	rcRect.top );
		::LineTo( m_hDC,	rcRect.right - iWidth,	rcRect.bottom - iWidth );
		::LineTo( m_hDC,	rcRect.left,			rcRect.bottom - iWidth );
		::LineTo( m_hDC,	rcRect.left,			rcRect.top );
		::SelectObject( m_hDC, hOldPen );
		::DeleteObject( hPen );
	}

	void CBitmapDC::AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc )
	{
		if ( ! ::AlphaBlend( m_hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), blendFunc ) ) 
		{
			ASSERT( FALSE );
		}
	}

	void CBitmapDC::BitBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, DWORD dwRop )
	{
		::BitBlt( m_hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, dwRop );
	}

	void CBitmapDC::StretchBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, DWORD dwRop )
	{
		::StretchBlt( m_hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), dwRop );
	}

	void CBitmapDC::TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent )
	{
		::TransparentBlt( m_hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), clTransparent.ToBGR() );
	}

	void CBitmapDC::DrawBitmap( CRect const & rcDest, HBITMAP hBitmap, CRect const & rcBitmap )
	{
		CBitmapDC bmpDC( m_hBaseDC );
		bmpDC.Attach( hBitmap );
		StretchBlt( rcDest, bmpDC, rcBitmap, SRCCOPY );
	}

	void CBitmapDC::ReleaseBitmap()
	{
		if ( m_bOwnBitmap && m_hBitmap )
		{
			::DeleteObject( m_hBitmap );
		}

		m_hBitmap = NULL;
		m_bOwnBitmap = true;
	}

	void CBitmapDC::SelectBitmap()
	{
		::SelectObject( m_hDC, m_hBitmap );
		::SetBkMode( m_hDC, TRANSPARENT );
		::SetStretchBltMode( m_hDC, HALFTONE );
	}
}
