#include "stdafx.h"

#include "TransparentDialogGDI.h"

#include "DrawerGDI.h"

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

namespace Joker
{
	typedef CTransparentCtrlT< CDialog, eRENDERER_GDI > CTransparentDlgGDI;

	CTransparentDlgGDI::CTransparentCtrlT()
	{
		m_ctrl = this;
	}

	CTransparentDlgGDI::CTransparentCtrlT( UINT nTemplate, CWnd * pParent )
		: BaseType( nTemplate, pParent )
	{
		m_ctrl = this;
	}

	CTransparentDlgGDI::CTransparentCtrlT( LPCTSTR szTemplate, CWnd * pParent )
		: BaseType( szTemplate, pParent )
	{
		m_ctrl = this;
	}

	CTransparentDlgGDI::~CTransparentCtrlT()
	{
		DoRelease();
	}

	bool CTransparentDlgGDI::GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
	{
		bool bReturn = false;
		BITMAPINFO bmiSrc = { { sizeof( BITMAPINFOHEADER ), 0, 0, 0, 0, 0 } };

		if ( ::GetDIBits( hDC, hBitmap, 0, 1, NULL, & bmiSrc, DIB_RGB_COLORS ) )
		{
			size.cx = bmiSrc.bmiHeader.biWidth;
			size.cy = bmiSrc.bmiHeader.biHeight;
			int bitCount = 32;
			BITMAPINFO bmi = { { sizeof( BITMAPINFOHEADER ), size.cx, size.cy, 1, bitCount, BI_RGB } };
			arrayBits.resize( size.cx * size.cy * bitCount / 8, 0 );
			std::vector< BYTE > arrayBitsSrc( arrayBits.size(), 0 );

			if ( ::GetDIBits( hDC, hBitmap, 0, size.cy, &arrayBitsSrc[0], &bmi, DIB_RGB_COLORS ) )
			{
				bReturn = true;
				memcpy( &arrayBits[0], &arrayBitsSrc[0], arrayBits.size() );
			}
		}

		if ( !bReturn )
		{
			arrayBits.clear();
			size.cx = 0;
			size.cy = 0;
		}

		return bReturn;
	}

	void CTransparentDlgGDI::DrawBitmap( CRect const & rcDst, HBITMAP hBitmapp, CRect const & rcSrc, BOOL bSrcAlpha )
	{
		CSize size;
		std::vector< BYTE > arrayBits;

		if ( GetBitmapInfos( *m_pBackDC, hBitmapp, size, arrayBits ) )
		{
			HBITMAP hBitmap;
			BITMAPINFO bmi;
			VOID * pvBits;
			BLENDFUNCTION bf;

			// create a DC for our bitmap -- the source DC for AlphaBlend
			CBitmapDC bmpDC( *m_pBackDC );

			// setup bitmap info
			// set the bitmap width and height to 60% of the width and height of each of the three horizontal areas. Later on, the
			bmi.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
			bmi.bmiHeader.biWidth = size.cx;
			bmi.bmiHeader.biHeight = size.cy;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage = size.cx * size.cy * 4;

			// create our DIB section and select the bitmap into the dc
			hBitmap = ::CreateDIBSection( bmpDC, & bmi, DIB_RGB_COLORS, & pvBits, NULL, 0x0 );

			// select the bitmap into the dc
			bmpDC.Attach( hBitmap );

			memcpy( pvBits, & arrayBits[0], bmi.bmiHeader.biSizeImage );

			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = 0xFF;

			if ( bSrcAlpha )
			{
				bf.AlphaFormat = AC_SRC_ALPHA;
			}
			else
			{
				bf.AlphaFormat = 0;
			}

			if ( !::AlphaBlend( *m_pBackDC, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), bmpDC, rcSrc.left, rcSrc.top, std::min( rcSrc.Width(), int( size.cx ) ), std::min( rcSrc.Height(), int( size.cy ) ), bf ) )
			{
				DWORD dwError = GetLastError();
				ASSERT( dwError == 0 );
				String strReturn;
				LPTSTR szError = NULL;

				if ( dwError != ERROR_SUCCESS && ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, LPTSTR( &szError ), 0, NULL ) != 0 )
				{
					strReturn = CStrUtils::ToTStr( std::to_string( dwError ) ) + _T( " (" ) + szError + _T( ")" );
					CStrUtils::Replace( strReturn, _T( "\r" ), _T( "" ) );
					CStrUtils::Replace( strReturn, _T( "\n" ), _T( "" ) );
					LocalFree( szError );
				}

				CLogger::LogWarning( strReturn );
			}

