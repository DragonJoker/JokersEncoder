// stdafx.cpp : source file that includes just the standard includes
// JokersGraphics.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

namespace Joker
{
	COLORREF MakeRGBA( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA )
	{
		return ( ( dwA & 0xFF ) ) | ( ( dwR & 0xFF ) << 24 ) | ( ( dwG & 0xFF ) << 16 ) | ( ( dwB & 0xFF ) << 8 );
	}

	COLORREF MakeBGRA( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA )
	{
		return ( ( dwA & 0xFF ) ) | ( ( dwB & 0xFF ) << 24 ) | ( ( dwG & 0xFF ) << 16 ) | ( ( dwR & 0xFF ) << 8 );
	}

	COLORREF MakeARGB( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA )
	{
		return ( ( dwA & 0xFF ) << 24 ) | ( ( dwR & 0xFF ) << 16 ) | ( ( dwG & 0xFF ) << 8 ) | ( ( dwB & 0xFF ) );
	}

	COLORREF MakeABGR( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA )
	{
		return ( ( dwA & 0xFF ) << 24 ) | ( ( dwB & 0xFF ) << 16 ) | ( ( dwG & 0xFF ) << 8 ) | ( ( dwR & 0xFF ) );
	}

	COLORREF MakeRGBA( COLORREF crRGB, DWORD dwA )
	{
		return ( ( dwA & 0x000000FF ) ) | ( ( crRGB & 0x000000FF ) << 24 ) | ( ( crRGB & 0x0000FF00 ) << 8 ) | ( ( crRGB & 0x00FF0000 ) >> 8 );
	}

	COLORREF MakeBGRA( COLORREF crRGB, DWORD dwA )
	{
		return ( ( dwA & 0x000000FF ) ) | ( ( crRGB & 0x000000FF ) << 8 ) | ( crRGB & 0x0000FF00 ) << 8 | ( ( crRGB & 0x00FF0000 ) << 8 );
	}

	COLORREF MakeARGB( COLORREF crRGB, DWORD dwA )
	{
		return ( ( dwA & 0x000000FF ) << 24 ) | ( ( crRGB & 0x000000FF ) << 16 ) | ( crRGB & 0x0000FF00 ) | ( ( crRGB & 0x00FF0000 ) >> 16 );
	}

	COLORREF MakeABGR( COLORREF crRGB, DWORD dwA )
	{
		return ( ( dwA & 0x000000FF ) << 24 ) | ( ( crRGB & 0x000000FF ) ) | ( crRGB & 0x0000FF00 ) | ( ( crRGB & 0x00FF0000 ) );
	}

	int GetR( COLORREF crColour )
	{
		return GetBValue( crColour );
	}

	int GetG( COLORREF crColour )
	{
		return GetGValue( crColour );
	}

	int GetB( COLORREF crColour )
	{
		return GetRValue( crColour );
	}

	int GetA( COLORREF crColour )
	{
		return GetAValue( crColour );
	}
}