#pragma once

#include "Drawer.h"

namespace Joker
{
	template <>
	class JGRA_API CDrawer< eRENDERER_GDI >
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
		virtual void SetFont( Joker::CFont & ca2iFont );
		virtual void UnsetFont( Joker::CFont & ca2iFont );
		virtual void BitBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, DWORD dwRop );
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP );
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent );
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
		virtual COLORREF SetForegroundColour( COLORREF crColour );
		virtual COLORREF SetBackgroundColour( COLORREF crColour );
		virtual void FillRect( RECT const * pRect, HBRUSH hBrush );
		virtual void Ellipse( int left, int top, int right, int bottom );
		virtual	CDrawerBase * CreateCompatibleDrawer();
		virtual HBITMAP CreateCompatibleBitmap( int iWidth, int iHeight );

		virtual void AttachImage( ImagePtr pImage )
		{
			DoAttachImage( pImage );
		}
		virtual	void DetachImage()
		{
			DoDetachImage();
		}
		virtual HPEN SetPen( HPEN hPen )
		{
			DoSetPen( hPen );
			return SelectGdiObject( hPen );
		}
		virtual HBRUSH SetBrush( HBRUSH hBrush )
		{
			DoSetBrush( hBrush );
			return SelectGdiObject( hBrush );
		}
		virtual HBITMAP SetBitmap( HBITMAP hBitmap )
		{
			DoSetBitmap( hBitmap );
			return SelectGdiObject( hBitmap );
		}

	private:
		template< typename T >
		inline	T SelectGdiObject( T tObj )
		{
			return T( SelectObject( m_hDC, tObj ) );
		}
		HPEN DoCreateCustomPen( int iSize, COLORREF cColour, double dRatio, int iPenStyle = PS_SOLID );

	private:
		HDC m_hDcSaved;
		HBITMAP m_hBitmap;
		CRect m_rcBack;
	};
}