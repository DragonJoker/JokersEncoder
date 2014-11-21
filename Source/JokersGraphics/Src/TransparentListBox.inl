#include "Image.h"

namespace Joker
{
	template< eRENDERER Renderer >
	CTransparentListBox< Renderer >::CTransparentListBox()
		:	m_sItemHeight( 18 )
		,	m_iFocusedItem( -1 )
		,	m_clFocusBorder( CColour( CColour::FullAlphaGrey ) )
		,	m_iFocusBorderStyle( PS_DOT )
		,	m_brushMouse( CColour::FromCOLORREF( ::GetSysColor( COLOR_HIGHLIGHT ), 64 ) )
		,	m_clMouseLine( CColour::FromCOLORREF( ::GetSysColor( COLOR_HIGHLIGHT ) ) )
		,	m_iMouseLineStyle( PS_SOLID )
	{
		m_itemColours[eLB_ITEM_STATUS_NORMAL] = CAlphaLBItem( CColour( CColour::Transparent ), CColour::FromCOLORREF( ::GetSysColor( COLOR_CAPTIONTEXT ), 255 ) );
		m_itemColours[eLB_ITEM_STATUS_SELECTED] = CAlphaLBItem( CColour::FromCOLORREF( ::GetSysColor( COLOR_HIGHLIGHT ), 127 ),	CColour::FromCOLORREF( ::GetSysColor( COLOR_HIGHLIGHTTEXT ), 255 ) );
	}

