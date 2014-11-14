#include "stdafx.h"

#include "ImageHandler.h"
#include "Image.h"

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
	bool CImageHandler::Load( CImage & p_image )
	{
		bool l_bReturn = false;

		if ( !p_image.GetFilePath().empty() )
		{
			std::basic_fstream< CString::XCHAR > l_file( p_image.GetFilePath(), std::ios_base::in | std::ios_base::binary );

			if ( l_file )
			{
				l_file.seekg( 0, std::ios_base::end );
				long long llSize = l_file.tellg();
				l_file.seekg( 0, std::ios_base::beg );
				p_image.m_llSize = llSize;
			}

			Load( p_image, p_image.GetFilePath() );
		}
		else if ( p_image.GetId() > 0 )
		{
			HINSTANCE hResourceModule = ::AfxGetResourceHandle();
			HRSRC hRes = ::FindResource( hResourceModule, MAKEINTRESOURCE( p_image.GetId() ), RT_BITMAP );

			if ( ! hRes )
			{
				hRes = ::FindResource( hResourceModule, MAKEINTRESOURCE( p_image.GetId() ), _T( "PNG" ) );
			}

			if ( hRes )
			{
				p_image.m_llSize = ::SizeofResource( hResourceModule, hRes );
			}

			Load( p_image, p_image.GetId() );
		}

		l_bReturn = ! p_image.IsNull();

		return l_bReturn;
	}
}
