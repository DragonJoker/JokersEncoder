#ifndef ___GL2D_GL_FRAME_BUFFER_H___
#define ___GL2D_GL_FRAME_BUFFER_H___

#include "GLObject.h"
#include "OpenGL.h"

namespace GL2D
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		G�re un frame buffer OpenGL
	*/
	class CFrameBuffer
		: public CObject
	{
	public:
		/** Constructeur
		*/
		CFrameBuffer();

		/** Destructeur
		*/
		~CFrameBuffer();

		/** Initialise le frame buffer, cr�e ses attaches et autres
		*/
		STDMETHOD( Initialise )( std::shared_ptr< CContext > context );

		/** Nettoie le frame buffer
		*/
		STDMETHOD_( void, Cleanup )();

		/** R�cup�re les pixels du frame buffer, dans le format donn�
		*/
		STDMETHOD( ReadPixels )( std::shared_ptr< CContext > context, GL2D_RECT_U const & srcRect, GL2D_PIXEL_FORMAT format, void * data );

		/** Active le frame buffer, dans le mode voulu
		@param mode
			Le mode d'activation
		*/
		STDMETHOD( Bind )( GL2D_GL_FRAMEBUFFER_MODE mode );

		/** D�sactive le frame buffer
		*/
		STDMETHOD( Unbind )();

	private:
		std::weak_ptr< CContext > m_context;
		GL2D_GL_FRAMEBUFFER_MODE m_mode;
	};
}

#endif
