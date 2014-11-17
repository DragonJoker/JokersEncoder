#pragma once

#define DEF_USING_D2D 1
#define DEF_USING_OGL 0

#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <memory>

#if DEF_USING_OGL
#	include <GL2D.h>
#	include <GLHelper.h>
#endif

#if !defined( STATIC_LIB )
#	if defined( JokersGraphics_EXPORTS )
#		define JGRA_API __declspec( dllexport )
#	else
#		define JGRA_API __declspec( dllimport )
#	endif
#else
#	define JGRA_API
#endif

#define DEF_A2I_STRING

#if defined( __AFX_H__ )
//#	define DEF_USING_CSTRING 1
#endif

typedef std::basic_string<			TCHAR						>	String;
typedef std::basic_stringstream<	TCHAR						>	StringStream;
typedef std::vector<				String						>	StringArray;
typedef std::list<					String						>	StringList;
typedef std::set<					String						>	StrSet;
typedef std::pair<					int,		String			>	StrIntPair;
typedef std::map<					int,		String			>	StrIntMap;
typedef std::map<					float,		String			>	StrFloatMap;
typedef std::map<					UINT,		String			>	StrUIntMap;
typedef std::map<					String,		StringArray		>	StringArrayStrMap;
typedef std::map<					String,		String			>	StrStrMap;
typedef std::map<					String,		String *		>	StrPtrStrMap;
typedef std::map<					String,		int				>	IntStrMap;
typedef std::map<					String,		float			>	FloatStrMap;
typedef std::vector<				StrIntPair					>	StrIntPairArray;
typedef std::map<					String,		StrIntPairArray	>	StrIntPairArrayStrMap;

#pragma warning( push )
#pragma warning( disable:4996 )

namespace Joker
{
	class CImage;
	typedef std::shared_ptr< CImage > ImagePtr;
	
	class CFont;
	typedef std::shared_ptr< CFont > FontPtr;

	typedef enum
	{	eRENDERER_GDI
	,	eRENDERER_D2D
	,	eRENDERER_OGL
	,	eRENDERER_COUNT
	}	eRENDERER;

	JGRA_API COLORREF MakeRGBA( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA );
	JGRA_API COLORREF MakeBGRA( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA );
	JGRA_API COLORREF MakeARGB( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA );
	JGRA_API COLORREF MakeABGR( DWORD dwR, DWORD dwG, DWORD dwB, DWORD dwA );
	JGRA_API COLORREF MakeRGBA( COLORREF crRGB, DWORD dwA );
	JGRA_API COLORREF MakeBGRA( COLORREF crRGB, DWORD dwA );
	JGRA_API COLORREF MakeARGB( COLORREF crRGB, DWORD dwA );
	JGRA_API COLORREF MakeABGR( COLORREF crRGB, DWORD dwA );
	JGRA_API int GetR( COLORREF crColour );
	JGRA_API int GetG( COLORREF crColour );
	JGRA_API int GetB( COLORREF crColour );
	JGRA_API int GetA( COLORREF crColour );

	#define GetAValue( argb ) ( LOBYTE( ( argb ) >>24 ) )

	template< class T >
	inline void SafeRelease( T *& pPointer, bool bDelete = true )
	{
		if ( pPointer && bDelete )
		{
			pPointer->Release();
		}

		pPointer = NULL;
	}

	template< typename T, eRENDERER Renderer > class CTransparentCtrlT;
}