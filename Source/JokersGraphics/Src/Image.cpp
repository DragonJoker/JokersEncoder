#include "stdafx.h"

#include "Image.h"
#include "Logger.h"

#include <fstream>

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
	CImage::HandlerMap CImage::s_handlers;

	CImage::CImage( unsigned int uiIndex, unsigned int uiResourceID )
		:	CResource( uiIndex )
		,	m_eType( DoRetrieveType( uiResourceID ) )
		,	m_uiResourceID( uiResourceID )
	{
		DoLoadImage();
	}

	CImage::CImage( unsigned int uiIndex, String const & strFilePath )
		:	CResource( uiIndex )
		,	m_strFilePath( strFilePath )
		,	m_eType( eIMAGE_TYPE_BITMAP )
		,	m_uiResourceID( 0xFFFFFFFF )
	{
		CStrUtils::ToLong( m_strFilePath );

		if ( m_strFilePath.find( _T( ".png" ) ) != String::npos )
		{
			m_eType = eIMAGE_TYPE_PNG;
		}

		DoLoadImage();
	}

	CImage::CImage( unsigned int uiIndex, int iWidth, int iHeight, int iBPP )
		:	CResource( uiIndex )
		,	m_eType( eIMAGE_TYPE_BITMAP )
		,	m_uiResourceID( 0xFFFFFFFF )
	{
		ATL::CImage::CreateEx( iWidth, iHeight, iBPP, BI_RGB, NULL, ( iBPP == 32 ? createAlphaChannel : 0 ) );
	}

	CImage::~CImage()
	{
		Destroy();
	}

	void CImage::Delete()
	{
		m_strFilePath.clear();
		Release();
	}

	BOOL CImage::CopyToClipboard( HWND hWndOwner )
	{
		BOOL bReturn = FALSE;

		if ( ::OpenClipboard( hWndOwner ) )
		{
			if ( EmptyClipboard() )
			{
				if ( SetClipboardData( CF_BITMAP, this->operator HBITMAP() ) == NULL )
				{
					CLogger::LogLastError( _T( "CImage::CopyToClipboard - SetClipboardData : " ) );
				}
				else
				{
					bReturn = TRUE;
				}
			}
			else
			{
				CLogger::LogLastError( _T( "CImage::CopyToClipboard - EmptyClipboard : " ) );
			}

			CloseClipboard();
		}
		else
		{
			CLogger::LogLastError( _T( "CImage::CopyToClipboard - OpenClipboard : " ) );
		}

		return bReturn;
	}

	void CImage::CopyFrom( HDC hdcSrc, CRect const & rcSrc, DWORD dwROP )
	{
		StretchBlt( hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), 0, 0, GetWidth(), GetHeight(), dwROP );
	}

	void CImage::CopyFrom( HDC hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, DWORD dwROP )
	{
		StretchBlt( hdcSrc, xSrc, ySrc, cxSrc, cySrc, 0, 0, GetWidth(), GetHeight(), dwROP );
	}

	void CImage::CopyFrom( HDC hdcSrc, CRect const & rcSrc, CRect const & rcDest, DWORD dwROP )
	{
		StretchBlt( hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), dwROP );
	}

	void CImage::CopyFrom( HDC hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP )
	{
		if ( !IsNull() )
		{
			HDC hDC = GetDC();

			::StretchBlt( hDC, xDest, yDest, cxDest, cyDest, hdcSrc, xSrc, ySrc, cxSrc, cySrc, dwROP );

			ReleaseDC();
		}
	}

	void CImage::StretchBlt( HDC hdcDest, CRect const & rcDest, DWORD dwROP, double dRatio )
	{
		StretchBlt( hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), 0, 0, GetWidth(), GetHeight(), dwROP, dRatio );
	}

	void CImage::StretchBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio )
	{
		StretchBlt( hdcDest, xDest, yDest, cxDest, cyDest, 0, 0, GetWidth(), GetHeight(), dwROP, dRatio );
	}

	void CImage::StretchBlt( HDC hdcDest, CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio )
	{
		StretchBlt( hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), rcOrigin.left, rcOrigin.top, rcOrigin.Width(), rcOrigin.Height(), dwROP, dRatio );
	}

	void CImage::StretchBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio )
	{
		if ( !IsNull() )
		{
			ATL::CImage::StretchBlt( hdcDest, int( xDest * dRatio ), int( yDest * dRatio ), int( cxDest * dRatio ), int( cyDest * dRatio ), xOrigin, yOrigin, cxOrigin, cyOrigin, dwROP );
		}
	}

	void CImage::TransparentBlt( HDC hdcDest, CRect const & rcDest, COLORREF crTransparent, double dRatio )
	{
		TransparentBlt( hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), 0, 0, GetWidth(), GetHeight(), crTransparent, dRatio );
	}

	void CImage::TransparentBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio )
	{
		TransparentBlt( hdcDest, xDest, yDest, cxDest, cyDest, 0, 0, GetWidth(), GetHeight(), crTransparent, dRatio );
	}

	void CImage::TransparentBlt( HDC hdcDest, CRect const & rcDest, CRect const & rcOrigin, COLORREF crTransparent, double dRatio )
	{
		TransparentBlt( hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), rcOrigin.left, rcOrigin.top, rcOrigin.Width(), rcOrigin.Height(), crTransparent, dRatio );
	}

	void CImage::TransparentBlt( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio )
	{
		if ( !IsNull() )
		{
			ATL::CImage::TransparentBlt( hdcDest, int( xDest * dRatio ), int( yDest * dRatio ), int( cxDest * dRatio ), int( cyDest * dRatio ), xOrigin, yOrigin, cxOrigin, cyOrigin, crTransparent );
		}
	}

	void CImage::AlphaBlend( HDC hdcDest, CRect const & rcDest, double dRatio )
	{
		AlphaBlend( hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), 0, 0, GetWidth(), GetHeight(), dRatio );
	}

	void CImage::AlphaBlend( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, double dRatio )
	{
		AlphaBlend( hdcDest, xDest, yDest, cxDest, cyDest, 0, 0, GetWidth(), GetHeight(), dRatio );
	}

	void CImage::AlphaBlend( HDC hdcDest, CRect const & rcDest, CRect const & rcOrigin, double dRatio )
	{
		AlphaBlend( hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), rcOrigin.left, rcOrigin.top, rcOrigin.Width(), rcOrigin.Height(), dRatio );
	}

	void CImage::AlphaBlend( HDC hdcDest, int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio )
	{
		if ( !IsNull() )
		{
			ATL::CImage::AlphaBlend( hdcDest, int( xDest * dRatio ), int( yDest * dRatio ), int( cxDest * dRatio ), int( cyDest * dRatio ), xOrigin, yOrigin, cxOrigin, cyOrigin );
		}
	}

	void CImage::DoLoadImage()
	{
		HandlerMap::iterator l_it = s_handlers.find( m_eType );

		if ( l_it != s_handlers.end() )
		{
			if ( !l_it->second->Load( * this ) )
			{
				Destroy();
			}
		}
	}

	void CImage::AddHandler( eIMAGE_TYPE p_eType, CImageHandler * p_pHandler )
	{
		HandlerMap::iterator l_it = s_handlers.find( p_eType );

		if ( l_it == s_handlers.end() )
		{
			s_handlers.insert( HandlerMap::value_type( p_eType, p_pHandler ) );
		}
		else
		{
			delete p_pHandler;
		}
	}

	void CImage::DeleteHandlers()
	{
		std::for_each( s_handlers.begin(), s_handlers.end(), []( HandlerMap::value_type it )
		{
			delete it.second;
		} );
	}

	eIMAGE_TYPE CImage::DoRetrieveType( int iResourceID )
	{
		eIMAGE_TYPE eReturn = eIMAGE_TYPE_BITMAP;
		HINSTANCE hResourceModule = ::AfxGetResourceHandle();
		HRSRC hRes = ::FindResource( hResourceModule, MAKEINTRESOURCE( iResourceID ), _T( "PNG" ) );

		if ( hRes != NULL )
		{
			eReturn = eIMAGE_TYPE_PNG;
		}

		return eReturn;
	}
}