			bmpDC.Detach();
			::DeleteObject( hBitmap );
		}
	}

	void CTransparentDlgGDI::FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth, UINT uiStyle )
	{
		LOGPEN lpLogPen;
		memset( & lpLogPen, 0, sizeof( lpLogPen ) );
		lpLogPen.lopnColor = clColour.ToBGR();
		lpLogPen.lopnWidth = CPoint( iWidth, iWidth );
		lpLogPen.lopnStyle = uiStyle;
		HPEN hPen = ::CreatePenIndirect( & lpLogPen );
		HPEN hOldPen = HPEN( ::SelectObject( *m_pBackDC, hPen ) );
		::MoveToEx(	*m_pBackDC,	rcRect.left,			rcRect.top, NULL );
		::LineTo(	*m_pBackDC,	rcRect.right - iWidth,	rcRect.top );
		::LineTo(	*m_pBackDC,	rcRect.right - iWidth,	rcRect.bottom - iWidth );
		::LineTo(	*m_pBackDC,	rcRect.left,			rcRect.bottom - iWidth );
		::LineTo(	*m_pBackDC,	rcRect.left,			rcRect.top );
		::SelectObject( *m_pBackDC, hOldPen );
		::DeleteObject( hPen );
	}

	void CTransparentDlgGDI::DrawSolidText( HFONT UNUSED( hFont ), LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle )
	{
//	if ( dwStyle & DT_VCENTER )
		{
			CFont a2iFont( logFont );
			CDrawer< eRENDERER_GDI > drawer( *m_pBackDC, m_brushMask.GetRect() );
			drawer.DrawFormattedText( a2iFont, clColour.ToCOLORREF(), ( LPCTSTR )csText, rcRect, dwStyle );
	//		::DrawText( *m_pBackDC, csText, csText.GetLength(), rcRect, dwStyle );
		}
// 	else
// 	{
// 		HFONT hOldFont = HFONT( ::SelectObject( *m_pBackDC, hFont ) );
// 		COLORREF crOldTextColor = ::SetTextColor( *m_pBackDC, clColour.ToBGR() );
// 		::DrawText( *m_pBackDC, csText, csText.GetLength(), rcRect, dwStyle );
// 		::SetTextColor( *m_pBackDC, crOldTextColor );
// 		::SelectObject( *m_pBackDC, hOldFont );
// 	}
	}

	void CTransparentDlgGDI::FillSolidRect( CColour const & clColour, CRect rcRect )
	{
		HBRUSH hBrush = CreateSolidBrush( clColour.ToBGR() );
		::FillRect( *m_pBackDC, rcRect, hBrush );
		::DeleteObject( hBrush );
	}

	void CTransparentDlgGDI::TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent )
	{
		::TransparentBlt( *m_pBackDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), clTransparent.ToBGR() );
	}

	void CTransparentDlgGDI::AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc )
	{
		if ( !::AlphaBlend( *m_pBackDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), blendFunc ) )
		{
			ASSERT( FALSE );
		}
	}

	BOOL CTransparentDlgGDI::SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		return SetWindowPosition( pWndInsertAfter, x, y, cx, cy, uiFlags );
	}

	inline void CTransparentDlgGDI::DoRelease()
	{
	}

	void CTransparentDlgGDI::DoDrawBackground( CRect const & rcRect )
	{
		// On met l'image d'arrière plan dans le backbuffer
		DrawBitmap( rcRect, m_bmpBackground, rcRect, FALSE );
		// on blende le backbuffer et le masque
		DrawBitmap( rcRect, m_brushMask.GetDC(), m_brushMask.GetRect() );
	}

	void CTransparentDlgGDI::DoDrawForeground( CRect const & rcRect )
	{
	}

	inline void CTransparentDlgGDI::DoDraw()
	{
		::SetBkMode( m_hDC, TRANSPARENT );
		//::SetStretchBltMode( m_hDC, HALFTONE );

		CRect rcRect;
		GetClientRect( & rcRect );

		// On crée le backbuffer
		CBitmapDC backDC( m_hDC );
		backDC.CreateBitmap( rcRect );
		m_pBackDC = & backDC;

		// On dessine l'arrière plan
		DoDrawBackground( rcRect );

		// On dessine le premier plan
		DoDrawForeground( rcRect );

		// On blitte le backbuffer dans le dc final
		::BitBlt( m_hDC, 0, 0, rcRect.Width(), rcRect.Height(), backDC, 0, 0, SRCCOPY );
		m_pBackDC = NULL;
	}

	void CTransparentDlgGDI::PreSubclassWindow()
	{
		BaseType::PreSubclassWindow();
	}

	BEGIN_MESSAGE_MAP( CTransparentDlgGDI, CTransparentDlgGDI::BaseType )
		ON_WM_ERASEBKGND()
		ON_WM_PAINT()
		ON_WM_SIZE()
		ON_WM_MOUSEMOVE()
		ON_MESSAGE( WM_MOUSELEAVE,	OnMouseLeave )
		ON_WM_SETFOCUS()
		ON_WM_KILLFOCUS()
	END_MESSAGE_MAP()

	BOOL CTransparentDlgGDI::OnEraseBkgnd( CDC * pDC )
	{
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetStretchBltMode( HALFTONE );

		if ( !m_bHasBackground )
		{
			DoInitialiseBackground();
			m_bHasBackground = true;
		}

		return TRUE;
	}

	void CTransparentDlgGDI::OnSize( UINT type, int cx, int cy )
	{
		LockWindowUpdate();
		BaseType::OnSize( type, cx, cy );
		m_bReinitBackground = true;
		UnlockWindowUpdate();
	}

	void CTransparentDlgGDI::OnPaint()
	{
		if ( BaseType::IsWindowVisible() )
		{
			if ( m_bReinitBackground )
			{
				DoInitialiseBackground();
			}

			CPaintDC l_paintDC( this );
			l_paintDC.SetBkMode( TRANSPARENT );
			m_bPainting = true;
			m_hDC = l_paintDC;
			DoDraw();
			m_hDC = NULL;
			m_bPainting = false;
		}
	}

	void CTransparentDlgGDI::OnSetFocus( CWnd * pOldWnd )
	{
		m_bFocused = true;
		BaseType::OnSetFocus( pOldWnd );
	}

	void CTransparentDlgGDI::OnKillFocus( CWnd * pNewWnd )
	{
		m_bFocused = false;
		BaseType::OnKillFocus( pNewWnd );
	}

	void CTransparentDlgGDI::OnMouseMove( UINT nFlags, CPoint point )
	{
		if ( !m_bMouseOver )
		{
			TRACKMOUSEEVENT tme = { sizeof( TRACKMOUSEEVENT ), TME_LEAVE, m_hWnd, 0 };
			TrackMouseEvent( & tme );
			m_bMouseOver = true;
		}

		BaseType::OnMouseMove( nFlags, point );
	}

	LRESULT CTransparentDlgGDI::OnMouseLeave( WPARAM UNUSED( wParam ), LPARAM UNUSED( lParam ) )
	{
		m_bMouseOver = false;
		BaseType::OnMouseLeave();
		return 0;
	}
}