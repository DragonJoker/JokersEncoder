#include "stdafx.h"

#include "TransparentCheck.h"
#include "Image.h"
#include "ColourManager.h"
#include "FontManager.h"
#include "ImageManager.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CTransparentRadioCheck::CTransparentRadioCheck()
	{
		m_brushesCheck[eBTN_STATE_DISABLED		].SetSolidBrush( CColour( CColour::Transparent	) );
		m_brushesCheck[eBTN_STATE_ENABLED		].SetSolidBrush( CColour( CColour::Transparent	) );
		m_brushesCheck[eBTN_STATE_HIGHLIGHTED	].SetSolidBrush( CColour( CColour::LowAlphaLightBlue	) );
		m_brushesCheck[eBTN_STATE_PUSHED		].SetSolidBrush( CColour( CColour::MediumAlphaLightBlue	) );
	}

	CTransparentRadioCheck::~CTransparentRadioCheck()
	{
	}

	void CTransparentRadioCheck::DoRelease()
	{
	}

	void CTransparentRadioCheck::DoDrawBackground( CRect const & rcRect )
	{
		// On met l'image d'arrière plan dans le backbuffer
		DrawBitmap( rcRect, m_bmpBackground, rcRect, FALSE );
		// on blende le backbuffer et le masque
		DrawBitmap( rcRect, m_brushMask.GetDC(), m_brushMask.GetRect() );
	}

	void CTransparentRadioCheck::DoDrawForeground( CRect const & rcRect )
	{
		// On dessine le texte
		ImagePtr pImage;
		int iOffset = 3;
		int iWidth	= std::min< int >( rcRect.Width(),	12 );
		int iHeight	= std::min< int >( rcRect.Height(),	12 );
		int iTop = ( rcRect.Height() - iHeight ) / 2;
		CRect rcRectCheck;
		CRect rcRectText;
		CString csText;
		BaseType::GetWindowText( csText );
		CFont * pFont;
		LOGFONT logFont;
		DWORD dwAlign = 0;

		if ( BaseType::GetStyle() & BS_LEFTTEXT )
		{
			rcRectText = CRect( CPoint( rcRect.left, rcRect.top ), CSize( rcRect.Width() - ( iWidth + iOffset ), rcRect.Height() ) );
			rcRectCheck = CRect( CPoint( rcRect.right - iWidth, iTop ), CSize( iWidth, iHeight ) );
		}
		else
		{
			rcRectText = CRect( CPoint( rcRect.left + iWidth + iOffset, rcRect.top ), CSize( rcRect.Width() - ( iWidth + iOffset ), rcRect.Height() ) );
			rcRectCheck = CRect( CPoint( rcRect.left, iTop ), CSize( iWidth, iHeight ) );
		}

		if ( BaseType::GetStyle() & BS_CENTER )
		{
			dwAlign |= DT_CENTER;
		}

		if ( ( BaseType::GetStyle() & BS_MULTILINE ) == 0 )
		{
			dwAlign |= DT_SINGLELINE;
			dwAlign |= DT_VCENTER;
		}

		if ( !csText.IsEmpty() )
		{
			pFont = new Joker::CFont( GetFont() );
			pFont->GetLogFont( & logFont );

#if DEF_USING_D2D

			if ( logFont.lfHeight > 0 )
			{
				logFont.lfHeight += 3;
			}
			else
			{
				logFont.lfHeight -= 3;
			}

#endif

			if ( IsWindowEnabled() )
			{
				BaseType::DrawSolidText( ( *pFont ), logFont, m_clText, csText, rcRectText, dwAlign );
			}
			else
			{
				BaseType::DrawSolidText( ( *pFont ), logFont, m_clText + CColour::FromComponents( 127, 127, 127, 255 ), csText, rcRectText, dwAlign );
			}
		}

		if ( BaseType::IsWindowEnabled() )
		{
			if ( BaseType::GetCheck() == BST_CHECKED )
			{
				pImage = m_pImgCheck;
			}
			else
			{
				pImage = m_pImgUncheck;
			}
		}
		else
		{
			pImage = m_pImgDisable;
		}

		if ( pImage )
		{
			BaseType::DrawBitmap( rcRectCheck, ( *pImage ), CRect( 0, 0, pImage->GetWidth(), pImage->GetHeight() ) );
		}

		BaseType::DrawBitmap( rcRectCheck, m_brushesCheck[GetState()].GetDC(), m_brushesCheck[GetState()].GetRect() );
	}
}
