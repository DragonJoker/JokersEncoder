#ifndef ___GL2D_GL_UNIFORM_H___
#define ___GL2D_GL_UNIFORM_H___

#include "GLObject.h"

namespace GL2D
{
	class CUniform
	{
	public:
		CUniform();
		~CUniform();

		STDMETHOD( Initialise )( GLuint program, std::string const & name );
		STDMETHOD( SetValue )( std::shared_ptr< CContext > context, int value );
		STDMETHOD( SetValue )( std::shared_ptr< CContext > context, glm::mat4 const & value );

	private:
		GLint m_location;
	};
}

#endif
