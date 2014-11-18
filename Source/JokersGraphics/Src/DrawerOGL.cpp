#include "stdafx.h"

#include "DrawerOGL.h"
#include "Logger.h"

#ifdef DrawText
#	undef DrawText
#endif

namespace Joker
{
#if DEF_USING_OGL
	IGL2DFactory 	*	CDrawer< eRENDERER_OGL >:: m_pFactory		= NULL;
	IDWriteFactory *	CDrawer< eRENDERER_OGL >:: m_pWriteFactory	= NULL;
	int					CDrawer< eRENDERER_OGL >:: m_iReferences	= 0;

	CDrawer< eRENDERER_OGL >::CDrawer()
		:	CDrawerDC()
		,	m_pRenderTarget( NULL )
		,	m_pDcRenderTarget( NULL )
		,	m_pBmpRenderTarget( NULL )
		,	m_pOGLBitmap( NULL )
	{
		DoInitOGL();
	}

	CDrawer< eRENDERER_OGL >::CDrawer( HDC hDC, CRect const & rcRect, BOOL bOwn )
		:	CDrawerDC( hDC, rcRect, bOwn )
		,	m_pRenderTarget( NULL )
		,	m_pDcRenderTarget( NULL )
		,	m_pBmpRenderTarget( NULL )
		,	m_pOGLBitmap( NULL )
	{
		DoInitOGL();
		DoInitDeviceDependent();
	}

	CDrawer< eRENDERER_OGL >::CDrawer( CDrawer const & drawer )
		:	CDrawerDC( drawer )
		,	m_pRenderTarget( NULL )
		,	m_pDcRenderTarget( NULL )
		,	m_pBmpRenderTarget( NULL )
		,	m_pOGLBitmap( NULL )
	{
		DoInitOGL();
		DoInitDeviceDependent();
	}

	CDrawer< eRENDERER_OGL >::~CDrawer()
	{
		// Afin que le destructeur ne lance pas d'exception on fait la finalisation de dessin dans un try catch
		try
		{
			DoCleanupDeviceDependent();
		}
		catch ( ... )
		{
		}

		SafeRelease( m_pDcRenderTarget );
		DoReleaseDC();

		m_iReferences--;

		if ( m_iReferences <= 0 )
		{
			SafeRelease( m_pFactory );
			SafeRelease( m_pWriteFactory );
		}
	}

	void CDrawer< eRENDERER_OGL >::BeginDraw( HDC hDC, CRect const & rcRect, BOOL bOwn )
	{
		DoSetDC( hDC, rcRect, bOwn );
		DoInitDeviceDependent();

		if ( m_pRenderTarget )
		{
			m_pRenderTarget->BeginDraw();
			m_pRenderTarget->Clear( GL2D::ColorF( 0, 0.0f ) );
		}
	}

	void CDrawer< eRENDERER_OGL >::EndDraw()
	{
		if ( m_pRenderTarget )
		{
			m_pRenderTarget->EndDraw();

			if ( m_pRenderTarget == m_pBmpRenderTarget )
			{
				IGL2DBitmap * pBitmap = NULL;
				HRESULT hr = m_pBmpRenderTarget->GetBitmap( & pBitmap );

				if ( hr == S_OK )
				{
					m_pDcRenderTarget->BeginDraw();
					m_pDcRenderTarget->DrawBitmap( pBitmap, GL2D::RectF( FLOAT( m_rcRect.left ), FLOAT( m_rcRect.top ), FLOAT( m_rcRect.right ), FLOAT( m_rcRect.bottom ) ) );
					m_pDcRenderTarget->EndDraw();
				}
			}
		}

		DoReleaseDC();
		DoCleanupDeviceDependent();
	}

	void CDrawer< eRENDERER_OGL >::CreateBackbuffer( CRect const & UNUSED( rcRect ) )
	{
	}

	void CDrawer< eRENDERER_OGL >::Finalise()
	{
	}

