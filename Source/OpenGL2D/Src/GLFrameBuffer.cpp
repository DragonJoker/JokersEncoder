#include "stdafx.h"

#include "GLFrameBuffer.h"
#include "GLContext.h"

namespace GL2D
{
	CFrameBuffer::CFrameBuffer()
		: CObject()
	{
	}

	CFrameBuffer::~CFrameBuffer()
	{
	}

	HRESULT CFrameBuffer::Initialise( std::shared_ptr< CContext > context )
	{
		HRESULT hr = CObject::Create(
			std::bind( &CContext::GenFramebuffers, context, std::placeholders::_1, std::placeholders::_2 ),
			std::bind( &CContext::DeleteFramebuffers, context, std::placeholders::_1, std::placeholders::_2 )
		);

		m_context = context;
		return hr;
	}

	void CFrameBuffer::Cleanup()
	{
		CObject::Destroy();
	}

	HRESULT CFrameBuffer::Bind( GL2D_GL_FRAMEBUFFER_MODE mode )
	{
		std::shared_ptr< CContext > context = m_context.lock();
		HRESULT hr = E_POINTER;

		if ( context )
		{
			m_mode = mode;
			hr = context->BindFramebuffer( mode, m_name );
		}

		return hr;
	}

	void CFrameBuffer::Unbind()
	{
		std::shared_ptr< CContext > context = m_context.lock();

		if ( context )
		{
			context->BindFramebuffer( m_mode, 0 );
		}
	}
}