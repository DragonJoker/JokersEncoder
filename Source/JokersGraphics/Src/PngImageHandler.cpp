#include "stdafx.h"

#include "PngImageHandler.h"
#include "Image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	void Joker::CPngImageHandler::Load( CImage & p_image, String const & p_csFile )
	{
		std::basic_fstream< CString::XCHAR > l_file( p_image.GetFilePath(), std::ios_base::in | std::ios_base::binary );

		if ( l_file )
		{
			long long llSize = p_image.GetSize();
			HGLOBAL hImg = ::GlobalAlloc( GHND, SIZE_T( llSize ) );
			BYTE * pbyImg = ( BYTE * )::GlobalLock( hImg );
			l_file.read( ( CString::XCHAR * ) pbyImg, llSize / sizeof( CString::XCHAR ) );
			LoadPNGFromHGlobal( hImg, llSize, p_image );
			::GlobalFree( hImg );
		}
	}

	void Joker::CPngImageHandler::Load( CImage & p_image, UINT uiResourceId )
	{
		HINSTANCE hResourceModule = ::AfxGetResourceHandle();
		HRSRC hRes = ::FindResource( hResourceModule, MAKEINTRESOURCE( p_image.GetResourceId() ), _T( "PNG" ) );

		if ( hRes != NULL )
		{
			unsigned long ulSizeResource = ::SizeofResource( hResourceModule, hRes );
			HGLOBAL hMem = ::LoadResource( hResourceModule, hRes );

			BYTE * pbyRes = ( BYTE * )::LockResource( hMem );
			HGLOBAL hImg = ::GlobalAlloc( GHND, ulSizeResource );
			BYTE * pbyImg = ( BYTE * )::GlobalLock( hImg );
			memcpy_s( pbyImg, ulSizeResource, pbyRes, ulSizeResource );
			::GlobalUnlock( pbyImg );
			LoadPNGFromHGlobal( hImg, ulSizeResource, p_image );
			::GlobalFree( hImg );
		}
	}

	void Joker::CPngImageHandler::PreMultiplyRGBChannels( CImage & p_image )
	{
		unsigned char * pCol = NULL;
		long lW = p_image.GetWidth();
		long lH = p_image.GetHeight();

		for ( long ixy = 0; ixy < lH; ixy ++ )
		{
			for ( long ixx = 0; ixx < lW; ixx ++ )
			{
				pCol = static_cast< unsigned char * >( p_image.GetPixelAddress( ixx, ixy ) );
				unsigned char ucAlpha = pCol[3];

				if ( ucAlpha < 255 )
				{
					pCol[0] = ( ( pCol[0] * ucAlpha ) + 127 ) / 255;
					pCol[1] = ( ( pCol[1] * ucAlpha ) + 127 ) / 255;
					pCol[2] = ( ( pCol[2] * ucAlpha ) + 127 ) / 255;
				}
			}
		}
	}

	void Joker::CPngImageHandler::LoadPNGFromHGlobal( HGLOBAL hImg, long long UNUSED( llSize ), CImage & p_image )
	{
		bool bReturn = false;

		IStream * pStream = NULL;

		if ( SUCCEEDED( ::CreateStreamOnHGlobal( hImg, FALSE, & pStream ) ) )
		{
			p_image.Load( pStream );
			PreMultiplyRGBChannels( p_image );
			pStream->Release();
			bReturn = true;
		}
	}
}
