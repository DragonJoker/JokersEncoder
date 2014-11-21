#include "stdafx.h"

#include "GLUniform.h"
#include "GLContext.h"

#include <glm/gtc/type_ptr.hpp>

namespace GL2D
{
	CUniform::CUniform()
		: m_location( -1 )
	{
	}

	CUniform::~CUniform()
	{
	}

	STDMETHODIMP CUniform::Initialise( GLuint program, std::string const & name )
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		m_location = context->GetUniformLocation( program, name.c_str() );
		HRESULT hr = S_OK;

		if ( m_location == -1 )
		{
			hr = E_FAIL;
		}

		return hr;
	}

	STDMETHODIMP CUniform::SetValue( std::shared_ptr< CContext > context, int value )
	{
		return context->Uniform1i( m_location, value );
	}

	STDMETHODIMP CUniform::SetValue( std::shared_ptr< CContext > context, glm::mat4 const & value )
	{
		return context->UniformMatrix4fv( m_location, 1, GL_FALSE, glm::value_ptr( value ) );
	}
}
