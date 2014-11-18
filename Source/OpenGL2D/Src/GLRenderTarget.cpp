#include "stdafx.h"

#include "GLRenderTarget.h"
#include "GLContext.h"

#include <cassert>

namespace GL2D
{
	CComRenderTarget::CComRenderTarget()
	{
	}

	CComRenderTarget::~CComRenderTarget()
	{
		std::shared_ptr< CContext > context = GetContext();
		context->MakeCurrent( context->GetDC() );
		m_frameBuffer.Cleanup();
		context->EndCurrent( context->GetDC() );
	}

	STDMETHODIMP_( void ) CComRenderTarget::BeginDraw()
	{
		std::shared_ptr< CContext > context = GetContext();
		context->MakeCurrent( context->GetDC() );
		m_frameBuffer.Bind( GL2D_GL_FRAMEBUFFER_MODE_DRAW );
		glDrawBuffer( GL_BACK );
		context->Disable( GL_DEPTH_TEST );
		GL2D_SIZE_U size = GetPixelSize();
		context->Viewport( 0, 0, size.width, size.height );
		context->Ortho( 0, 1, 0, 1, 0, 1 );
		context->LoadIdentity();
	}

	STDMETHODIMP CComRenderTarget::EndDraw( GL2D_TAG * tag1, GL2D_TAG * tag2 )
	{
		std::shared_ptr< CContext > context = GetContext();
		HRESULT hr = m_frameBuffer.Unbind();
		context->EndCurrent( context->GetDC() );
		context->SwapBuffers( context->GetDC() );
		return hr;
	}
}