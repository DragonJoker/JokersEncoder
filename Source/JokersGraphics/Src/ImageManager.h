#pragma once

#include "AutoSingleton.h"
#include "StrUtils.h"
#include <atlimage.h>

#ifdef LoadImage
#	undef LoadImage
#endif

namespace Joker
{
	class JGRA_API CImageManager
		: public CAutoSingleton <CImageManager>
	{
	protected:
		friend class CAutoSingleton <CImageManager>;
		std::map <UINT, ImagePtr> m_mapImages;
		std::map <String, UINT> m_mapLoadedPaths;
		std::map <UINT, UINT> m_mapLoadedResources;
		unsigned int m_uiMaxID;

	protected:
		CImageManager(){}
		~CImageManager(){ DoDeleteImages(); }

	public:
		static void			DeleteImages			();
		static ImagePtr	AddImage				( UINT uiIndex, UINT uiResourceID );
		static ImagePtr	AddImage				( UINT uiIndex, String const & strPath );
		static ImagePtr	AddImage				( UINT uiIndex, int iWidth, int iHeight, int iBPP );
		static ImagePtr	AddImage				( UINT uiResourceID );
		static ImagePtr	AddImage				( String const & strPath );
		static ImagePtr	AddImage				( int iWidth, int iHeight, int iBPP );
		static ImagePtr	GetImageByIndex			( UINT uiIndex );
		static ImagePtr	GetImageByResourceID	( UINT uiResourceID );

	private:
		void		DoDeleteImages			();
		ImagePtr	DoAddImage				( UINT uiIndex, UINT uiResourceID );
		ImagePtr	DoAddImage				( UINT uiIndex, String const & strPath );
		ImagePtr	DoAddImage				( UINT uiIndex, int iWidth, int iHeight, int iBPP );
		ImagePtr	DoAddImage				( UINT uiResourceID );
		ImagePtr	DoAddImage				( String const & strPath );
		ImagePtr	DoAddImage				( int iWidth, int iHeight, int iBPP );
		ImagePtr	DoGetImageByIndex		( UINT uiIndex );
		ImagePtr	DoGetImageByResourceID	( UINT uiResourceID );
	};
}