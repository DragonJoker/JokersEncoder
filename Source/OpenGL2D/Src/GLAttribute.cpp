#include "stdafx.h"

#include "GLAttribute.h"
#include "GLContext.h"

namespace GL2D
{
	CAttribute::CAttribute()
		: m_location( -1 )
	{
	}

	CAttribute::~CAttribute()
	{
	}

	STDMETHODIMP CAttribute::Initialise( GLuint program, std::string const & name )
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		m_location = context->GetAttribLocation( program, name.c_str() );
		HRESULT hr = S_OK;

		if ( m_location == -1 )
		{
			hr = E_FAIL;
		}

		return hr;
	}

	STDMETHODIMP CAttribute::Bind( std::shared_ptr< CContext > context, GLuint offset )
	{
		HRESULT hr = context->EnableVertexAttribArray( m_location );

		if ( hr == S_OK )
		{
			hr = context->VertexAttribPointer( m_location, 2, GL_FLOAT, GL_FALSE, sizeof( SVertex ), BUFFER_OFFSET( offset ) );
		}

		return hr;
	}
}
