#include "stdafx.h"

#include "TransparentDialogD2D.h"

#include <iostream>

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

namespace Joker
{
#if DEF_USING_D2D
	typedef CTransparentCtrlT< CDialog, eRENDERER_D2D > CTransparentDlgD2D;

	CTransparentDlgD2D::CTransparentCtrlT()
		: BaseType()
		, m_pRenderTarget( NULL )
		, m_brush( NULL )
	{
		m_ctrl = this;
	}

	CTransparentDlgD2D::CTransparentCtrlT( UINT nTemplate, CWnd * pParent )
		: BaseType( nTemplate, pParent )
		, m_pRenderTarget( NULL )
		, m_brush( NULL )
	{
		m_ctrl = this;
	}

	CTransparentDlgD2D::CTransparentCtrlT( LPCTSTR szTemplate, CWnd * pParent )
		: BaseType( szTemplate, pParent )
		, m_pRenderTarget( NULL )
		, m_brush( NULL )
	{
		m_ctrl = this;
	}

	CTransparentDlgD2D::~CTransparentCtrlT()
	{
	}

	bool CTransparentDlgD2D::GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
	{
		bool bReturn = false;
		BITMAPINFO bmiSrc = { { sizeof( BITMAPINFOHEADER ), 0, 0, 0, 0, 0 } };
		int result = ::GetDIBits( hDC, hBitmap, 0, 1, NULL, &bmiSrc, DIB_RGB_COLORS );

		if ( result && result != ERROR_INVALID_PARAMETER )
		{
			size.cx = bmiSrc.bmiHeader.biWidth;
			size.cy = bmiSrc.bmiHeader.biHeight;
			int bitCount = 32;
			BITMAPINFO bmi = { { sizeof( BITMAPINFOHEADER ), size.cx, size.cy, 1, bitCount, BI_RGB } };
			arrayBits.resize( size.cx * size.cy * bitCount / 8, 0 );

			std::vector< BYTE > arrayBitsSrc( arrayBits.size(), 0 );
			result = ::GetDIBits( hDC, hBitmap, 0, size.cy, &arrayBitsSrc[0], &bmi, DIB_RGB_COLORS );

			if ( result && result != ERROR_INVALID_PARAMETER )
			{
				bReturn = true;
				UINT uiStep = arrayBits.size() / size.cy;

				for ( int i = 0 ; i < size.cy ; ++i )
				{
					memcpy( &arrayBits[i * uiStep], &arrayBitsSrc[arrayBits.size() - uiStep - i * uiStep], uiStep );
				}
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

	void CTransparentDlgD2D::DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL UNUSED( bSrcAlpha ) )
	{
		std::map< HBITMAP, ID2D1Bitmap * >::iterator it = m_bitmaps.find( hBitmap );
		ID2D1Bitmap * pBmp = NULL;

		if ( it == m_bitmaps.end() )
		{
			CSize size;
			std::vector< BYTE > arrayBits;

			if ( GetBitmapInfos( m_hDC, hBitmap, size, arrayBits ) )
			{
				D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties( D2D1::PixelFormat( DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED ) );
				m_pRenderTarget->CreateBitmap( D2D1::SizeU( size.cx, size.cy ), & arrayBits[0], size.cx * 4, props, &pBmp );

				if ( pBmp )
				{
					m_bitmaps.insert( std::make_pair( hBitmap, pBmp ) );
				}
			}
		}
		else
		{
			pBmp = it->second;
		}

		if ( pBmp )
		{
			D2D1_RECT_F rcfSrc = D2D1::RectF( float( rcSrc.left ), float( rcSrc.top ), float( rcSrc.right ), float( rcSrc.bottom ) );
			D2D1_RECT_F rcfDst = D2D1::RectF( float( rcDst.left ), float( rcDst.top ), float( rcDst.right ), float( rcDst.bottom ) );
			m_pRenderTarget->DrawBitmap( pBmp, rcfDst, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rcfSrc );
		}
	}

	void CTransparentDlgD2D::FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth, UINT uiStyle )
	{
		ID2D1StrokeStyle * pStroke;
		ID2D1SolidColorBrush * pBrush;
		float tmp[2] = { 50, 50 };
		m_pFactory->CreateStrokeStyle( D2D1::StrokeStyleProperties( D2D1_CAP_STYLE_SQUARE, D2D1_CAP_STYLE_SQUARE, D2D1_CAP_STYLE_SQUARE, D2D1_LINE_JOIN_MITER, FLOAT( iWidth ), D2D1_DASH_STYLE( uiStyle ), FLOAT( iWidth ) ), tmp, 2, & pStroke );
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToD2DColor(), & pBrush );
		m_pRenderTarget->DrawLine( D2D1::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.top ) ), D2D1::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.top ) ), pBrush, FLOAT( iWidth ), pStroke );
		m_pRenderTarget->DrawLine( D2D1::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.top ) ), D2D1::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.bottom - iWidth ) ), pBrush, FLOAT( iWidth ), pStroke );
		m_pRenderTarget->DrawLine( D2D1::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.bottom - iWidth ) ), D2D1::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.bottom - iWidth ) ), pBrush, FLOAT( iWidth ), pStroke );
		m_pRenderTarget->DrawLine( D2D1::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.bottom - iWidth ) ), D2D1::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.top ) ), pBrush, FLOAT( iWidth ), pStroke );
		SafeRelease( pStroke );
		SafeRelease( pBrush );
	}

	void CTransparentDlgD2D::DrawSolidText( HFONT UNUSED( hFont ), LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle )
	{
		DWRITE_FONT_STYLE style = logFont.lfItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
		ID2D1SolidColorBrush * pBrush = NULL;
		IDWriteTextFormat * pTextFormat = NULL;
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToD2DColor(), & pBrush );
		HRESULT hr;
		std::wstring strTmp = CStrUtils::ToWStr( logFont.lfFaceName );

		if ( !strTmp.empty() )
		{
			hr = m_pWriteFactory->CreateTextFormat( strTmp.c_str(), NULL, DWRITE_FONT_WEIGHT( logFont.lfWeight ), style, DWRITE_FONT_STRETCH_NORMAL, FLOAT( abs( logFont.lfHeight ) ), L"", & pTextFormat );
		}
		else
		{
			hr = S_FALSE;
		}

		if ( hr == S_OK )
		{
			if ( dwStyle & DT_VCENTER )
			{
				pTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
			}
			else if ( dwStyle & DT_BOTTOM )
			{
				pTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_FAR );
			}
			else
			{
				pTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_NEAR );
			}

			if ( dwStyle & DT_CENTER )
			{
				pTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER );
			}
			else if ( dwStyle & DT_RIGHT )
			{
				pTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_TRAILING );
			}
			else
			{
				pTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_LEADING );
			}

			strTmp = CStrUtils::ToWStr( CString::PCXSTR( csText ) );

			if ( !strTmp.empty() )
			{
#if defined( _UNICODE )
				m_pRenderTarget->DrawTextW( strTmp.c_str(), strTmp.size(), pTextFormat, D2D1::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
#else
				m_pRenderTarget->DrawTextA( strTmp.c_str(), strTmp.size(), pTextFormat, D2D1::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
#endif
			}
		}

		SafeRelease( pBrush );
		SafeRelease( pTextFormat );
	}

	void CTransparentDlgD2D::FillSolidRect( CColour const & clColour, CRect rcRect )
	{
		ID2D1SolidColorBrush * pBrush;
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToD2DColor(), & pBrush );
		m_pRenderTarget->FillRectangle( D2D1::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
		SafeRelease( pBrush );
	}

	void CTransparentDlgD2D::TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent )
	{
//		::TransparentBlt( hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), clTransparent.ToBGR() );
	}

	void CTransparentDlgD2D::AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc )
	{
		HBITMAP hBitmap = HBITMAP( ::SelectObject( srcDC, NULL ) );
		DrawBitmap( rcDest, hBitmap, rcSrc );
		::SelectObject( srcDC, hBitmap );
	}

	BOOL CTransparentDlgD2D::SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		return SetWindowPosition( pWndInsertAfter, x, y, cx, cy, uiFlags );
	}

	BOOL CTransparentDlgD2D::SetTransparentColour( COLORREF colour )
	{
		m_colour = colour;
		Delete( m_brush );
		m_brush = ::CreateSolidBrush( colour );
		return SetLayeredWindowAttributes( colour, 255, LWA_COLORKEY | LWA_ALPHA );
	}

	void CTransparentDlgD2D::DoInitialiseDeviceDependent()
	{
		CRect rcRect;
		BaseType::GetClientRect( rcRect );
		D2D1_SIZE_U size = D2D1::SizeU( rcRect.Width(), rcRect.Height() );
		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties( D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat( DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED ) );
		HRESULT hr = m_pFactory->CreateHwndRenderTarget( props, D2D1::HwndRenderTargetProperties( m_hWnd, size ), &m_pRenderTarget );

		if ( hr != S_OK )
		{
			CLogger::LogError( String( _T( "CreateHwndRenderTarget failed" ) ), false );
		}
	}

	void CTransparentDlgD2D::DoCleanupDeviceDependent()
	{
		if ( m_pRenderTarget )
		{
			SafeRelease( m_pRenderTarget );
			m_pRenderTarget = NULL;
		}
	}

	inline void CTransparentDlgD2D::DoDraw()
	{
		if ( m_hWnd &&::IsWindowVisible( m_hWnd ) )
		{
			CRect rcRect;
			GetClientRect( & rcRect );

			if ( m_pRenderTarget )
			{
				m_pRenderTarget->BeginDraw();
				m_pRenderTarget->Clear( D2D1::ColorF( D2D1::ColorF::Enum::Black, 0.0F ) );

				// on blende le backbuffer et le masque
				DrawBitmap( rcRect, m_brushMask.GetDC(), m_brushMask.GetRect() );

				m_pRenderTarget->EndDraw();
			}
		}
	}

	void CTransparentDlgD2D::PreSubclassWindow()
	{
		BaseType::PreSubclassWindow();
	}

	BEGIN_MESSAGE_MAP( CTransparentDlgD2D, CTransparentDlgD2D::BaseType )
		ON_WM_CREATE()
		ON_WM_ERASEBKGND()
		ON_WM_CTLCOLOR()
		ON_WM_PAINT()
		ON_WM_SIZE()
		ON_MESSAGE( WM_DISPLAYCHANGE, OnDisplayChange )
		ON_WM_MOUSEMOVE()
		ON_MESSAGE( WM_MOUSELEAVE,	OnMouseLeave )
		ON_WM_SETFOCUS()
		ON_WM_KILLFOCUS()
	END_MESSAGE_MAP()

	int CTransparentDlgD2D::OnCreate( LPCREATESTRUCT pCreate )
	{
		int ret = BaseType::OnCreate( pCreate );

		if ( !ret )
		{
			BOOL res = ModifyStyleEx( 0, WS_EX_COMPOSITED | WS_EX_LAYERED, 0 );

			if ( res )
			{
				res = SetTransparentColour( RGB( 0, 255, 0 ) );
			}
		}

		return ret;
	}

	BOOL CTransparentDlgD2D::OnEraseBkgnd( CDC * pDC )
	{
		if ( m_bHasBackground )
		{
			if ( !m_pRenderTarget || m_hWnd != m_pRenderTarget->GetHwnd() )
			{
				// Si on a détruit la partie graphique du contrôle puis reconstruite, on doit réinitialiser la partie Device Dependant
				DoCleanupDeviceDependent();
				DoInitialiseDeviceDependent();
			}
		}

		return TRUE;
	}

	HBRUSH CTransparentDlgD2D::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID )
	{
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetStretchBltMode( HALFTONE );

		if ( m_brush )
		{
			return m_brush;
		}
		else
		{
			return HBRUSH( ::GetStockObject( NULL_BRUSH ) );
		}
	}

	void CTransparentDlgD2D::OnPaint()
	{
		if ( BaseType::IsWindowVisible() )
		{
			CPaintDC l_paintDC( this );
			l_paintDC.SetBkMode( TRANSPARENT );
			l_paintDC.SetStretchBltMode( HALFTONE );
			m_bPainting = true;
			m_hDC = l_paintDC;
			DoDraw();
			m_hDC = NULL;
			m_bPainting = false;
		}
	}

	void CTransparentDlgD2D::OnSize( UINT type, int cx, int cy )
	{
		LockWindowUpdate();
		BaseType::OnSize( type, cx, cy );

		if ( m_pRenderTarget )
		{
			m_pRenderTarget->Resize( D2D1::SizeU( cx, cy ) );
		}

		m_bReinitBackground = true;
		UnlockWindowUpdate();
	}

	LRESULT CTransparentDlgD2D::OnDisplayChange( WPARAM, LPARAM )
	{
		m_bReinitBackground = true;
		DoDraw();
		return 0;
	}

	void CTransparentDlgD2D::OnSetFocus( CWnd * pOldWnd )
	{
		m_bFocused = true;
		BaseType::OnSetFocus( pOldWnd );
	}

	void CTransparentDlgD2D::OnKillFocus( CWnd * pNewWnd )
	{
		m_bFocused = false;
		BaseType::OnKillFocus( pNewWnd );
	}

	void CTransparentDlgD2D::OnMouseMove( UINT nFlags, CPoint point )
	{
		if ( !m_bMouseOver )
		{
			TRACKMOUSEEVENT mouseEvent;
			mouseEvent.cbSize = sizeof( TRACKMOUSEEVENT );
			mouseEvent.dwFlags = TME_LEAVE;
			mouseEvent.hwndTrack = m_hWnd;
			mouseEvent.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent( & mouseEvent );
			m_bMouseOver = true;
		}

		BaseType::OnMouseMove( nFlags, point );
	}

	LRESULT CTransparentDlgD2D::OnMouseLeave( WPARAM UNUSED( wParam ), LPARAM UNUSED( lParam ) )
	{
		m_bMouseOver = false;
		BaseType::OnMouseLeave();
		return 0;
	}
#endif
}