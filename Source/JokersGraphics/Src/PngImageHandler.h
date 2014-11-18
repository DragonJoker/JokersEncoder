#pragma once

#include "ImageHandler.h"

namespace Joker
{
	class JGRA_API CPngImageHandler
		: public CImageHandler
	{
	public:
		virtual void Load( Joker::CImage & p_image, String const & p_csFile );
		virtual void Load( Joker::CImage & p_image, UINT uiResourceId );

	private:
		void PreMultiplyRGBChannels( Joker::CImage & p_image );
		void LoadPNGFromHGlobal( HGLOBAL hImg, long long llSize, Joker::CImage & p_image );
	};
}