	template< eRENDERER Renderer >
	CTransparentListBox< Renderer >::~CTransparentListBox()
	{
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::SetItemHeight( short sHeight )
	{
		m_sItemHeight = sHeight;
		Invalidate();
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::SetItemTextColour( eLB_ITEM_STATUS eStatus, CColour const & clColour )
	{
		m_itemColours[eStatus].SetTextColour( clColour );
		Invalidate();
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::SetItemLineColour( eLB_ITEM_STATUS eStatus, CColour const & clColour )
	{
		m_itemColours[eStatus].SetLineColour( clColour );
		Invalidate();
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::SetItemLineStyle( eLB_ITEM_STATUS eStatus, int iLineStyle )
	{
		m_itemColours[eStatus].SetLineStyle( iLineStyle );
		Invalidate();
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::DoDrawBackground( CRect const & rcRectp )
	{
		CRect rcRect( rcRectp );

#if eDEFAULT_RENDERER == eRENDERER_D2D
		SCROLLBARINFO sbi = { 0 };
		sbi.cbSize = sizeof( SCROLLBARINFO );
		GetScrollBarInfo( OBJID_VSCROLL, & sbi );
		rcRect.right += ( sbi.rcScrollBar.right - sbi.rcScrollBar.left );
#endif

		BaseType::DoDrawBackground( rcRect );

		ScrollList();

		// On récupère les items sélectionnés
		std::vector< int > arraySelected( GetCount(), 0 );

		if ( !arraySelected.empty() )
		{
			int iCount = GetSelItems( GetCount(), &arraySelected[0] );

			if ( iCount == LB_ERR )
			{
				int iSelected = GetCurSel();

				// Single Selection Listbox
				if ( iSelected != LB_ERR )
				{
					arraySelected.resize( 1 );
					arraySelected[0] = iSelected;
				}
				else
				{
					arraySelected.clear();
				}
			}
			else
			{
				arraySelected.resize( iCount );
			}
		}

		// On dessine les items
		CRect rcItem;

		for ( int i = 0 ; i < GetCount() ; i++ )
		{
			GetItemRect( i, rcItem );

			if ( rcItem.top >= rcRect.top && rcItem.bottom <= rcRect.bottom )
			{
				// Si l'item courant ne sort pas du cadre, on le dessine
				DrawItem( i, rcItem, arraySelected );
			}
			else if ( rcItem.top < rcRect.top && rcItem.bottom > rcRect.top )
			{
				// Si seul le haut de l'item courant sort du cadre, on le dessine
				DrawItem( i, rcItem, arraySelected );
			}
			else if ( rcItem.bottom > rcRect.bottom && rcItem.top < rcItem.bottom )
			{
				// Si seul le bas de l'item courant sort du cadre, on le dessine
				DrawItem( i, rcItem, arraySelected );
			}
			else
			{
				// Item dépassant complètement du cadre, on ne le dessine pas
			}
		}
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::DoDrawForeground( CRect const & rcRectp )
	{
		CRect rcRect( rcRectp );

#if eDEFAULT_RENDERER == eRENDERER_D2D
		SCROLLBARINFO sbi = { 0 };
		sbi.cbSize = sizeof( SCROLLBARINFO );
		GetScrollBarInfo( OBJID_VSCROLL, & sbi );
		rcRect.right += ( sbi.rcScrollBar.right - sbi.rcScrollBar.left );
#endif

		BaseType::DoDrawForeground( rcRect );

		if ( m_bFocused && m_bMouseLDown )
		{
			CRect rcMouse = m_rcMouse;
			rcMouse.NormalizeRect();
			DrawBitmap( rcMouse, m_brushMouse, m_brushMouse.GetRect() );
			FrameRect( rcMouse, m_clMouseLine, 1, m_iMouseLineStyle );
		}
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::DrawItem( int iItem, CRect rcRect, std::vector< int > const & arraySelected )
	{
		CString csItem;
		bool bFocused;
		eLB_ITEM_STATUS eStatus;
		size_t GL2D_SIZE_I = 0;
		bool bSelected = false;

		GetText( iItem, csItem );

		// On vérifie si l'item courant est sélectionné ou pas
		bSelected = std::find( arraySelected.begin(), arraySelected.end(), iItem ) != arraySelected.end();

		// On définit le statut de l'item courant
		bFocused = iItem == m_iFocusedItem;

		if ( bSelected )
		{
			eStatus = eLB_ITEM_STATUS_SELECTED;
		}
		else
		{
			eStatus = eLB_ITEM_STATUS_NORMAL;
		}

		// On blend le masque et le dc final
		DrawBitmap( rcRect, m_itemColours[eStatus].GetBrush(), m_itemColours[eStatus].GetBrush().GetRect() );

		// On dessine le texte de l'item
		LOGFONT logFont;
		GetFont()->GetLogFont( & logFont );
		DrawSolidText( ( * GetFont() ), logFont, m_itemColours[eStatus].GetTextColour(), csItem, rcRect + CRect( -5, 0, 0, 0 ), DT_SINGLELINE | DT_VCENTER );

		// On dessine le rectangle de contour, si besoin est
		if ( bFocused && m_bFocused )
		{
			// Contour de focus
			FrameRect( rcRect, m_clFocusBorder, 1, m_iFocusBorderStyle );
		}
		else if ( m_itemColours[eStatus].HasLine() )
		{
			// Contour de pas de focus, s'il existe
			FrameRect( rcRect, m_itemColours[eStatus].GetLineColour(), 1, m_itemColours[eStatus].GetLineStyle() );
		}
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
	{
		if ( ( lpDrawItemStruct->itemAction & ODA_FOCUS ) && ( lpDrawItemStruct->itemState & ODS_FOCUS ) )
		{
			m_iFocusedItem = lpDrawItemStruct->itemID;
		}
		else if ( ( lpDrawItemStruct->itemAction & ODA_FOCUS ) && !( lpDrawItemStruct->itemState & ODS_FOCUS ) )
		{
			m_iFocusedItem = lpDrawItemStruct->itemID;
		}

		if ( !IsPainting() )
		{
			Invalidate();
		}
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
	{
		lpMeasureItemStruct->itemHeight = m_sItemHeight;
	}

	template< eRENDERER Renderer >
	int CTransparentListBox< Renderer >::CompareItem( LPCOMPAREITEMSTRUCT UNUSED( lpCompareItemStruct ) )
	{
		return 0;
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::ScrollList()
	{
		if ( m_bMouseLDown )
		{
			int iScrollPos = GetScrollPos( SB_VERT );
			int iScrollDelta = m_iScrollPos - iScrollPos;
			m_rcMouse.top += iScrollDelta * m_sItemHeight;
			m_iScrollPos = iScrollPos;
		}
	}

	PTM_WARNING_DISABLE
    template< eRENDERER Renderer >
	const AFX_MSGMAP * CTransparentListBox< Renderer >::GetMessageMap() const
	{
		return GetThisMessageMap();
	}
    
    template< eRENDERER Renderer >
	const AFX_MSGMAP * PASCAL CTransparentListBox< Renderer >::GetThisMessageMap()
	{
		typedef CTransparentListBox< Renderer > ThisClass;
		typedef ThisClass::BaseType TheBaseClass;
		static const AFX_MSGMAP_ENTRY _messageEntries[] =
		{
			ON_WM_VSCROLL()
			ON_WM_MOUSEMOVE()
			ON_WM_LBUTTONDOWN()
			ON_WM_LBUTTONUP()
			{
				0, 0, 0, 0, AfxSig_end, ( AFX_PMSG )0
			}
		};
		static const AFX_MSGMAP messageMap =
		{
			& TheBaseClass::GetThisMessageMap, &_messageEntries[0]
		};
		return &messageMap;
	}
	PTM_WARNING_RESTORE

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar * pScrollBar )
	{
		SetRedraw( FALSE );
		BaseType::OnVScroll( nSBCode, nPos, pScrollBar );
		SetRedraw( TRUE );
		RedrawWindow( 0, 0, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW );
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::OnMouseMove( UINT nFlags, CPoint point )
	{
		m_bMouseLDown = nFlags & MK_LBUTTON;

		if ( m_bMouseLDown )
		{
			m_rcMouse.right = point.x;
			m_rcMouse.bottom = point.y;
			Invalidate();
		}

		BaseType::OnMouseMove( nFlags, point );
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::OnLButtonDown( UINT nFlags, CPoint point )
	{
		m_bFocused = true;
		m_bMouseLDown = true;
		m_rcMouse.left = point.x;
		m_rcMouse.top = point.y;
		m_rcMouse.right = point.x;
		m_rcMouse.bottom = point.y;
		m_iScrollPos = GetScrollPos( SB_VERT );
		BaseType::OnLButtonDown( nFlags, point );
	}

	template< eRENDERER Renderer >
	void CTransparentListBox< Renderer >::OnLButtonUp( UINT nFlags, CPoint point )
	{
		m_bMouseLDown = false;
		BaseType::OnLButtonUp( nFlags, point );
	}
}
