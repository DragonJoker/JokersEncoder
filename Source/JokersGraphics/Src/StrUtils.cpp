#include "stdafx.h"

#include <algorithm>

#pragma warning( push )
#pragma warning( disable:4996 )

#include "StrUtils.h"

#include <locale>

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_STRING_SIZE 1048576

namespace Joker
{
	bool CStrUtils::IsInteger( std::string const & strIn )
	{
		bool bReturn = true;

		if ( !strIn.empty() )
		{
			bReturn = ( strIn[0] >= '0' && strIn[0] <= '9' ) || strIn[0] == '-';

			for ( std::size_t GL2D_SIZE_I = 1 ; GL2D_SIZE_I < strIn.size() && bReturn ; GL2D_SIZE_I++ )
			{
				bReturn = strIn[GL2D_SIZE_I] >= '0' && strIn[GL2D_SIZE_I] <= '9';
			}
		}

		return bReturn;
	}

	bool CStrUtils::IsFloat( std::string const & strIn )
	{
		bool bReturn = false;
		std::string strText( strIn );
		std::vector< std::string > arraySplitted;
		std::size_t nSize;

		CStrUtils::Replace( strText, ",", "." );
		CStrUtils::Split( strText, ".", arraySplitted );
		nSize = arraySplitted.size();

		if ( nSize > 0 && nSize < 3 )
		{
			bReturn = CStrUtils::IsInteger( arraySplitted[0] );

			if ( bReturn && nSize > 1 )
			{
				bReturn = CStrUtils::IsInteger( arraySplitted[1] );
			}
		}

		return bReturn;
	}

	short CStrUtils::ToShort( std::string const & strIn )
	{
		short sReturn = 0;

		if ( !strIn.empty() )
		{
			sReturn = short( atoi( strIn.c_str() ) );
		}

		return sReturn;
	}

	int CStrUtils::ToInt( std::string const & strIn )
	{
		int iReturn = 0;

		if ( !strIn.empty() )
		{
			iReturn = atoi( strIn.c_str() );
		}

		return iReturn;
	}

	long CStrUtils::ToLong( std::string const & strIn )
	{
		long lReturn = 0;

		if ( !strIn.empty() )
		{
			lReturn = atol( strIn.c_str() );
		}

		return lReturn;
	}

	long long CStrUtils::ToLongLong( std::string const & strIn )
	{
		long long llReturn = 0;

		if ( !strIn.empty() )
		{
			llReturn = long long( atol( strIn.c_str() ) );
		}

		return llReturn;
	}

	float CStrUtils::ToFloat( std::string const & strIn )
	{
		float fReturn = 0;

		if ( !strIn.empty() )
		{
			fReturn = float( atof( strIn.c_str() ) );
		}

		return fReturn;
	}

	double CStrUtils::ToDouble( std::string const & strIn )
	{
		double dReturn = 0;

		if ( !strIn.empty() )
		{
			dReturn = atof( strIn.c_str() );
		}

		return dReturn;
	}

	bool CStrUtils::IsUpperCase( std::string const & strIn, std::locale const & locale )
	{
		return strIn == UpperCase( strIn, locale );
	}

	bool CStrUtils::IsLowerCase( std::string const & strIn, std::locale const & locale )
	{
		return strIn == LowerCase( strIn, locale );
	}

	std::string CStrUtils::UpperCase( std::string const & strIn, std::locale const & locale )
	{
		std::string strReturn;

		for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strIn.size() ; GL2D_SIZE_I++ )
		{
			strReturn += std::toupper( strIn[GL2D_SIZE_I], locale );
		}

