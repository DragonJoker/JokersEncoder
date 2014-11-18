#pragma once

#include "Drawer.h"

namespace Joker
{
#if DEF_USING_D2D
	template <>
	class JGRA_API CDrawer< eRENDERER_D2D >
		: public CDrawerDC
	{
	public:
		CDrawer();
		CDrawer( HDC hDC, CRect const & rcRect, BOOL bOwn = FALSE );
		CDrawer( CDrawer const & drawer );
		virtual ~CDrawer();

		virtual void BeginDraw( HDC hDC, CRect const & rcRect, BOOL bOwn = FALSE );
		virtual void EndDraw();
		virtual void CreateBackbuffer( CRect const & rcRect );
		virtual void Finalise();
		virtual void DrawLine( int iPenHeight, COLORREF cPenColour, CPoint const & ptOrign, CPoint const & ptDest, int iPenStyle = PS_SOLID );
		virtual void DrawLine( CPoint const & ptOrign, CPoint const & ptDest, double dRatio = 1 );
		virtual void DrawRect( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CRect const & rcRect, double dRatio = 1 );
		virtual void DrawVoidRect( int iPenHeight, COLORREF cPenColour, CRect const & rcRect, double dRatio );
		virtual LONG DrawText( String const & strText, LPRECT pRect, UINT uiFormat, double dRatio = 1 );
		virtual void BitBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, DWORD dwRop );
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP );
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent );
		virtual void AttachImage( ImagePtr pImage );
		virtual	void DetachImage();
		virtual void StretchBlt( CRect const & rcDest, DWORD dwROP, double dRatio = 1 );
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio = 1 );
		virtual void StretchBlt( CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio = 1 );
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio = 1 );
		virtual void TransparentBlt( CRect const & rcDest, COLORREF crTransparent, double dRatio = 1 );
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio = 1 );
		virtual void TransparentBlt( CRect const & rcDest, CRect const & rcOrigin, COLORREF crTransparent, double dRatio = 1 );
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio = 1 );
		virtual void AlphaBlend( CRect const & rcDest, double dRatio = 1 );
		virtual void AlphaBlend( CRect const & rcDest, CRect const & rcSource, double dRatio = 1 );
		virtual void AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, double dRatio = 1 );
		virtual void AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio = 1 );
		virtual void FillRect( RECT const * pRect, HBRUSH hBrush );
		virtual void Ellipse( int left, int top, int right, int bottom );
		virtual	CDrawerBase * CreateCompatibleDrawer();
		virtual HBITMAP CreateCompatibleBitmap( int iWidth, int iHeight );

		virtual void SetFont( Joker::CFont & ca2iFont )
		{
			DoSetFont( ca2iFont );
		}
		virtual void UnsetFont( Joker::CFont & UNUSED( ca2iFont ) )
		{
			DoUnsetFont();
		}
		virtual COLORREF SetForegroundColour( COLORREF crColour )
		{
			return DoSetForegroundColour( crColour );
		}
		virtual COLORREF SetBackgroundColour( COLORREF crColour )
		{
			return DoSetBackgroundColour( crColour );
		}
		virtual HPEN SetPen( HPEN hPen )
		{
			return DoSetPen( hPen );
		}
		virtual HBRUSH SetBrush( HBRUSH hBrush )
		{
			return DoSetBrush( hBrush );
		}
		virtual HBITMAP SetBitmap( HBITMAP hBitmap )
		{
			return DoSetBitmap( hBitmap );
		}

	private:
		void DoInitD2D();
		void DoInitDeviceDependent();
		void DoCleanupDeviceDependent();
		bool DoGetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits );
		void DoDrawBitmap( HDC hDC, CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL bSrcAlpha = TRUE );
		void DoDrawBitmap( CRect const & rcDst, ImagePtr pImage, CRect const & rcSrc, BOOL bSrcAlpha = TRUE );
		void DoDrawBitmap( CRect const & rcDst, ID2D1Bitmap * pBitmap, CRect const & rcSrc, BOOL bSrcAlpha = TRUE );
		ID2D1Brush * DoCreateSolidBrush( COLORREF crColour );
		ID2D1Brush * DoCreateSolidBrush( HBRUSH hBrush );

	private:
		static ID2D1Factory * m_pFactory;
		static IDWriteFactory * m_pWriteFactory;
		static int m_iReferences;

		ID2D1DCRenderTarget * m_pDcRenderTarget;
		ID2D1BitmapRenderTarget * m_pBmpRenderTarget;
		ID2D1RenderTarget * m_pRenderTarget;
		ID2D1Bitmap * m_pD2DBitmap;
	};
#endif
}