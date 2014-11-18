#include "stdafx.h"

#include "ScalableLayout.h"

namespace Joker
{
	CScalableLayout::CElement::CElement( HWND hElement, HWND hParent, LPRECT rcFixed, bool scalable, eHORIZ_ALIGN horiz, eVERTIC_ALIGN vertic )
		:	m_hElement( hElement )
		,	m_rcFixed( rcFixed )
		,	m_scalable( scalable )
		,	m_horizAlign( horiz )
		,	m_verticAlign( vertic )
	{
		CRect rcOriginal;
		::GetWindowRect( m_hElement, rcOriginal );
		m_ptOriginal = rcOriginal.TopLeft();
		::ScreenToClient( hParent, & m_ptOriginal );

		m_sizeOriginal.cx = rcOriginal.Width();
		m_sizeOriginal.cy = rcOriginal.Height();
		m_ptOriginal.x += -m_rcFixed->left;
		m_ptOriginal.y += -m_rcFixed->top;
	}

	void CScalableLayout::CElement ::Resize( double dX, double dY, LPRECT rcMaxExtent )
	{
		LONG iLeft = LONG( dX * m_ptOriginal.x );
		LONG iTop = LONG( dY * m_ptOriginal.y );
		LONG iWidth = LONG( dX * m_sizeOriginal.cx );
		LONG iHeight = LONG( dY * m_sizeOriginal.cy );

		if ( !m_scalable )
		{
			if ( m_horizAlign == eHORIZ_ALIGN_RIGHT )
			{
				iLeft = iLeft + iWidth - m_sizeOriginal.cx;
			}
			else if ( m_horizAlign == eHORIZ_ALIGN_CENTER )
			{
				iLeft = iLeft + ( iWidth - m_sizeOriginal.cx ) / 2;
			}

			if ( m_verticAlign == eVERTIC_ALIGN_BOTTOM )
			{
				iTop = iTop + iHeight - m_sizeOriginal.cy;
			}
			else if ( m_verticAlign == eVERTIC_ALIGN_CENTER )
			{
				iTop = iTop + ( iHeight - m_sizeOriginal.cy ) / 2;
			}

			iWidth = m_sizeOriginal.cx;
			iHeight = m_sizeOriginal.cy;
		}

		if( iLeft < rcMaxExtent->left )
		{
			iLeft = rcMaxExtent->left;
		}
		else if( iLeft > rcMaxExtent->right - iWidth )
		{
			iLeft = rcMaxExtent->right - iWidth;
		}

		if( iTop < rcMaxExtent->top )
		{
			iTop = rcMaxExtent->top;
		}
		else if( iTop > rcMaxExtent->bottom - iHeight )
		{
			iTop = rcMaxExtent->bottom - iHeight;
		}

		::MoveWindow( m_hElement, iLeft + m_rcFixed->left, iTop + m_rcFixed->top, iWidth, iHeight, TRUE );
	}

	//*************************************************************************************************

	CScalableLayout::CScalableLayout()
		:	CWndLayout()
	{
	}

	CScalableLayout::~CScalableLayout()
	{
		Flush();
	}

	void CScalableLayout::AddElement( UINT uiId, HWND hElement, bool scalable, eHORIZ_ALIGN horiz, eVERTIC_ALIGN vertic )
	{
		ElementMap::iterator it = m_mapElements.find( uiId );

		if( it == m_mapElements.end() )
		{
			m_mapElements.insert( std::make_pair( uiId, CElement( hElement, m_hParent, &m_rcFixedBorders, scalable, horiz, vertic ) ) );
		}
	}

	void CScalableLayout::RemoveElement( UINT uiId )
	{
		ElementMap::iterator it = m_mapElements.find( uiId );

		if( it != m_mapElements.end() )
		{
			m_mapElements.erase( it );
		}
	}

	void CScalableLayout::Flush()
	{
		m_mapElements.clear();
	}

	void CScalableLayout::DoResize()
	{
		int iCurrentWidth = m_rcCurrent.right - m_rcCurrent.left;
		int iCurrentHeight = m_rcCurrent.bottom - m_rcCurrent.top;
		int iOriginalWidth = m_rcOriginal.right - m_rcOriginal.left;
		int iOriginalHeight = m_rcOriginal.bottom - m_rcOriginal.top;

		double dRatioX = double( iCurrentWidth ) / double( iOriginalWidth );
		double dRatioY = double( iCurrentHeight ) / double( iOriginalHeight );

		for( ElementMap::iterator it = m_mapElements.begin() ; it != m_mapElements.end() ; ++it )
		{
			it->second.Resize( dRatioX, dRatioY, &m_rcCurrent );
		}
	}
}