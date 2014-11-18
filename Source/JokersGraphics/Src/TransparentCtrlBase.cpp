#include "stdafx.h"

#include "TransparentCtrlBase.h"

namespace Joker
{
	CTransparentCtrlBase::CTransparentCtrlBase()
		:	m_bPainting( false )
		,	m_bHasBackground( false )
		,	m_brushMask( CColour( CColour::Transparent ) )
		,	m_clText( CColour( CColour::FullAlphaBlack ) )
		,	m_clBorder( CColour( CColour::FullAlphaBlack ) )
		,	m_bFocused( false )
		,	m_bMouseOver( false )
		,	m_bHasBorder( true )
		,	m_bReinitBackground( false )
	{
	}

	CTransparentCtrlBase::~CTransparentCtrlBase()
	{
	}

	void CTransparentCtrlBase::SetBorderColour( CColour const & clColour )
	{
		m_clBorder = clColour;
		m_ctrl->Invalidate();
	}

	void CTransparentCtrlBase::SetTextColour( CColour const & clColour )
	{
		m_clText = clColour;
		m_ctrl->Invalidate();
	}

	void CTransparentCtrlBase::GetRelativeRect( CRect & rcRect )
	{
		CRect l_rcRect1, l_rcRect2;
		m_ctrl->GetWindowRect( l_rcRect1 );
		CWnd * pParent = m_ctrl->GetParent();

		if ( pParent )
		{
			pParent->GetWindowRect( l_rcRect2 );
		}

		rcRect.left = l_rcRect1.left - l_rcRect2.left;
		rcRect.top = l_rcRect1.top - l_rcRect2.top;
		rcRect.right = rcRect.left + l_rcRect1.Width();
		rcRect.bottom = rcRect.top + l_rcRect1.Height();
	}

	BOOL CTransparentCtrlBase::SetWindowPosition( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		m_bReinitBackground = true;
		BOOL bReturn = m_ctrl->SetWindowPos( pWndInsertAfter, x, y, cx, cy, uiFlags );
		return bReturn;
	}

	void CTransparentCtrlBase::DoInitialiseBackground()
	{
		CWnd * pParent = m_ctrl->GetParent();

		if ( pParent )
		{
			CRect rcRect;
			m_ctrl->GetWindowRect( & rcRect );
			pParent->ScreenToClient( & rcRect );

			CDC * pDC = pParent->GetDC();
			int iWidth = rcRect.Width();
			int iHeight = rcRect.Height();

			CDC memdc;
			m_bmpBackground.DeleteObject();
			m_bmpBackground.CreateCompatibleBitmap( pDC, rcRect.Width(), rcRect.Height() );
			memdc.CreateCompatibleDC( pDC );

			CBitmap * pOldbmp = memdc.SelectObject( & m_bmpBackground );
			memdc.BitBlt( 0, 0, iWidth, iHeight, pDC, rcRect.left, rcRect.top, SRCCOPY );
			memdc.SelectObject( pOldbmp );
			pParent->ReleaseDC( pDC );
			memdc.DeleteDC();
			m_bReinitBackground = false;
		}
	}
}