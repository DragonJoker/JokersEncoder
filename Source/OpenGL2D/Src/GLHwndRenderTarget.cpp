#include "stdafx.h"

#include "GLHwndRenderTarget.h"
#include "GLContext.h"

namespace GL2D
{
	CComHwndRenderTarget::CComHwndRenderTarget()
	{
	}

	CComHwndRenderTarget::~CComHwndRenderTarget()
	{
		DestroyContext();
	}

	STDMETHODIMP CComHwndRenderTarget::CreateContext( const GL2D_RENDER_TARGET_PROPERTIES & renderTargetProperties, const GL2D_HWND_RENDER_TARGET_PROPERTIES & hwndRenderTargetProperties )
	{
		HRESULT hr = E_FAIL;

		try
		{
			m_context = CContext::CreateContext( hwndRenderTargetProperties.hwnd );
			m_context->Initialise();
			hr = S_OK;
		}
		catch ( ... )
		{
		}

		return hr;
	}

	STDMETHODIMP_( void ) CComHwndRenderTarget::DestroyContext()
	{
		if ( m_context != CContext::GetMainContext() )
		{
			m_context->Cleanup();
		}

		m_context.reset();
	}

	STDMETHODIMP_( void ) CComHwndRenderTarget::BeginDraw()
	{
		std::shared_ptr< CContext > context = GetContext();
		context->MakeCurrent( context->GetDC() );
		glDrawBuffer( GL_BACK );
		glFrontFace( GL_CW );
		glCullFace( GL_BACK );
		context->Enable( GL_CULL_FACE );
		context->Enable( GL_TEXTURE_2D );
		context->Disable( GL_DEPTH_TEST );
		context->Enable( GL_BLEND );
		context->BlendFuncSeparate( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		GL2D_SIZE_U size = GetPixelSize();
		context->MatrixMode( GL_PROJECTION );
		context->LoadIdentity();
		context->Viewport( 0, 0, size.width, size.height );
		context->Ortho( 0, 1, 0, 1, 0, 1 );
		context->MatrixMode( GL_MODELVIEW );
		context->LoadIdentity();
	}

	STDMETHODIMP CComHwndRenderTarget::EndDraw( GL2D_TAG * tag1, GL2D_TAG * tag2 )
	{
		std::shared_ptr< CContext > context = GetContext();
		HRESULT hr = context->EndCurrent( context->GetDC() );
		context->SwapBuffers( context->GetDC() );
		return hr;
	}

	STDMETHODIMP_( GL2D_WINDOW_STATE ) CComHwndRenderTarget::CheckWindowState()
	{
		return GL2D_WINDOW_STATE_NONE;
	}

	STDMETHODIMP CComHwndRenderTarget::Resize( const GL2D_SIZE_U * pixelSize )
	{
		HRESULT hr = E_POINTER;

		if ( pixelSize )
		{
			m_size = *pixelSize;
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP_( HWND ) CComHwndRenderTarget::GetHwnd()const
	{
		return m_context->GetWindow();
	}
}
