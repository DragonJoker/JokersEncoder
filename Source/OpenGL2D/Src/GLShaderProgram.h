#ifndef ___GL2D_GL_ShaderProgram_H___
#define ___GL2D_GL_ShaderProgram_H___

#include "GLObject.h"

namespace GL2D
{
	class CShaderProgram
	{
	public:
		CShaderProgram( std::string const & vtx, std::string const & pxl );
		~CShaderProgram();
		
		STDMETHOD( Bind )( std::shared_ptr< CContext > context );
		STDMETHOD_( void, Unbind )( std::shared_ptr< CContext > context );
		STDMETHOD_( std::shared_ptr< CUniform >, GetUniform )( std::shared_ptr< CContext > context, std::string const & name );
		STDMETHOD_( std::shared_ptr< CAttribute >, GetAttribute )( std::shared_ptr< CContext > context, std::string const & name );

	private:
		STDMETHOD_( GLuint, DoCreateShader )( std::shared_ptr< CContext > context, const std::string & source, GL2D_GL_SHADER_TYPE type );

	private:
		GLuint m_program;
	};
}

#endif
