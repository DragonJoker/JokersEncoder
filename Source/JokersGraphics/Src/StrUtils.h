#pragma once

#include "JokersGraphicsPrerequisites.h"
#include <cstring>

namespace Joker
{
	class JGRA_API CStrUtils
	{
	public:
		static bool IsInteger( std::string const & strIn );
		static bool IsFloat( std::string const & strIn );
		static bool IsDate( std::string const & strIn, std::string const & strFormat );
		static bool IsDateTime( std::string const & strIn, std::string const & strFormat );
		static bool IsTime( std::string const & strIn, std::string const & strFormat );
		static short ToShort( std::string const & strIn );
		static int ToInt( std::string const & strIn );
		static long ToLong( std::string const & strIn );
		static long long ToLongLong( std::string const & strIn );
		static float ToFloat( std::string const & strIn );
		static double ToDouble( std::string const & strIn );
		static bool IsUpperCase( std::string const & strIn, std::locale const & locale = std::locale( "french" ) );
		static bool IsLowerCase( std::string const & strIn, std::locale const & locale = std::locale( "french" ) );
		static std::string UpperCase( std::string const & strIn, std::locale const & locale = std::locale( "french" ) );
		static std::string LowerCase( std::string const & strIn, std::locale const & locale = std::locale( "french" ) );
		static void Split( std::string const & strIn, std::string const & strDelims, std::vector< std::string > & aResult, BOOL bKeepVoid = TRUE );
		static void Split( std::string const & strIn, char cDelim, std::vector< std::string > & aResult );
		static void SplitText( std::string const & strIn, std::string const & strDelims, std::vector< std::string > & aResult, BOOL bKeepVoid = TRUE );
		static double DistanceJaro( std::string const & strA, std::string const & strB );
		static double DistanceJaroWinkler( std::string const & strA, std::string const & strB, int iPrefixe, double dCoeff );
		static void ToUpperCase( std::string & strIn, std::locale const & locale = std::locale( "french" ) );
		static void ToLowerCase( std::string & strIn, std::locale const & locale = std::locale( "french" ) );
		static std::string & Trim( std::string & strIn, std::string const & strTargets = " ", bool bLeft = true, bool bRight = true );
		static void Format( std::string & strIn, int iMaxSize, char const * szFormat, ... );
		static int Replace( std::string & strIn, std::string const & strToReplace, std::string const & strReplacer );
		static std::string const & ToStr( std::string const & strIn );
		template< size_t N > static std::wstring ToStr( char const ( & strIn )[N] ) { return ToStr( std::string( strIn ) ); }
		static std::string ToStr( char const * strIn ) { return std::string( strIn ); }
		static std::string ToStr( char const cIn );
		static std::wstring ToWStr( std::string const & strIn );
		template< size_t N > static std::wstring ToWStr( char const ( & strIn )[N] ) { return ToWStr( std::string( strIn ) ); }
		static std::wstring ToWStr( char const * strIn ) { return ToWStr( std::string( strIn ) ); }
		static std::wstring ToWStr( char const cIn );
		static String ToTStr( std::string const & strIn );
		static String ToTStr( char const * pszIn );
		static String ToTStr( char const cIn );

