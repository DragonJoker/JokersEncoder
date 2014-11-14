#include "stdafx.h"

#include "Drawer.h"
#include "Logger.h"

#ifdef DrawText
#	undef DrawText
#endif

namespace Joker
{
	CDrawerDC::CDrawerDC()
		:	CDrawerBase			()
		,	m_hDC				( NULL				)
		,	m_bOwnDc			( TRUE				)
		,	m_initialFont		( _T( "Arial" ), 14	)
		,	m_pCurrentFont		( & m_initialFont	)
		,	m_pOldFont			( NULL				)
		,	m_crForeground		( NULL				)
		,	m_crBackground		( NULL				)
		,	m_hCurrentPen		( NULL				)
		,	m_hOldPen			( NULL				)
		,	m_hCurrentBrush		( NULL				)
		,	m_hOldBrush			( NULL				)
		,	m_hCurrentBitmap	( NULL				)
		,	m_hOldBitmap		( NULL				)
	{
	}

	CDrawerDC::CDrawerDC( HDC hDC, CRect const & rcRect, BOOL bOwn )
		:	CDrawerBase			( rcRect			)
		,	m_hDC				( hDC				)
		,	m_bOwnDc			( bOwn				)
		,	m_initialFont		( _T( "Arial" ), 14	)
		,	m_pCurrentFont		( & m_initialFont	)
		,	m_pOldFont			( NULL				)
		,	m_crForeground		( NULL				)
		,	m_crBackground		( NULL				)
		,	m_hCurrentPen		( NULL				)
		,	m_hOldPen			( NULL				)
		,	m_hCurrentBrush		( NULL				)
		,	m_hOldBrush			( NULL				)
		,	m_hCurrentBitmap	( NULL				)
		,	m_hOldBitmap		( NULL				)
	{
		DoSetDC( hDC, rcRect, bOwn );
	}

	CDrawerDC::CDrawerDC( CDrawerDC const & drawer )
		:	CDrawerBase			( drawer					)
		,	m_hDC				( drawer.m_hDC				)
		,	m_bOwnDc			( FALSE						)
		,	m_initialFont		( _T( "Arial" ), 14			)
		,	m_pCurrentFont		( & m_initialFont			)
		,	m_pOldFont			( drawer.m_pOldFont			)
		,	m_crForeground		( drawer.m_crForeground		)
		,	m_crBackground		( drawer.m_crBackground		)
		,	m_hCurrentPen		( drawer.m_hCurrentPen		)
		,	m_hOldPen			( drawer.m_hOldPen			)
		,	m_hCurrentBrush		( drawer.m_hCurrentBrush	)
		,	m_hOldBrush			( drawer.m_hOldBrush		)
		,	m_hCurrentBitmap	( drawer.m_hCurrentBitmap	)
		,	m_hOldBitmap		( drawer.m_hOldBitmap		)
	{
	}

	CDrawerDC::~CDrawerDC()
	{
		DoReleaseDC();
	}

	void CDrawerDC::DoReleaseDC()
	{
		if ( m_bOwnDc && m_hDC )
		{
			::DeleteDC( m_hDC );
			m_hDC = NULL;
			m_bOwnDc = TRUE;
		}
	}

	void CDrawerDC::DoSetDC( HDC hDC, CRect const & rcRect, BOOL bOwn )
	{
		DoReleaseDC();
		m_hDC = hDC;
		m_bOwnDc = bOwn;
		m_rcRect = rcRect;
		::SetStretchBltMode( m_hDC, HALFTONE );
		::SetBrushOrgEx( m_hDC, rcRect.left, rcRect.top, NULL );
		::SetBkMode( m_hDC, TRANSPARENT );
	}
}

#if DEF_USING_D2D
#	pragma comment( lib, "d2d1.lib" )
#endif
