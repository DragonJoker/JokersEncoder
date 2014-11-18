#ifndef ___GL2D_CONTEXT_H___
#define ___GL2D_CONTEXT_H___

#include "OpenGL2DPrerequisites.h"

#include <map>
#include <thread>
#include <mutex>
#include <stack>

#define DEF_USE_FUNCTIONAL 0

#if DEF_USE_FUNCTIONAL
#	define GL_FUNCTION( ret, name, ... ) std::function< ret ( __VA_ARGS__ ) > name
#else
#	define GL_FUNCTION( ret, name, ... ) ret ( CALLBACK * name )( __VA_ARGS__ )
#endif

namespace GL2D
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Gère un contexte OpenGL
	*/
	class CContext
	{
	public:
		/** Constructeur
		@param window
			L'identifcateur de la fenêtre, peut être nul, à ce moment le contexte est initiélisé avec la fenêtre du bureau
		*/
		CContext( HWND window = NULL );

		/** Destructeur
		*/
		~CContext();

		HRESULT Initialise();
		void Cleanup();
		static CContext * GetActiveContext();

		HRESULT MakeCurrent( HDC dc );
		HRESULT EndCurrent( HDC dc );
		HRESULT SwapBuffers( HDC dc );
		HWND GetWindow()const;
		HRESULT Clear( uint32_t param );
		HRESULT ClearColor( float r, float g, float b, float a );
		HRESULT Enable( GLenum value );
		HRESULT Disable( GLenum value );
		HRESULT Viewport( int x, int y, int width, int height );

		int GetInt( GLenum param );

		HRESULT Ortho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar );
		HRESULT PushMatrix();
		HRESULT PopMatrix();
		HRESULT MultMatrix( glm::mat4x4 const & mtx );
		HRESULT LoadIdentity();

		HRESULT GenFramebuffers( GLsizei n, GLuint * framebuffers );
		HRESULT DeleteFramebuffers( GLsizei n, GLuint const * framebuffers );
		HRESULT BindFramebuffer( GL2D_GL_FRAMEBUFFER_MODE target, uint32_t framebuffer );
		uint32_t CheckFramebufferStatus( uint32_t target );
		HRESULT FramebufferTexture( uint32_t target, uint32_t attachment, uint32_t texture, int level );
		HRESULT FramebufferTexture1D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		HRESULT FramebufferTexture2D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		HRESULT FramebufferTextureLayer( uint32_t target, uint32_t attachment, uint32_t texture, int level, int layer );
		HRESULT FramebufferTexture3D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		HRESULT BlitFramebuffer( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
		HRESULT DrawBuffers( int n, uint32_t const * bufs );
		HRESULT GenTextures( GLsizei n, GLuint * textures );
		HRESULT DeleteTextures( GLsizei n, GLuint const * textures );
		HRESULT ActiveTexture( uint32_t texture );
		HRESULT BindTexture( uint32_t target, uint32_t texture );
		HRESULT TexImage2D( uint32_t target, int level, int internalFormat, int width, int height, int border, uint32_t format, uint32_t type, const void * data );
		HRESULT TexSubImage2D( uint32_t target, int level, int xoffset, int yoffset, int width, int height, uint32_t format, uint32_t type, const void * data );
		HRESULT GetTexImage( uint32_t target, int level, uint32_t format, uint32_t type, void * img );
		HRESULT ReadPixels( int x, int y, int width, int height, uint32_t format, uint32_t type, void * data );
		HRESULT FramebufferRenderbuffer( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId );
		HRESULT GenRenderbuffers( GLsizei n, GLuint * ids );
		HRESULT DeleteRenderbuffers( GLsizei n, GLuint const * ids );
		HRESULT BindRenderbuffer( uint32_t target, uint32_t id );
		HRESULT RenderbufferStorage( uint32_t target, uint32_t internalFormat, int width, int height );
		HRESULT RenderbufferStorageMultisample( uint32_t target, int isamples, uint32_t internalFormat, int width, int height );
		HRESULT TexImage2DMultisample( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
		HRESULT GetRenderbufferParameteriv( uint32_t target, uint32_t param, int * value );
		HRESULT GenBuffers( GLsizei n, GLuint * buffers );
		HRESULT DeleteBuffers( GLsizei n, GLuint const * buffers );
		HRESULT BindBuffer( GL2D_GL_BUFFER_TARGET target, uint32_t buffer );
		HRESULT BufferData( GL2D_GL_BUFFER_TARGET target, ptrdiff_t size, const GLvoid * data, GL2D_GL_BUFFER_USAGE usage );
		void * MapBuffer( GL2D_GL_BUFFER_TARGET target, GL2D_GL_ACCESS access );
		bool UnmapBuffer( GL2D_GL_BUFFER_TARGET target );
		void DebugLog( GL2D_GL_DEBUG_SOURCE source, GL2D_GL_DEBUG_TYPE type, uint32_t id, GL2D_GL_DEBUG_SEVERITY severity, int length, const char * message );
		void DebugLogAMD( uint32_t id, GL2D_GL_DEBUG_CATEGORY category, GL2D_GL_DEBUG_SEVERITY severity, int length, const char * message );

		HRESULT DrawTexture( GLuint name, const GL2D_RECT_F & destinationRectangle, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F & sourceRectangle );

		inline HDC GetDC()const
		{
			return m_dc;
		}

	private:
		HGLRC DoCreateContext();
		bool DoSelectPixelFormat();
		void DoCleanup();
		GLuint DoCreateShader( const std::string & source, GL2D_GL_SHADER_TYPE type );
		void DoLoadContext();
		HRESULT DoLoadProgram();
		HRESULT DoLoadBuffer();

		typedef ptrdiff_t GLintptr;
		typedef ptrdiff_t GLsizeiptr;
		typedef char GLchar;

		HWND m_window;
		HDC m_dc;
		HGLRC m_context;
		CContext * m_previous;
		GLuint m_vao;
		GLuint m_buffer;
		GLuint m_program;
		GLuint m_sampler;
		GLuint m_projection;
		GLuint m_view;
		GLuint m_vertex;
		GLuint m_texture;
		typedef glm::mat4x4 mat4x4;
		mat4x4 m_proj;
		std::stack< mat4x4 > m_matrices;

		static std::recursive_mutex m_mutex;
		static std::map< std::thread::id, CContext * > m_activeContexts;

		/**@name FBO */
		//@{

		GL_FUNCTION( void, glGenFramebuffers, GLsizei, GLuint * );
		GL_FUNCTION( void, glDeleteFramebuffers, GLsizei n, GLuint const * framebuffers );
		GL_FUNCTION( void, glBindFramebuffer, GLenum target, GLuint framebuffer );
		GL_FUNCTION( uint32_t, glCheckFramebufferStatus, GLenum target );
		GL_FUNCTION( void, glFramebufferTexture, GLenum target, uint32_t attachment, uint32_t texture, int level );
		GL_FUNCTION( void, glFramebufferTexture1D, GLenum target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		GL_FUNCTION( void, glFramebufferTexture2D, GLenum target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		GL_FUNCTION( void, glFramebufferTextureLayer, GLenum target, uint32_t attachment, uint32_t texture, int level, int layer );

#if DEF_HAS_VARIADIC_TEMPLATES
		GL_FUNCTION( void, glFramebufferTexture3D, GLenum target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		GL_FUNCTION( void, glBlitFramebuffer, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
#else
		void ( CALLBACK * glFramebufferTexture3D )( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		void ( CALLBACK * glBlitFramebuffer )( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
#endif
		GL_FUNCTION( void, glDrawBuffers, int n, GLenum const * bufs );

		//@}
		/**@name Textures */
		//@{

		GL_FUNCTION( void, glActiveTexture, GLenum texture );

		//@}
		/**@name RBO */
		//@{

		GL_FUNCTION( void, glFramebufferRenderbuffer, uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId );
		GL_FUNCTION( void, glGenRenderbuffers, GLsizei n, GLuint * ids );
		GL_FUNCTION( void, glDeleteRenderbuffers, GLsizei n, GLuint const * ids );
		GL_FUNCTION( void, glBindRenderbuffer, uint32_t target, uint32_t id );
		GL_FUNCTION( void, glRenderbufferStorage, uint32_t target, uint32_t internalFormat, int width, int height );
		GL_FUNCTION( void, glRenderbufferStorageMultisample, uint32_t target, int isamples, uint32_t internalFormat, int width, int height );
#if DEF_HAS_VARIADIC_TEMPLATES
		GL_FUNCTION( void, glTexImage2DMultisample, uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
#else
		void ( CALLBACK * glTexImage2DMultisample )( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
#endif
		GL_FUNCTION( void, glGetRenderbufferParameteriv, uint32_t target, uint32_t param, int * value );

		//@}
		/**@name VBO */
		//@{

		GL_FUNCTION( void, glGenBuffers, GLsizei n, GLuint * buffers );
		GL_FUNCTION( void, glDeleteBuffers, GLsizei n, GLuint const * buffers );
		GL_FUNCTION( void, glBindBuffer, GLenum target, GLuint buffer );
		GL_FUNCTION( void, glBufferData, GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage );
		GL_FUNCTION( void *, glMapBuffer, GLenum target, GLenum access );
		GL_FUNCTION( GLboolean, glUnmapBuffer, GLenum target );
#if DEF_HAS_VARIADIC_TEMPLATES
		GL_FUNCTION( void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer );
#else
		void ( CALLBACK * glVertexAttribPointer )( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer );
#endif

		//@}
		/**@name VAO */
		//@{

		GL_FUNCTION( void, glGenVertexArrays, GLsizei n, GLuint * buffers );
		GL_FUNCTION( void, glDeleteVertexArrays, GLsizei n, GLuint const * buffers );
		GL_FUNCTION( void, glBindVertexArray, GLuint buffer );

		//@}
		/**@name Shader */
		//@{

		GL_FUNCTION( GLuint, glCreateShader, GLenum type );
		GL_FUNCTION( void, glDeleteShader, GLuint name );
		GL_FUNCTION( void, glShaderSource, GLuint shader, GLsizei count, const GLchar ** string, const GLint * length );
		GL_FUNCTION( void, glCompileShader, GLuint shader );
		GL_FUNCTION( void, glGetShaderiv, GLuint shader, GLenum pname, GLint * params );
		GL_FUNCTION( void, glGetShaderInfoLog, GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog );
		GL_FUNCTION( GLuint, glCreateProgram );
		GL_FUNCTION( void, glDeleteProgram, GLuint name );
		GL_FUNCTION( void, glAttachShader, GLuint program, GLuint shader );
		GL_FUNCTION( void, glLinkProgram, GLuint program );
		GL_FUNCTION( void, glGetProgramiv, GLuint program, GLenum pname, GLint * params );
		GL_FUNCTION( void, glGetProgramInfoLog, GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog );
		GL_FUNCTION( GLint, glGetUniformLocation, GLuint program, const GLchar * name );
		GL_FUNCTION( void, glUniform1i, GLint location, GLint v0 );
		GL_FUNCTION( void, glUniformMatrix4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value );
		GL_FUNCTION( GLint, glGetAttribLocation, GLuint program, const GLchar * name );
		GL_FUNCTION( GLint, glUseProgram, GLuint program );

		//@}
		/**@name Debug */
		//@{

		typedef void ( __stdcall * PFNGLDEBUGPROC )( uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char * message, void * userParam );
		typedef void ( __stdcall * PFNGLDEBUGAMDPROC )( uint32_t id, uint32_t category, uint32_t severity, int length, const char * message, void * userParam );
		GL_FUNCTION( void, glDebugMessageCallback, PFNGLDEBUGPROC callback, void * userParam );
		GL_FUNCTION( void, glDebugMessageCallbackAMD, PFNGLDEBUGAMDPROC callback, void * userParam );

		//@}
	};
}

#endif
