#include "stdafx.h"

#include "ImageManager.h"
#include "Image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef LoadImage
#	undef LoadImage
#endif

namespace Joker
{
	void CImageManager::DeleteImages()
	{
		GetSingleton().DoDeleteImages();
	}

	ImagePtr CImageManager::AddImage( UINT uiIndex, UINT uiResourceID )
	{
		return GetSingleton().DoAddImage( uiIndex, uiResourceID );
	}

	ImagePtr CImageManager::AddImage( UINT uiIndex, String const & strPath )
	{
		return GetSingleton().DoAddImage( uiIndex, strPath );
	}

	ImagePtr CImageManager::AddImage( UINT uiIndex, int iWidth, int iHeight, int iBPP )
	{
		return GetSingleton().DoAddImage( uiIndex, iWidth, iHeight, iBPP );
	}

	ImagePtr CImageManager::AddImage( UINT uiResourceID )
	{
		return GetSingleton().DoAddImage( uiResourceID );
	}

	ImagePtr CImageManager::AddImage( String const & strPath )
	{
		return GetSingleton().DoAddImage( strPath );
	}

	ImagePtr CImageManager::AddImage( int iWidth, int iHeight, int iBPP )
	{
		return GetSingleton().DoAddImage( iWidth, iHeight, iBPP );
	}

	ImagePtr CImageManager::GetImageByIndex( UINT uiIndex )
	{
		return GetSingleton().DoGetImageByIndex( uiIndex );
	}

	ImagePtr CImageManager::GetImageByResourceID( UINT uiResourceID )
	{
		return GetSingleton().DoGetImageByResourceID( uiResourceID );
	}

	ImagePtr CImageManager::DoAddImage( UINT uiIndex, UINT uiResourceID )
	{
		ImagePtr pReturn;

		if ( m_mapImages.find( uiIndex ) != m_mapImages.end() )
		{
			pReturn = m_mapImages.find( uiIndex )->second;
			pReturn->Ref();
		}
		else
		{
			if ( m_mapLoadedResources.find( uiResourceID ) != m_mapLoadedResources.end() )
			{
				pReturn = m_mapImages.find( m_mapLoadedResources.find( uiResourceID )->second )->second;
				pReturn->Ref();
			}
			else
			{
				pReturn = ImagePtr( new CImage( uiIndex, uiResourceID ) );
				m_mapLoadedResources.insert( std::make_pair( uiResourceID, uiIndex ) );
			}

			m_mapImages.insert( std::make_pair( uiIndex, pReturn ) );
			m_uiMaxID = m_mapImages.rbegin()->first;
		}

		return pReturn;
	}

	ImagePtr CImageManager::DoAddImage( UINT uiIndex, String const & strPath )
	{
		ImagePtr pReturn;

		if ( m_mapImages.find( uiIndex ) != m_mapImages.end() )
		{
			pReturn = m_mapImages.find( uiIndex )->second;
			pReturn->Ref();
		}
		else
		{
			String strTmp = strPath;
			CStrUtils::ToLowerCase( strTmp );

			if ( m_mapLoadedPaths.find( strTmp ) != m_mapLoadedPaths.end() )
			{
				pReturn = m_mapImages.find( m_mapLoadedPaths.find( strTmp )->second )->second;
				pReturn->Ref();
			}
			else
			{
				pReturn = ImagePtr( new CImage( uiIndex, strTmp ) );
				m_mapLoadedPaths.insert( std::make_pair( strTmp, uiIndex ) );
			}

			m_mapImages.insert( std::make_pair( uiIndex, pReturn ) );
			m_uiMaxID = m_mapImages.rbegin()->first;
		}

		return pReturn;
	}

	ImagePtr CImageManager::DoAddImage( UINT uiIndex, int iWidth, int iHeight, int iBPP )
	{
		ImagePtr pReturn;

		if ( m_mapImages.find( uiIndex ) != m_mapImages.end() )
		{
			pReturn = m_mapImages.find( uiIndex )->second;
			pReturn->Ref();
		}
		else
		{
			pReturn = ImagePtr( new CImage( uiIndex, iWidth, iHeight, iBPP ) );
			m_mapImages.insert( std::make_pair( uiIndex, pReturn ) );
			m_uiMaxID = m_mapImages.rbegin()->first;
		}

		return pReturn;
	}

	ImagePtr CImageManager::DoAddImage( UINT uiResourceID )
	{
		ImagePtr pReturn;

		m_uiMaxID++;

		if ( m_mapLoadedResources.find( uiResourceID ) != m_mapLoadedResources.end() )
		{
			pReturn = m_mapImages.find( m_mapLoadedResources.find( uiResourceID )->second )->second;
			pReturn->Ref();
		}
		else
		{
			pReturn = ImagePtr( new CImage( m_uiMaxID, uiResourceID ) );
			m_mapLoadedResources.insert( std::make_pair( uiResourceID, m_uiMaxID ) );
		}

		m_mapImages.insert( std::make_pair( m_uiMaxID, pReturn ) );

		return pReturn;
	}

	ImagePtr CImageManager::DoAddImage( String const & strPath )
	{
		ImagePtr pReturn;

		m_uiMaxID++;

		String strTmp = strPath;
		CStrUtils::ToLowerCase( strTmp );

		if ( m_mapLoadedPaths.find( strTmp ) != m_mapLoadedPaths.end() )
		{
			pReturn = m_mapImages.find( m_mapLoadedPaths.find( strTmp )->second )->second;
			pReturn->Ref();
		}
		else
		{
			pReturn = ImagePtr( new CImage( m_uiMaxID, strTmp ) );
			m_mapLoadedPaths.insert( std::make_pair( strTmp, m_uiMaxID ) );
		}

		m_mapImages.insert( std::make_pair( m_uiMaxID, pReturn ) );

		return pReturn;
	}

	ImagePtr CImageManager::DoAddImage( int iWidth, int iHeight, int iBPP )
	{
		ImagePtr pReturn;

		m_uiMaxID++;

		pReturn = ImagePtr( new CImage( m_uiMaxID, iWidth, iHeight, iBPP ) );

		m_mapImages.insert( std::make_pair( m_uiMaxID, pReturn ) );

		return pReturn;
	}

	ImagePtr CImageManager::DoGetImageByIndex( UINT uiIndex )
	{
		ImagePtr pReturn;

		if ( m_mapImages.find( uiIndex ) != m_mapImages.end() )
		{
			pReturn = m_mapImages.find( uiIndex )->second;
		}

		return pReturn;
	}

	ImagePtr CImageManager::DoGetImageByResourceID( UINT uiResourceId )
	{
		ImagePtr pReturn;

		if ( m_mapLoadedResources.find( uiResourceId ) != m_mapLoadedResources.end() )
		{
			pReturn = m_mapImages.find( m_mapLoadedResources.find( uiResourceId )->second )->second;
		}

		return pReturn;
	}

	void CImageManager::DoDeleteImages()
	{
		if ( m_mapImages.size() > 0 )
		{
			for ( static std::map <UINT, ImagePtr >::iterator it = m_mapImages.begin() ; it != m_mapImages.end() ; ++it )
			{
				it->second->Delete();
				it->second.reset();
			}

			m_mapImages.clear();
		}
	}
}
