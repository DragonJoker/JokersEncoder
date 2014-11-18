#include "stdafx.h"

#include "Colour.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CColour::CColour()
		:	r( 0 )
		,	g( 0 )
		,	b( 0 )
		,	a( 0 )
	{
	}

	CColour::CColour( ePREDEFINED eCColour )
		:	r( BYTE( ( eCColour & 0xFF000000 ) >> 24 ) )
		,	g( BYTE( ( eCColour & 0x00FF0000 ) >> 16 ) )
		,	b( BYTE( ( eCColour & 0x0000FF00 ) >>  8 ) )
		,	a( BYTE( ( eCColour & 0x000000FF ) >>  0 ) )
	{
	}

	CColour::CColour( CColour const & p_colour )
		:	r( p_colour.r )
		,	g( p_colour.g )
		,	b( p_colour.b )
		,	a( p_colour.a )
	{
	}

	CColour & CColour::operator =( CColour const & p_colour )
	{
		r = p_colour.r;
		g = p_colour.g;
		b = p_colour.b;
		a = p_colour.a;
		return * this;
	}

	CColour & CColour::operator +=( CColour const & p_colour )
	{
		if ( UINT( r ) + UINT( p_colour.r ) < 255 )
		{
			r += p_colour.r;
		}
		else
		{
			r = 255;
		}

		if ( UINT( g ) + UINT( p_colour.g ) < 255 )
		{
			g += p_colour.g;
		}
		else
		{
			g = 255;
		}

		if ( UINT( b ) + UINT( p_colour.b ) < 255 )
		{
			b += p_colour.b;
		}
		else
		{
			b = 255;
		}

		if ( UINT( a ) + UINT( p_colour.a ) < 255 )
		{
			a += p_colour.a;
		}
		else
		{
			a = 255;
		}

		return * this;
	}

	CColour & CColour::operator -=( CColour const & p_colour )
	{
		if ( int( r ) - int( p_colour.r ) > 0 )
		{
			r -= p_colour.r;
		}
		else
		{
			r = 0;
		}

		if ( int( g ) - int( p_colour.g ) > 0 )
		{
			g -= p_colour.g;
		}
		else
		{
			g = 0;
		}

		if ( int( b ) - int( p_colour.b ) > 0 )
		{
			b -= p_colour.b;
		}
		else
		{
			b = 0;
		}

		if ( int( a ) - int( p_colour.a ) > 0 )
		{
			a -= p_colour.a;
		}
		else
		{
			a = 0;
		}

		return * this;
	}

	CColour CColour::FromCOLORREF( COLORREF crCColour, BYTE byAlpha )
	{
		CColour l_clrReturn;
		l_clrReturn.r = GetRValue( crCColour );
		l_clrReturn.g = GetGValue( crCColour );
		l_clrReturn.b = GetBValue( crCColour );
		l_clrReturn.a = byAlpha;
		return l_clrReturn;
	}

	CColour CColour::FromD2DColor( D2D1::ColorF clfCColour )
	{
		CColour l_clrReturn;
		l_clrReturn.r = BYTE( clfCColour.r * 255.0f );
		l_clrReturn.g = BYTE( clfCColour.g * 255.0f );
		l_clrReturn.b = BYTE( clfCColour.b * 255.0f );
		l_clrReturn.a = BYTE( clfCColour.a * 255.0f );
		return l_clrReturn;
	}

	CColour CColour::FromComponents( BYTE p_r, BYTE p_g, BYTE p_b, BYTE p_a )
	{
		CColour l_clrReturn;
		l_clrReturn.r = p_r;
		l_clrReturn.g = p_g;
		l_clrReturn.b = p_b;
		l_clrReturn.a = p_a;
		return l_clrReturn;
	}

	CColour CColour::FromRGB( DWORD dwCColour )
	{
		BYTE r = BYTE( ( dwCColour & 0x00FF0000 ) >> 16 );
		BYTE g = BYTE( ( dwCColour & 0x0000FF00 ) >>  8 );
		BYTE b = BYTE( ( dwCColour & 0x000000FF ) >>  0 );
		BYTE a = 255;
		return FromComponents( r, g, b, a );
	}

	CColour CColour::FromBGR( DWORD dwCColour )
	{
		BYTE b = BYTE( ( dwCColour & 0x00FF0000 ) >> 16 );
		BYTE g = BYTE( ( dwCColour & 0x0000FF00 ) >>  8 );
		BYTE r = BYTE( ( dwCColour & 0x000000FF ) >>  0 );
		BYTE a = 255;
		return FromComponents( r, g, b, a );
	}

	CColour CColour::FromARGB( DWORD dwCColour )
	{
		BYTE a = BYTE( ( dwCColour & 0xFF000000 ) >> 24 );
		BYTE r = BYTE( ( dwCColour & 0x00FF0000 ) >> 16 );
		BYTE g = BYTE( ( dwCColour & 0x0000FF00 ) >>  8 );
		BYTE b = BYTE( ( dwCColour & 0x000000FF ) >>  0 );
		return FromComponents( r, g, b, a );
	}

	CColour CColour::FromBGRA( DWORD dwCColour )
	{
		BYTE b = BYTE( ( dwCColour & 0xFF000000 ) >> 24 );
		BYTE g = BYTE( ( dwCColour & 0x00FF0000 ) >> 16 );
		BYTE r = BYTE( ( dwCColour & 0x0000FF00 ) >>  8 );
		BYTE a = BYTE( ( dwCColour & 0x000000FF ) >>  0 );
		return FromComponents( r, g, b, a );
	}

	CColour CColour::FromRGBA( DWORD dwCColour )
	{
		BYTE r = BYTE( ( dwCColour & 0xFF000000 ) >> 24 );
		BYTE g = BYTE( ( dwCColour & 0x00FF0000 ) >> 16 );
		BYTE b = BYTE( ( dwCColour & 0x0000FF00 ) >>  8 );
		BYTE a = BYTE( ( dwCColour & 0x000000FF ) >>  0 );
		return FromComponents( r, g, b, a );
	}

	CColour CColour::FromABGR( DWORD dwCColour )
	{
		BYTE a = BYTE( ( dwCColour & 0xFF000000 ) >> 24 );
		BYTE b = BYTE( ( dwCColour & 0x00FF0000 ) >> 16 );
		BYTE g = BYTE( ( dwCColour & 0x0000FF00 ) >>  8 );
		BYTE r = BYTE( ( dwCColour & 0x000000FF ) >>  0 );
		return FromComponents( r, g, b, a );
	}

	COLORREF CColour::ToCOLORREF()const
	{
		return ToBGR();
	}

