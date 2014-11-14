#ifndef ___OGL2D_RENDER_TARGET_H___
#define ___OGL2D_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"

namespace GL2D
{
	class CComRenderTarget
		: public IGL2DRenderTarget
	{
	public:
		GL2D_API CComRenderTarget();
		GL2D_API virtual ~CComRenderTarget();

		inline const std::shared_ptr< CContext > & GetContext()const
		{
			return m_context;
		}

	protected:
		std::shared_ptr< CContext > m_context;
	};
}

#include "GLRenderTargetBase.h"

#endif // ___OGL2D_RENDER_TARGET_H___
