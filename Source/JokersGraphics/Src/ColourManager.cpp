#include "stdafx.h"

#include "ColourManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CColourManager::CColourManager()
	{
	}

	CColourManager::~CColourManager()
	{
		DoCleanup();
	}

	void CColourManager::AddColour( UINT uiIndex, COLORREF crColour )
	{
		GetSingleton().DoAddColour( uiIndex, crColour );
	}

	COLORREF CColourManager::GetColour( UINT uiIndex )
	{
		return GetSingleton().DoGetColour( uiIndex );
	}

	void CColourManager::DeleteColours()
	{
		return GetSingleton().DoCleanup();
	}

	void CColourManager::DoAddColour( UINT uiIndex, COLORREF crColour )
	{
		if ( m_mapColours.find( uiIndex ) == m_mapColours.end() )
		{
			m_mapColours.insert( std::make_pair( uiIndex, crColour ) );
		}
	}

	COLORREF CColourManager::DoGetColour( UINT uiIndex )
	{
		COLORREF crReturn = 0;

		if ( m_mapColours.find( uiIndex ) != m_mapColours.end() )
		{
			crReturn = m_mapColours.find( uiIndex )->second;
		}

		return crReturn;
	}

	void CColourManager::DoCleanup()
	{
		if ( m_mapColours.size() > 0 )
		{
			m_mapColours.clear();
		}
	}
}
