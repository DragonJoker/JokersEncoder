#include "stdafx.h"

#include "TransparentBrush.h"
#include "BitmapDC.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CTransparentBrush::CTransparentBrush( CColour const & clColour )
		:	m_hPattern		( NULL )
		,	m_bmpPatternDC	( NULL )
		,	m_rcSrcPattern	()
	{
		SetSolidBrush( clColour );
	}

	CTransparentBrush::CTransparentBrush( HBITMAP hPattern, CRect const & rcPattern )
		:	m_hPattern		( NULL )
		,	m_bmpPatternDC	( NULL )
		,	m_rcSrcPattern	( rcPattern )
	{
		SetPatternBrush( hPattern, rcPattern );
	}

	CTransparentBrush::CTransparentBrush( int iType, CColour const & clDebut, CColour const & clMilieu, CColour const & clFin, int iSteps )
		:	m_hPattern		( NULL )
		,	m_bmpPatternDC	( NULL )
		,	m_rcSrcPattern	()
	{
		SetGradientBrush( iType, clDebut, clMilieu, clFin, iSteps );
	}

	CTransparentBrush::CTransparentBrush( CTransparentBrush const & brush )
		:	m_hPattern		( NULL )
		,	m_bmpPatternDC	( NULL )
		,	m_rcSrcPattern	()
	{
		SetPatternBrush( brush.m_hPattern, brush.m_rcSrcPattern );
	}

	CTransparentBrush::~CTransparentBrush()
	{
		Release();
	}

	void CTransparentBrush::SetSolidBrush( CColour const & clColour )
	{
		Release();
		m_hPattern		= NULL;
		m_rcSrcPattern	= CRect( 0, 0, 1, 1 );

		BYTE * pBits;
		CreateBitmap( 1, 1, & pBits );
		int iATmp = clColour.a;
		int iRTmp =(( clColour.r * iATmp ) + 127 ) / 255;
		int iGTmp =(( clColour.g * iATmp ) + 127 ) / 255;
		int iBTmp =(( clColour.b * iATmp ) + 127 ) / 255;
		DWORD dwRet = MakeARGB( iRTmp, iGTmp, iBTmp, iATmp );
		memcpy( pBits, & dwRet, sizeof( DWORD ) );
	}

	void CTransparentBrush::SetPatternBrush( HBITMAP hPattern, CRect const & rcPattern )
	{
		Release();
		CopyPattern( hPattern, rcPattern );
	}

	void CTransparentBrush::SetGradientBrush( int iType, CColour const & clDebut, CColour const & clMilieu, CColour const & clFin, int iSteps )
	{
		int iRDebut = clDebut.r, iRMilieu = clMilieu.r, iRFin = clFin.r;
		int iGDebut = clDebut.g, iGMilieu = clMilieu.g, iGFin = clFin.g;
		int iBDebut = clDebut.b, iBMilieu = clMilieu.b, iBFin = clFin.b;
		int iADebut = clDebut.a, iAMilieu = clMilieu.a, iAFin = clFin.a;
		DWORD dwR, dwG, dwB, dwA;
		int iMilieu = iSteps / 2;
		BYTE * pPixels = NULL;
		int iIncrement = 0;
		BYTE * pBits;
		COLORREF crColour;

		if ( iType == 0 )
		{
			CreateBitmap( 1, iSteps, & pBits );
			pPixels = & pBits[( 4 * iSteps ) - 1];
			iIncrement = -4;
		}
		else
		{
			CreateBitmap( iSteps, 1, & pBits );
			pPixels = & pBits[0];
			iIncrement = 4;
		}

		for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < iMilieu ; GL2D_SIZE_I++ )
		{
			dwR = DWORD( double(( iMilieu - GL2D_SIZE_I ) * iRDebut ) / iMilieu + double( GL2D_SIZE_I * iRMilieu ) / iMilieu );
			dwG = DWORD( double(( iMilieu - GL2D_SIZE_I ) * iGDebut ) / iMilieu + double( GL2D_SIZE_I * iGMilieu ) / iMilieu );
			dwB = DWORD( double(( iMilieu - GL2D_SIZE_I ) * iBDebut ) / iMilieu + double( GL2D_SIZE_I * iBMilieu ) / iMilieu );
			dwA = DWORD( double(( iMilieu - GL2D_SIZE_I ) * iADebut ) / iMilieu + double( GL2D_SIZE_I * iAMilieu ) / iMilieu );
			crColour = MakeBGRA( dwR, dwG, dwB, dwA );
			memcpy( pPixels, & crColour, sizeof( COLORREF ) );
			pPixels += iIncrement;
		}

		for ( int GL2D_SIZE_I = iMilieu ; GL2D_SIZE_I < iSteps ; GL2D_SIZE_I++ )
		{
			dwR = int( double(( iSteps - GL2D_SIZE_I ) * iRMilieu ) / iMilieu + double(( GL2D_SIZE_I - iMilieu ) * iRFin ) / iMilieu );
			dwG = int( double(( iSteps - GL2D_SIZE_I ) * iGMilieu ) / iMilieu + double(( GL2D_SIZE_I - iMilieu ) * iGFin ) / iMilieu );
			dwB = int( double(( iSteps - GL2D_SIZE_I ) * iBMilieu ) / iMilieu + double(( GL2D_SIZE_I - iMilieu ) * iBFin ) / iMilieu );
			dwA = int( double(( iSteps - GL2D_SIZE_I ) * iAMilieu ) / iMilieu + double(( GL2D_SIZE_I - iMilieu ) * iAFin ) / iMilieu );
			crColour = MakeBGRA( dwR, dwG, dwB, dwA );
			memcpy( pPixels, & crColour, sizeof( COLORREF ) );
			pPixels += iIncrement;
		}
	}

	CTransparentBrush & CTransparentBrush::operator=( CTransparentBrush const & brush )
	{
		Release();
		CopyPattern( brush.m_hPattern, brush.m_rcSrcPattern );
		return * this;
	}

	void CTransparentBrush::CopyPattern( HBITMAP hPattern, CRect const & rcPattern )
	{
		m_hPattern		= NULL;
		m_rcSrcPattern	= rcPattern;

		BYTE * pBits;
		CreateBitmap( rcPattern.Width(), rcPattern.Height(), & pBits );
		BYTE * pSrcBits = new BYTE[rcPattern.Width() * rcPattern.Height() * 4];
		BITMAPINFO bmiSrc = { { sizeof( BITMAPINFOHEADER ), 0, 0, 0, 0, 0 } };
		BYTE iRTmp, iGTmp, iBTmp, iATmp=255;

		if ( GetDIBits( m_bmpPatternDC, hPattern, 0, rcPattern.Height(), NULL, & bmiSrc, DIB_RGB_COLORS ) )
		{
			BITMAPINFO bmi = { { sizeof( BITMAPINFOHEADER ), bmiSrc.bmiHeader.biWidth, bmiSrc.bmiHeader.biHeight, 1, 32, BI_RGB } };

			if ( GetDIBits( m_bmpPatternDC, hPattern, 0, rcPattern.Height(), pSrcBits, & bmi, DIB_RGB_COLORS ) )
			{
				if ( bmiSrc.bmiHeader.biBitCount != 32 )
				{
					COLORREF crColour;

					for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < rcPattern.Width() * rcPattern.Height() ; ++GL2D_SIZE_I )
					{
						iBTmp = pSrcBits[( GL2D_SIZE_I << 2 ) + 0];
						iGTmp = pSrcBits[( GL2D_SIZE_I << 2 ) + 1];
						iRTmp = pSrcBits[( GL2D_SIZE_I << 2 ) + 2];
						crColour = MakeARGB( iRTmp, iGTmp, iBTmp, iATmp );
						memcpy( pBits, & crColour, sizeof( COLORREF ) );
						pBits += 4;
					}
				}
				else
				{
					memcpy( pBits, pSrcBits, rcPattern.Width() * rcPattern.Height() * 4 );
				}
			}
		}

		delete [] pSrcBits;
	}

	void CTransparentBrush::CreateBitmap( int iWidth, int iHeight, BYTE ** pBits )
	{
		BITMAPINFO bmi = { { sizeof( BITMAPINFOHEADER ), iWidth, iHeight, 1, 32, BI_RGB } };
		m_hPattern = CreateDIBSection( NULL, & bmi, DIB_RGB_COLORS, ( void ** ) pBits, NULL, NULL );
		m_rcSrcPattern = CRect( 0, 0, iWidth, iHeight );
		m_bmpPatternDC.Attach( m_hPattern );
	}

	void CTransparentBrush::Release()
	{
		if ( m_hPattern )
		{
			DeleteObject( m_hPattern );
			m_hPattern = NULL;
		}

		m_bmpPatternDC.Detach();
	}
}