		return strReturn;
	}

	std::string CStrUtils::LowerCase( std::string const & strIn, std::locale const & locale )
	{
		std::string strReturn;

		for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strIn.size() ; GL2D_SIZE_I++ )
		{
			strReturn += std::tolower( strIn[GL2D_SIZE_I], locale );
		}

		return strReturn;
	}

	void CStrUtils::Split( std::string const & strIn, std::string const & strDelims, std::vector< std::string > & aResult, BOOL bKeepVoid )
	{
		if ( !strIn.empty() && !strDelims.empty() )
		{
			std::size_t uiNumSplits = 0;
			std::size_t uiStart = 0;
			std::size_t uiPos = 0;

			do
			{
				uiPos = strIn.size();

				for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strDelims.size() ; GL2D_SIZE_I++ )
				{
					uiPos = std::min< std::size_t >( uiPos, strIn.find_first_of( strDelims[GL2D_SIZE_I], uiStart ) );
				}

				if ( uiPos == uiStart )
				{
					uiStart = uiPos + 1;

					if ( bKeepVoid )
					{
						aResult.push_back( "" );
					}
				}
				else if ( uiPos == std::string::npos )
				{
					aResult.push_back( strIn.substr( uiStart ) );
				}
				else
				{
					aResult.push_back( strIn.substr( uiStart, uiPos - uiStart ) );
					uiStart = uiPos + 1;
				}

				if ( !bKeepVoid && uiPos != std::string::npos )
				{
					uiStart = strIn.find_first_not_of( strDelims, uiStart );
				}

				++uiNumSplits;
			}
			while ( uiPos != std::string::npos && uiStart < strIn.size() );
		}
	}

	void CStrUtils::Split( std::string const & strIn, char cDelim, std::vector< std::string > & arrayResult )
	{
		std::size_t uiIndex = 0;
		std::size_t uiPreviousIndex = 0;

		while ( uiPreviousIndex < strIn.size() && ( uiIndex = strIn.find_first_of( cDelim, uiPreviousIndex ) ) != std::string::npos )
		{
			arrayResult.push_back( strIn.substr( uiPreviousIndex, uiIndex - uiPreviousIndex ) );
			uiPreviousIndex = uiIndex + 1;
		}

		if ( uiPreviousIndex < strIn.size() )
		{
			arrayResult.push_back( strIn.substr( uiPreviousIndex ) );
		}
	}

	void CStrUtils::SplitText( std::string const & strIn, std::string const & strTextDelim, std::vector< std::string > & arrayResult, BOOL bKeepVoid )
	{
		std::size_t uiIndex = 0;
		std::size_t uiPreviousIndex = 0;
		std::string strToken;

		while ( uiPreviousIndex < strIn.size() && ( uiIndex = strIn.find( strTextDelim, uiPreviousIndex ) ) != std::string::npos )
		{
			strToken = strIn.substr( uiPreviousIndex, uiIndex - uiPreviousIndex );

			if ( !strToken.empty() )
			{
				arrayResult.push_back( strToken );
			}
			else if ( bKeepVoid )
			{
				arrayResult.push_back( strToken );
			}

			uiPreviousIndex = uiIndex + strTextDelim.size();
		}

		if ( uiPreviousIndex < strIn.size() )
		{
			arrayResult.push_back( strIn.substr( uiPreviousIndex ) );
		}
	}

	double CStrUtils::DistanceJaro( std::string const & strA, std::string const & strB )
	{
		double dReturn = 1;
		std::string strString1 = strA;
		std::string strString2 = strB;

		if ( strString1 != strString2 )
		{
			std::size_t uiMax = std::max< std::size_t >( strString2.size(), strString1.size() );
			std::string strCorresp1;
			std::string strCorresp2;
			double dCommon = 0;
			std::size_t uiMaxDist = ( ( uiMax / 2 ) - 1 );
			std::size_t j;

			for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strString1.size() ; GL2D_SIZE_I++ )
			{
				j = strString2.find( strString1[GL2D_SIZE_I] );

				while ( j != std::string::npos )
				{
					if ( GL2D_SIZE_I >= j )
					{
						if ( GL2D_SIZE_I - j < uiMaxDist )
						{
							strCorresp1 += strString1[GL2D_SIZE_I];
							dCommon += 1;
						}
					}
					else if ( j - GL2D_SIZE_I < uiMaxDist )
					{
						strCorresp1 += strString1[GL2D_SIZE_I];
						dCommon += 1;
					}

					j = strString2.find( strString1[GL2D_SIZE_I], j + 1 );
				}
			}

			for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strString2.size() ; GL2D_SIZE_I++ )
			{
				j = strString1.find( strString2[GL2D_SIZE_I] );

				while ( j != std::string::npos )
				{
					if ( GL2D_SIZE_I >= j )
					{
						if ( GL2D_SIZE_I - j < uiMaxDist )
						{
							strCorresp2 += strString2[GL2D_SIZE_I];
						}
					}
					else if ( j - GL2D_SIZE_I < uiMaxDist )
					{
						strCorresp2 += strString2[GL2D_SIZE_I];
					}

					j = strString1.find( strString2[GL2D_SIZE_I], j + 1 );
				}
			}

			double dTranspositions = 0.0;

			for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strCorresp1.size() ; GL2D_SIZE_I++ )
			{
				if ( strCorresp1[GL2D_SIZE_I] != strCorresp2[GL2D_SIZE_I] )
				{
					dTranspositions += 1.0;
				}
			}

			dTranspositions /= 2.0;

			if ( dCommon > 0 )
			{
				dReturn = std::min< double >( 1, ( ( dCommon / strString1.size() ) + ( dCommon / strString2.size() ) + ( ( dCommon - dTranspositions ) / dCommon ) ) / 3 );
			}
			else
			{
				dReturn = 0;
			}
		}

		return dReturn;
	}

	double CStrUtils::DistanceJaroWinkler( std::string const & strA, std::string const & strB, int iPrefixe, double dCoeff )
	{
		double dJaro = DistanceJaro( strA, strB );
		return dJaro + ( iPrefixe * dCoeff * ( 1 - dJaro ) );
	}

	void CStrUtils::ToUpperCase( std::string & strIn, std::locale const & locale )
	{
		strIn = UpperCase( strIn, locale );
	}

	void CStrUtils::ToLowerCase( std::string & strIn, std::locale const & locale )
	{
		strIn = LowerCase( strIn, locale );
	}

	std::string & CStrUtils::Trim( std::string & strIn, std::string const & strTargets, bool bLeft, bool bRight )
	{
		if ( !strTargets.empty() )
		{
			if ( bLeft )
			{
				std::size_t uiIndex = strIn.find_first_not_of( strTargets.c_str(), 0, strTargets.size() );

				if ( uiIndex != std::string::npos )
				{
					strIn = strIn.substr( uiIndex );
				}
			}

			if ( bRight )
			{
				std::size_t uiIndex = strIn.find_last_not_of( strTargets.c_str(), std::string::npos, strTargets.size() );

				if ( uiIndex != 0 )
				{
					strIn = strIn.substr( 0, uiIndex + 1 );
				}
			}
		}

		return strIn;
	}

	void CStrUtils::Format( std::string & strIn, int iMaxSize, char const * szFormat, ... )
	{
		strIn.clear();

		std::string strText( iMaxSize, 0 );

		try
		{
			va_list vaList;

			if ( szFormat != NULL )
			{
				va_start( vaList, szFormat );
				vsprintf_s( &strText.front(), iMaxSize, szFormat, vaList );
				va_end( vaList );
				strIn = strText;
			}
		}
		catch ( ... )
		{
		}
	}

	int CStrUtils::Replace( std::string & strIn, std::string const & strToReplace, std::string const & strReplacer )
	{
		int iReturn = 0;
		std::size_t uiIndex = 0;
		std::size_t uiPrev = 0;
		std::string strReplaced;

		if ( !strIn.empty() )
		{
			uiIndex = strIn.find( strToReplace );

			if ( uiIndex == std::string::npos )
			{
				strReplaced = strIn;
			}
			else
			{
				while ( uiIndex != std::string::npos )
				{
					strReplaced += strIn.substr( uiPrev, uiIndex - uiPrev ) + strReplacer;
					uiPrev = uiIndex + strToReplace.size();
					uiIndex = strIn.find( strToReplace, uiPrev );
				}

				strReplaced += strIn.substr( uiPrev );
			}

			strIn = strReplaced;
		}

		return iReturn;
	}

	std::string const & CStrUtils::ToStr( std::string const & strIn )
	{
		return strIn;
	}

	std::wstring CStrUtils::ToWStr( std::string const & strIn )
	{
		USES_CONVERSION;
		return A2W( strIn.c_str() );
	}

	std::string CStrUtils::ToStr( char const cIn )
	{
		char szTmp[] = { cIn, 0 };
		return szTmp;
	}

	std::wstring CStrUtils::ToWStr( char const cIn )
	{
		USES_CONVERSION;
		char szTmp[] = { cIn, 0 };
		return A2W( szTmp );
	}