#if DEF_USING_D2D
	D2D1::ColorF CColour::ToD2DColor()const
	{
		return D2D1::ColorF( float( r ) / 255.0f, float( g ) / 255.0f, float( b ) / 255.0f, float( a ) / 255.0f );
	}
#endif
#if DEF_USING_OGL
	GL2D::ColorF CColour::ToGL2DColor()const
	{
		return GL2D::ColorF( float( r ) / 255.0f, float( g ) / 255.0f, float( b ) / 255.0f, float( a ) / 255.0f );
	}
#endif

	DWORD CColour::ToRGB()const
	{
		DWORD dwR = 0;
		DWORD dwG = 0;
		DWORD dwB = 0;
		dwR = DWORD( r ) << 16;
		dwG = DWORD( g ) <<  8;
		dwB = DWORD( b ) <<  0;
		DWORD dwReturn = dwR | dwG | dwB;
		return dwReturn;
	}

	DWORD CColour::ToBGR()const
	{
		DWORD dwR = 0;
		DWORD dwG = 0;
		DWORD dwB = 0;
		dwR = DWORD( r ) <<  0;
		dwG = DWORD( g ) <<  8;
		dwB = DWORD( b ) << 16;
		DWORD dwReturn = dwR | dwG | dwB;
		return dwReturn;
	}

	DWORD CColour::ToARGB()const
	{
		DWORD dwA = 0;
		DWORD dwR = 0;
		DWORD dwG = 0;
		DWORD dwB = 0;
		dwA = DWORD( a ) << 24;
		dwR = DWORD( r ) << 16;
		dwG = DWORD( g ) <<  8;
		dwB = DWORD( b ) <<  0;
		DWORD dwReturn = dwR | dwG | dwB | dwA;
		return dwReturn;
	}

	DWORD CColour::ToRGBA()const
	{
		DWORD dwA = 0;
		DWORD dwR = 0;
		DWORD dwG = 0;
		DWORD dwB = 0;
		dwR = DWORD( r ) << 24;
		dwG = DWORD( g ) << 16;
		dwB = DWORD( b ) <<  8;
		dwA = DWORD( a ) <<  0;
		DWORD dwReturn = dwR | dwG | dwB | dwA;
		return dwReturn;
	}

	DWORD CColour::ToABGR()const
	{
		DWORD dwA = 0;
		DWORD dwR = 0;
		DWORD dwG = 0;
		DWORD dwB = 0;
		dwA = DWORD( a ) << 24;
		dwB = DWORD( b ) << 16;
		dwG = DWORD( g ) <<  8;
		dwR = DWORD( r ) <<  0;
		DWORD dwReturn = dwR | dwG | dwB | dwA;
		return dwReturn;
	}

	unsigned long CColour::ToBGRA()const
	{
		DWORD dwA = 0;
		DWORD dwR = 0;
		DWORD dwG = 0;
		DWORD dwB = 0;
		dwB = DWORD( b ) << 24;
		dwG = DWORD( g ) << 16;
		dwR = DWORD( r ) <<  8;
		dwA = DWORD( a ) <<  0;
		DWORD dwReturn = dwR | dwG | dwB | dwA;
		return dwReturn;
	}

	CColour operator +( CColour const & colourA, CColour const & colourB )
	{
		CColour clReturn( colourA );
		clReturn += colourB;
		return clReturn;
	}

	CColour operator -( CColour const & colourA, CColour const & colourB )
	{
		CColour clReturn( colourA );
		clReturn -= colourB;
		return clReturn;
	}
}
