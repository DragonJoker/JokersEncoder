#pragma once

#include "JokersGraphicsPrerequisites.h"

namespace Joker
{
	class CImage;

	typedef enum
	{	eIMAGE_TYPE_UNKNOWN
	,	eIMAGE_TYPE_BITMAP
	,	eIMAGE_TYPE_PNG
	,	eIMAGE_TYPE_COUNT
	} eIMAGE_TYPE;

	class JGRA_API CImageHandler
	{
	public:
		CImageHandler(){}
		virtual ~CImageHandler(){}

		bool Load( Joker::CImage & p_image );

	protected:
		virtual void Load( Joker::CImage & p_image, String const & p_csFile )=0;
		virtual void Load( Joker::CImage & p_image, UINT uiResourceId )=0;
	};
}