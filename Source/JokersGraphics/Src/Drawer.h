#pragma once

#include "DrawerBase.h"

namespace Joker
{
	class JGRA_API CDrawerDC
		: public CDrawerBase
	{
	public:
		CDrawerDC();
		CDrawerDC( HDC hDC, CRect const & rcRect, BOOL bOwn = FALSE );
		CDrawerDC( CDrawerDC const & drawer );
		virtual ~CDrawerDC();

		virtual void BeginDraw( HDC hDC, CRect const & rcRect, BOOL bOwn = FALSE ) = 0;
		virtual void EndDraw() = 0;

		inline operator HDC()const
		{
			return m_hDC;
		}
		inline operator HBITMAP()const
		{
			return m_hCurrentBitmap;
		}

	protected:
		void		DoReleaseDC();
		void		DoSetDC( HDC hDC, CRect const & rcRect, BOOL bOwn = FALSE );

		inline void		DoAttachImage( ImagePtr pImage )
		{
			m_pImage = pImage;
		}
		inline void		DoDetachImage()
		{
			m_pImage.reset();
		}
		inline COLORREF	DoSetForegroundColour( COLORREF crColour )
		{
			COLORREF crReturn = m_crForeground;
			m_crForeground = crColour;
			return crReturn;
		}
		inline COLORREF	DoSetBackgroundColour( COLORREF crColour )
		{
			COLORREF crReturn = m_crBackground;
			m_crBackground = crColour;
			return crReturn;
		}
		inline void		DoSetFont( Joker::CFont & ca2iFont )
		{
			m_pOldFont = m_pCurrentFont;
			m_pCurrentFont = & ca2iFont;
		}
		inline void		DoUnsetFont()
		{
			m_pCurrentFont = m_pOldFont;
			m_pOldFont = & m_initialFont;
		}
		inline HPEN		DoSetPen( HPEN hPen )
		{
			m_hOldPen = m_hCurrentPen;
			m_hCurrentPen = hPen;
			return m_hOldPen;
		}
		inline HBRUSH	DoSetBrush( HBRUSH hBrush )
		{
			m_hOldBrush = m_hCurrentBrush;
			m_hCurrentBrush = hBrush;
			return m_hOldBrush;
		}
		inline HBITMAP	DoSetBitmap( HBITMAP hBitmap )
		{
			m_hOldBitmap = m_hCurrentBitmap;
			m_hCurrentBitmap = hBitmap;
			return m_hOldBitmap;
		}

	protected:
		BOOL m_bOwnDc;
		HDC m_hDC;
		Joker::CFont m_initialFont;
		Joker::CFont * m_pCurrentFont;
		Joker::CFont * m_pOldFont;
		COLORREF m_crForeground;
		COLORREF m_crBackground;
		HPEN m_hCurrentPen;
		HPEN m_hOldPen;
		HBRUSH m_hCurrentBrush;
		HBRUSH m_hOldBrush;
		HBITMAP m_hCurrentBitmap;
		HBITMAP m_hOldBitmap;
		ImagePtr m_pImage;
	};

	template< eRENDERER Type > class CDrawer;
}