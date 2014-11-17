#ifndef ___OGL2D_RENDER_TARGET_BASE_H___
#define ___OGL2D_RENDER_TARGET_BASE_H___

#include "OpenGL2DPrerequisites.h"

namespace GL2D
{
	class CComRenderTargetBase
	{
	public:
		CComRenderTargetBase();
		virtual ~CComRenderTargetBase();

		inline const std::shared_ptr< CContext > & GetContext()const
		{
			return m_context;
		}

		inline const GL2D_SIZE_U & GetSize()const
		{
			return m_size;
		}

	protected:
		GL2D_SIZE_U m_size;
		std::shared_ptr< CContext > m_context;
	};
}

#endif
