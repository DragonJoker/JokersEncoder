#ifndef ___GL2D_GL_ATTRIBUTE_H___
#define ___GL2D_GL_ATTRIBUTE_H___

#include "GLObject.h"

namespace GL2D
{
	class CAttribute
	{
	public:
		CAttribute();
		~CAttribute();

		STDMETHOD( Initialise )( GLuint program, std::string const & name );
		STDMETHOD( Bind )( std::shared_ptr< CContext > context, GLuint offset );

	private:
		GLint m_location;
	};
}

#endif