#if defined( _UNICODE )
	String CStrUtils::ToTStr( std::string const & strIn )
	{
		return ToWStr( strIn );
	}

	String CStrUtils::ToTStr( char const * pszIn )
	{
		return ToWStr( std::string( pszIn ) );
	}

	String CStrUtils::ToTStr( char const cIn )
	{
		return ToWStr( cIn );
	}
#else
	String CStrUtils::ToTStr( std::string const & strIn )
	{
		return ToStr( strIn );
	}

	String CStrUtils::ToTStr( char const * pszIn )
	{
		return ToStr( std::string( pszIn ) );
	}

	String CStrUtils::ToTStr( char const cIn )
	{
		return ToStr( cIn );
	}
#endif

	//*************************************************************************************************

	bool CStrUtils::IsInteger( std::wstring const & strIn )
	{
		bool bReturn = true;

		if ( !strIn.empty() )
		{
			bReturn = ( strIn[0] >= L'0' && strIn[0] <= L'9' ) || strIn[0] == L'-';

			for ( std::size_t GL2D_SIZE_I = 1 ; GL2D_SIZE_I < strIn.size() && bReturn ; GL2D_SIZE_I++ )
			{
				bReturn = strIn[GL2D_SIZE_I] >= L'0' && strIn[GL2D_SIZE_I] <= L'9';
			}
		}

		return bReturn;
	}

	bool CStrUtils::IsFloat( std::wstring const & strIn )
	{
		bool bReturn = false;
		std::wstring strText( strIn );
		std::vector< std::wstring > arraySplitted;
		std::size_t nSize;

		CStrUtils::Replace( strText, L",", L"." );
		CStrUtils::Split( strText, L".", arraySplitted );
		nSize = arraySplitted.size();

		if ( nSize > 0 && nSize < 3 )
		{
			bReturn = CStrUtils::IsInteger( arraySplitted[0] );

			if ( bReturn && nSize > 1 )
			{
				bReturn = CStrUtils::IsInteger( arraySplitted[1] );
			}
		}

		return bReturn;
	}

	short CStrUtils::ToShort( std::wstring const & strIn )
	{
		short sReturn = 0;

		if ( !strIn.empty() )
		{
			sReturn = short( _wtoi( strIn.c_str() ) );
		}

		return sReturn;
	}

	int CStrUtils::ToInt( std::wstring const & strIn )
	{
		int iReturn = 0;

		if ( !strIn.empty() )
		{
			iReturn = _wtoi( strIn.c_str() );
		}

		return iReturn;
	}

	long CStrUtils::ToLong( std::wstring const & strIn )
	{
		long lReturn = 0;

		if ( !strIn.empty() )
		{
			lReturn = _wtol( strIn.c_str() );
		}

		return lReturn;
	}

	long long CStrUtils::ToLongLong( std::wstring const & strIn )
	{
		long long llReturn = 0;

		if ( !strIn.empty() )
		{
			llReturn = long long( _wtol( strIn.c_str() ) );
		}

		return llReturn;
	}

	float CStrUtils::ToFloat( std::wstring const & strIn )
	{
		float fReturn = 0;

		if ( !strIn.empty() )
		{
			fReturn = float( _wtof( strIn.c_str() ) );
		}

		return fReturn;
	}

	double CStrUtils::ToDouble( std::wstring const & strIn )
	{
		double dReturn = 0;

		if ( !strIn.empty() )
		{
			dReturn = _wtof( strIn.c_str() );
		}

		return dReturn;
	}

	bool CStrUtils::IsUpperCase( std::wstring const & strIn, std::locale const & locale )
	{
		return strIn == UpperCase( strIn, locale );
	}

	bool CStrUtils::IsLowerCase( std::wstring const & strIn, std::locale const & locale )
	{
		return strIn == LowerCase( strIn, locale );
	}

	std::wstring CStrUtils::UpperCase( std::wstring const & strIn, std::locale const & locale )
	{
		std::wstring strReturn;

		for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strIn.size() ; GL2D_SIZE_I++ )
		{
			strReturn += std::toupper( strIn[GL2D_SIZE_I], locale );
		}

		return strReturn;
	}

	std::wstring CStrUtils::LowerCase( std::wstring const & strIn, std::locale const & locale )
	{
		std::wstring strReturn;

		for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strIn.size() ; GL2D_SIZE_I++ )
		{
			strReturn += std::tolower( strIn[GL2D_SIZE_I], locale );
		}

		return strReturn;
	}

	void CStrUtils::Split( std::wstring const & strIn, std::wstring const & strDelims, std::vector< std::wstring > & aResult, BOOL bKeepVoid )
	{
		if ( !strIn.empty() && !strDelims.empty() )
		{
			std::size_t uiNumSplits = 0;
			std::size_t uiStart = 0;
			std::size_t uiPos = 0;

			do
			{
				uiPos = strIn.size();

				for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strDelims.size() ; GL2D_SIZE_I++ )
				{
					uiPos = std::min< std::size_t >( uiPos, strIn.find_first_of( strDelims[GL2D_SIZE_I], uiStart ) );
				}

				if ( uiPos == uiStart )
				{
					uiStart = uiPos + 1;

					if ( bKeepVoid )
					{
						aResult.push_back( L"" );
					}
				}
				else if ( uiPos == std::wstring::npos )
				{
					aResult.push_back( strIn.substr( uiStart ) );
				}
				else
				{
					aResult.push_back( strIn.substr( uiStart, uiPos - uiStart ) );
					uiStart = uiPos + 1;
				}

				if ( !bKeepVoid && uiPos != std::wstring::npos )
				{
					uiStart = strIn.find_first_not_of( strDelims, uiStart );
				}

				++uiNumSplits;
			}
			while ( uiPos != std::wstring::npos && uiStart < strIn.size() );
		}
	}

	void CStrUtils::Split( std::wstring const & strIn, wchar_t cDelim, std::vector< std::wstring > & arrayResult )
	{
		std::size_t uiIndex = 0;
		std::size_t uiPreviousIndex = 0;

		while ( uiPreviousIndex < strIn.size() && ( uiIndex = strIn.find_first_of( cDelim, uiPreviousIndex ) ) != std::wstring::npos )
		{
			arrayResult.push_back( strIn.substr( uiPreviousIndex, uiIndex - uiPreviousIndex ) );
			uiPreviousIndex = uiIndex + 1;
		}

		if ( uiPreviousIndex < strIn.size() )
		{
			arrayResult.push_back( strIn.substr( uiPreviousIndex ) );
		}
	}

	void CStrUtils::SplitText( std::wstring const & strIn, std::wstring const & strTextDelim, std::vector< std::wstring > & arrayResult, BOOL bKeepVoid )
	{
		std::size_t uiIndex = 0;
		std::size_t uiPreviousIndex = 0;
		std::wstring strToken;

		while ( uiPreviousIndex < strIn.size() && ( uiIndex = strIn.find( strTextDelim, uiPreviousIndex ) ) != std::wstring::npos )
		{
			strToken = strIn.substr( uiPreviousIndex, uiIndex - uiPreviousIndex );

			if ( !strToken.empty() )
			{
				arrayResult.push_back( strToken );
			}
			else if ( bKeepVoid )
			{
				arrayResult.push_back( strToken );
			}

			uiPreviousIndex = uiIndex + strTextDelim.size();
		}

		if ( uiPreviousIndex < strIn.size() )
		{
			arrayResult.push_back( strIn.substr( uiPreviousIndex ) );
		}
	}

	double CStrUtils::DistanceJaro( std::wstring const & strA, std::wstring const & strB )
	{
		double dReturn = 1;
		std::wstring strString1 = strA;
		std::wstring strString2 = strB;

		if ( strString1 != strString2 )
		{
			std::size_t uiMax = std::max< std::size_t >( strString2.size(), strString1.size() );
			std::wstring strCorresp1;
			std::wstring strCorresp2;
			double dCommon = 0;
			std::size_t uiMaxDist = ( ( uiMax / 2 ) - 1 );
			std::size_t j;

			for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strString1.size() ; GL2D_SIZE_I++ )
			{
				j = strString2.find( strString1[GL2D_SIZE_I] );

				while ( j != std::wstring::npos )
				{
					if ( GL2D_SIZE_I >= j )
					{
						if ( GL2D_SIZE_I - j < uiMaxDist )
						{
							strCorresp1 += strString1[GL2D_SIZE_I];
							dCommon += 1;
						}
					}
					else if ( j - GL2D_SIZE_I < uiMaxDist )
					{
						strCorresp1 += strString1[GL2D_SIZE_I];
						dCommon += 1;
					}

					j = strString2.find( strString1[GL2D_SIZE_I], j + 1 );
				}
			}

			for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strString2.size() ; GL2D_SIZE_I++ )
			{
				j = strString1.find( strString2[GL2D_SIZE_I] );

				while ( j != std::wstring::npos )
				{
					if ( GL2D_SIZE_I >= j )
					{
						if ( GL2D_SIZE_I - j < uiMaxDist )
						{
							strCorresp2 += strString2[GL2D_SIZE_I];
						}
					}
					else if ( j - GL2D_SIZE_I < uiMaxDist )
					{
						strCorresp2 += strString2[GL2D_SIZE_I];
					}

					j = strString1.find( strString2[GL2D_SIZE_I], j + 1 );
				}
			}

			double dTranspositions = 0.0;

			for ( std::size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strCorresp1.size() ; GL2D_SIZE_I++ )
			{
				if ( strCorresp1[GL2D_SIZE_I] != strCorresp2[GL2D_SIZE_I] )
				{
					dTranspositions += 1.0;
				}
			}

			dTranspositions /= 2.0;

			if ( dCommon > 0 )
			{
				dReturn = std::min< double >( 1, ( ( dCommon / strString1.size() ) + ( dCommon / strString2.size() ) + ( ( dCommon - dTranspositions ) / dCommon ) ) / 3 );
			}
			else
			{
				dReturn = 0;
			}
		}

		return dReturn;
	}

	double CStrUtils::DistanceJaroWinkler( std::wstring const & strA, std::wstring const & strB, int iPrefixe, double dCoeff )
	{
		double dJaro = DistanceJaro( strA, strB );
		return dJaro + ( iPrefixe * dCoeff * ( 1 - dJaro ) );
	}

	void CStrUtils::ToUpperCase( std::wstring & strIn, std::locale const & locale )
	{
		strIn = UpperCase( strIn, locale );
	}

	void CStrUtils::ToLowerCase( std::wstring & strIn, std::locale const & locale )
	{
		strIn = LowerCase( strIn, locale );
	}

	std::wstring & CStrUtils::Trim( std::wstring & strIn, std::wstring const & strTargets, bool bLeft, bool bRight )
	{
		if ( !strTargets.empty() )
		{
			if ( bLeft )
			{
				std::size_t uiIndex = strIn.find_first_not_of( strTargets.c_str(), 0, strTargets.size() );

				if ( uiIndex != std::wstring::npos )
				{
					strIn = strIn.substr( uiIndex );
				}
			}

			if ( bRight )
			{
				std::size_t uiIndex = strIn.find_last_not_of( strTargets.c_str(), std::wstring::npos, strTargets.size() );

				if ( uiIndex != 0 )
				{
					strIn = strIn.substr( 0, uiIndex + 1 );
				}
			}
		}

		return strIn;
	}

	void CStrUtils::Format( std::wstring & strIn, int iMaxSize, wchar_t const * szFormat, ... )
	{
		strIn.clear();

		std::wstring strText( iMaxSize, 0 );

		try
		{
			va_list vaList;

			if ( szFormat != NULL )
			{
				va_start( vaList, szFormat );
				vswprintf_s( &strText.front(), iMaxSize, szFormat, vaList );
				va_end( vaList );
				strIn = strText;
			}
		}
		catch ( ... )
		{
		}
	}

	int CStrUtils::Replace( std::wstring & strIn, std::wstring const & strToReplace, std::wstring const & strReplacer )
	{
		int iReturn = 0;
		std::size_t uiIndex = 0;
		std::size_t uiPrev = 0;
		std::wstring strReplaced;

		if ( !strIn.empty() )
		{
			uiIndex = strIn.find( strToReplace );

			if ( uiIndex == std::wstring::npos )
			{
				strReplaced = strIn;
			}
			else
			{
				while ( uiIndex != std::wstring::npos )
				{
					strReplaced += strIn.substr( uiPrev, uiIndex - uiPrev ) + strReplacer;
					uiPrev = uiIndex + strToReplace.size();
					uiIndex = strIn.find( strToReplace, uiPrev );
				}

				strReplaced += strIn.substr( uiPrev );
			}

			strIn = strReplaced;
		}

		return iReturn;
	}

	std::string CStrUtils::ToStr( std::wstring const & strIn )
	{
		USES_CONVERSION;
		return W2A( strIn.c_str() );
	}

	std::wstring const & CStrUtils::ToWStr( std::wstring const & strIn )
	{
		return strIn;
	}

	std::string CStrUtils::ToStr( wchar_t const wcIn )
	{
		wchar_t wszTmp[] = { wcIn, 0 };
		USES_CONVERSION;
		return W2A( wszTmp );
	}

	std::wstring CStrUtils::ToWStr( wchar_t const wcIn )
	{
		wchar_t wszTmp[] = { wcIn, 0 };
		return std::wstring( wszTmp );
	}

