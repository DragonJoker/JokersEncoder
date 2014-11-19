#include "stdafx.h"

#include "TransparentDialogOGL.h"

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
#if DEF_USING_OGL
	typedef CTransparentCtrlT< CDialog, eRENDERER_OGL > CTransparentDlgOGL;

	CTransparentDlgOGL::CTransparentCtrlT()
		: m_pRenderTarget( NULL )
	{
		m_ctrl = this;
	}

	CTransparentDlgOGL::CTransparentCtrlT( UINT nTemplate, CWnd * pParent )
		: BaseType( nTemplate, pParent )
		, m_pRenderTarget( NULL )
	{
		m_ctrl = this;
	}

	CTransparentDlgOGL::CTransparentCtrlT( LPCTSTR szTemplate, CWnd * pParent )
		: BaseType( szTemplate, pParent )
		, m_pRenderTarget( NULL )
	{
		m_ctrl = this;
	}

	CTransparentDlgOGL::~CTransparentCtrlT()
	{
		DoRelease();
	}

	bool CTransparentDlgOGL::GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
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

	void CTransparentDlgOGL::DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL UNUSED( bSrcAlpha ) )
	{
		IGL2DBitmap * pBmp = NULL;
		std::map< HBITMAP, IGL2DBitmap * >::iterator it = m_bitmaps.find( hBitmap );

		if ( it == m_bitmaps.end() )
		{
			CSize size;
			std::vector< BYTE > arrayBits;

			if ( GetBitmapInfos( m_hDC, hBitmap, size, arrayBits ) )
			{
				GL2D_BITMAP_PROPERTIES props = GL2D::BitmapProperties( GL2D::PixelFormat( GL2D_GL_FORMAT_RGBA, GL2D_GL_INTERNAL_4, GL2D_GL_TYPE_UNSIGNED_BYTE ) );
				m_pRenderTarget->CreateBitmap( GL2D::SizeU( size.cx, size.cy ), & arrayBits[0], size.cx * 4, props, & pBmp );

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
			GL2D_RECT_F rcfSrc = GL2D::RectF( float( rcSrc.left ), float( rcSrc.top ), float( rcSrc.right ), float( rcSrc.bottom ) );
			GL2D_RECT_F rcfDst = GL2D::RectF( float( rcDst.left ), float( rcDst.top ), float( rcDst.right ), float( rcDst.bottom ) );
			m_pRenderTarget->DrawBitmap( pBmp, rcfDst, 1.0f, GL2D_BITMAP_INTERPOLATION_MODE_LINEAR, rcfSrc );
		}
	}

	void CTransparentDlgOGL::FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth, UINT uiStyle )
	{
		IGL2DStrokeStyle * pStroke;
		IGL2DSolidColorBrush * pBrush;
		float tmp[2] = { 50, 50 };
		m_pFactory->CreateStrokeStyle( GL2D::StrokeStyleProperties( GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_LINE_JOIN_MITER, FLOAT( iWidth ), GL2D_DASH_STYLE( uiStyle ), FLOAT( iWidth ) ), tmp, 2, & pStroke );
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToGL2DColor(), & pBrush );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.top ) ), GL2D::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.top ) ), pBrush, FLOAT( iWidth ), pStroke );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.top ) ), GL2D::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.bottom - iWidth ) ), pBrush, FLOAT( iWidth ), pStroke );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.right - iWidth ),	FLOAT( rcRect.bottom - iWidth ) ), GL2D::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.bottom - iWidth ) ), pBrush, FLOAT( iWidth ), pStroke );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.bottom - iWidth ) ), GL2D::Point2F( FLOAT( rcRect.left ),	FLOAT( rcRect.top ) ), pBrush, FLOAT( iWidth ), pStroke );
		SafeRelease( pStroke );
		SafeRelease( pBrush );
	}

	void CTransparentDlgOGL::DrawSolidText( HFONT UNUSED( hFont ), LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle )
	{
		DWRITE_FONT_STYLE style = logFont.lfItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
		IGL2DSolidColorBrush * pBrush = NULL;
		IDWriteTextFormat * pTextFormat = NULL;
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToGL2DColor(), & pBrush );
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
				m_pRenderTarget->DrawText( strTmp.c_str(), strTmp.size(), pTextFormat, GL2D::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
			}
		}

		SafeRelease( pBrush );
		SafeRelease( pTextFormat );
	}

	void CTransparentDlgOGL::FillSolidRect( CColour const & clColour, CRect rcRect )
	{
		IGL2DSolidColorBrush * pBrush;
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToGL2DColor(), & pBrush );
		m_pRenderTarget->FillRectangle( GL2D::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
		SafeRelease( pBrush );
	}

	void CTransparentDlgOGL::TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent )
	{
		//::TransparentBlt( hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), clTransparent.ToBGR() );
	}

	void CTransparentDlgOGL::AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc )
	{
		HBITMAP hBitmap = HBITMAP( ::SelectObject( srcDC, NULL ) );
		DrawBitmap( rcDest, hBitmap, rcSrc );
		::SelectObject( srcDC, hBitmap );
	}

	BOOL CTransparentDlgOGL::SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		return SetWindowPosition( pWndInsertAfter, x, y, cx, cy, uiFlags );
	}

	void CTransparentDlgOGL::DoInitDeviceDependent()
	{
		CRect rcRect;
		BaseType::GetClientRect( rcRect );
		GL2D_SIZE_U size = GL2D::SizeU( rcRect.Width(), rcRect.Height() );
		GL2D_RENDER_TARGET_PROPERTIES props = GL2D::RenderTargetProperties( GL2D_RENDER_TARGET_TYPE_DEFAULT, GL2D::PixelFormat( GL2D_GL_FORMAT_RGBA, GL2D_GL_INTERNAL_4, GL2D_GL_TYPE_UNSIGNED_BYTE ) );
		HRESULT hr = m_pFactory->CreateHwndRenderTarget( props, GL2D::HwndRenderTargetProperties( m_hWnd, size ), &m_pRenderTarget );

		if ( hr != S_OK )
		{
			CLogger::LogError( String( _T( "CreateHwndRenderTarget failed" ) ), false );
		}
	}

	void CTransparentDlgOGL::DoCleanupDeviceDependent()
	{
		if ( m_pRenderTarget )
		{
			SafeRelease( m_pRenderTarget );
			m_pRenderTarget = NULL;
		}
	}

	inline void CTransparentDlgOGL::DoRelease()
	{
		DoCleanupDeviceDependent();
	}

	void CTransparentDlgOGL::DoDrawBackground( CRect const & rcRect )
	{
		// On met l'image d'arrière plan dans le backbuffer
		//DrawBitmap( rcRect, m_bmpBackground, rcRect, FALSE );
		// on blende le backbuffer et le masque
		DrawBitmap( rcRect, m_brushMask.GetDC(), m_brushMask.GetRect() );
	}

	void CTransparentDlgOGL::DoDrawForeground( CRect const & rcRect )
	{
	}

	inline void CTransparentDlgOGL::DoDraw()
	{
		if ( m_hWnd &&::IsWindowVisible( m_hWnd ) )
		{
			CRect rcRect;
			GetClientRect( & rcRect );

			if ( m_pRenderTarget )
			{
				m_pRenderTarget->BeginDraw();
				m_pRenderTarget->Clear( GL2D::ColorF( GL2D::ColorF::Enum::Black, 0.0F ) );

				// On dessine l'arrière plan
				DoDrawBackground( rcRect );

				// On dessine le premier plan
				DoDrawForeground( rcRect );

				m_pRenderTarget->EndDraw();
			}
		}
	}

	void CTransparentDlgOGL::PreSubclassWindow()
	{
		BaseType::PreSubclassWindow();
	}

	BEGIN_MESSAGE_MAP( CTransparentDlgOGL, CTransparentDlgOGL::BaseType )
		ON_WM_ERASEBKGND()
		ON_WM_CTLCOLOR()
		ON_WM_DESTROY()
		ON_WM_PAINT()
		ON_WM_SIZE()
		ON_MESSAGE( WM_DISPLAYCHANGE, OnDisplayChange )
		ON_WM_MOUSEMOVE()
		ON_MESSAGE( WM_MOUSELEAVE,	OnMouseLeave )
		ON_WM_SETFOCUS()
		ON_WM_KILLFOCUS()
	END_MESSAGE_MAP()

	BOOL CTransparentDlgOGL::OnEraseBkgnd( CDC * UNUSED( pDC ) )
	{
		if ( m_bHasBackground )
		{
			if ( !m_pRenderTarget || m_hWnd != m_pRenderTarget->GetHwnd() )
			{
				// Si on a détruit la partie graphique du contrôle puis reconstruite, on doit réinitialiser la partie Device Dependant
				m_pRenderTarget = NULL;
				SafeRelease( m_pRenderTarget );
				DoInitDeviceDependent();
			}
		}

		if ( !m_bHasBackground )
		{
			DoInitDeviceDependent();
			DoInitialiseBackground();
			m_bHasBackground = true;
		}
		else if ( m_bReinitBackground )
		{
			DoInitialiseBackground();
		}

		return TRUE;
	}

	HBRUSH CTransparentDlgOGL::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID )
	{
		pDC->SetBkMode( TRANSPARENT );
		return HBRUSH( ::GetStockObject( NULL_BRUSH ) );
	}

	void CTransparentDlgOGL::OnDestroy()
	{
		DoRelease();
	}

	void CTransparentDlgOGL::OnPaint()
	{
		if ( BaseType::IsWindowVisible() )
		{
			CPaintDC l_paintDC( this );
			l_paintDC.SetBkMode( TRANSPARENT );
			m_bPainting = true;
			m_hDC = l_paintDC;
			DoDraw();
			m_hDC = NULL;
			m_bPainting = false;
		}
	}

	void CTransparentDlgOGL::OnSize( UINT type, int cx, int cy )
	{
		LockWindowUpdate();
		BaseType::OnSize( type, cx, cy );

		if ( m_pRenderTarget )
		{
			m_pRenderTarget->Resize( GL2D::SizeU( cx, cy ) );
		}

		m_bReinitBackground = true;
		UnlockWindowUpdate();
	}

	LRESULT CTransparentDlgOGL::OnDisplayChange( WPARAM, LPARAM )
	{
		m_bReinitBackground = true;
		DoDraw();
		return 0;
	}

	void CTransparentDlgOGL::OnSetFocus( CWnd * pOldWnd )
	{
		m_bFocused = true;
		BaseType::OnSetFocus( pOldWnd );
	}

	void CTransparentDlgOGL::OnKillFocus( CWnd * pNewWnd )
	{
		m_bFocused = false;
		BaseType::OnKillFocus( pNewWnd );
	}

	void CTransparentDlgOGL::OnMouseMove( UINT nFlags, CPoint point )
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

	LRESULT CTransparentDlgOGL::OnMouseLeave( WPARAM UNUSED( wParam ), LPARAM UNUSED( lParam ) )
	{
		m_bMouseOver = false;
		BaseType::OnMouseLeave();
		return 0;
	}
#endif
}