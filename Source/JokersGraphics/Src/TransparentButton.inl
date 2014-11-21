#include "Image.h"
#include "ColourManager.h"
#include "FontManager.h"
#include "ImageManager.h"

namespace Joker
{
    template< eRENDERER Renderer >
	CTransparentButton< Renderer >::CTransparentButton()
		: m_eState( eBTN_STATE_ENABLED )
		, m_dwAlign( DT_CENTER | DT_VCENTER )
		, m_bDrawBorder( FALSE )
		, m_bDrawFocus( FALSE )
	{
		m_brushMask.SetSolidBrush( CColour( CColour::Transparent ) );

		for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eBTN_STATE_COUNT ; GL2D_SIZE_I++ )
		{
			m_pFonts[GL2D_SIZE_I] = NULL;
		}
	}
    
    template< eRENDERER Renderer >
	CTransparentButton< Renderer >::~CTransparentButton()
	{
		DoRelease();
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetSolidBrush( eBTN_STATE eState, CColour const & clColour, BOOL bRedraw )
	{
		if ( eState >= eBTN_STATE_COUNT )
		{
			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eBTN_STATE_COUNT ; GL2D_SIZE_I++ )
			{
				m_brushes[GL2D_SIZE_I].SetSolidBrush( clColour );
			}
		}
		else if ( eState >= 0 )
		{
			m_brushes[eState].SetSolidBrush( clColour );
		}

		if ( bRedraw )
		{
			BaseType::Invalidate();
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetSolidBrushes( CColour const & clEnable, CColour const & clHighlt, CColour const & clPushed, CColour const & clDisabl )
	{
		SetSolidBrush( eBTN_STATE_DISABLED		, clDisabl	);
		SetSolidBrush( eBTN_STATE_ENABLED		, clEnable	);
		SetSolidBrush( eBTN_STATE_HIGHLIGHTED	, clHighlt	);
		SetSolidBrush( eBTN_STATE_PUSHED		, clPushed	);
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetPatternBrush( eBTN_STATE eState, HBITMAP hPattern, CRect const & rcPattern, BOOL bRedraw )
	{
		if ( eState >= eBTN_STATE_COUNT )
		{
			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eBTN_STATE_COUNT ; GL2D_SIZE_I++ )
			{
				m_brushes[GL2D_SIZE_I].SetPatternBrush( hPattern, rcPattern );
			}
		}
		else if ( eState >= 0 )
		{
			m_brushes[eState].SetPatternBrush( hPattern, rcPattern );
		}

		if ( bRedraw )
		{
			BaseType::Invalidate();
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetGradientBrush( eBTN_STATE eState, int iType, CColour const & clDebut, CColour const & clMilieu, CColour const & clFin, int iSteps, BOOL bRedraw )
	{
		if ( eState >= eBTN_STATE_COUNT )
		{
			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eBTN_STATE_COUNT ; GL2D_SIZE_I++ )
			{
				m_brushes[GL2D_SIZE_I].SetGradientBrush( iType, clDebut, clMilieu, clFin, iSteps );
			}
		}
		else if ( eState >= 0 )
		{
			m_brushes[eState].SetGradientBrush( iType, clDebut, clMilieu, clFin, iSteps );
		}

		if ( bRedraw )
		{
			BaseType::Invalidate();
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetImages( int iEnabled, int iHighlight, int iPush, int iDisabled, CRect const & rcFixed, BOOL bFromResources )
	{
		ImagePtr pImgEnable;
		ImagePtr pImgHighlt;
		ImagePtr pImgPushed;
		ImagePtr pImgDisabl;

		if ( bFromResources )
		{
			pImgEnable = CImageManager::AddImage( iEnabled	);
			pImgHighlt = CImageManager::AddImage( iHighlight	);
			pImgPushed = CImageManager::AddImage( iPush	);
			pImgDisabl = CImageManager::AddImage( iDisabled	);
		}
		else
		{
			pImgEnable = CImageManager::GetImageByIndex( iEnabled	);
			pImgHighlt = CImageManager::GetImageByIndex( iHighlight	);
			pImgPushed = CImageManager::GetImageByIndex( iPush	);
			pImgDisabl = CImageManager::GetImageByIndex( iDisabled	);
		}

		SetFixedSizes( rcFixed );
		SetPatternBrush( eBTN_STATE_ENABLED,		*pImgEnable, CRect( 0, 0, pImgEnable->GetWidth(), pImgEnable->GetHeight() ) );
		SetPatternBrush( eBTN_STATE_HIGHLIGHTED,	*pImgHighlt, CRect( 0, 0, pImgHighlt->GetWidth(), pImgHighlt->GetHeight() ) );
		SetPatternBrush( eBTN_STATE_PUSHED,			*pImgPushed, CRect( 0, 0, pImgPushed->GetWidth(), pImgPushed->GetHeight() ) );
		SetPatternBrush( eBTN_STATE_DISABLED,		*pImgDisabl, CRect( 0, 0, pImgDisabl->GetWidth(), pImgDisabl->GetHeight() ) );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetTextColour( eBTN_STATE eState, CColour const & clColour, BOOL bRedraw )
	{
		if ( eState >= eBTN_STATE_COUNT )
		{
			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eBTN_STATE_COUNT ; GL2D_SIZE_I++ )
			{
				m_textColours[GL2D_SIZE_I] = clColour;
			}
		}
		else if ( eState >= 0 )
		{
			m_textColours[eState] = clColour;
		}

		if ( bRedraw )
		{
			BaseType::Invalidate();
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetTextColour( eBTN_STATE eState, UINT uiId, BOOL bRedraw )
	{
		SetTextColour( eState, CColour::FromCOLORREF( CColourManager::GetColour( uiId ) ), bRedraw );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetTextColours( CColour const & clEnabled, CColour const & clHighlight, CColour const & clPush, CColour const & clDisabled )
	{
		SetTextColour( eBTN_STATE_DISABLED		, clDisabled	, FALSE	);
		SetTextColour( eBTN_STATE_ENABLED		, clEnabled		, FALSE	);
		SetTextColour( eBTN_STATE_HIGHLIGHTED	, clHighlight	, FALSE	);
		SetTextColour( eBTN_STATE_PUSHED		, clPush		, TRUE	);
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetTextColours( UINT uiEnable, UINT uiHighlt, UINT uiPushed, UINT uiDisabl, BOOL bFromResources )
	{
		if ( bFromResources )
		{
			SetTextColours( CColour::FromCOLORREF( uiEnable ), CColour::FromCOLORREF( uiHighlt ), CColour::FromCOLORREF( uiPushed ), CColour::FromCOLORREF( uiDisabl )	);
		}
		else
		{
			SetTextColours( CColour::FromCOLORREF( CColourManager::GetColour( uiEnable ) ), CColour::FromCOLORREF( CColourManager::GetColour( uiHighlt ) ), CColour::FromCOLORREF( CColourManager::GetColour( uiPushed ) ), CColour::FromCOLORREF( CColourManager::GetColour( uiDisabl ) ) );
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetFont( eBTN_STATE eState, Joker::FontPtr pFont, BOOL bRedraw )
	{
		if ( eState >= eBTN_STATE_COUNT )
		{
			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eBTN_STATE_COUNT ; GL2D_SIZE_I++ )
			{
				m_pFonts[GL2D_SIZE_I] = pFont;
			}
		}
		else if ( eState >= 0 )
		{
			m_pFonts[eState] = pFont;
		}

		if ( bRedraw )
		{
			BaseType::Invalidate();
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetFont( eBTN_STATE eState, UINT uiId, BOOL bRedraw )
	{
		SetFont( eState, CFontManager::GetFont( uiId ), bRedraw );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetFonts( Joker::FontPtr pEnabledFont, Joker::FontPtr pHighlightFont, Joker::FontPtr pDownFont, Joker::FontPtr pDisabledFont )
	{
		SetFont( eBTN_STATE_DISABLED	, pDisabledFont		, FALSE	);
		SetFont( eBTN_STATE_ENABLED		, pEnabledFont		, FALSE	);
		SetFont( eBTN_STATE_HIGHLIGHTED	, pHighlightFont	, FALSE	);
		SetFont( eBTN_STATE_PUSHED		, pDownFont			, TRUE	);
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetFonts( int iEnabledIndex, int iHighlightIndex, int iDownIndex, int iDisabledIndex )
	{
		SetFont( eBTN_STATE_DISABLED	, iEnabledIndex		, FALSE	);
		SetFont( eBTN_STATE_ENABLED		, iHighlightIndex	, FALSE	);
		SetFont( eBTN_STATE_HIGHLIGHTED	, iDownIndex		, FALSE	);
		SetFont( eBTN_STATE_PUSHED		, iDisabledIndex	, TRUE	);
	}
    
    template< eRENDERER Renderer >
	BOOL CTransparentButton< Renderer >::EnableWindow( BOOL bEnable )
	{
		BOOL bReturn = BaseType::EnableWindow( bEnable );

		if ( bEnable )
		{
			if ( m_bMouseOver )
			{
				m_eState = eBTN_STATE_HIGHLIGHTED;
			}
			else
			{
				m_eState = eBTN_STATE_ENABLED;
			}
		}
		else
		{
			m_eState = eBTN_STATE_DISABLED;
		}

		BaseType::Invalidate();

		return bReturn;
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::SetText( String const & strText )
	{
		BaseType::SetWindowText( strText.c_str() );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::DoRelease()
	{
		m_bMouseOver = false;

		if ( IsWindow( m_hWnd ) && BaseType::IsWindowEnabled() )
		{
			m_eState = eBTN_STATE_ENABLED;
		}
		else
		{
			m_eState = eBTN_STATE_DISABLED;
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::DoDrawBackground( CRect const & rcRect )
	{
		BaseType::DoDrawBackground( rcRect );
		// On blend le backbuffer et le pattern de ce bouton
		int iImgHeight = m_brushes[m_eState].GetRect().Height();
		int iImgWidth = m_brushes[m_eState].GetRect().Width();

		float fLeftRatio = float( m_rcFixedSizes.left ) / float( iImgHeight );
		float fRightRatio = float( m_rcFixedSizes.right ) / float( iImgHeight );

		int iWidth = rcRect.Width();
		int iHeight = rcRect.Height();

		int iLeft = int( iHeight * fLeftRatio );
		int iRight = iWidth - int( iHeight * fRightRatio );

		BaseType::DrawBitmap(	CRect( 0, 0, iLeft, iHeight ),			m_brushes[m_eState], CRect( 0, 0, m_rcFixedSizes.left, iImgHeight ) );
		BaseType::DrawBitmap(	CRect( iRight, 0, iWidth, iHeight ),	m_brushes[m_eState], CRect( iImgWidth - m_rcFixedSizes.right, 0, iImgWidth, iImgHeight ) );
		BaseType::DrawBitmap(	CRect( iLeft, 0, iRight, iHeight ),		m_brushes[m_eState], CRect( m_rcFixedSizes.left, 0, iImgWidth - m_rcFixedSizes.right, iImgHeight ) );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::DoDrawForeground( CRect const & rcRect )
	{
		// On dessine le texte, s'il y en a un
		CString csText;
		LOGFONT logFont;
		CRect rcTmp( rcRect );
		CRect rcText( rcRect );
		FontPtr pFont = m_pFonts[m_eState];

		BaseType::GetWindowText( csText );

		if ( !csText.IsEmpty() && pFont )
		{
			int iOffset = rcRect.Height() / 10;
			rcText.DeflateRect( iOffset, iOffset, iOffset, iOffset ); // Pour que le texte ne soit pas collé au bord du bouton
			pFont->GetLogFont( & logFont );
			BaseType::DrawSolidText( ( *pFont ), logFont, m_textColours[m_eState], csText, rcText, m_dwAlign );
		}

		if ( m_bDrawBorder )
		{
			// On dessine le contour
			BaseType::FrameRect( rcRect, m_clBorder );
		}

		if ( m_bFocused && m_bDrawFocus )
		{
			rcTmp.DeflateRect( 2, 2, 2, 2 );
			BaseType::FrameRect( rcTmp, CColour::FromComponents( 127, 127, 127, 255 ), 1, PS_DOT );
		}
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::DrawItem( LPDRAWITEMSTRUCT UNUSED( lpDrawItemStruct ) )
	{
		// 	m_hDC = lpDrawItemStruct->hDC;
		// 	Draw();
		// 	m_hDC = NULL;
	}

	PTM_WARNING_DISABLE
    template< eRENDERER Renderer >
	const AFX_MSGMAP * CTransparentButton< Renderer >::GetMessageMap() const
	{
		return GetThisMessageMap();
	}
    
    template< eRENDERER Renderer >
	const AFX_MSGMAP * PASCAL CTransparentButton< Renderer >::GetThisMessageMap()
	{
		typedef CTransparentButton< Renderer > ThisClass;
		typedef ThisClass::BaseType TheBaseClass;
		static const AFX_MSGMAP_ENTRY _messageEntries[] =
		{
			ON_MESSAGE( WM_SETFONT, OnSetFont )
			ON_WM_MOUSEMOVE()
			ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
			ON_WM_SETFOCUS()
			ON_WM_KILLFOCUS()
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
	LRESULT CTransparentButton< Renderer >::OnSetFont( WPARAM wParam, LPARAM lParam )
	{
		HFONT hFont = HFONT( wParam );

		if ( !hFont )
		{
			hFont = HFONT( ::GetStockObject( SYSTEM_FONT ) );
		}

		if ( hFont )
		{
			LOGFONT logfont;
			::GetObject( hFont, sizeof( LOGFONT ), &logfont );

			for ( int i = 0; i < eBTN_STATE_COUNT; ++i )
			{
				if ( m_pFonts[i] )
				{
					m_pFonts[i]->SetLogFont( logfont );
				}
			}
		}

		return LRESULT( 0 );
	}

	template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::OnMouseMove( UINT nFlags, CPoint point )
	{
		if ( m_eState != eBTN_STATE_DISABLED )
		{
			CCursor< CButton >::OnMouseMove( nFlags, point );// Pour ne pas appeler celui de CTransparentCtrl

			if ( nFlags & MK_LBUTTON )
			{
				m_eState = eBTN_STATE_PUSHED;
			}
			else
			{
				m_eState = eBTN_STATE_HIGHLIGHTED;
			}

			CRect rRect;
			BaseType::GetClientRect( & rRect );
			BOOL bMouseOverMe = ( point.x >= 0 && point.x <= rRect.Width() && point.y >= 0 && point.y <= rRect.Height() );

			if ( !m_bMouseOver && bMouseOverMe )
			{
				TRACKMOUSEEVENT mouseEvent;
				mouseEvent.cbSize = sizeof( TRACKMOUSEEVENT );
				mouseEvent.dwFlags = TME_LEAVE;
				mouseEvent.hwndTrack = m_hWnd;
				mouseEvent.dwHoverTime = HOVER_DEFAULT;
				TrackMouseEvent( & mouseEvent );
				m_bMouseOver = true;

				BaseType::Invalidate();
			}
			else if ( m_bMouseOver && !bMouseOverMe )
			{
				m_eState = eBTN_STATE_ENABLED;
				m_bMouseOver = false;

				BaseType::Invalidate();

			}
		}
	}
    
    template< eRENDERER Renderer >
	LRESULT CTransparentButton< Renderer >::OnMouseLeave( WPARAM wParam, LPARAM lParam )
	{
		BaseType::OnMouseLeave( wParam, lParam );

		if ( BaseType::IsWindowEnabled() )
		{
			m_eState = eBTN_STATE_ENABLED;
		}
		else
		{
			m_eState = eBTN_STATE_DISABLED;
		}

		BaseType::Invalidate();

		return 0;
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::OnLButtonDown( UINT nFlags, CPoint point )
	{
		m_bFocused = true;
		m_eState = eBTN_STATE_PUSHED;
		BaseType::OnLButtonDown( nFlags, point );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::OnLButtonUp( UINT nFlags, CPoint point )
	{
		if ( BaseType::IsWindowEnabled() )
		{
			if ( m_bMouseOver )
			{
				m_eState = eBTN_STATE_HIGHLIGHTED;
			}
			else
			{
				m_eState = eBTN_STATE_ENABLED;
			}
		}
		else
		{
			m_eState = eBTN_STATE_DISABLED;
		}

		BaseType::OnLButtonUp( nFlags, point );
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::OnSetFocus( CWnd * pOldWnd )
	{
		BaseType::OnSetFocus( pOldWnd );
		Invalidate();
	}
    
    template< eRENDERER Renderer >
	void CTransparentButton< Renderer >::OnKillFocus( CWnd * pNewWnd )
	{
		BaseType::OnKillFocus( pNewWnd );
		Invalidate();
	}
}