		static bool IsInteger( std::wstring const & strIn );
		static bool IsFloat( std::wstring const & strIn );
		static bool IsDate( std::wstring const & strIn, std::wstring const & strFormat );
		static bool IsDateTime( std::wstring const & strIn, std::wstring const & strFormat );
		static bool IsTime( std::wstring const & strIn, std::wstring const & strFormat );
		static short ToShort( std::wstring const & strIn );
		static int ToInt( std::wstring const & strIn );
		static long ToLong( std::wstring const & strIn );
		static long long ToLongLong( std::wstring const & strIn );
		static float ToFloat( std::wstring const & strIn );
		static double ToDouble( std::wstring const & strIn );
		static bool IsUpperCase( std::wstring const & strIn, std::locale const & locale = std::locale( "french" ) );
		static bool IsLowerCase( std::wstring const & strIn, std::locale const & locale = std::locale( "french" ) );
		static std::wstring UpperCase( std::wstring const & strIn, std::locale const & locale = std::locale( "french" ) );
		static std::wstring LowerCase( std::wstring const & strIn, std::locale const & locale = std::locale( "french" ) );
		static void Split( std::wstring const & strIn, std::wstring const & strDelims, std::vector< std::wstring > & aResult, BOOL bKeepVoid = TRUE );
		static void Split( std::wstring const & strIn, wchar_t cDelim, std::vector< std::wstring > & aResult );
		static void SplitText( std::wstring const & strIn, std::wstring const & strDelims, std::vector< std::wstring > & aResult, BOOL bKeepVoid = TRUE );
		static double DistanceJaro( std::wstring const & strA, std::wstring const & strB );
		static double DistanceJaroWinkler( std::wstring const & strA, std::wstring const & strB, int iPrefixe, double dCoeff );
		static void ToUpperCase( std::wstring & strIn, std::locale const & locale = std::locale( "french" ) );
		static void ToLowerCase( std::wstring & strIn, std::locale const & locale = std::locale( "french" ) );
		static std::wstring & Trim( std::wstring & strIn, std::wstring const & strTargets = L" ", bool bLeft = true, bool bRight = true );
		static void Format( std::wstring & strIn, int iMaxSize, wchar_t const * szFormat, ... );
		static int Replace( std::wstring & strIn, std::wstring const & strToReplace, std::wstring const & strReplacer );
		static std::string ToStr( std::wstring const & strIn );
		static std::string ToStr( wchar_t const wcIn );
		template< size_t N > static std::string ToStr( wchar_t const ( & strIn )[N] ) { return ToStr( std::wstring( strIn ) ); }
		static std::string ToStr( wchar_t const * strIn ) { return ToStr( std::wstring( strIn ) ); }
		static std::wstring const & ToWStr( std::wstring const & strIn );
		static std::wstring ToWStr( wchar_t const wcIn );
		template< size_t N > static std::wstring ToWStr( wchar_t const ( & strIn )[N] ) { return ToWStr( std::wstring( strIn ) ); }
		static std::wstring ToWStr( wchar_t const * strIn ) { return ToWStr( std::wstring( strIn ) ); }
		static String ToTStr( std::wstring const & strIn );
		static String ToTStr( wchar_t const * pszIn );
		static String ToTStr( wchar_t const wcIn );

#if defined( DEF_USING_CSTRING )
		static bool IsInteger( CString const & strIn );
		static bool IsFloat( CString const & strIn );
		static bool IsDate( CString const & strIn, CString const & strFormat );
		static bool IsDateTime( CString const & strIn, CString const & strFormat );
		static bool IsTime( CString const & strIn, CString const & strFormat );
		static short ToShort( CString const & strIn );
		static int ToInt( CString const & strIn );
		static long ToLong( CString const & strIn );
		static long long ToLongLong( CString const & strIn );
		static float ToFloat( CString const & strIn );
		static double ToDouble( CString const & strIn );
		static bool IsUpperCase( CString const & strIn, std::locale const & locale = std::locale( "french" ) );
		static bool IsLowerCase( CString const & strIn, std::locale const & locale = std::locale( "french" ) );
		static CString UpperCase( CString const & strIn, std::locale const & locale = std::locale( "french" ) );
		static CString LowerCase( CString const & strIn, std::locale const & locale = std::locale( "french" ) );
		static void Split( CString const & strIn, CString const & strDelims, std::vector< CString > & aResult, BOOL bKeepVoid = TRUE );
		static void Split( CString const & strIn, TCHAR cDelim, std::vector< CString > & aResult );
		static void SplitText( CString const & strIn, CString const & strDelims, std::vector< CString > & aResult, BOOL bKeepVoid = TRUE );
		static double DistanceJaro( CString const & strA, CString const & strB );
		static double DistanceJaroWinkler( CString const & strA, CString const & strB, int iPrefixe, double dCoeff );
		static void ToUpperCase( CString & strIn, std::locale const & locale = std::locale( "french" ) );
		static void ToLowerCase( CString & strIn, std::locale const & locale = std::locale( "french" ) );
		static CString & Trim( CString & strIn, CString const & strTargets = _T( " " ), bool bLeft = true, bool bRight = true );
		static void Format( CString & strIn, int iMaxSize, TCHAR const * szFormat, ... );
		static int Replace( CString & strIn, CString const & strToReplace, CString const & strReplacer );
		static std::string ToStr( CString const & strIn );
		static std::wstring ToWStr( CString const & strIn );
		static String ToTStr( CString const & strIn );
#endif
	};

