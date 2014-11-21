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

	STDMETHODIMP CFrameBuffer::Initialise( std::shared_ptr< CContext > context )
	{
		HRESULT hr = CObject::Create(
						 std::bind( &CContext::GenFramebuffers, context, std::placeholders::_1, std::placeholders::_2 ),
						 std::bind( &CContext::DeleteFramebuffers, context, std::placeholders::_1, std::placeholders::_2 )
					 );

		m_context = context;
		return hr;
	}

	STDMETHODIMP_( void ) CFrameBuffer::Cleanup()
	{
		CObject::Destroy();
	}

	STDMETHODIMP CFrameBuffer::ReadPixels( std::shared_ptr< CContext > context, GL2D_RECT_U const & rect, GL2D_PIXEL_FORMAT format, void * data )
	{
		return context->ReadPixels( rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, format.format, format.type, data );
	}

	STDMETHODIMP CFrameBuffer::Bind( GL2D_GL_FRAMEBUFFER_MODE mode )
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

	STDMETHODIMP CFrameBuffer::Unbind()
	{
		std::shared_ptr< CContext > context = m_context.lock();
		HRESULT hr = E_POINTER;

		if ( context )
		{
			hr = context->BindFramebuffer( m_mode, 0 );
		}

		return hr;
	}
}