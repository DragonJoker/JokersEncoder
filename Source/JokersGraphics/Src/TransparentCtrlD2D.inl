#include <iostream>

namespace Joker
{
#if DEF_USING_D2D
	template< typename T >
	int CTransparentCtrlT< T, eRENDERER_D2D >:: m_iReferences = 0;
	template< typename T >
	IDWriteFactory * CTransparentCtrlT< T, eRENDERER_D2D >:: m_pWriteFactory = NULL;
	template< typename T >
	ID2D1Factory * CTransparentCtrlT< T, eRENDERER_D2D >:: m_pFactory = NULL;
	template< typename T >
	std::map< HBITMAP, ID2D1Bitmap * > CTransparentCtrlT< T, eRENDERER_D2D >:: m_bitmaps;

	template< typename T >
	CTransparentCtrlT< T, eRENDERER_D2D >::CTransparentCtrlT()
		: m_pRenderTarget( NULL )
	{
		m_ctrl = this;
		DoInitDeviceIndependent();
	}

	template< typename T >
	CTransparentCtrlT< T, eRENDERER_D2D >::~CTransparentCtrlT()
	{
		DoRelease();
		DoCleanupDeviceIndependent();
	}

	template< typename T >
	bool CTransparentCtrlT< T, eRENDERER_D2D >::GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
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
	void CTransparentCtrlT< T, eRENDERER_D2D >::DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL UNUSED( bSrcAlpha ) )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth, UINT uiStyle )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DrawSolidText( HFONT UNUSED( hFont ), LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::FillSolidRect( CColour const & clColour, CRect rcRect )
	{
		ID2D1SolidColorBrush * pBrush;
		m_pRenderTarget->CreateSolidColorBrush( clColour.ToD2DColor(), & pBrush );
		m_pRenderTarget->FillRectangle( D2D1::RectF( float( rcRect.left ), float( rcRect.top ), float( rcRect.right ), float( rcRect.bottom ) ), pBrush );
		SafeRelease( pBrush );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent )
	{
		//	::TransparentBlt( hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), srcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), clTransparent.ToBGR() );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc )
	{
		HBITMAP hBitmap = HBITMAP( ::SelectObject( srcDC, NULL ) );
		DrawBitmap( rcDest, hBitmap, rcSrc );
		::SelectObject( srcDC, hBitmap );
	}

	template< typename T >
	BOOL CTransparentCtrlT< T, eRENDERER_D2D >::SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		return SetWindowPosition( pWndInsertAfter, x, y, cx, cy, uiFlags );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DoInitDeviceIndependent()
	{
		m_iReferences++;

		if ( !m_pFactory )
		{
			::D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, & m_pFactory );
		}

		if ( !m_pWriteFactory )
		{
			::DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof( IDWriteFactory ), reinterpret_cast< IUnknown ** >( & m_pWriteFactory ) );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DoCleanupDeviceIndependent()
	{
		m_iReferences--;

		if ( m_iReferences <= 0 )
		{
			std::for_each( m_bitmaps.begin(), m_bitmaps.end(), [&]( std::pair< HBITMAP, ID2D1Bitmap * > pair )
			{
				SafeRelease( pair.second );
			} );

			m_bitmaps.clear();

			SafeRelease( m_pFactory );
			SafeRelease( m_pWriteFactory );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DoInitDeviceDependent()
	{
		CRect rcRect;
		T::GetClientRect( rcRect );
		D2D1_SIZE_U size = D2D1::SizeU( rcRect.Width(), rcRect.Height() );
		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties( D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat( DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED ) );
		HRESULT hr = m_pFactory->CreateHwndRenderTarget( props, D2D1::HwndRenderTargetProperties( m_hWnd, size ), &m_pRenderTarget );

		if ( hr != S_OK )
		{
			CLogger::LogError( String( _T( "CreateHwndRenderTarget failed" ) ), false );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DoCleanupDeviceDependent()
	{
		if ( m_pRenderTarget )
		{
			SafeRelease( m_pRenderTarget );
			m_pRenderTarget = NULL;
		}
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_D2D >::DoRelease()
	{
		DoCleanupDeviceDependent();
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DoDrawBackground( CRect const & rcRect )
	{
		// On met l'image d'arrière plan dans le backbuffer
		DrawBitmap( rcRect, m_bmpBackground, rcRect, FALSE );
		// on blende le backbuffer et le masque
		DrawBitmap( rcRect, m_brushMask.GetDC(), m_brushMask.GetRect() );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::DoDrawForeground( CRect const & rcRect )
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
	inline void CTransparentCtrlT< T, eRENDERER_D2D >::DoDraw()
	{
		if ( m_hWnd &&::IsWindowVisible( m_hWnd ) )
		{
			if ( m_bReinitBackground )
			{
				DoInitialiseBackground();
			}

			CRect rcRect;
			GetClientRect( & rcRect );

			if ( m_pRenderTarget )
			{
				m_pRenderTarget->BeginDraw();
				m_pRenderTarget->Clear( D2D1::ColorF( D2D1::ColorF::Enum::Black, 0.0F ) );

				// On dessine l'arrière plan
				DoDrawBackground( rcRect );

				// On dessine le premier plan
				DoDrawForeground( rcRect );

				m_pRenderTarget->EndDraw();
			}
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::PreSubclassWindow()
	{
		BaseType::PreSubclassWindow();
	}

	PTM_WARNING_DISABLE
	template< typename T >
	const AFX_MSGMAP * CTransparentCtrlT< T, eRENDERER_D2D >::GetMessageMap() const
	{
		return GetThisMessageMap();
	}

	template< typename T >
	const AFX_MSGMAP * PASCAL CTransparentCtrlT< T, eRENDERER_D2D >::GetThisMessageMap()
	{
		typedef CTransparentCtrlT< T, eRENDERER_D2D > ThisClass;
		typedef T TheBaseClass;
		static const AFX_MSGMAP_ENTRY _messageEntries[] =
		{
			ON_WM_ERASEBKGND()
			ON_WM_CTLCOLOR()
			ON_WM_PAINT()
			ON_WM_SIZE()
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
	BOOL CTransparentCtrlT< T, eRENDERER_D2D >::OnEraseBkgnd( CDC * UNUSED( pDC ) )
	{
		BOOL bReturn = TRUE;

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

		return bReturn;
	}

	template< typename T >
	HBRUSH CTransparentCtrlT< T, eRENDERER_D2D >::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID )
	{
		pDC->SetBkMode( TRANSPARENT );
		return HBRUSH( ::GetStockObject( NULL_BRUSH ) );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::OnPaint()
	{
		if ( T::IsWindowVisible() )
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

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::OnSize( UINT type, int cx, int cy )
	{
		BaseType::OnSize( type, cx, cy );

		if ( m_pRenderTarget )
		{
			m_pRenderTarget->Resize( D2D1::SizeU( cx, cy ) );
		}

		m_bReinitBackground = true;
	}

	template< typename T >
	LRESULT CTransparentCtrlT< T, eRENDERER_D2D >::OnDisplayChange( WPARAM, LPARAM )
	{
		m_bReinitBackground = true;
		DoDraw();
		return 0;
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::OnSetFocus( CWnd * pOldWnd )
	{
		m_bFocused = true;
		BaseType::OnSetFocus( pOldWnd );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::OnKillFocus( CWnd * pNewWnd )
	{
		m_bFocused = false;
		BaseType::OnKillFocus( pNewWnd );
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_D2D >::OnMouseMove( UINT nFlags, CPoint point )
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
	LRESULT CTransparentCtrlT< T, eRENDERER_D2D >::OnMouseLeave( WPARAM UNUSED( wParam ), LPARAM UNUSED( lParam ) )
	{
		m_bMouseOver = false;
		BaseType::Invalidate();
		BaseType::OnMouseLeave();
		return 0;
	}
#endif
}