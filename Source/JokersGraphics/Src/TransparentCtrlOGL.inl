namespace Joker
{
#if DEF_USING_OGL
	template< typename T > int CTransparentCtrlT< T, eRENDERER_OGL >::m_iReferences = 0;
	template< typename T > IDWriteFactory * CTransparentCtrlT< T, eRENDERER_OGL >::m_pWriteFactory = NULL;
	template< typename T > IGL2DFactory * CTransparentCtrlT< T, eRENDERER_OGL >::m_pFactory = NULL;

	template< typename T >
	CTransparentCtrlT< T, eRENDERER_OGL >::CTransparentCtrlT()
		:	m_bPainting			( false	 )
		,	m_bHasBackground	( false	 )
		,	m_brushMask			( CColour( CColour::Transparent ) )
		,	m_clText			( CColour( CColour::FullAlphaBlack ) )
		,	m_clBorder			( CColour( CColour::FullAlphaBlack ) )
		,	m_bHasBorder		( true	)
		,	m_bFocused			( false	 )
		,	m_bMouseOver		( false )
		,	m_pHwndRenderTarget	( NULL )
		,	m_pBmpRenderTarget	( NULL )
		,	m_pRenderTarget		( NULL )
		,	m_eRenderer			( eRENDERER_OGL )
		,	m_bReinitBackground	( false )
	{
		DoInitDeviceIndependent();
	}

	template< typename T >
	CTransparentCtrlT< T, eRENDERER_OGL >::~CTransparentCtrlT()
	{
		Release();
		DoCleanupDeviceIndependent();
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_OGL >::SetBorderColour( CColour const & clColour )
	{
		m_clBorder = clColour;
		Invalidate();
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_OGL >::SetTextColour( CColour const & clColour )
	{
		m_clText = clColour;
		Invalidate();
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_OGL >::GetRelativeRect( CRect & rcRect )
	{
		CRect l_rcRect1, l_rcRect2;
		GetWindowRect( l_rcRect1 );
		CWnd * pParent = GetParent();

		if ( pParent )
		{
			pParent->GetWindowRect( l_rcRect2 );
		}

		rcRect.left = l_rcRect1.left - l_rcRect2.left;
		rcRect.top = l_rcRect1.top - l_rcRect2.top;
		rcRect.right = rcRect.left + l_rcRect1.Width();
		rcRect.bottom = rcRect.top + l_rcRect1.Height();
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_OGL >::Release()
	{
		DoRelease();
		DoCleanupDeviceDependent();
	}

	template< typename T >
	inline void CTransparentCtrlT< T, eRENDERER_OGL >::Draw()
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
				m_pRenderTarget->Clear( CColour( CColour::Transparent ).ToGL2DColor() );

				// On dessine l'arri�re plan
				DoDrawBackground( rcRect );

				// On dessine le premier plan
				DoDrawForeground( rcRect );

				m_pRenderTarget->EndDraw();

				if ( m_pRenderTarget == m_pBmpRenderTarget )
				{
					IGL2DBitmap * pBitmap = NULL;
					HRESULT hr = m_pBmpRenderTarget->GetBitmap( & pBitmap );

					if ( hr == S_OK )
					{
						m_pHwndRenderTarget->BeginDraw();
						m_pHwndRenderTarget->DrawBitmap( pBitmap, GL2D::RectF( FLOAT( rcRect.left ), FLOAT( rcRect.top ), FLOAT( rcRect.right ), FLOAT( rcRect.bottom ) ) ); 
						m_pHwndRenderTarget->EndDraw();
					}
				}
			}
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoDrawBackground( CRect const & rcRect )
	{
		// On met l'image d'arri�re plan dans le backbuffer
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

		if ( ! csText.IsEmpty() )
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
	bool CTransparentCtrlT< T, eRENDERER_OGL >::GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
	{
		bool bReturn = false;
		BITMAPINFO bmiSrc = { { sizeof( BITMAPINFOHEADER ), 0, 0, 0, 0, 0 } };

		if ( ::GetDIBits( hDC, hBitmap, 0, 1, NULL, & bmiSrc, DIB_RGB_COLORS ) )
		{
			size.cx = bmiSrc.bmiHeader.biWidth;
			size.cy = bmiSrc.bmiHeader.biHeight;
			BITMAPINFO bmi = { { sizeof( BITMAPINFOHEADER ), size.cx, size.cy, 1, 32, BI_RGB } };
			arrayBits.resize( bmiSrc.bmiHeader.biSizeImage, 0 );

			std::vector< BYTE > arrayBitsSrc( bmiSrc.bmiHeader.biSizeImage, 0 );

			if ( ::GetDIBits( hDC, hBitmap, 0, size.cy, & arrayBitsSrc[0], & bmi, DIB_RGB_COLORS ) )
			{
				bReturn = true;
				UINT uiStep = size.cx * 4;

				for ( int i = 0 ; i < size.cy ; ++i )
				{
					memcpy( & arrayBits[i * uiStep], & arrayBitsSrc[bmi.bmiHeader.biSizeImage - uiStep - i * uiStep], uiStep );
				}
			}
		}

		if ( ! bReturn )
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
		IGL2DBitmap * pBmp = NULL;
		CSize size;
		std::vector< BYTE > arrayBits;

		if ( GetBitmapInfos( m_hDC, hBitmap, size, arrayBits ) )
		{
			GL2D_BITMAP_PROPERTIES props = GL2D::BitmapProperties( GL2D::PixelFormat( GL2D_GL_FORMAT_BGRA, GL2D_GL_INTERNAL_RGBA8, GL2D_GL_TYPE_BYTE ) );
			m_pRenderTarget->CreateBitmap( GL2D::SizeU( size.cx, size.cy ), & arrayBits[0], size.cx * 4, props, & pBmp );

			if ( pBmp )
			{
				GL2D_RECT_F rcfSrc = GL2D::RectF( float( rcSrc.left ), float( rcSrc.top ), float( rcSrc.right ), float( rcSrc.bottom ) );
				GL2D_RECT_F rcfDst = GL2D::RectF( float( rcDst.left ), float( rcDst.top ), float( rcDst.right ), float( rcDst.bottom ) );
				m_pRenderTarget->DrawBitmap( pBmp, rcfDst, 1.0f, GL2D_BITMAP_INTERPOLATION_MODE_LINEAR, rcfSrc );
				SafeRelease( pBmp );
			}
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth, UINT uiStyle )
	{
		IGL2DStrokeStyle * pStroke = NULL;
		IGL2DSolidColorBrush * pBrush = NULL;
		float tmp[2] = { 50, 50 };
		HRESULT hr = m_pFactory->CreateStrokeStyle( GL2D::StrokeStyleProperties( GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_LINE_JOIN_MITER, FLOAT( iWidth ), GL2D_DASH_STYLE( uiStyle ), FLOAT( iWidth ) ), tmp, 2, & pStroke );

		if ( hr == S_OK )
		{
			hr = m_pRenderTarget->CreateSolidColorBrush( clColour.ToGL2DColor(), &pBrush );
		}

		if ( hr == S_OK )
		{
			m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.left			 ),	FLOAT( rcRect.top				 ) ), GL2D::Point2F( FLOAT( rcRect.right - iWidth	 ),	FLOAT( rcRect.top				 ) ), pBrush, FLOAT( iWidth ), pStroke );
			m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.right - iWidth	 ),	FLOAT( rcRect.top				 ) ), GL2D::Point2F( FLOAT( rcRect.right - iWidth	 ),	FLOAT( rcRect.bottom - iWidth	 ) ), pBrush, FLOAT( iWidth ), pStroke );
			m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.right - iWidth	 ),	FLOAT( rcRect.bottom - iWidth	 ) ), GL2D::Point2F( FLOAT( rcRect.left				 ),	FLOAT( rcRect.bottom - iWidth	 ) ), pBrush, FLOAT( iWidth ), pStroke );
			m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( rcRect.left			 ),	FLOAT( rcRect.bottom - iWidth	 ) ), GL2D::Point2F( FLOAT( rcRect.left				 ),	FLOAT( rcRect.top				 ) ), pBrush, FLOAT( iWidth ), pStroke );
		}

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
		HBITMAP hBitmap = HBITMAP( SelectObject( srcDC, NULL ) );
		DrawBitmap( rcDest, hBitmap, rcSrc );
		SelectObject( srcDC, hBitmap );
	}

	template< typename T >
	BOOL CTransparentCtrlT< T, eRENDERER_OGL >::SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		m_bReinitBackground = true;
		BOOL bReturn = T::SetWindowPos( pWndInsertAfter, x, y, cx, cy, uiFlags );
		return bReturn;
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoInitDeviceIndependent()
	{
		m_iReferences++;

		if ( !m_pFactory )
		{
			GL2DCreateFactory( GL2D_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory );
		}

		if ( !m_pWriteFactory )
		{
			DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof( IDWriteFactory ), reinterpret_cast< IUnknown ** >( &m_pWriteFactory ) );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoCleanupDeviceIndependent()
	{
		m_iReferences--;

		if ( m_iReferences <= 0 )
		{
			SafeRelease( m_pFactory );
			SafeRelease( m_pWriteFactory );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoInitDeviceDependent()
	{
		CRect rcRect;
		T::GetClientRect( rcRect );
		GL2D_SIZE_U size = GL2D::SizeU( rcRect.Width(), rcRect.Height() );
		HRESULT hr = m_pFactory->CreateHwndRenderTarget( GL2D::RenderTargetProperties(), GL2D::HwndRenderTargetProperties( m_hWnd, size ), &m_pHwndRenderTarget );

		if ( hr == S_OK )
		{
			m_pRenderTarget = m_pHwndRenderTarget;
		}
		else
		{
			CLogger::LogError( String( _T( "CreateHwndRenderTarget failed" ) ), false );
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoCleanupDeviceDependent()
	{
		if ( m_pRenderTarget )
		{
			SafeRelease( m_pBmpRenderTarget );
			SafeRelease( m_pHwndRenderTarget );
			m_pRenderTarget = NULL;
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::PreSubclassWindow()
	{
		BaseType::PreSubclassWindow();
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::DoInitialiseBackground()
	{
		CRect		rcRect;
		CDC *		pDC;
		int			iWidth;
		int			iHeight;
		CDC			memdc;
		CBitmap *	pOldbmp;
		CWnd *		pParent;

		pParent = BaseType::GetParent();

		if ( pParent )
		{
			GetWindowRect( &rcRect );
			pParent->ScreenToClient( &rcRect );

			pDC = pParent->GetDC();
			iWidth = rcRect.Width();
			iHeight = rcRect.Height();

			m_bmpBackground.DeleteObject();
			m_bmpBackground.CreateCompatibleBitmap( pDC, rcRect.Width(), rcRect.Height() );
			memdc.CreateCompatibleDC( pDC );

			pOldbmp = memdc.SelectObject( & m_bmpBackground );
			memdc.BitBlt( 0, 0, iWidth, iHeight, pDC, rcRect.left, rcRect.top, SRCCOPY );
			memdc.SelectObject( pOldbmp );
			pParent->ReleaseDC( pDC );
			m_bReinitBackground = false;
		}
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
			ON_WM_DESTROY()
			ON_WM_PAINT()
			ON_WM_SIZE()
			ON_MESSAGE( WM_DISPLAYCHANGE, OnDisplayChange )
			ON_WM_MOUSEMOVE()
			ON_MESSAGE( WM_MOUSELEAVE,	OnMouseLeave )
			ON_WM_SETFOCUS()
			ON_WM_KILLFOCUS()
			{0, 0, 0, 0, AfxSig_end, ( AFX_PMSG )0 }
		};
		static const AFX_MSGMAP messageMap =
		{
			& TheBaseClass::GetThisMessageMap, &_messageEntries[0]
		};
		return &messageMap;
	}
	PTM_WARNING_RESTORE

	template< typename T >
	BOOL CTransparentCtrlT< T, eRENDERER_OGL >::OnEraseBkgnd( CDC * UNUSED( pDC ) )
	{
		BOOL bReturn = TRUE;

		if ( m_bHasBackground )
		{
			if ( ! m_pHwndRenderTarget || m_hWnd != m_pHwndRenderTarget->GetHwnd() )
			{
				// Si on a d�truit la partie graphique du contr�le puis reconstruite, on doit r�initialiser la partie Device Dependant
				m_pRenderTarget = NULL;
				SafeRelease( m_pBmpRenderTarget );
				SafeRelease( m_pHwndRenderTarget );
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
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnDestroy()
	{
		Release();
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnPaint()
	{
		if ( IsWindowVisible() )
		{
			CPaintDC l_paintDC( this );
			m_bPainting = true;
			m_hDC = l_paintDC;
			Draw();
			m_hDC = NULL;
			m_bPainting = false;
		}
	}

	template< typename T >
	void CTransparentCtrlT< T, eRENDERER_OGL >::OnSize( UINT type, int cx, int cy )
	{
		BaseType::OnSize( type, cx, cy );

		if ( m_pHwndRenderTarget )
		{
			SafeRelease( m_pBmpRenderTarget );
			m_pHwndRenderTarget->Resize( GL2D::SizeU( cx, cy ) );

			if ( m_pHwndRenderTarget->CreateCompatibleRenderTarget( & m_pBmpRenderTarget ) == S_OK )
			{
				m_pRenderTarget = m_pBmpRenderTarget;
			}
			else
			{
				ASSERT( FALSE );
				m_pRenderTarget = m_pHwndRenderTarget;
			}
		}

		m_bReinitBackground = true;
	}

	template< typename T >
	LRESULT CTransparentCtrlT< T, eRENDERER_OGL >::OnDisplayChange( WPARAM, LPARAM )
	{
		m_bReinitBackground = true;
		Draw();
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