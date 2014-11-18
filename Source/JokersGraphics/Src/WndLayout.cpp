#include "stdafx.h"

#include "WndLayout.h"

namespace Joker
{
	CWndLayout::CWndLayout()
		:	m_hParent( NULL )
	{
	}

	CWndLayout::~CWndLayout()
	{
	}

	void CWndLayout::Create( HWND hParent, LPRECT rcFixedBorders )
	{
		m_hParent = hParent;
		memcpy( &m_rcFixedBorders, rcFixedBorders, sizeof( RECT ) );
		DoUpdateSize();
		m_rcOriginal = m_rcCurrent;
	}

	void CWndLayout::Resize()
	{
		if( m_hParent )
		{
			DoUpdateSize();
			DoResize();
			RECT rcCurrent( m_rcCurrent );
			::OffsetRect( &rcCurrent, m_rcFixedBorders.left, m_rcFixedBorders.top );
			rcCurrent.left		-= m_rcFixedBorders.left;
			rcCurrent.right		+= m_rcFixedBorders.right;
			rcCurrent.top		-= m_rcFixedBorders.top;
			rcCurrent.bottom	+= m_rcFixedBorders.bottom;
			::InvalidateRect( m_hParent, &rcCurrent, TRUE );
		}
	}

	void CWndLayout::DoUpdateSize()
	{
		::GetClientRect( m_hParent, &m_rcCurrent );
		m_rcCurrent.left	+= m_rcFixedBorders.left;
		m_rcCurrent.right	-= m_rcFixedBorders.right;
		m_rcCurrent.top		+= m_rcFixedBorders.top;
		m_rcCurrent.bottom	-= m_rcFixedBorders.bottom;
		::OffsetRect( &m_rcCurrent, -m_rcFixedBorders.left, -m_rcFixedBorders.top );
	}
}
