#ifndef ___GL2D_GL_FRAME_BUFFER_H___
#define ___GL2D_GL_FRAME_BUFFER_H___

#include "GLObject.h"
#include "OpenGL.h"

namespace GL2D
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Gère un frame buffer OpenGL
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

		/** Initialise le frame buffer, crée ses attaches et autres
		*/
		HRESULT Initialise( std::shared_ptr< CContext > context );

		/** Nettoie le frame buffer
		*/
		void Cleanup();
		/** Active le frame buffer, dans le mode voulu
		@param mode
			Le mode d'activation
		*/
		HRESULT Bind( GL2D_GL_FRAMEBUFFER_MODE mode );

		/** Désactive le frame buffer
		*/
		HRESULT Unbind();

	private:
		std::weak_ptr< CContext > m_context;
		GL2D_GL_FRAMEBUFFER_MODE m_mode;
	};
}

#endif