	void CDrawer< eRENDERER_OGL >::DrawLine( int iPenHeight, COLORREF cPenColour, CPoint const & ptOrign, CPoint const & ptDest, int iPenStyle )
	{
		IGL2DStrokeStyle * pStroke;
		IGL2DBrush * pBrush;
		float tmp[2] = { 50, 50 };

		m_pFactory->CreateStrokeStyle( GL2D::StrokeStyleProperties( GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_LINE_JOIN_MITER, FLOAT( iPenHeight ), GL2D_DASH_STYLE( iPenStyle ), FLOAT( iPenHeight ) ), tmp, 2, & pStroke );
		pBrush = DoCreateSolidBrush( cPenColour );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( ptOrign.x ), FLOAT( ptOrign.y ) ), GL2D::Point2F( FLOAT( ptDest.x ), FLOAT( ptDest.y ) ), pBrush, FLOAT( iPenHeight ), pStroke );

		SafeRelease( pStroke );
		SafeRelease( pBrush );
	}

	void CDrawer< eRENDERER_OGL >::DrawLine( CPoint const & ptOrign, CPoint const & ptDest, double dRatio )
	{
		LOGPEN logPen = {0};
		IGL2DStrokeStyle * pStroke;
		IGL2DBrush * pBrush;
		float tmp[2] = { 50, 50 };

		::GetObject( m_hCurrentPen, sizeof( LOGPEN ), & logPen );

		m_pFactory->CreateStrokeStyle( GL2D::StrokeStyleProperties( GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_LINE_JOIN_MITER, FLOAT( logPen.lopnWidth.x ), GL2D_DASH_STYLE( logPen.lopnStyle ), FLOAT( logPen.lopnWidth.x ) ), tmp, 2, & pStroke );
		pBrush = DoCreateSolidBrush( logPen.lopnColor );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( ptOrign.x * dRatio ), FLOAT( ptOrign.y * dRatio ) ), GL2D::Point2F( FLOAT( ptDest.x * dRatio ), FLOAT( ptDest.y * dRatio ) ), pBrush, FLOAT( logPen.lopnWidth.x ), pStroke );

		SafeRelease( pStroke );
		SafeRelease( pBrush );
	}

	void CDrawer< eRENDERER_OGL >::DrawRect( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CRect const & rcRect, double dRatio )
	{
		IGL2DBrush * pBrush = DoCreateSolidBrush( cBrushColour );
		m_pRenderTarget->FillRectangle( GL2D::RectF( float( rcRect.left * dRatio ), float( rcRect.top * dRatio ), float( rcRect.right * dRatio ), float( rcRect.bottom * dRatio ) ), pBrush );
		SafeRelease( pBrush );

		DrawVoidRect( iPenHeight, cPenColour, rcRect, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::DrawVoidRect( int iPenHeight, COLORREF cPenColour, CRect const & rcRect, double dRatio )
	{
		IGL2DBrush * pBrush;
		IGL2DStrokeStyle * pStroke;
		float tmp[2] = { 50, 50 };
		float fWidth = float( dRatio * iPenHeight );

		m_pFactory->CreateStrokeStyle( GL2D::StrokeStyleProperties( GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_CAP_STYLE_SQUARE, GL2D_LINE_JOIN_MITER, fWidth, GL2D_DASH_STYLE_SOLID, fWidth ), tmp, 2, & pStroke );
		pBrush = DoCreateSolidBrush( cPenColour );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( dRatio * rcRect.left ),	FLOAT( dRatio * rcRect.top ) ), GL2D::Point2F( FLOAT( dRatio * rcRect.right - fWidth ),	FLOAT( dRatio * rcRect.top ) ), pBrush, fWidth, pStroke );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( dRatio * rcRect.right - fWidth ),	FLOAT( dRatio * rcRect.top ) ), GL2D::Point2F( FLOAT( dRatio * rcRect.right - fWidth ),	FLOAT( dRatio * rcRect.bottom - fWidth ) ), pBrush, fWidth, pStroke );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( dRatio * rcRect.right - fWidth ),	FLOAT( dRatio * rcRect.bottom - fWidth ) ), GL2D::Point2F( FLOAT( dRatio * rcRect.left ),	FLOAT( dRatio * rcRect.bottom - fWidth ) ), pBrush, fWidth, pStroke );
		m_pRenderTarget->DrawLine( GL2D::Point2F( FLOAT( dRatio * rcRect.left ),	FLOAT( dRatio * rcRect.bottom - fWidth ) ), GL2D::Point2F( FLOAT( dRatio * rcRect.left ),	FLOAT( dRatio * rcRect.top ) ), pBrush, fWidth, pStroke );

		SafeRelease( pStroke );
		SafeRelease( pBrush );
	}

	LONG CDrawer< eRENDERER_OGL >::DrawText( String const & strText, LPRECT pRect, UINT uiFormat, double dRatio )
	{
		CRect rcRect( LONG( pRect->left * dRatio ), LONG( pRect->top * dRatio ), LONG( pRect->right * dRatio ), LONG( pRect->bottom * dRatio ) );
		DWRITE_FONT_STYLE style = m_pCurrentFont->IsItalic() ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
		IGL2DBrush * pBrush = NULL;
		IDWriteTextFormat * pTextFormat = NULL;
		IDWriteTextLayout * pTextLayout = NULL;
		HRESULT hr;

		if ( uiFormat & DT_CALCRECT )
		{
			m_pCurrentFont->Select( m_hDC );
#if defined( _UNICODE )
			::DrawTextW( m_hDC, strText.c_str(), strText.size(), rcRect, uiFormat );
#else
			::DrawTextA( m_hDC, strText.c_str(), strText.size(), rcRect, uiFormat );
#endif
			m_pCurrentFont->Deselect( m_hDC );
			pRect->left = LONG( rcRect.left / dRatio );
			pRect->right = 1 + LONG( 1.0f + float( rcRect.right ) / dRatio );
			pRect->top = LONG( rcRect.top / dRatio );
			pRect->bottom = LONG( rcRect.bottom / dRatio );
		}
		else
		{
			hr = m_pWriteFactory->CreateTextFormat( m_pCurrentFont->GetFaceName().c_str(), NULL, DWRITE_FONT_WEIGHT( m_pCurrentFont->GetWeight() ), style, DWRITE_FONT_STRETCH_NORMAL, FLOAT( abs( m_pCurrentFont->GetHeight() * dRatio ) - 3 * dRatio ), L"", & pTextFormat );

			if ( hr == S_OK )
			{
				if ( uiFormat & DT_VCENTER )
				{
					pTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
				}
				else if ( uiFormat & DT_BOTTOM )
				{
					pTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_FAR );
				}
				else
				{
					pTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_NEAR );
				}

				if ( uiFormat & DT_CENTER )
				{
					pTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER );
				}
				else if ( uiFormat & DT_RIGHT )
				{
					pTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_TRAILING );
				}
				else
				{
					pTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_LEADING );
				}

				if ( uiFormat & DT_SINGLELINE )
				{
					pTextFormat->SetWordWrapping( DWRITE_WORD_WRAPPING_NO_WRAP );
				}
				else if ( uiFormat & DT_WORDBREAK )
				{
					pTextFormat->SetWordWrapping( DWRITE_WORD_WRAPPING_WRAP );
				}

				if ( uiFormat & DT_RTLREADING )
				{
					pTextFormat->SetReadingDirection( DWRITE_READING_DIRECTION_RIGHT_TO_LEFT );
				}
				else
				{
					pTextFormat->SetReadingDirection( DWRITE_READING_DIRECTION_LEFT_TO_RIGHT );
				}

				hr = m_pWriteFactory->CreateTextLayout( CStrUtils::ToWStr( strText ).c_str(), strText.size(), pTextFormat, FLOAT( rcRect.Width() ), FLOAT( rcRect.Height() ), & pTextLayout );
			}

			if ( hr == S_OK )
			{
				pBrush = DoCreateSolidBrush( m_crForeground );
				m_pRenderTarget->DrawTextLayout( GL2D::Point2F( FLOAT( rcRect.left ), FLOAT( rcRect.top ) ), pTextLayout, pBrush, GL2D_DRAW_TEXT_OPTIONS_NONE );
			}
		}

		SafeRelease( pBrush );
		SafeRelease( pTextFormat );
		SafeRelease( pTextLayout );

		return 0;
	}

	void CDrawer< eRENDERER_OGL >::BitBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, DWORD dwRop )
	{
		DoDrawBitmap( *static_cast< CDrawerDC * >( pDrawer ), CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), *static_cast< CDrawerDC * >( pDrawer ), CRect( CPoint( xOrigin, yOrigin ), CSize( m_rcRect.Width() - ( xOrigin - m_rcRect.left ), m_rcRect.Height() - ( yOrigin - m_rcRect.top ) ) ), dwRop & SRCCOPY );
	}

	void CDrawer< eRENDERER_OGL >::StretchBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwRop )
	{
		DoDrawBitmap( *static_cast< CDrawerDC * >( pDrawer ), CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), *static_cast< CDrawerDC * >( pDrawer ), CRect( CPoint( xOrigin, yOrigin ), CSize( cxOrigin, cyOrigin ) ), dwRop & SRCCOPY );
	}

	void CDrawer< eRENDERER_OGL >::TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF UNUSED( crTransparent ) )
	{
		DoDrawBitmap( *static_cast< CDrawerDC * >( pDrawer ), CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), *static_cast< CDrawerDC * >( pDrawer ), CRect( CPoint( xOrigin, yOrigin ), CSize( cxOrigin, cyOrigin ) ), TRUE );
	}

	void CDrawer< eRENDERER_OGL >::AttachImage( ImagePtr pImage )
	{
		if ( m_pOGLBitmap )
		{
			DetachImage();
		}

		DoAttachImage( pImage );
		CSize size;
		std::vector< BYTE > arrayBits;

		if ( DoGetBitmapInfos( pImage->GetDC(), *pImage, size, arrayBits ) )
		{
			GL2D_BITMAP_PROPERTIES props = GL2D::BitmapProperties( GL2D::PixelFormat( GL2D_GL_FORMAT_BGRA, GL2D_GL_INTERNAL_RGBA8, GL2D_GL_TYPE_BYTE ) );
			m_pRenderTarget->CreateBitmap( GL2D::SizeU( size.cx, size.cy ), & arrayBits[0], size.cx * 4, props, & m_pOGLBitmap );
		}

		pImage->ReleaseDC();
		ASSERT( m_pOGLBitmap );
	}

	void CDrawer< eRENDERER_OGL >::DetachImage()
	{
		ASSERT( m_pOGLBitmap );
		DoDetachImage();
		SafeRelease( m_pOGLBitmap );
	}

	void CDrawer< eRENDERER_OGL >::StretchBlt( CRect const & rcDest, DWORD dwROP, double dRatio )
	{
		StretchBlt( rcDest, m_rcRect, dwROP, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::StretchBlt( int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio )
	{
		StretchBlt( CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), m_rcRect, dwROP, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::StretchBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio )
	{
		StretchBlt( CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), CRect( CPoint( xOrigin, yOrigin ), CSize( cxOrigin, cyOrigin ) ), dwROP, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::StretchBlt( CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio )
	{
		DoDrawBitmap( CRect( LONG( rcDest.left * dRatio ), LONG( rcDest.top * dRatio ), LONG( rcDest.right * dRatio ), LONG( rcDest.bottom * dRatio ) ), m_pOGLBitmap, rcOrigin, dwROP & SRCCOPY );
	}

	void CDrawer< eRENDERER_OGL >::TransparentBlt( CRect const & rcDest, COLORREF crTransparent, double dRatio )
	{
		TransparentBlt( rcDest, m_rcRect, crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio )
	{
		TransparentBlt( CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), m_rcRect, crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio )
	{
		TransparentBlt( CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), CRect( CPoint( xOrigin, yOrigin ), CSize( cxOrigin, cyOrigin ) ), crTransparent, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::TransparentBlt( CRect const & rcDest, CRect const & rcOrigin, COLORREF UNUSED( crTransparent ), double dRatio )
	{
		DoDrawBitmap( CRect( LONG( rcDest.left * dRatio ), LONG( rcDest.top * dRatio ), LONG( rcDest.right * dRatio ), LONG( rcDest.bottom * dRatio ) ), m_pOGLBitmap, rcOrigin, TRUE );
	}

	void CDrawer< eRENDERER_OGL >::AlphaBlend( CRect const & rcDest, double dRatio )
	{
		AlphaBlend( rcDest, m_rcRect, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, double dRatio )
	{
		AlphaBlend( CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), m_rcRect, dRatio );
	}

	void CDrawer< eRENDERER_OGL >::AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio )
	{
		AlphaBlend( CRect( CPoint( xDest, yDest ), CSize( cxDest, cyDest ) ), CRect( CPoint( xOrigin, yOrigin ), CSize( cxOrigin, cyOrigin ) ), dRatio );
	}

	void CDrawer< eRENDERER_OGL >::AlphaBlend( CRect const & rcDest, CRect const & rcSource, double dRatio )
	{
		DoDrawBitmap( CRect( LONG( rcDest.left * dRatio ), LONG( rcDest.top * dRatio ), LONG( rcDest.right * dRatio ), LONG( rcDest.bottom * dRatio ) ), m_pOGLBitmap, rcSource, TRUE );
	}

	void CDrawer< eRENDERER_OGL >::FillRect( RECT const * pRect, HBRUSH hBrush )
	{
		IGL2DBrush * pBrush;
		pBrush = DoCreateSolidBrush( hBrush );
		m_pRenderTarget->FillRectangle( GL2D::RectF( float( pRect->left ), float( pRect->top ), float( pRect->right ), float( pRect->bottom ) ), pBrush );
		SafeRelease( pBrush );
	}

	void CDrawer< eRENDERER_OGL >::Ellipse( int left, int top, int right, int bottom )
	{
		FLOAT fWidth = FLOAT( right ) - FLOAT( left );
		FLOAT fHeight = FLOAT( bottom ) - FLOAT( top );
		FLOAT fxCenter = FLOAT( left ) + fWidth;
		FLOAT fyCenter = FLOAT( top ) + fHeight;
		GL2D_ELLIPSE ellipse = GL2D::Ellipse( GL2D::Point2F( fxCenter, fyCenter ), fWidth, fHeight );
		IGL2DBrush * pBrush;

		if ( m_hCurrentBrush )
		{
			pBrush = DoCreateSolidBrush( m_hCurrentBrush );
		}
		else
		{
			pBrush = DoCreateSolidBrush( COLORREF( 0 ) );
		}

		m_pRenderTarget->FillEllipse( & ellipse, pBrush );
		SafeRelease( pBrush );

		if ( m_hCurrentPen )
		{
			LOGPEN logPen = {0};
			::GetObject( m_hCurrentPen, sizeof( LOGPEN ), & logPen );
			pBrush = DoCreateSolidBrush( logPen.lopnColor );
		}
		else
		{
			pBrush = DoCreateSolidBrush( COLORREF( 0 ) );
		}

		m_pRenderTarget->DrawEllipse( & ellipse, pBrush );
		SafeRelease( pBrush );
	}

	CDrawerBase * CDrawer< eRENDERER_OGL >::CreateCompatibleDrawer()
	{
		HDC hDC = ::CreateCompatibleDC( m_hDC );
		return new CDrawer< eRENDERER_OGL >( hDC, m_rcRect, TRUE );
	}

	HBITMAP CDrawer< eRENDERER_OGL >::CreateCompatibleBitmap( int iWidth, int iHeight )
	{
		return ::CreateCompatibleBitmap( m_hDC, iWidth, iHeight );
	}

	void CDrawer< eRENDERER_OGL >::DoInitOGL()
	{
		HRESULT hr = S_OK;

		if ( !m_pFactory )
		{
			hr = GL2DCreateFactory( GL2D_FACTORY_TYPE_SINGLE_THREADED, & m_pFactory );
		}

		if ( !m_pWriteFactory && hr == S_OK )
		{
			hr = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof( IDWriteFactory ), reinterpret_cast< IUnknown ** >( & m_pWriteFactory ) );
		}

		m_iReferences++;

		GL2D_RENDER_TARGET_PROPERTIES d2d1Props = GL2D::RenderTargetProperties(
					GL2D_RENDER_TARGET_TYPE_DEFAULT,
					GL2D::PixelFormat( GL2D_GL_FORMAT_BGRA, GL2D_GL_INTERNAL_RGBA8, GL2D_GL_TYPE_BYTE ),
					0,
					0,
					GL2D_RENDER_TARGET_USAGE_NONE,
					GL2D_FEATURE_LEVEL_DEFAULT
				);

		if ( hr == S_OK )
		{
			hr = m_pFactory->CreateDCRenderTarget( & d2d1Props, & m_pDcRenderTarget );
		}
		else
		{
			throw std::exception( "Impossible d'initialiser Direct2D" );
		}

		if ( hr != S_OK )
		{
			throw std::exception( "Impossible d'initialiser IGL2DDCRenderTarget" );
		}
	}

	void CDrawer< eRENDERER_OGL >::DoInitDeviceDependent()
	{
		HRESULT hr = S_OK;

		if ( hr == S_OK )
		{
			hr = m_pDcRenderTarget->BindDC( m_hDC, m_rcRect );
		}

		if ( hr == S_OK )
		{
			hr = m_pDcRenderTarget->CreateCompatibleRenderTarget( & m_pBmpRenderTarget );
		}

		if ( hr == S_OK )
		{
			m_pRenderTarget = m_pBmpRenderTarget;
		}
		else
		{
			ASSERT( FALSE );
			m_pRenderTarget = m_pDcRenderTarget;
		}
	}

	void CDrawer< eRENDERER_OGL >::DoCleanupDeviceDependent()
	{
		if ( m_pRenderTarget && m_pRenderTarget == m_pBmpRenderTarget )
		{
			SafeRelease( m_pBmpRenderTarget );
		}
	}

	bool CDrawer< eRENDERER_OGL >::DoGetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits )
	{
		bool bReturn = false;
		BITMAPINFO bmiSrc = { { sizeof( BITMAPINFOHEADER ), 0, 0, 0, 0, 0 } };

		// On récupère tout d'abord les infos du HBITMAP (dimensions, bpp, taille en bytes)
		if ( ::GetDIBits( hDC, hBitmap, 0, 1, NULL, & bmiSrc, DIB_RGB_COLORS ) )
		{
			size.cx = bmiSrc.bmiHeader.biWidth;
			size.cy = bmiSrc.bmiHeader.biHeight;
			BITMAPINFO bmi = { { sizeof( BITMAPINFOHEADER ), size.cx, size.cy, 1, 32, BI_RGB } };
			arrayBits.resize( bmiSrc.bmiHeader.biSizeImage * 32 / bmiSrc.bmiHeader.biBitCount, 0 );// Ici 32/bmiSrc.bmiHeader.biBitCount pour avoir la taille une fois convertie en 32 bpp (RGB 24 bits + alpha 8 bits)

			std::vector< BYTE > arrayBitsSrc( arrayBits.size(), 0 );

			// ON récupère maintenant le contenu de l'image que l'on met dans notre buffer à nous
			if ( ::GetDIBits( hDC, hBitmap, 0, size.cy, & arrayBitsSrc[0], & bmi, DIB_RGB_COLORS ) )
			{
				bReturn = true;
				UINT uiStep = size.cx * 4;

				// Pour Direct2D il faut inverser les lignes
				for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < size.cy ; ++GL2D_SIZE_I )
				{
					memcpy( & arrayBits[GL2D_SIZE_I * uiStep], & arrayBitsSrc[bmi.bmiHeader.biSizeImage - uiStep - GL2D_SIZE_I * uiStep], uiStep );
				}
			}
			else
			{
				CLogger::LogLastError( String( _T( "DoGetBitmapInfos - GetDIBits" ) ), false );
			}
		}
		else
		{
			CLogger::LogLastError( String( _T( "DoGetBitmapInfos - GetDIBits" ) ), false );
		}

		if ( !bReturn )
		{
			arrayBits.clear();
			size.cx = 0;
			size.cy = 0;
		}

		return bReturn;
	}

	void CDrawer< eRENDERER_OGL >::DoDrawBitmap( HDC hDC, CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL bSrcAlpha )
	{
		IGL2DBitmap * pBmp = NULL;
		CSize size;
		std::vector< BYTE > arrayBits;

		if ( DoGetBitmapInfos( hDC, hBitmap, size, arrayBits ) )
		{
			GL2D_BITMAP_PROPERTIES props = GL2D::BitmapProperties( GL2D::PixelFormat( GL2D_GL_FORMAT_BGRA, GL2D_GL_INTERNAL_RGBA8, GL2D_GL_TYPE_BYTE ) );
			m_pRenderTarget->CreateBitmap( GL2D::SizeU( size.cx, size.cy ), & arrayBits[0], size.cx * 4, props, & pBmp );
			DoDrawBitmap( rcDst, pBmp, rcSrc, bSrcAlpha );
			SafeRelease( pBmp );
		}
	}

	void CDrawer< eRENDERER_OGL >::DoDrawBitmap( CRect const & rcDst, ImagePtr pImage, CRect const & rcSrc, BOOL bSrcAlpha )
	{
		IGL2DBitmap * pBmp = NULL;
		CSize size( pImage->GetWidth(), pImage->GetHeight() );
		GL2D_BITMAP_PROPERTIES props = GL2D::BitmapProperties( GL2D::PixelFormat( GL2D_GL_FORMAT_BGRA, GL2D_GL_INTERNAL_RGBA8, GL2D_GL_TYPE_BYTE ) );
		m_pRenderTarget->CreateBitmap( GL2D::SizeU( size.cx, size.cy ), pImage->GetBits(), size.cx * 4, props, & pBmp );
		DoDrawBitmap( rcDst, pBmp, rcSrc, bSrcAlpha );
		SafeRelease( pBmp );
	}

	void CDrawer< eRENDERER_OGL >::DoDrawBitmap( CRect const & rcDst, IGL2DBitmap * pBitmap, CRect const & rcSrc, BOOL UNUSED( bSrcAlpha ) )
	{
		if ( pBitmap )
		{
			GL2D_RECT_F rcfSrc = GL2D::RectF( float( rcSrc.left ), float( rcSrc.top ), float( rcSrc.right ), float( rcSrc.bottom ) );
			GL2D_RECT_F rcfDst = GL2D::RectF( float( rcDst.left ), float( rcDst.top ), float( rcDst.right ), float( rcDst.bottom ) );
			m_pRenderTarget->DrawBitmap( pBitmap, rcfDst, 1.0f, GL2D_BITMAP_INTERPOLATION_MODE_LINEAR, rcfSrc );
		}
	}

	IGL2DBrush * CDrawer< eRENDERER_OGL >::DoCreateSolidBrush( COLORREF crColour )
	{
		IGL2DSolidColorBrush * pBrush = NULL;
		m_pRenderTarget->CreateSolidColorBrush( CColour::FromCOLORREF( crColour ).ToGL2DColor(), & pBrush );
		return pBrush;
	}

	IGL2DBrush * CDrawer< eRENDERER_OGL >::DoCreateSolidBrush( HBRUSH hBrush )
	{
		IGL2DBrush * pReturn = NULL;

		if ( hBrush == ::GetStockObject( HOLLOW_BRUSH ) )
		{
			m_pRenderTarget->CreateSolidColorBrush( GL2D::ColorF( 0, 0.0f ), reinterpret_cast< IGL2DSolidColorBrush ** >( & pReturn ) );
		}
		else
		{
			LOGBRUSH logBrush = {0};
			::GetObject( hBrush, sizeof( LOGBRUSH ), & logBrush );
			pReturn = DoCreateSolidBrush( logBrush.lbColor );
		}

		return pReturn;
	}
#endif
}