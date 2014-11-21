#include "stdafx.h"

#include "GLTexture.h"
#include "GLContext.h"

namespace GL2D
{
	CTexture::CTexture()
	{
	}

	CTexture::~CTexture()
	{
		std::shared_ptr< CContext > context = m_context.lock();

		if ( !context )
		{
			context = CContext::GetMainContext();
		}

		if ( context )
		{
			context->MakeCurrent( context->GetDC() );
			CObject::Destroy();
			context->EndCurrent( context->GetDC() );
		}
		else
		{
			m_name = GL_INVALID_INDEX;
			std::cerr << "Leaked a texture" << std::endl;
		}
	}

	STDMETHODIMP CTexture::Initialise( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props )
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		m_context = context;
		m_size = size;
		m_format = props.pixelFormat;
		HRESULT hr = Bind( context );

		if ( hr == S_OK )
		{
			hr = context->TexImage2D( GL_TEXTURE_2D, 0, m_format.internal, m_size.width, m_size.height, 0, m_format.format, m_format.type, NULL );

			if ( hr == S_OK )
			{
				hr = Fill( context, data );
			}

			Unbind( context );
		}

		return hr;
	}

	STDMETHODIMP CTexture::Fill( std::shared_ptr< CContext > context, const void * data )
	{
		return context->TexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, m_size.width, m_size.height, m_format.format, m_format.type, data );
	}
	
	STDMETHODIMP CTexture::GetImage( std::shared_ptr< CContext > context, GL2D_PIXEL_FORMAT format, void * data )
	{
		return context->GetTexImage( GL_TEXTURE_2D, 0, format.format, format.type, data );
	}

	STDMETHODIMP CTexture::Bind( std::shared_ptr< CContext > context )
	{
		return context->BindTexture( GL_TEXTURE_2D, m_name );
	}

	STDMETHODIMP CTexture::Interpolate( std::shared_ptr< CContext > context, GL2D_GL_TEXTURE_FILTER filter )
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
		HRESULT hr = glGetLastError( "glTexParameteri" );

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
			hr = glGetLastError( "glTexParameteri" );
		}

		return hr;
	}

	STDMETHODIMP_( void ) CTexture::Unbind( std::shared_ptr< CContext > context )
	{
		CContext::GetActiveContext()->BindTexture( GL_TEXTURE_2D, 0 );
	}

	STDMETHODIMP_( GL2D_PIXEL_FORMAT ) CTexture::GetPixelFormat()const
	{
		return m_format;
	}

	STDMETHODIMP_( GL2D_SIZE_U ) CTexture::GetSize()const
	{
		return m_size;
	}
}
