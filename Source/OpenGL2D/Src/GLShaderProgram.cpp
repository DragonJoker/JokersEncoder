#include "stdafx.h"

#include "GLShaderProgram.h"
#include "GLContext.h"
#include "GLUniform.h"
#include "GLAttribute.h"

namespace GL2D
{
	namespace
	{
		template< typename InfoGetter, typename LogGetter >
		HRESULT GetInfoLog( std::shared_ptr< CContext > context, GLuint name, GLenum info, InfoGetter infoGetter, LogGetter logGetter )
		{
			int infologLength = 0;
			int charsWritten  = 0;
			infoGetter( name, info, &infologLength );
			HRESULT hr = glGetLastError( "glGet***iv" );

			if ( infologLength > 0 )
			{
				char * infoLog = new char[infologLength];
				logGetter( name, infologLength, &charsWritten, infoLog );
				hr = glGetLastError( "glGet***InfoLog" );

				if ( strlen( infoLog ) > 0 && strcmp( "No errors.\n", infoLog ) )
				{
					std::cerr << infoLog << std::endl;
				}

				delete [] infoLog;
			}

			return hr;
		}
	}

	CShaderProgram::CShaderProgram( std::string const & vtx, std::string const & pxl )
		: m_program( GL_INVALID_INDEX )
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		GLuint vs = DoCreateShader( context, vtx, GL2D_GL_SHADER_TYPE_VERTEX );
		GLuint fs = DoCreateShader( context, pxl, GL2D_GL_SHADER_TYPE_FRAGMENT );

		HRESULT hr = ( fs != GL_INVALID_INDEX && vs != GL_INVALID_INDEX ) ? S_OK : E_FAIL;

		if ( hr == S_OK )
		{
			m_program = context->CreateProgram();
			hr = m_program == GL_INVALID_INDEX ? E_FAIL : S_OK;
		}

		if ( hr == S_OK )
		{
			hr = context->AttachShader( m_program, vs );
		}

		if ( hr == S_OK )
		{
			hr = context->AttachShader( m_program, fs );
		}

		if ( hr == S_OK )
		{
			hr = context->LinkProgram( m_program );
		}

		if ( hr == S_OK )
		{
			int linked = 0;
			hr = context->GetProgramiv( m_program, GL2D_GL_PROGRAM_QUERY_LINK_STATUS, &linked );
		}

		if ( hr == S_OK )
		{
			hr = GetInfoLog(
				context,
				m_program,
				GL2D_GL_PROGRAM_QUERY_INFO_LOG_LENGTH,
				[&]( GLuint name, GLenum info, int * infologLength ) { context->GetProgramiv( name, info, infologLength ); },
				[&]( GLuint name, int infologLength, int * charsWritten, char * infoLog ) { context->GetProgramInfoLog( name, infologLength, charsWritten, infoLog ); }
			);
		}

		if ( vs != GL_INVALID_INDEX )
		{
			context->DeleteShader( vs );
		}

		if ( fs != GL_INVALID_INDEX )
		{
			context->DeleteShader( fs );
		}

		if ( hr != S_OK )
		{
			throw hr;
		}
	}

	CShaderProgram::~CShaderProgram()
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
			context->DeleteProgram( m_program );

			if ( !active )
			{
				context->EndCurrent( context->GetDC() );
			}
		}
		else
		{
			std::cerr << "Leaked a shader program" << std::endl;
		}

		m_program = GL_INVALID_INDEX;
	}

	STDMETHODIMP CShaderProgram::Bind( std::shared_ptr< CContext > context )
	{
		return context->UseProgram( m_program );
	}

	STDMETHODIMP_( void ) CShaderProgram::Unbind( std::shared_ptr< CContext > context )
	{
		context->UseProgram( 0 );
	}

	STDMETHODIMP_( std::shared_ptr< CUniform > ) CShaderProgram::GetUniform( std::shared_ptr< CContext > context, std::string const & name )
	{
		std::shared_ptr< CUniform > result = std::make_shared< CUniform >();
		HRESULT hr = result->Initialise( m_program, name );

		if ( hr != S_OK )
		{
			result.reset();
		}

		return result;
	}

	STDMETHODIMP_( std::shared_ptr< CAttribute > ) CShaderProgram::GetAttribute( std::shared_ptr< CContext > context, std::string const & name )
	{
		std::shared_ptr< CAttribute > result = std::make_shared< CAttribute >();
		HRESULT hr = result->Initialise( m_program, name );

		if ( hr != S_OK )
		{
			result.reset();
		}

		return result;
	}

	STDMETHODIMP_( GLuint ) CShaderProgram::DoCreateShader( std::shared_ptr< CContext > context, const std::string & source, GL2D_GL_SHADER_TYPE type )
	{
		GLuint shader = context->CreateShader( type );
		HRESULT hr = glGetLastError( "glCreateShader" );

		if ( hr == S_OK )
		{
			int l_iLength = int( source.size() );
			char * l_pszTmp = new char[source.size() + 1];
			strncpy_s( l_pszTmp, source.size() + 1, source.c_str(), source.size() );
			hr = context->ShaderSource( shader, 1, const_cast< const char ** >( &l_pszTmp ), &l_iLength );
			delete [] l_pszTmp;

			if ( hr == S_OK )
			{
				hr = context->CompileShader( shader );
			}

			if ( hr == S_OK )
			{
				int compiled = 0;
				hr = context->GetShaderiv( shader, GL2D_GL_SHADER_QUERY_COMPILE_STATUS, &compiled );
			}

			if ( hr == S_OK )
			{
				hr = GetInfoLog(
					context,
					shader,
					GL2D_GL_SHADER_QUERY_INFO_LOG_LENGTH,
					[&]( GLuint name, GLenum info, int * infologLength ) { context->GetShaderiv( name, info, infologLength ); },
					[&]( GLuint name, int infologLength, int * charsWritten, char * infoLog ) { context->GetShaderInfoLog( name, infologLength, charsWritten, infoLog ); }
				);
			}

			if ( hr != S_OK )
			{
				context->DeleteShader( shader );
				shader = GL_INVALID_INDEX;
			}
		}

		return shader;
	}
}
