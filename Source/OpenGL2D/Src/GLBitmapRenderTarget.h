#ifndef ___OGL2D_BITMAP_RENDER_TARGET_H___
#define ___OGL2D_BITMAP_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"
#include "GLFrameBuffer.h"

namespace GL2D
{
	class CComBitmapRenderTarget
		: public IGL2DBitmapRenderTarget
		, public CComRenderTargetBase
	{
	public:
		GL2D_API CComBitmapRenderTarget();
		GL2D_API virtual ~CComBitmapRenderTarget();

		GL2D_API STDMETHOD_( void, BeginDraw )();
		GL2D_API STDMETHOD( EndDraw )( GL2D_TAG * tag1 = NULL, GL2D_TAG * tag2 = NULL );
		GL2D_API STDMETHOD( GetBitmap )( IGL2DBitmap ** bitmap );

		CFrameBuffer * GetFrameBuffer()
		{
			return &m_frameBuffer;
		}

	protected:
		CFrameBuffer m_frameBuffer;
	};
}

#endif // ___OGL2D_RENDER_TARGET_H___