	bool operator ==( std::string const & strA, char cChar );
	bool operator !=( std::string const & strA, char cChar );
	bool operator  <( std::string const & strA, char cChar );
	bool operator  >( std::string const & strA, char cChar );
	bool operator <=( std::string const & strA, char cChar );
	bool operator >=( std::string const & strA, char cChar );
	std::string operator  +( std::string const & strA, char cChar );
	std::string operator  +( char const * pszText, std::string const & strText );

	template< typename T >
	inline std::string & operator <<( std::string & strTxt, T const & val )
	{
		std::stringstream l_out;
		l_out << val;
		strTxt += l_out.str();
		return strTxt;
	}
	template< typename T >
	inline std::string & operator >>( std::string & strTxt, T & val )
	{
		std::stringstream l_in( strTxt );
		l_in >> val;
		strTxt.assign( l_in.str() );
		return strTxt;
	}

	bool operator ==( std::wstring const & strA, wchar_t cChar );
	bool operator !=( std::wstring const & strA, wchar_t cChar );
	bool operator  <( std::wstring const & strA, wchar_t cChar );
	bool operator  >( std::wstring const & strA, wchar_t cChar );
	bool operator <=( std::wstring const & strA, wchar_t cChar );
	bool operator >=( std::wstring const & strA, wchar_t cChar );
	std::wstring operator  +( std::wstring const & strA, wchar_t cChar );
	std::wstring operator  +( wchar_t const * pszText, std::wstring const & strText );

	template< typename T >
	inline std::wstring & operator <<( std::wstring & strTxt, T const & val )
	{
		std::wstringstream l_out;
		l_out << val;
		strTxt += l_out.str();
		return strTxt;
	}
	template< typename T >
	inline std::wstring & operator >>( std::wstring & strTxt, T & val )
	{
		std::wstringstream l_in( strTxt );
		l_in >> val;
		strTxt.assign( l_in.str() );
		return strTxt;
	}
	
#if defined( DEF_USING_CSTRING )
	bool operator ==( CString const & strA, TCHAR cChar );
	bool operator !=( CString const & strA, TCHAR cChar );
	bool operator  <( CString const & strA, TCHAR cChar );
	bool operator  >( CString const & strA, TCHAR cChar );
	bool operator <=( CString const & strA, TCHAR cChar );
	bool operator >=( CString const & strA, TCHAR cChar );
	CString operator  +( CString const & strA, TCHAR cChar );
	CString operator  +( TCHAR const * pszText, CString const & strText );

	template< typename T >
	inline CString & operator <<( CString & strTxt, T const & val )
	{
		StringStream l_out;
		l_out << val;
		strTxt += l_out.str().c_str();
		return strTxt;
	}
	template< typename T >
	inline CString & operator >>( CString & strTxt, T & val )
	{
		StringStream l_in( ( LPCTSTR )strTxt );
		l_in >> val;
		strTxt = l_in.str().c_str();
		return strTxt;
	}
#endif
}

#pragma warning( pop )