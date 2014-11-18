#include "stdafx.h"

#include "DrawerBase.h"
#include "StrUtils.h"

namespace Joker
{
	int CDrawerBase::FormatText( CRect & rcRect, int iMaxWidth, String const & strUnformattedp, String & strFormatted, CFont & cFont, double dRatio, UINT uiFormat )
	{
		SetFont( cFont );

		CSize sizeWord;
		int iFontHeight = cFont.GetHeight();
		String strWord;
		String strLine;
		int iNbLines = 1;
		int iWordWidth = 0;
		int iLineWidth = 0;
		int iLineHeight = int( ( iFontHeight + 4 ) * dRatio );
		int iTotalHeight = iLineHeight;
		String strUnformatted = strUnformattedp;
		StringArray aLines;
		StringArray aWords;

		CStrUtils::Replace( strUnformatted, _T( "\r\n" ), _T( "\r" ) );
		CStrUtils::Replace( strUnformatted, _T( "\n" ), _T( " " ) );
		CStrUtils::Replace( strUnformatted, _T( "  " ), _T( " " ) );
		CStrUtils::Split( strUnformatted, _T( "\r" ), aLines );
		strFormatted.clear();

		for ( size_t j = 0 ; j < aLines.size() ; j++ )
		{
			aWords.clear();

			if ( uiFormat & DT_WORDBREAK )
			{
				CStrUtils::Split( aLines[j], _T( " " ), aWords );
			}
			else
			{
				for ( size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < aLines[j].size() ; GL2D_SIZE_I++ )
				{
					aWords.push_back( String( _T( "" ) ) + aLines[j][GL2D_SIZE_I] );
				}
			}

			iLineWidth = 0;

			for ( size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < aWords.size() ; GL2D_SIZE_I++ )
			{
				strWord = aWords[GL2D_SIZE_I];
				GetTextExtent( strWord, sizeWord );
				iWordWidth = int( sizeWord.cx + dRatio );

				if ( iLineWidth + iWordWidth > iMaxWidth * dRatio )
				{
					if ( !strFormatted.empty() )
					{
						iNbLines++;
						strFormatted += _T( "\n" );
					}

					strFormatted += strLine;
					strLine.clear();
					iLineWidth = 0;
					iTotalHeight += iLineHeight;
				}

				if ( uiFormat & DT_WORDBREAK )
				{
					strLine += strWord + _T( ' ' );
				}
				else
				{
					strLine += strWord;
				}

				iLineWidth += iWordWidth;
			}

			if ( !strLine.empty() )
			{
				if ( !strFormatted.empty() )
				{
					iNbLines++;
					strFormatted += _T( "\n" );
				}

				strFormatted += strLine;
				strLine.clear();
			}

			if ( j < aLines.size() - 1 )
			{
				strFormatted += _T( "\n" );
				iNbLines++;
			}
		}

		CSize sizeText;
		GetFormattedTextExtent( strFormatted, int( iMaxWidth * dRatio ), sizeText, cFont );
		rcRect.top = 0;
		rcRect.bottom = int( sizeText.cy / dRatio );
		rcRect.left = 0;
		rcRect.right = int( sizeText.cx / dRatio );

		UnsetFont( cFont );

		return iNbLines;
	}

	void CDrawerBase::GetTextExtent( String const & strText, CSize & sizeText )
	{
		CRect rcRect( 0, 0, 10000, 10000 );

		if ( !strText.empty() )
		{
			DrawText( strText, & rcRect, DT_CALCRECT );
		}
		else
		{
			rcRect.right = 0;
			rcRect.bottom = 0;
		}

		sizeText.cx = rcRect.Width();
		sizeText.cy = rcRect.Height();
	}

	void CDrawerBase::GetFormattedTextExtent( String const & strText, int iMaxWidth, CSize & sizeText, CFont & cFont )
	{
		String strTextTmp;
		int iTmpWidth = iMaxWidth;

		SetFont( cFont );
		DoGetFormattedTextExtent( strText, iTmpWidth, sizeText );
		UnsetFont( cFont );

		while ( sizeText.cx > iTmpWidth )
		{
			iTmpWidth -= ( iMaxWidth / 10 );
			CRect rcRect( CPoint( 0, 0 ), CSize( iTmpWidth, 10000 ) );
			FormatText( rcRect, iTmpWidth, strText, strTextTmp, cFont, 1.0, 0 );
			SetFont( cFont );
			DoGetFormattedTextExtent( strTextTmp, iTmpWidth, sizeText );
			UnsetFont( cFont );
		}
	}