#if defined( _UNICODE )
	String CStrUtils::ToTStr( std::wstring const & strIn )
	{
		return ToWStr( strIn );
	}

	String CStrUtils::ToTStr( wchar_t const * pszIn )
	{
		return ToWStr( std::wstring( pszIn ) );
	}

	String CStrUtils::ToTStr( wchar_t const wcIn )
	{
		return ToWStr( wcIn );
	}
#else
	String CStrUtils::ToTStr( std::wstring const & strIn )
	{
		return ToStr( strIn );
	}

	String CStrUtils::ToTStr( wchar_t const * pszIn )
	{
		return ToStr( std::wstring( pszIn ) );
	}

	String CStrUtils::ToTStr( wchar_t const wcIn )
	{
		return ToStr( wcIn );
	}
#endif

	//*************************************************************************************************
#if DEF_USE_CSTRING
	bool CStrUtils::IsInteger( CString const & strIn )
	{
		bool bReturn = true;

		if ( !strIn.IsEmpty() )
		{
			bReturn = ( strIn[0] >= _T( '0' ) && strIn[0] <= _T( '9' ) ) || strIn[0] == _T( '-' );

			for ( int GL2D_SIZE_I = 1 ; GL2D_SIZE_I < strIn.GetLength() && bReturn ; GL2D_SIZE_I++ )
			{
				bReturn = strIn[GL2D_SIZE_I] >= _T( '0' ) && strIn[GL2D_SIZE_I] <= _T( '9' );
			}
		}

		return bReturn;
	}

	bool CStrUtils::IsFloat( CString const & strIn )
	{
		bool bReturn = false;
		CString strText( strIn );
		std::vector< CString > arraySplitted;
		std::size_t nSize;

		CStrUtils::Replace( strText, _T( "," ), _T( "." ) );
		CStrUtils::Split( strText, _T( "." ), arraySplitted );
		nSize = arraySplitted.size();

		if ( nSize > 0 && nSize < 3 )
		{
			bReturn = CStrUtils::IsInteger( arraySplitted[0] );

			if ( bReturn && nSize > 1 )
			{
				bReturn = CStrUtils::IsInteger( arraySplitted[1] );
			}
		}

		return bReturn;
	}

	bool CStrUtils::IsDate( CString const & strIn, CString const & strFormat )
	{
		return A2i::CA2iDate::IsDate( ToTStr( strIn ), ToTStr( strFormat ) ) == TRUE;
	}

	bool CStrUtils::IsDateTime( CString const & strIn, CString const & strFormat )
	{
		return A2i::CA2iDateTime::IsDateTime( ToTStr( strIn ), ToTStr( strFormat ) ) == TRUE;
	}

	bool CStrUtils::IsTime( CString const & strIn, CString const & strFormat )
	{
		return A2i::CA2iTime::IsTime( ToTStr( strIn ), ToTStr( strFormat ) ) == TRUE;
	}

	short CStrUtils::ToShort( CString const & strIn )
	{
		short sReturn = 0;

		if ( !strIn.IsEmpty() )
		{
			sReturn = short( _ttoi( strIn ) );
		}

		return sReturn;
	}

	int CStrUtils::ToInt( CString const & strIn )
	{
		int iReturn = 0;

		if ( !strIn.IsEmpty() )
		{
			iReturn = _ttoi( strIn );
		}

		return iReturn;
	}

	long CStrUtils::ToLong( CString const & strIn )
	{
		long lReturn = 0;

		if ( !strIn.IsEmpty() )
		{
			lReturn = _ttol( strIn );
		}

		return lReturn;
	}

	long long CStrUtils::ToLongLong( CString const & strIn )
	{
		long long llReturn = 0;

		if ( !strIn.IsEmpty() )
		{
			llReturn = long long( _ttol( strIn ) );
		}

		return llReturn;
	}

	float CStrUtils::ToFloat( CString const & strIn )
	{
		float fReturn = 0;

		if ( !strIn.IsEmpty() )
		{
			fReturn = float( _ttof( strIn ) );
		}

		return fReturn;
	}

	double CStrUtils::ToDouble( CString const & strIn )
	{
		double dReturn = 0;

		if ( !strIn.IsEmpty() )
		{
			dReturn = _ttof( strIn );
		}

		return dReturn;
	}

	bool CStrUtils::IsUpperCase( CString const & strIn, std::locale const & locale )
	{
		return strIn == UpperCase( strIn, locale );
	}

	bool CStrUtils::IsLowerCase( CString const & strIn, std::locale const & locale )
	{
		return strIn == LowerCase( strIn, locale );
	}

	CString CStrUtils::UpperCase( CString const & strIn, std::locale const & UNUSED( locale ) )
	{
		CString csReturn( strIn );
		return csReturn.MakeUpper();
	}

	CString CStrUtils::LowerCase( CString const & strIn, std::locale const & UNUSED( locale ) )
	{
		CString csReturn( strIn );
		return csReturn.MakeLower();
	}

	void CStrUtils::Split( CString const & strIn, CString const & strDelims, std::vector< CString > & aResult, BOOL bKeepVoid )
	{
		if ( !strIn.IsEmpty() && !strDelims.IsEmpty() )
		{
			int iNumSplits = 0;
			int iStart = 0;

			CString csToken = strIn.Tokenize( strDelims, iStart );

			while ( iStart != -1 )
			{
				if ( csToken.IsEmpty() )
				{
					if ( bKeepVoid )
					{
						aResult.push_back( csToken );
					}
				}
				else
				{
					aResult.push_back( csToken );
				}

				++iNumSplits;
				csToken = strIn.Tokenize( strDelims, iStart );
			}
		}
	}

	void CStrUtils::Split( CString const & strIn, TCHAR cDelim, std::vector< CString > & arrayResult )
	{
		int iIndex = 0;
		int iPreviousIndex = 0;

		while ( iPreviousIndex < strIn.GetLength() && ( iIndex = strIn.Find( cDelim, iPreviousIndex ) ) != -1 )
		{
			arrayResult.push_back( strIn.Mid( iPreviousIndex, iIndex - iPreviousIndex ) );
			iPreviousIndex = iIndex + 1;
		}

		if ( iPreviousIndex < strIn.GetLength() )
		{
			arrayResult.push_back( strIn.Mid( iPreviousIndex ) );
		}
	}

	void CStrUtils::SplitText( CString const & strIn, CString const & strTextDelim, std::vector< CString > & arrayResult, BOOL bKeepVoid )
	{
		int iIndex = 0;
		int iPreviousIndex = 0;
		CString csToken;

		while ( iPreviousIndex < strIn.GetLength() && ( iIndex = strIn.Find( strTextDelim, iPreviousIndex ) ) != -1 )
		{
			csToken = strIn.Mid( iPreviousIndex, iIndex - iPreviousIndex );

			if ( !csToken.IsEmpty() )
			{
				arrayResult.push_back( csToken );
			}
			else if ( bKeepVoid )
			{
				arrayResult.push_back( csToken );
			}

			iPreviousIndex = iIndex + strTextDelim.GetLength();
		}

		if ( iPreviousIndex < strIn.GetLength() )
		{
			arrayResult.push_back( strIn.Mid( iPreviousIndex ) );
		}
	}

	double CStrUtils::DistanceJaro( CString const & strA, CString const & strB )
	{
		double dReturn = 1;
		CString strString1 = strA;
		CString strString2 = strB;

		if ( strString1 != strString2 )
		{
			int iMax = std::max< std::size_t >( strString2.GetLength(), strString1.GetLength() );
			CString strCorresp1;
			CString strCorresp2;
			double dCommon = 0;
			int iMaxDist = ( ( iMax / 2 ) - 1 );
			int j;

			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strString1.GetLength() ; GL2D_SIZE_I++ )
			{
				j = strString2.Find( strString1[GL2D_SIZE_I] );

				while ( j != -1 )
				{
					if ( GL2D_SIZE_I >= j )
					{
						if ( GL2D_SIZE_I - j < iMaxDist )
						{
							strCorresp1 += strString1[GL2D_SIZE_I];
							dCommon += 1;
						}
					}
					else if ( j - GL2D_SIZE_I < iMaxDist )
					{
						strCorresp1 += strString1[GL2D_SIZE_I];
						dCommon += 1;
					}

					j = strString2.Find( strString1[GL2D_SIZE_I], j + 1 );
				}
			}

			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strString2.GetLength() ; GL2D_SIZE_I++ )
			{
				j = strString1.Find( strString2[GL2D_SIZE_I] );

				while ( j != -1 )
				{
					if ( GL2D_SIZE_I >= j )
					{
						if ( GL2D_SIZE_I - j < iMaxDist )
						{
							strCorresp2 += strString2[GL2D_SIZE_I];
						}
					}
					else if ( j - GL2D_SIZE_I < iMaxDist )
					{
						strCorresp2 += strString2[GL2D_SIZE_I];
					}

					j = strString1.Find( strString2[GL2D_SIZE_I], j + 1 );
				}
			}

			double dTranspositions = 0.0;

			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < strCorresp1.GetLength() ; GL2D_SIZE_I++ )
			{
				if ( strCorresp1[GL2D_SIZE_I] != strCorresp2[GL2D_SIZE_I] )
				{
					dTranspositions += 1.0;
				}
			}

			dTranspositions /= 2.0;

			if ( dCommon > 0 )
			{
				dReturn = std::min< double >( 1.0, ( ( dCommon / strString1.GetLength() ) + ( dCommon / strString2.GetLength() ) + ( ( dCommon - dTranspositions ) / dCommon ) ) / 3 );
			}
			else
			{
				dReturn = 0;
			}
		}

		return dReturn;
	}

	double CStrUtils::DistanceJaroWinkler( CString const & strA, CString const & strB, int iPrefixe, double dCoeff )
	{
		double dJaro = DistanceJaro( strA, strB );
		return dJaro + ( iPrefixe * dCoeff * ( 1 - dJaro ) );
	}

	void CStrUtils::ToUpperCase( CString & strIn, std::locale const & UNUSED( locale ) )
	{
		strIn.MakeUpper();
	}

	void CStrUtils::ToLowerCase( CString & strIn, std::locale const & UNUSED( locale ) )
	{
		strIn.MakeLower();
	}

	CString & CStrUtils::Trim( CString & strIn, CString const & strTargets, bool bLeft, bool bRight )
	{
		if ( !strTargets.IsEmpty() )
		{
			if ( bLeft )
			{
				strIn.TrimLeft( strTargets );
			}

			if ( bRight )
			{
				strIn.TrimRight( strTargets );
			}
		}

		return strIn;
	}

	void CStrUtils::Format( CString & strIn, int iMaxSize, TCHAR const * szFormat, ... )
	{
		strIn.Empty();

		TCHAR * pszText = new TCHAR[iMaxSize];
		memset( pszText, 0, iMaxSize );

		try
		{
			va_list vaList;

			if ( szFormat != NULL )
			{
				va_start( vaList, szFormat );
				_vstprintf_s( pszText, iMaxSize, szFormat, vaList );
				va_end( vaList );
				strIn = pszText;
			}
		}
		catch ( ... )
		{
		}

		delete [] pszText;
	}

	int CStrUtils::Replace( CString & strIn, CString const & strToReplace, CString const & strReplacer )
	{
		return strIn.Replace( strToReplace, strReplacer );
	}

