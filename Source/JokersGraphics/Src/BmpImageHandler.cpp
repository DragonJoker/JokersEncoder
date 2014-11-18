#include "stdafx.h"

#include "BmpImageHandler.h"
#include "Image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	void Joker::CBmpImageHandler::Load( CImage & p_image, String const & p_csFile )
	{
		p_image.Load( p_image.GetFilePath().c_str() );
	}

	void Joker::CBmpImageHandler::Load( CImage & p_image, UINT uiResourceId )
	{
		p_image.LoadFromResource( AfxGetResourceHandle(), MAKEINTRESOURCE( p_image.GetResourceId() ) );
	}
}
