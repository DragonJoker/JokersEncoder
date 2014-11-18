#include "stdafx.h"

#include "CursorBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CCursorBase::CCursorBase()
		:	m_bOwn( FALSE )
		,	m_hCurrentCursor( NULL )
		,	m_hBasicCursor( NULL )
	{
	}

	CCursorBase::~CCursorBase()
	{
		if ( m_bOwn )
		{
			DeleteObject( m_hCurrentCursor );
		}
	}

	HCURSOR CCursorBase::SetCursor( HCURSOR hCursor, BOOL bOwn )
	{
		if ( m_bOwn )
		{
			DeleteObject( m_hCurrentCursor );
		}

		m_bOwn = bOwn;
		HCURSOR hPrevious = m_hCurrentCursor;
		m_hCurrentCursor = hCursor;
		return hPrevious;
	}

	void CCursorBase::RestoreCursor()
	{
		m_hCurrentCursor = m_hBasicCursor;
	}
}