#	if defined( _UNICODE )
	std::string CStrUtils::ToStr( CString const & strIn )
	{
		USES_CONVERSION;
		return W2A( strIn );
	}

	std::wstring CStrUtils::ToWStr( CString const & strIn )
	{
		return ( LPCTSTR )strIn;
	}

	String CStrUtils::ToTStr( CString const & strIn )
	{
		return ToWStr( strIn );
	}
#	else
	std::string CStrUtils::ToStr( CString const & strIn )
	{
		return ( LPCTSTR )strIn;
	}

	std::wstring CStrUtils::ToWStr( CString const & strIn )
	{
		USES_CONVERSION;
		return A2W( strIn );
	}

	String CStrUtils::ToTStr( CString const & strIn )
	{
		return ToStr( strIn );
	}
#	endif
#endif
	//*************************************************************************************************

	bool Joker::operator ==( std::string const & strA, char cToCompare )
	{
		char szTmp[] = { cToCompare, 0 };
		return strA == std::string( szTmp );
	}

	bool Joker::operator !=( std::string const & strA, char cToCompare )
	{
		return !operator ==( strA, cToCompare );
	}

	bool Joker::operator <( std::string const & strA, char cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] < cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator >( std::string const & strA, char cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] > cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator <=( std::string const & strA, char cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] <= cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator >=( std::string const & strA, char cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] >= cToCompare;
		}

		return bReturn;
	}

	std::string Joker::operator +( std::string const & strA, char cChar )
	{
		std::string strTmp( strA );
		strTmp += cChar;
		return strTmp;
	}

	std::string Joker::operator +( char const * pszText, std::string const & strText )
	{
		return std::string( pszText ) + strText;
	}

	//*************************************************************************************************

	bool Joker::operator ==( std::wstring const & strA, wchar_t cToCompare )
	{
		wchar_t szTmp[] = { cToCompare, 0 };
		return strA == std::wstring( szTmp );
	}

	bool Joker::operator !=( std::wstring const & strA, wchar_t cToCompare )
	{
		return !operator ==( strA, cToCompare );
	}

	bool Joker::operator <( std::wstring const & strA, wchar_t cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] < cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator >( std::wstring const & strA, wchar_t cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] > cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator <=( std::wstring const & strA, wchar_t cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] <= cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator >=( std::wstring const & strA, wchar_t cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.empty() )
		{
			bReturn = strA[0] >= cToCompare;
		}

		return bReturn;
	}

	std::wstring Joker::operator +( std::wstring const & strA, wchar_t cChar )
	{
		std::wstring strTmp( strA );
		strTmp += cChar;
		return strTmp;
	}

	std::wstring Joker::operator +( wchar_t const * pszText, std::wstring const & strText )
	{
		return std::wstring( pszText ) + strText;
	}

	//*************************************************************************************************
