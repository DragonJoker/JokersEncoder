#ifndef ___OGL2D_RENDER_TARGET_H___
#define ___OGL2D_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"
#include "GLFrameBuffer.h"

namespace GL2D
{
	class CComRenderTarget
		: public IGL2DRenderTarget
		, public CComRenderTargetBase
	{
	public:
		GL2D_API CComRenderTarget();
		GL2D_API virtual ~CComRenderTarget();

		GL2D_API STDMETHOD_( void, BeginDraw )();
		GL2D_API STDMETHOD( EndDraw )( GL2D_TAG * tag1 = NULL, GL2D_TAG * tag2 = NULL );

		CFrameBuffer * GetFrameBuffer()
		{
			return &m_frameBuffer;
		}

	protected:
		CFrameBuffer m_frameBuffer;
	};
}

#include "GLRenderTargetBase.h"

#endif // ___OGL2D_RENDER_TARGET_H___
