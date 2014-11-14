#pragma once

#include "ImageHandler.h"

namespace Joker
{
	class JGRA_API CBmpImageHandler
		: public CImageHandler
	{
	public:
		virtual void Load( Joker::CImage & p_image, String const & p_csFile );
		virtual void Load( Joker::CImage & p_image, UINT uiResourceId );
	};
}