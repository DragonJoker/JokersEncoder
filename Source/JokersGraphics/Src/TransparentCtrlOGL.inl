#include <iostream>

namespace Joker
{
#if DEF_USING_OGL
	template< typename T >
	CTransparentCtrlT< T, eRENDERER_OGL >::CTransparentCtrlT()
		: m_pRenderTarget( NULL )
	{
		m_ctrl = this;
	}

	template< typename T >
	CTransparentCtrlT< T, eRENDERER_OGL >::~CTransparentCtrlT()
	{
	}

	template< typename T >
	bool CTransparentCtrlT< T, eRENDERER_OGL >::GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL UNUSED( bSrcAlpha ) )
	{
		std::map< HBITMAP, IGL2DBitmap * >::iterator it = m_bitmaps.find( hBitmap );
		IGL2DBitmap * pBmp = NULL;

		if ( it == m_bitmaps.end() )
		{
			CSize size;
			std::vector< BYTE > arrayBits;

			if ( GetBitmapInfos( m_hDC, hBitmap, size, arrayBits ) )
			{
				GL2D_BITMAP_PROPERTIES props = GL2D::BitmapProperties( GL2D::PixelFormat( GL2D_GL_FORMAT_RGBA, GL2D_GL_INTERNAL_RGB8, GL2D_GL_TYPE_UNSIGNED_BYTE ) );
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth, UINT uiStyle )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DrawSolidText( HFONT UNUSED( hFont ), LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::FillSolidRect( CColour const & clColour, CRect rcRect )
	{
		IGL2DSolidColorBrush * pBrush;
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToGL2DColor(), & pBrush );
		m_pRenderTarget->FillRectangle( GL2D::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
		SafeRelease( pBrush );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent )
	{
		//	::TransparentBlt( hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), clTransparent.ToBGR() );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc )
	{
		HBITMAP hBitmap = HBITMAP( ::SelectObject( srcDC, NULL ) );
		DrawBitmap( rcDest, hBitmap, rcSrc );
		::SelectObject( srcDC, hBitmap );
	}

	template< typename T >
	BOOL CTransparentCtrlT< T, eRENDERER_OGL >::SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		return SetWindowPosition( pWndInsertAfter, x, y, cx, cy, uiFlags );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoInitialiseDeviceDependent()
	{
		CRect rcRect;
		T::GetClientRect( rcRect );
		GL2D_SIZE_U size = GL2D::SizeU( rcRect.Width(), rcRect.Height() );
		GL2D_RENDER_TARGET_PROPERTIES props = GL2D::RenderTargetProperties( GL2D_RENDER_TARGET_TYPE_DEFAULT, GL2D::PixelFormat( GL2D_GL_FORMAT_RGBA, GL2D_GL_INTERNAL_RGB8, GL2D_GL_TYPE_UNSIGNED_BYTE ) );
		HRESULT hr = m_pFactory->CreateHwndRenderTarget( props, GL2D::HwndRenderTargetProperties( m_hWnd, size ), &m_pRenderTarget );

		if ( hr != S_OK )
		{
			CLogger::LogError( String( _T( "CreateHwndRenderTarget failed" ) ), false );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoCleanupDeviceDependent()
	{
		if ( m_pRenderTarget )
		{
			SafeRelease( m_pRenderTarget );
			m_pRenderTarget = NULL;
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoDrawBackground( CRect const & rcRect )
	{
		// On met l'image d'arrière plan dans le backbuffer
		DrawBitmap( rcRect, m_bmpBackground, rcRect, FALSE );
		// on blende le backbuffer et le masque
		DrawBitmap( rcRect, m_brushMask.GetDC(), m_brushMask.GetRect() );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoDrawForeground( CRect const & rcRect )
	{
		// On dessine le texte, s'il y en a un
		CString csText;
		GetWindowText( csText );

		if ( !csText.IsEmpty() )
		{
			LOGFONT logFont;
			GetFont()->GetLogFont( & logFont );
			DrawSolidText( ( * GetFont() ), logFont, m_clText, csText, rcRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
		}

		// On dessine le contour
		if ( m_bHasBorder )
		{
			FrameRect( rcRect, m_clBorder );
		}
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_OGL >::DoDraw()
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::PreSubclassWindow()
	{
		BaseType::PreSubclassWindow();
	}

	PTM_WARNING_DISABLE
	template< typename T >
	const AFX_MSGMAP * CTransparentCtrlT< T, eRENDERER_OGL >::GetMessageMap() const
	{
		return GetThisMessageMap();
	}

	template< typename T >
	const AFX_MSGMAP * PASCAL CTransparentCtrlT< T, eRENDERER_OGL >::GetThisMessageMap()
	{
		typedef CTransparentCtrlT< T, eRENDERER_OGL > ThisClass;
		typedef T TheBaseClass;
		static const AFX_MSGMAP_ENTRY _messageEntries[] =
		{
			ON_WM_ERASEBKGND()
			ON_WM_CTLCOLOR()
			ON_WM_PAINT()
			ON_WM_SIZE()
			ON_WM_MOVE()
			ON_MESSAGE( WM_DISPLAYCHANGE, OnDisplayChange )
			ON_WM_MOUSEMOVE()
			ON_MESSAGE( WM_MOUSELEAVE,	OnMouseLeave )
			ON_WM_SETFOCUS()
			ON_WM_KILLFOCUS()
			{
				0, 0, 0, 0, AfxSig_end, ( AFX_PMSG )0
			}
		};
		static const AFX_MSGMAP messageMap =
		{
			& TheBaseClass::GetThisMessageMap, &_messageEntries[0]
		};
		return &messageMap;
	}
	PTM_WARNING_RESTORE

	template< typename T >
	BOOL CTransparentCtrlT< T, eRENDERER_OGL >::OnEraseBkgnd( CDC * pDC )
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

		CRect rect;
		GetClientRect( rect );
		return DoDrawParentBackground( pDC, rect );
	}

	template< typename T >
	HBRUSH CTransparentCtrlT< T, eRENDERER_OGL >::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID )
	{
		pDC->SetBkMode( TRANSPARENT );
		return HBRUSH( ::GetStockObject( NULL_BRUSH ) );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnPaint()
	{
		if ( T::IsWindowVisible() )
		{
			if ( !m_bHasBackground || m_bReinitBackground )
			{
				DoInitialiseBackground();
			}

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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnSize( UINT type, int cx, int cy )
	{
		BaseType::OnSize( type, cx, cy );

		if ( m_pRenderTarget )
		{
			m_pRenderTarget->Resize( GL2D::SizeU( cx, cy ) );
		}

		m_bReinitBackground = true;
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnMove( int x, int y )
	{
		BaseType::OnMove( x, y );
		m_bReinitBackground = true;
	}

	template< typename T >
	LRESULT CTransparentCtrlT< T, eRENDERER_OGL >::OnDisplayChange( WPARAM, LPARAM )
	{
		m_bReinitBackground = true;
		DoDraw();
		return 0;
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnSetFocus( CWnd * pOldWnd )
	{
		m_bFocused = true;
		BaseType::OnSetFocus( pOldWnd );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnKillFocus( CWnd * pNewWnd )
	{
		m_bFocused = false;
		BaseType::OnKillFocus( pNewWnd );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnMouseMove( UINT nFlags, CPoint point )
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
			BaseType::Invalidate();
		}

		BaseType::OnMouseMove( nFlags, point );
	}

	template< typename T >
	LRESULT CTransparentCtrlT< T, eRENDERER_OGL >::OnMouseLeave( WPARAM UNUSED( wParam ), LPARAM UNUSED( lParam ) )
	{
		m_bMouseOver = false;
		BaseType::Invalidate();
		BaseType::OnMouseLeave();
		return 0;
	}
#endif
}