#include "stdafx.h"

#include "FontManager.h"
#include "StrUtils.h"

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

namespace Joker
{
	CFontManager::CFontManager()
	{
		m_uiManualID = 1;
	}

	CFontManager::~CFontManager()
	{
		DoCleanup();
	}

	void CFontManager::DeleteFonts()
	{
		GetSingleton().DoCleanup();
	}

	FontPtr CFontManager::AddFont( UINT uiIndex, LPCTSTR szFontInfos )
	{
		return GetSingleton().DoAddFont( uiIndex, szFontInfos );
	}

	UINT CFontManager::AddFont( LPCTSTR szFace, int iHeight, int iWeight, BOOL bItalic, BOOL bUnderlined )
	{
		return GetSingleton().DoAddFont( szFace, iHeight, iWeight, bItalic, bUnderlined );
	}

	FontPtr CFontManager::GetFont( UINT uiIndex, BOOL bManual )
	{
		return GetSingleton().DoGetFont( uiIndex, bManual );
	}

	void CFontManager::DoCleanup()
	{
		if ( m_mapFonts.size() > 0 )
		{
			for ( FontPtrUIntMap::iterator it = m_mapFonts.begin() ; it != m_mapFonts.end() ; ++it )
			{
				it->second.reset();
			}

			m_mapFonts.clear();
		}

		if ( m_mapManualFonts.size() > 0 )
		{
			for ( FontPtrUIntMap::iterator it = m_mapManualFonts.begin() ; it != m_mapManualFonts.end() ; ++it )
			{
				it->second.reset();
			}

			m_mapManualFonts.clear();
		}
	}

	FontPtr CFontManager::DoAddFont( UINT uiIndex, LPCTSTR szFontInfos )
	{
		FontPtr pFont = NULL;

		if ( m_mapFonts.find( uiIndex ) == m_mapFonts.end() )
		{
			StringArray arrayInfos;
			CStrUtils::Split( szFontInfos, _T( "," ), arrayInfos );

			if ( arrayInfos.size() == 5 )
			{
				for ( size_t GL2D_SIZE_I = 0 ; GL2D_SIZE_I < arrayInfos.size() ; GL2D_SIZE_I++ )
				{
					CStrUtils::ToLowerCase( arrayInfos[GL2D_SIZE_I] );
				}

				String strFace		= arrayInfos[0];
				int iFontHeight		= CStrUtils::ToInt( arrayInfos[1] );
				int iWeight			= ( arrayInfos[2] == _T( "bold" ) ? FW_BOLD : FW_NORMAL );
				BOOL bItalic		= ( arrayInfos[3] == _T( "true" ) );
				BOOL bUnderlined	= ( arrayInfos[4] == _T( "true" ) );

				pFont = std::make_shared< CFont >( strFace.c_str(), iFontHeight, iWeight, bItalic, bUnderlined );
				m_mapFonts.insert( std::make_pair( uiIndex, pFont ) );
			}
		}

		return pFont;
	}

	UINT CFontManager::DoAddFont( LPCTSTR szFace, int iHeight, int iWeight, BOOL bItalic, BOOL bUnderlined )
	{
		UINT uiReturn = m_uiManualID++;
		FontPtr pFont = std::make_shared< CFont >( szFace, iHeight, iWeight, bItalic, bUnderlined );
		m_mapManualFonts.insert( std::make_pair( uiReturn, pFont ) );
		return uiReturn;
	}

	FontPtr CFontManager::DoGetFont( UINT uiIndex, BOOL bManual )
	{
		FontPtr pReturn = NULL;
		FontPtrUIntMap::iterator it;

		if ( !bManual )
		{
			it = m_mapFonts.find( uiIndex );

			if ( it != m_mapFonts.end() )
			{
				pReturn = it->second;
			}
		}
		else
		{
			it = m_mapManualFonts.find( uiIndex );

			if ( it != m_mapManualFonts.end() )
			{
				pReturn = it->second;
			}
		}

		return pReturn;
	}
}