	CSize CDrawerBase::DrawFormattedText( CFont & cFont, COLORREF crTextColour, String const & strText, CRect const & rcRect, UINT uiFormat, double dRatio )
	{
		CSize sizeReturn;
		CSize sizeText;
		CRect rcTextRect( rcRect );
		COLORREF rcOldColour = SetForegroundColour( crTextColour );

		rcTextRect.left		= LONG( rcTextRect.left		* dRatio );
		rcTextRect.right	= LONG( rcTextRect.right	* dRatio );
		rcTextRect.top		= LONG( rcTextRect.top		* dRatio );
		rcTextRect.bottom	= LONG( rcTextRect.bottom	* dRatio );

		SetFont( cFont );
		DoGetFormattedTextExtent( strText, rcTextRect.Width(), sizeText );

		if ( ( uiFormat & DT_VCENTER ) != 0 )
		{
			rcTextRect.top = rcTextRect.top + ( rcTextRect.Height() - sizeText.cy ) / 2;
			rcTextRect.bottom = rcTextRect.top + sizeText.cy;
		}

		sizeReturn.cy = this->DrawText( strText, rcTextRect, uiFormat | DT_WORDBREAK | DT_NOPREFIX );
		sizeReturn.cx = sizeText.cx;

		SetForegroundColour( rcOldColour );
		UnsetFont( cFont );

		sizeReturn.cx = LONG( sizeReturn.cx / dRatio );
		sizeReturn.cy = LONG( sizeReturn.cy / dRatio );

		return sizeReturn;
	}

	CSize CDrawerBase::DrawNudeText( CFont & cFont, COLORREF cTextColour, String const & strText, CRect const & rcRect, UINT uiFormat, double dRatio )
	{
		return DrawFormattedText( cFont, cTextColour, strText, rcRect, uiFormat | DT_VCENTER, dRatio );
	}

	void CDrawerBase::DrawTextBox( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CFont & cFont, COLORREF cTextColour, String const & strText, UINT uiFormat, CRect const & rcRect, double dRatio )
	{
		DrawRect( iPenHeight, cPenColour, cBrushColour, rcRect, dRatio );
		DrawNudeText( cFont, cTextColour, strText, rcRect, uiFormat, dRatio );
	}

	void CDrawerBase::DrawFormattedTextBox( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CFont & cFont, COLORREF cTextColour, String const & strText, UINT uiFormat, CRect const & rcRect, double dRatio )
	{
		DrawRect( iPenHeight, cPenColour, cBrushColour, rcRect, dRatio );
		CRect rcTmp( rcRect );
		rcTmp.DeflateRect( 2, 0, 2, 0 );
		DrawFormattedText( cFont, cTextColour, strText, rcTmp, uiFormat, dRatio );
	}

	void CDrawerBase::DrawCheckBox( int iPenHeight, COLORREF crPenColour, COLORREF crBrushColour, int x, int y, int iSize, BOOL bChecked, double dRatio )
	{
		int cx = x + iSize;
		int cy = y + iSize;
		DrawRect( iPenHeight, crPenColour, crBrushColour, CRect( x, y, cx, cy ), dRatio );

		if ( bChecked )
		{
			DrawLine( iPenHeight, crPenColour, CPoint( int( x * dRatio ), int( y * dRatio ) ), CPoint( int( cx * dRatio ), int( cy * dRatio ) ) );
			DrawLine( iPenHeight, crPenColour, CPoint( int( x * dRatio ), int( cy * dRatio ) ), CPoint( int( cx * dRatio ), int( y * dRatio ) ) );
		}
	}

	void CDrawerBase::DoGetFormattedTextExtent( String const & strText, int iMaxWidth, CSize & sizeText )
	{
		CRect rcRect( 0, 0, iMaxWidth, 10000 );

		if ( !strText.empty() )
		{
			DrawText( strText, &rcRect, DT_CALCRECT | DT_WORDBREAK );
		}
		else
		{
			rcRect.right = 0;
			rcRect.bottom = 0;
		}

		sizeText.cx = rcRect.Width();
		sizeText.cy = rcRect.Height();
	}
}