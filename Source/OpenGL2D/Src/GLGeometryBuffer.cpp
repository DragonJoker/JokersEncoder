#include "stdafx.h"

#include "GLGeometryBuffer.h"
#include "GLContext.h"
#include "GLAttribute.h"

namespace GL2D
{
	CGeometryBuffer::CGeometryBuffer()
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		HRESULT hr = context->GenBuffers( 1, &m_buffer );

		if ( hr == S_OK )
		{
			hr = context->GenVertexArrays( 1, &m_vao );
		}

		if ( hr != S_OK )
		{
			throw hr;
		}
	}

	CGeometryBuffer::~CGeometryBuffer()
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();;
		bool active = true;

		if ( !context )
		{
			context = CContext::GetMainContext();
			context->MakeCurrent( context->GetDC() );
			active = false;
		}

		if ( context )
		{
			if ( m_buffer != GL_INVALID_INDEX )
			{
				context->DeleteBuffers( 1, &m_buffer );
			}

			if ( m_vao != GL_INVALID_INDEX )
			{
				context->DeleteVertexArrays( 1, &m_vao );
			}

			if ( !active )
			{
				context->EndCurrent( context->GetDC() );
			}
		}
		else
		{
			std::cerr << "Leaked a vertex array object" << std::endl;
		}
		
		m_buffer = GL_INVALID_INDEX;
		m_vao = GL_INVALID_INDEX;
	}

	STDMETHODIMP CGeometryBuffer::Initialise( std::shared_ptr< CContext > context, std::shared_ptr< CAttribute > vertex, std::shared_ptr< CAttribute > texture )
	{
		HRESULT hr = context->BindVertexArray( m_vao );

		if ( hr == S_OK )
		{
			context->BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );

			if ( texture )
			{
				texture->Bind( context, 0 );
			}

			if ( vertex )
			{
				vertex->Bind( context, sizeof( glm::vec2 ) );
			}

			hr = context->BindVertexArray( 0 );
		}

		return hr;
	}

	STDMETHODIMP CGeometryBuffer::Fill( std::shared_ptr< CContext > context, SVertex const * data, size_t count )
	{
		HRESULT hr = context->BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );

		if ( hr == S_OK )
		{
			hr = context->BufferData( GL2D_GL_BUFFER_TARGET_ARRAY, sizeof( SVertex ) * count, data, GL2D_GL_BUFFER_USAGE_STATIC_DRAW );
			context->BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, 0 );
		}

		return hr;
	}

	STDMETHODIMP CGeometryBuffer::Bind( std::shared_ptr< CContext > context )
	{
		return context->BindVertexArray( m_vao );
	}

	STDMETHODIMP CGeometryBuffer::Unbind( std::shared_ptr< CContext > context )
	{
		return context->BindVertexArray( 0 );
	}
}
