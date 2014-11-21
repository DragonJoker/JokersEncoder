#ifndef ___GL2D_GL_TEXTURE_H___
#define ___GL2D_GL_TEXTURE_H___

#include "OpenGL2DPrerequisites.h"
#include "GLObject.h"

namespace GL2D
{
	class CTexture
		: public CObject
	{
	public:
		CTexture();
		~CTexture();
		
		STDMETHOD( Initialise )( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props );
		STDMETHOD( Fill )( std::shared_ptr< CContext > context, const void * data );
		STDMETHOD( GetImage )( std::shared_ptr< CContext > context, GL2D_PIXEL_FORMAT format, void * data );
		STDMETHOD( Bind )( std::shared_ptr< CContext > context );
		STDMETHOD( Interpolate )( std::shared_ptr< CContext > context, GL2D_GL_TEXTURE_FILTER filter );
		STDMETHOD_( void, Unbind )( std::shared_ptr< CContext > context );
		STDMETHOD_( GL2D_PIXEL_FORMAT, GetPixelFormat )()const;
		STDMETHOD_( GL2D_SIZE_U, GetSize )()const;

	private:
		GL2D_SIZE_U m_size;
		GL2D_PIXEL_FORMAT m_format;
		std::weak_ptr< CContext > m_context;
	};
}

#endif
