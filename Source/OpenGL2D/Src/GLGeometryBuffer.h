#ifndef ___GL2D_GL_GeometryBuffer_H___
#define ___GL2D_GL_GeometryBuffer_H___

#include "GLObject.h"

namespace GL2D
{
	class CGeometryBuffer
		: public CObject
	{
	public:
		CGeometryBuffer();
		~CGeometryBuffer();

		STDMETHOD( Initialise )( std::shared_ptr< CContext > context, std::shared_ptr< CAttribute > vertex, std::shared_ptr< CAttribute > texture );
		STDMETHOD( Fill )( std::shared_ptr< CContext > context, SVertex const * data, size_t count );
		STDMETHOD( Bind )( std::shared_ptr< CContext > context );
		STDMETHOD( Unbind )( std::shared_ptr< CContext > context );
		
		HRESULT Fill( std::shared_ptr< CContext > context, std::vector< SVertex > const & data )
		{
			return Fill( context, data.data(), data.size() );
		}

		template< size_t N >
		HRESULT Fill( std::shared_ptr< CContext > context, SVertex const ( & data )[N] )
		{
			return Fill( context, ( SVertex const * )data, N );
		}

	private:
		GLuint m_vao;
		GLuint m_buffer;
	};
}

#endif
