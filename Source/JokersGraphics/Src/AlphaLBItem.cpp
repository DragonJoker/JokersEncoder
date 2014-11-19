#include "stdafx.h"

#include "AlphaLBItem.h"

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

namespace Joker
{
	CAlphaLBItem::CAlphaLBItem( CColour const & clMaskColour, CColour const & clText, bool bHasLine, CColour const & clLineColour, int iLineStyle )
		:	m_brushMask( clMaskColour )
		,	m_clLine( clLineColour )
		,	m_clText( clText )
		,	m_bHasLine( bHasLine )
		,	m_iLineStyle( iLineStyle )
	{
	}

	CAlphaLBItem::CAlphaLBItem( CAlphaLBItem const & item )
		:	m_brushMask( item.m_brushMask )
		,	m_clLine( item.m_clLine )
		,	m_clText( item.m_clText )
		,	m_bHasLine( item.m_bHasLine )
		,	m_iLineStyle( item.m_iLineStyle )
	{
	}

	CAlphaLBItem::~CAlphaLBItem()
	{
	}

	CAlphaLBItem & CAlphaLBItem::operator=( CAlphaLBItem const & item )
	{
		m_brushMask		= item.m_brushMask;
		m_clLine		= item.m_clLine;
		m_clText		= item.m_clText;
		m_bHasLine		= item.m_bHasLine;
		m_iLineStyle	= item.m_iLineStyle;
		return * this;
	}

	void CAlphaLBItem::AlphaBlend( CBitmapDC & bmpDC, CRect const & rcDest )
	{
		BLENDFUNCTION blendFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		bmpDC.AlphaBlend( rcDest, m_brushMask.GetDC(), m_brushMask.GetRect(), blendFunction );
	}
}
