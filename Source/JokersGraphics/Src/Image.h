#pragma once

#include "ImageHandler.h"
#include "Resource.h"
#include <atlimage.h>

#ifdef LoadImage
#	undef LoadImage
#endif

namespace Joker
{
	class JGRA_API CImage
		: public ATL::CImage
		, public CResource
	{
	protected:
		friend class CImageManager;
		friend class std::shared_ptr< CImage >;
		friend class CImageHandler;
		typedef std::map< eIMAGE_TYPE, CImageHandler * > HandlerMap;

	protected:
		CImage( unsigned int uiIndex, unsigned int uiResourceID );
		CImage( unsigned int uiIndex, String const & strFilePath );
		CImage( unsigned int uiIndex, int iWidth, int iHeight, int iBPP );

	public:
		virtual ~CImage();
		void Delete();

		BOOL CopyToClipboard( HWND hWndOwner );

		// Copie du contenu d'un bitmap dans mon image
		void CopyFrom( HDC hdcSrc, CRect const & rcSrc, DWORD dwROP );
		void CopyFrom( HDC hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, DWORD dwROP );
		void CopyFrom( HDC hdcSrc, CRect const & rcSrc, CRect const & rcDest, DWORD dwROP );
		void CopyFrom( HDC hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP );

		// Copie de mon contenu dans un DC
		// en stretch simple
		void StretchBlt( HDC hdcDest, CRect const & rcDest, DWORD dwROP, double dRatio = 1 );
		void StretchBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio = 1 );
		void StretchBlt( HDC hdcDest, CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio = 1 );
		void StretchBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio = 1 );

		// stretch avec une couleur transparente
		void TransparentBlt( HDC hdcDest, CRect const & rcDest, COLORREF crTransparent, double dRatio = 1 );
		void TransparentBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio = 1 );
		void TransparentBlt( HDC hdcDest, CRect const & rcDest, CRect const & rcOrigin, COLORREF crTransparent, double dRatio = 1 );
		void TransparentBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio = 1 );

		// stretch en alpha blend
		void AlphaBlend( HDC hdcDest, CRect const & rcDest, double dRatio = 1 );
		void AlphaBlend( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, double dRatio = 1 );
		void AlphaBlend( HDC hdcDest, CRect const & rcDest, CRect const & rcOrigin, double dRatio = 1 );
		void AlphaBlend( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio = 1 );

		/**@name Accessors */
		//@{
		inline String const & GetFilePath()const
		{
			return m_strFilePath;
		}
		inline long long GetSize()const
		{
			return m_llSize;
		}
		inline unsigned int GetResourceId()const
		{
			return m_uiResourceID;
		}
		//@}

		static void AddHandler( eIMAGE_TYPE p_eType, CImageHandler * p_pHandler );
		static void DeleteHandlers();

	private:
		void DoLoadImage();
		eIMAGE_TYPE DoRetrieveType( int iResourceID );

	protected:
		static HandlerMap s_handlers;

		String m_strFilePath;
		UINT m_uiResourceID;
		eIMAGE_TYPE m_eType;
		long long m_llSize;
	};
}