#if DEF_USE_CSTRING
	bool Joker::operator ==( CString const & strA, TCHAR cToCompare )
	{
		TCHAR szTmp[] = { cToCompare, 0 };
		return strA == CString( szTmp );
	}

	bool Joker::operator !=( CString const & strA, TCHAR cToCompare )
	{
		return !A2i::operator ==( strA, cToCompare );
	}

	bool Joker::operator <( CString const & strA, TCHAR cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.IsEmpty() )
		{
			bReturn = strA[0] < cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator >( CString const & strA, TCHAR cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.IsEmpty() )
		{
			bReturn = strA[0] > cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator <=( CString const & strA, TCHAR cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.IsEmpty() )
		{
			bReturn = strA[0] <= cToCompare;
		}

		return bReturn;
	}

	bool Joker::operator >=( CString const & strA, TCHAR cToCompare )
	{
		bool bReturn = cToCompare != 0;

		if ( bReturn && !strA.IsEmpty() )
		{
			bReturn = strA[0] >= cToCompare;
		}

		return bReturn;
	}

	CString Joker::operator +( CString const & strA, TCHAR cChar )
	{
		CString strTmp( strA );
		strTmp += cChar;
		return strTmp;
	}

	CString Joker::operator +( TCHAR const * pszText, CString const & strText )
	{
		return CString( pszText ) + strText;
	}
#endif
}

#pragma warning( pop )