#include "stdafx.h"

#include "GLContext.h"

#include <sstream>
#include <set>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define BUFFER_OFFSET( x ) ( ( const GLvoid * )( x ) )

namespace GL2D
{
	namespace gl_api
	{
		template< typename Func >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, Func & p_func )
		{
			p_func = reinterpret_cast< Func >( wglGetProcAddress( p_strName.c_str() ) );

			if ( !p_func && !p_strExt.empty() )
			{
				p_func = reinterpret_cast< Func >( wglGetProcAddress( ( p_strName + p_strExt ).c_str() ) );
			}

			return p_func != NULL;
		}

#if DEF_HAS_VARIADIC_TEMPLATES
		template< typename Ret, typename ... Arguments >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( Arguments... ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( Arguments... );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}
#else
		template< typename Ret >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret() > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )();
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7, T8 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8, T9 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7, T8, T9 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}
#endif
		void __stdcall StDebugLog( uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char * message, void * userParam )
		{
			reinterpret_cast< CContext * >( userParam )->DebugLog( GL2D_GL_DEBUG_SOURCE( source ), GL2D_GL_DEBUG_TYPE( type ), id, GL2D_GL_DEBUG_SEVERITY( severity ), length, message );
		}

		void __stdcall StDebugLogAMD( uint32_t id, uint32_t category, uint32_t severity, int length, const char * message, void * userParam )
		{
			reinterpret_cast< CContext * >( userParam )->DebugLogAMD( id, GL2D_GL_DEBUG_CATEGORY( category ), GL2D_GL_DEBUG_SEVERITY( severity ), length, message );
		}
	}

	std::recursive_mutex CContext::m_mutex;
	std::map< std::thread::id, CContext * > CContext::m_activeContexts;

	CContext::CContext( HWND window )
		: m_window( window )
		, m_previous( NULL )
		, m_vao( GL_INVALID_INDEX )
		, m_buffer( GL_INVALID_INDEX )
		, m_program( GL_INVALID_INDEX )
		, m_sampler( GL_INVALID_INDEX )
		, m_projection( GL_INVALID_INDEX )
		, m_view( GL_INVALID_INDEX )
		, m_vertex( GL_INVALID_INDEX )
		, m_texture( GL_INVALID_INDEX )
	{
		m_dc = ::GetDC( m_window );
		m_context = DoCreateContext();
		m_viewMtx.push( glm::mat4x4( 1.0f ) );
		m_projMtx.push( glm::mat4x4( 1.0f ) );
	}

	CContext::~CContext()
	{
		::ReleaseDC( m_window, m_dc );
		wglDeleteContext( m_context );
	}

	HRESULT CContext::Initialise()
	{
		MakeCurrent( GetDC() );
		DoLoadContext();
		HRESULT hr = DoLoadProgram();

		if ( hr == S_OK )
		{
			hr = DoLoadBuffer();
		}

		EndCurrent( GetDC() );
		return hr;
	}

	void CContext::Cleanup()
	{
		MakeCurrent( GetDC() );

		if ( m_program != GL_INVALID_INDEX )
		{
			glDeleteProgram( m_program );
		}

		if ( m_buffer != GL_INVALID_INDEX )
		{
			glDeleteBuffers( 1, &m_buffer );
		}

		if ( m_vao != GL_INVALID_INDEX )
		{
			glDeleteVertexArrays( 1, &m_vao );
		}

		EndCurrent( GetDC() );
	}

	CContext * CContext::GetActiveContext()
	{
		CContext * result;
		m_mutex.lock();
		std::map< std::thread::id, CContext * >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it != m_activeContexts.end() )
		{
			result = it->second;
		}

		m_mutex.unlock();
		return result;
	}

	HRESULT CContext::MakeCurrent( HDC dc )
	{
		wglMakeCurrent( dc, m_context );

		m_mutex.lock();
		std::map< std::thread::id, CContext * >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it != m_activeContexts.end() )
		{
			m_previous = it->second;
		}

		m_activeContexts[std::this_thread::get_id()] = this;
		m_mutex.unlock();
		return glGetLastError( "glMakeCurrent" );
	}

	HRESULT CContext::EndCurrent( HDC dc )
	{
		m_mutex.lock();
		m_activeContexts[std::this_thread::get_id()] = m_previous;

		if ( m_previous )
		{
			wglMakeCurrent( dc, m_previous->m_context );
			m_previous = NULL;
		}
		else
		{
			wglMakeCurrent( dc, NULL );
		}

		m_mutex.unlock();
		return S_OK;
	}

	HRESULT CContext::SwapBuffers( HDC dc )
	{
		return ::SwapBuffers( dc ) ? S_OK : E_FAIL;
	}

	HWND CContext::GetWindow()const
	{
		return m_window;
	}

	HRESULT CContext::Clear( uint32_t param )
	{
		glClear( param );
		return glGetLastError( "glClear" );
	}

	HRESULT CContext::ClearColor( float r, float g, float b, float a )
	{
		glClearColor( r, g, b, a );
		return glGetLastError( "glClearColor" );
	}

	HRESULT CContext::Enable( GLenum value )
	{
		glEnable( value );
		return glGetLastError( "glEnable" );
	}

	HRESULT CContext::Disable( GLenum value )
	{
		glDisable( value );
		return glGetLastError( "glDisable" );
	}

	HRESULT CContext::Viewport( int x, int y, int width, int height )
	{
		glViewport( x, y, width, height );
		return glGetLastError( "glViewport" );
	}

	int CContext::GetInt( GLenum param )
	{
		m_mutex.lock();
		std::map< std::thread::id, CContext * >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it == m_activeContexts.end() )
		{
			MakeCurrent( GetDC() );
		}

		GLint value = 0;
		glGetIntegerv( param, &value );

		if ( it == m_activeContexts.end() )
		{
			EndCurrent( GetDC() );
		}

		m_mutex.unlock();
		return value;
	}

	HRESULT CContext::MatrixMode( GLenum mode )
	{
		if ( mode == GL_PROJECTION )
		{
			m_currentMtx = &m_projMtx;
		}
		else if ( mode == GL_MODELVIEW )
		{
			m_currentMtx = &m_viewMtx;
		}
        
		return glGetLastError( "glMatrixMode" );
	}

	HRESULT CContext::Ortho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar )
	{
		m_currentMtx->top() = m_currentMtx->top() * glm::mat4x4( glm::ortho( left, right, bottom, top, zNear, zFar ) );
		return glGetLastError( "glOrtho" );
	}

	HRESULT CContext::PushMatrix()
	{
		m_currentMtx->push( m_currentMtx->top() );
		return S_OK;
	}

	HRESULT CContext::PopMatrix()
	{
		m_currentMtx->pop();
		return S_OK;
	}

	HRESULT CContext::MultMatrix( glm::mat4x4 const & mtx )
	{
		m_currentMtx->top() = m_currentMtx->top() * mtx;
		return S_OK;
	}

	HRESULT CContext::LoadIdentity()
	{
		m_currentMtx->top() = glm::mat4x4();
		return S_OK;
	}

	HRESULT CContext::GenFramebuffers( GLsizei n, GLuint * framebuffers )
	{
		glGenFramebuffers( n, framebuffers );
		return glGetLastError( "glGenFramebuffers" );
	}

	HRESULT CContext::DeleteFramebuffers( GLsizei n, GLuint const * framebuffers )
	{
		glDeleteFramebuffers( n, framebuffers );
		return glGetLastError( "glDeleteFramebuffers" );
	}

	HRESULT CContext::BindFramebuffer( GL2D_GL_FRAMEBUFFER_MODE target, uint32_t framebuffer )
	{
		glBindFramebuffer( target, framebuffer );
		return glGetLastError( "glBindFramebuffer" );
	}

	uint32_t CContext::CheckFramebufferStatus( uint32_t target )
	{
		return glCheckFramebufferStatus( target );
	}

	HRESULT CContext::FramebufferTexture( uint32_t target, uint32_t attachment, uint32_t texture, int level )
	{
		glFramebufferTexture( target, attachment, texture, level );
		return glGetLastError( "glFramebufferTexture" );
	}

	HRESULT CContext::FramebufferTexture1D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level )
	{
		glFramebufferTexture1D( target, attachment, textarget, texture, level );
		return glGetLastError( "glFramebufferTexture1D" );
	}

	HRESULT CContext::FramebufferTexture2D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level )
	{
		glFramebufferTexture2D( target, attachment, textarget, texture, level );
		return glGetLastError( "glFramebufferTexture2D" );
	}

	HRESULT CContext::FramebufferTextureLayer( uint32_t target, uint32_t attachment, uint32_t texture, int level, int layer )
	{
		glFramebufferTextureLayer( target, attachment, texture, level, layer );
		return glGetLastError( "glFramebufferTextureLayer" );
	}

	HRESULT CContext::FramebufferTexture3D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer )
	{
		glFramebufferTexture3D( target, attachment, textarget, texture, level, layer );
		return glGetLastError( "glFramebufferTexture3D" );
	}

	HRESULT CContext::BlitFramebuffer( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter )
	{
		glBlitFramebuffer( srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
		return glGetLastError( "glBlitFramebuffer" );
	}

	HRESULT CContext::DrawBuffers( int n, uint32_t const * bufs )
	{
		glDrawBuffers( n, bufs );
		return glGetLastError( "glDrawBuffers" );
	}

	HRESULT CContext::GenTextures( GLsizei n, GLuint * textures )
	{
		glGenTextures( n, textures );
		return glGetLastError( "glGenTextures" );
	}

	HRESULT CContext::DeleteTextures( GLsizei n, GLuint const * textures )
	{
		glDeleteTextures( n, textures );
		return glGetLastError( "glDeleteTextures" );
	}

	HRESULT CContext::ActiveTexture( uint32_t texture )
	{
		glActiveTexture( texture );
		return glGetLastError( "glActiveTexture" );
	}

	HRESULT CContext::BindTexture( uint32_t target, uint32_t texture )
	{
		glBindTexture( target, texture );
		return glGetLastError( "glBindTexture" );
	}

	HRESULT CContext::TexImage2D( uint32_t target, int level, int internalFormat, int width, int height, int border, uint32_t format, uint32_t type, const void * data )
	{
		glTexImage2D( target, level, internalFormat, width, height, border, format, type, data );
		return glGetLastError( "glTexImage2D" );
	}

	HRESULT CContext::TexSubImage2D( uint32_t target, int level, int xoffset, int yoffset, int width, int height, uint32_t format, uint32_t type, const void * data )
	{
		glTexSubImage2D( target, level, xoffset, yoffset, width, height, format, type, data );
		return glGetLastError( "glTexSubImage2D" );
	}

	HRESULT CContext::GetTexImage( uint32_t target, int level, uint32_t format, uint32_t type, void * img )
	{
		glGetTexImage( target, level, format, type, img );
		return glGetLastError( "glGetTexImage" );
	}

	HRESULT CContext::ReadPixels( int x, int y, int width, int height, uint32_t format, uint32_t type, void * data )
	{
		glReadPixels( x, y, width, height, format, type, data );
		return glGetLastError( "glReadPixels" );
	}

	HRESULT CContext::FramebufferRenderbuffer( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId )
	{
		glFramebufferRenderbuffer( target, attachmentPoint, renderbufferTarget, renderbufferId );
		return glGetLastError( "FramebufferglFramebufferRenderbufferRenderbuffer" );
	}

	HRESULT CContext::GenRenderbuffers( GLsizei n, GLuint * ids )
	{
		glGenRenderbuffers( n, ids );
		return glGetLastError( "glGenRenderbuffers" );
	}

	HRESULT CContext::DeleteRenderbuffers( GLsizei n, GLuint const * ids )
	{
		glDeleteRenderbuffers( n, ids );
		return glGetLastError( "glDeleteRenderbuffers" );
	}

	HRESULT CContext::BindRenderbuffer( uint32_t target, uint32_t id )
	{
		glBindRenderbuffer( target, id );
		return glGetLastError( "glBindRenderbuffer" );
	}

	HRESULT CContext::RenderbufferStorage( uint32_t target, uint32_t internalFormat, int width, int height )
	{
		glRenderbufferStorage( target, internalFormat, width, height );
		return glGetLastError( "glRenderbufferStorage" );
	}

	HRESULT CContext::RenderbufferStorageMultisample( uint32_t target, int isamples, uint32_t internalFormat, int width, int height )
	{
		glRenderbufferStorageMultisample( target, isamples, internalFormat, width, height );
		return glGetLastError( "glRenderbufferStorageMultisample" );
	}

	HRESULT CContext::TexImage2DMultisample( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations )
	{
		glTexImage2DMultisample( target, samples, internalformat, width, height, fixedsamplelocations );
		return glGetLastError( "glTexImage2DMultisample" );
	}

	HRESULT CContext::GetRenderbufferParameteriv( uint32_t target, uint32_t param, int * value )
	{
		glGetRenderbufferParameteriv( target, param, value );
		return glGetLastError( "glGetRenderbufferParameteriv" );
	}

	HRESULT CContext::GenBuffers( GLsizei n, GLuint * buffers )
	{
		glGenBuffers( n, buffers );
		return glGetLastError( "glGenBuffers" );
	}

	HRESULT CContext::DeleteBuffers( GLsizei n, GLuint const * buffers )
	{
		glDeleteBuffers( n, buffers );
		return glGetLastError( "glDeleteBuffers" );
	}

	HRESULT CContext::BindBuffer( GL2D_GL_BUFFER_TARGET target, GLuint buffer )
	{
		glBindBuffer( target, buffer );
		return glGetLastError( "glBindBuffer" );
	}

	HRESULT CContext::BufferData( GL2D_GL_BUFFER_TARGET target, ptrdiff_t size, const GLvoid * data, GL2D_GL_BUFFER_USAGE usage )
	{
		glBufferData( target, GLsizeiptr( size ), data, usage );
		return glGetLastError( "glBufferData" );
	}

	void * CContext::MapBuffer( GL2D_GL_BUFFER_TARGET target, GL2D_GL_ACCESS access )
	{
		void * result = glMapBuffer( target, access );
		glGetLastError( "glMapBuffer" );
		return result;
	}

	bool CContext::UnmapBuffer( GL2D_GL_BUFFER_TARGET target )
	{
		GLboolean result = glUnmapBuffer( target );
		glGetLastError( "glUnmapBuffer" );
		return result == GL_TRUE;
	}

	HRESULT CContext::DrawTexture( GLuint name, const GL2D_RECT_F & destinationRectangle, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F & sourceRectangle )
	{
		HRESULT hr = S_OK;

		GL2D_GL_TEXTURE_FILTER filter = GL2D_GL_TEXTURE_FILTER_NEAREST;

		if ( interpolationMode == GL2D_BITMAP_INTERPOLATION_MODE_LINEAR )
		{
			filter = GL2D_GL_TEXTURE_FILTER_LINEAR;
		}
#if 0
		glUseProgram( m_program );
		hr = glGetLastError( "glUseProgram" );

		if ( hr == S_OK )
		{
			hr = ActiveTexture( GL_TEXTURE0 );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, name );
			hr = glGetLastError( "glBindTexture" );
		}

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
			hr = glGetLastError( "glTexParameteri" );
		}

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
			hr = glGetLastError( "glTexParameteri" );
		}

		if ( hr == S_OK )
		{
			glUniform1i( m_sampler, 0 );
			hr = glGetLastError( "glUniform1i" );
		}

		if ( hr == S_OK )
		{
			glUniformMatrix4fv( m_projection, 1, false, &m_proj[0][0] );
			hr = glGetLastError( "glUniformMatrix4fv" );
		}

		if ( hr == S_OK )
		{
			glUniformMatrix4fv( m_view, 1, false, &m_matrices.top()[0][0] );
			hr = glGetLastError( "glUniformMatrix4fv" );
		}

		if ( m_vao != GL_INVALID_INDEX )
		{
			if ( hr == S_OK )
			{
				glBindVertexArray( m_vao );
				hr = glGetLastError( "glBindVertexArray" );
			}
		}
		else
		{
			if ( hr == S_OK )
			{
				glBindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );
				hr = glGetLastError( "glBindBuffer" );
			}

			if ( hr == S_OK )
			{
				glVertexAttribPointer( m_texture, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), BUFFER_OFFSET( 0 ) );
				hr = glGetLastError( "glVertexAttribPointer" );
			}

			if ( hr == S_OK )
			{
				glVertexAttribPointer( m_vertex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), BUFFER_OFFSET( 2 * sizeof( float ) ) );
				hr = glGetLastError( "glVertexAttribPointer" );
			}
		}

		if ( hr == S_OK )
		{
			glDrawArrays( GL_TRIANGLES, 0, 6 );
			hr = glGetLastError( "glDrawArrays" );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, 0 );
			hr = glGetLastError( "glBindTexture" );
		}

		if ( m_vao != GL_INVALID_INDEX )
		{
			if ( hr == S_OK )
			{
				glBindVertexArray( 0 );
				hr = glGetLastError( "glBindVertexArray" );
			}
		}
		else
		{
			if ( hr == S_OK )
			{
				glBindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, 0 );
				hr = glGetLastError( "glBindBuffer" );
			}
		}

		if ( hr == S_OK )
		{
			glUseProgram( 0 );
			hr = glGetLastError( "glUseProgram" );
		}
#else
		hr = ActiveTexture( GL_TEXTURE0 );

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, name );
			hr = glGetLastError( "glBindTexture" );
		}

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
			hr = glGetLastError( "glTexParameteri" );
		}

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
			hr = glGetLastError( "glTexParameteri" );
		}

		if ( hr == S_OK )
		{
			glMatrixMode( GL_PROJECTION );
			hr = glGetLastError( "glMatrixMode" );
		}

		if ( hr == S_OK )
		{
			glMultMatrixf( glm::value_ptr( m_projMtx.top() ) );
			hr = glGetLastError( "glMultMatrixf" );
		}

		if ( hr == S_OK )
		{
			glMatrixMode( GL_MODELVIEW );
			hr = glGetLastError( "glMatrixMode" );
		}

		if ( hr == S_OK )
		{
			glMultMatrixf( glm::value_ptr( m_viewMtx.top() ) );
			hr = glGetLastError( "glMatrixMode" );
		}

		if ( hr == S_OK )
		{
			glBindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );
			hr = glGetLastError( "glBindBuffer" );
		}

		if ( hr == S_OK )
		{
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glTexCoordPointer( 2, GL_FLOAT, 5 * sizeof( float ), BUFFER_OFFSET( 0 ) );
			hr = glGetLastError( "glTexCoordPointer" );
		}

		if ( hr == S_OK )
		{
			glEnableClientState( GL_VERTEX_ARRAY );
			glVertexPointer( 3, GL_FLOAT, 5 * sizeof( float ), BUFFER_OFFSET( 2 * sizeof( float ) ) );
			hr = glGetLastError( "glVertexPointer" );
		}

		if ( hr == S_OK )
		{
			glDrawArrays( GL_TRIANGLES, 0, 6 );
			hr = glGetLastError( "glDrawArrays" );
		}

		if ( hr == S_OK )
		{
			glBindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, 0 );
			hr = glGetLastError( "glBindBuffer" );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, 0 );
			hr = glGetLastError( "glBindTexture" );
		}
#endif
		return hr;
	}

	HGLRC CContext::DoCreateContext()
	{
		HGLRC l_hReturn = NULL;

		if ( DoSelectPixelFormat() )
		{
			l_hReturn = wglCreateContext( m_dc );
		}

		return l_hReturn;
	}

	bool CContext::DoSelectPixelFormat()
	{
		bool result = false;
		PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		int pixelFormats = ::ChoosePixelFormat( m_dc, &pfd );

		if ( pixelFormats )
		{
			result = ::SetPixelFormat( m_dc, pixelFormats, &pfd ) != FALSE;
		}
		else
		{
			std::cout << "SetPixelFormat failed : " << std::endl;
		}

		return result;
	}

	GLuint CContext::DoCreateShader( const std::string & source, GL2D_GL_SHADER_TYPE type )
	{
		GLuint shader = glCreateShader( type );
		HRESULT hr = glGetLastError( "glCreateShader" );

		if ( hr == S_OK )
		{
			int l_iLength = int( source.size() );
			char * l_pszTmp = new char[source.size() + 1];
			strncpy_s( l_pszTmp, source.size() + 1, source.c_str(), source.size() );
			glShaderSource( shader, 1, const_cast< const char ** >( &l_pszTmp ), &l_iLength );
			delete [] l_pszTmp;
			hr = glGetLastError( "glShaderSource" );

			if ( hr == S_OK )
			{
				glCompileShader( shader );
				hr = glGetLastError( "glCompileShader" );
			}

			if ( hr == S_OK )
			{
				int compiled = 0;
				glGetShaderiv( shader, GL2D_GL_SHADER_QUERY_COMPILE_STATUS, &compiled );
				hr = glGetLastError( "glGetShaderiv" );
				int infologLength = 0;
				int charsWritten  = 0;
				glGetShaderiv( shader, GL2D_GL_SHADER_QUERY_INFO_LOG_LENGTH, &infologLength );

				if ( infologLength > 0 )
				{
					char * infoLog = new char[infologLength];
					glGetShaderInfoLog( shader, infologLength, &charsWritten, infoLog );

					if ( strlen( infoLog ) > 0 && strcmp( "No errors.\n", infoLog ) )
					{
						hr = glGetLastError( "glGetShaderInfoLog" );
						std::cout << infoLog << std::endl;
					}

					delete [] infoLog;
				}
			}

			if ( hr != S_OK )
			{
				glDeleteShader( shader );
				shader = GL_INVALID_INDEX;
			}
		}

		return shader;
	}

	void CContext::DebugLog( GL2D_GL_DEBUG_SOURCE source, GL2D_GL_DEBUG_TYPE type, uint32_t id, GL2D_GL_DEBUG_SEVERITY severity, int length, const char * message )
	{
		std::stringstream toLog;
		toLog << "OpenGl Debug - ";

		switch ( source )
		{
		case GL2D_GL_DEBUG_SOURCE_API:
			toLog << "Source:OpenGL\t";
			break;

		case GL2D_GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			toLog << "Source:Windows\t";
			break;

		case GL2D_GL_DEBUG_SOURCE_SHADER_COMPILER:
			toLog << "Source:Shader compiler\t";
			break;

		case GL2D_GL_DEBUG_SOURCE_THIRD_PARTY:
			toLog << "Source:Third party\t";
			break;

		case GL2D_GL_DEBUG_SOURCE_APPLICATION:
			toLog << "Source:Application\t";
			break;

		case GL2D_GL_DEBUG_SOURCE_OTHER:
			toLog << "Source:Other\t";
			break;
		}

		switch ( type )
		{
		case GL2D_GL_DEBUG_TYPE_ERROR:
			toLog << "Type:Error\t";
			break;

		case GL2D_GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			toLog << "Type:Deprecated behavior\t";
			break;

		case GL2D_GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			toLog << "Type:Undefined behavior\t";
			break;

		case GL2D_GL_DEBUG_TYPE_PORTABILITY:
			toLog << "Type:Portability\t";
			break;

		case GL2D_GL_DEBUG_TYPE_PERFORMANCE:
			toLog << "Type:Performance\t";
			break;

		case GL2D_GL_DEBUG_TYPE_OTHER:
			toLog << "Type:Other\t";
			break;
		}

		toLog << "ID:" << id << "\t";

		switch ( severity )
		{
		case GL2D_GL_DEBUG_SEVERITY_HIGH:
			std::cerr << toLog.str() << "Severity:High\tMessage:" << message;
			break;

		case GL2D_GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << toLog.str() << "Severity:Medium\tMessage:" << message;
			break;

		case GL2D_GL_DEBUG_SEVERITY_LOW:
			std::clog << toLog.str() << "Severity:Low\tMessage:" << message;
			break;

		default:
			std::clog << toLog.str() << "Severity:Info\tMessage:" << message;
			break;
		}
	}

	void CContext::DebugLogAMD( uint32_t id, GL2D_GL_DEBUG_CATEGORY category, GL2D_GL_DEBUG_SEVERITY severity, int length, const char * message )
	{
		std::stringstream toLog;
		toLog << "OpenGl Debug - ";

		switch ( category )
		{
		case GL2D_GL_DEBUG_CATEGORY_API_ERROR:
			toLog << "Category:OpenGL\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_WINDOW_SYSTEM:
			toLog << "Category:Windows\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_DEPRECATION:
			toLog << "Category:Deprecated behavior\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR:
			toLog << "Category:Undefined behavior\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_PERFORMANCE:
			toLog << "Category:Performance\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_SHADER_COMPILER:
			toLog << "Category:Shader compiler\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_APPLICATION:
			toLog << "Category:Application\t";
			break;

		case GL2D_GL_DEBUG_CATEGORY_OTHER:
			toLog << "Category:Other\t";
			break;
		}

		toLog << "ID:" << id << "\t";

		switch ( severity )
		{
		case GL2D_GL_DEBUG_SEVERITY_HIGH:
			std::cerr << toLog.str() << "Severity:High\tMessage:" << message;
			break;

		case GL2D_GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << toLog.str() << "Severity:Medium\tMessage:" << message;
			break;

		case GL2D_GL_DEBUG_SEVERITY_LOW:
			std::clog << toLog.str() << "Severity:Low\tMessage:" << message;
			break;

		default:
			std::clog << toLog.str() << "Severity:Info\tMessage:" << message;
			break;
		}
	}

	void CContext::DoLoadContext()
	{
		const char * ( CALLBACK * glGetExtensionsString )();
		gl_api::GetFunction( "wglGetExtensionsString", "EXT", glGetExtensionsString );
		std::string strExt;

		if ( glGetExtensionsString )
		{
			strExt = glGetExtensionsString();
		}

		strExt += ( char const * )glGetString( GL_EXTENSIONS );

		std::string vendor = ( char const * )glGetString( GL_VENDOR );
		std::string renderer = ( char const * )glGetString( GL_RENDERER );
		std::string glVersion = ( char const * )glGetString( GL_VERSION );
		std::stringstream streamExt( strExt );
		std::set< std::string > extensions;

		while ( !streamExt.eof() )
		{
			std::string tmp;
			streamExt >> tmp;

			if ( !tmp.empty() )
			{
				extensions.insert( tmp );
			}
		}

		double dVersion;
		std::stringstream stream( glVersion );
		stream >> dVersion;
		int version = int( dVersion * 10 );

		std::function< HGLRC( HDC hDC, HGLRC hShareContext, int const * attribList ) > glCreateContextAttribs;
		gl_api::GetFunction( "wglCreateContextAttribs", "ARB", glCreateContextAttribs );

		if ( !glCreateContextAttribs )
		{
			gl_api::GetFunction( "wglCreateContextAttribs", "EXT", glCreateContextAttribs );
		}

		if ( glCreateContextAttribs )
		{
			std::vector< int > attribList;
			attribList.push_back( GL2D_GL_CREATECONTEXT_ATTRIB_MAJOR_VERSION );
			attribList.push_back( version / 10 );
			attribList.push_back( GL2D_GL_CREATECONTEXT_ATTRIB_MINOR_VERSION );
			attribList.push_back( version % 10 );
#if !defined( NDEBUG )
			attribList.push_back( GL2D_GL_CREATECONTEXT_ATTRIB_FLAGS );
			attribList.push_back( GL2D_GL_CREATECONTEXT_ATTRIB_FORWARD_COMPATIBLE_BIT | GL2D_GL_CREATECONTEXT_ATTRIB_DEBUG_BIT );
			attribList.push_back( GL2D_GL_PROFILE_ATTRIB_MASK );
			attribList.push_back( GL2D_GL_PROFILE_ATTRIB_COMPATIBILITY_BIT );
#else
			attribList.push_back( GL2D_GL_CREATECONTEXT_ATTRIB_FLAGS );
			attribList.push_back( GL2D_GL_CREATECONTEXT_ATTRIB_FORWARD_COMPATIBLE_BIT );
			attribList.push_back( GL2D_GL_PROFILE_ATTRIB_MASK );
			attribList.push_back( GL2D_GL_PROFILE_ATTRIB_CORE_BIT );
#endif
			attribList.push_back( 0 );
			HGLRC context = glCreateContextAttribs( m_dc, NULL, &attribList[0] );
			EndCurrent( GetDC() );
			wglDeleteContext( m_context );
			m_context = context;
			MakeCurrent( GetDC() );
		}

		gl_api::GetFunction( "glDebugMessageCallback", "ARB", glDebugMessageCallback );
		gl_api::GetFunction( "glDebugMessageCallbackAMD", "ARB", glDebugMessageCallbackAMD );

		if ( glDebugMessageCallback )
		{
			glDebugMessageCallback( &gl_api::StDebugLog, this );
			glEnable( GL2D_GL_DEBUG_OUTPUT_SYNCHRONOUS );
		}

		if ( glDebugMessageCallbackAMD )
		{
			glDebugMessageCallbackAMD( &gl_api::StDebugLogAMD, this );
			glEnable( GL2D_GL_DEBUG_OUTPUT_SYNCHRONOUS );
		}

		gl_api::GetFunction( "glActiveTexture", "", glActiveTexture );
		gl_api::GetFunction( "glDrawBuffers", "ARB", glDrawBuffers );
		gl_api::GetFunction( "glBlitFramebuffer", "ARB", glBlitFramebuffer );
		gl_api::GetFunction( "glGenRenderbuffers", "ARB", glGenRenderbuffers );
		gl_api::GetFunction( "glDeleteRenderbuffers", "ARB", glDeleteRenderbuffers );
		gl_api::GetFunction( "glBindRenderbuffer", "ARB", glBindRenderbuffer );
		gl_api::GetFunction( "glRenderbufferStorage", "ARB", glRenderbufferStorage );
		gl_api::GetFunction( "glRenderbufferStorageMultisample", "ARB", glRenderbufferStorageMultisample );
		gl_api::GetFunction( "glTexImage2DMultisample", "ARB", glTexImage2DMultisample );
		gl_api::GetFunction( "glGetRenderbufferParameteriv", "ARB", glGetRenderbufferParameteriv );
		gl_api::GetFunction( "glFramebufferRenderbuffer", "ARB", glFramebufferRenderbuffer );
		gl_api::GetFunction( "glGenFramebuffers", "ARB", glGenFramebuffers );
		gl_api::GetFunction( "glDeleteFramebuffers", "ARB", glDeleteFramebuffers );
		gl_api::GetFunction( "glBindFramebuffer", "ARB", glBindFramebuffer );
		gl_api::GetFunction( "glFramebufferTexture", "ARB", glFramebufferTexture );
		gl_api::GetFunction( "glFramebufferTexture1D", "ARB", glFramebufferTexture1D );
		gl_api::GetFunction( "glFramebufferTexture2D", "ARB", glFramebufferTexture2D );
		gl_api::GetFunction( "glFramebufferTexture3D", "ARB", glFramebufferTexture3D );
		gl_api::GetFunction( "glFramebufferTextureLayer", "ARB", glFramebufferTextureLayer );
		gl_api::GetFunction( "glCheckFramebufferStatus", "ARB", glCheckFramebufferStatus );
		gl_api::GetFunction( "glGenBuffers", "ARB", glGenBuffers );
		gl_api::GetFunction( "glDeleteBuffers", "ARB", glDeleteBuffers );
		gl_api::GetFunction( "glBindBuffer", "ARB", glBindBuffer );
		gl_api::GetFunction( "glBufferData", "ARB", glBufferData );
		gl_api::GetFunction( "glMapBuffer", "ARB", glMapBuffer );
		gl_api::GetFunction( "glUnmapBuffer", "ARB", glUnmapBuffer );
		gl_api::GetFunction( "glCreateShader", "ARB", glCreateShader );
		gl_api::GetFunction( "glDeleteShader", "ARB", glDeleteShader );
		gl_api::GetFunction( "glShaderSource", "ARB", glShaderSource );
		gl_api::GetFunction( "glCompileShader", "ARB", glCompileShader );
		gl_api::GetFunction( "glGetShaderiv", "ARB", glGetShaderiv );
		gl_api::GetFunction( "glGetShaderInfoLog", "ARB", glGetShaderInfoLog );
		gl_api::GetFunction( "glAttachShader", "ARB", glAttachShader );
		gl_api::GetFunction( "glCreateProgram", "ARB", glCreateProgram );
		gl_api::GetFunction( "glDeleteProgram", "ARB", glDeleteProgram );
		gl_api::GetFunction( "glAttachShader", "ARB", glAttachShader );
		gl_api::GetFunction( "glLinkProgram", "ARB", glLinkProgram );
		gl_api::GetFunction( "glGetProgramiv", "ARB", glGetProgramiv );
		gl_api::GetFunction( "glGetProgramInfoLog", "ARB", glGetProgramInfoLog );
		gl_api::GetFunction( "glGetUniformLocation", "ARB", glGetUniformLocation );
		gl_api::GetFunction( "glUniform1i", "ARB", glUniform1i );
		gl_api::GetFunction( "glUniformMatrix4fv", "ARB", glUniformMatrix4fv );
		gl_api::GetFunction( "glGetAttribLocation", "ARB", glGetAttribLocation );
		gl_api::GetFunction( "glUseProgram", "ARB", glUseProgram );
		gl_api::GetFunction( "glVertexAttribPointer", "ARB", glVertexAttribPointer );
		gl_api::GetFunction( "glGenVertexArrays", "ARB", glGenVertexArrays );
		gl_api::GetFunction( "glDeleteVertexArrays", "ARB", glDeleteVertexArrays );
		gl_api::GetFunction( "glBindVertexArray", "ARB", glBindVertexArray );
	}

	HRESULT CContext::DoLoadProgram()
	{
		std::string vssrc;
		vssrc += "#version 130\n";
		vssrc += "\n";
		vssrc += "in vec4 vertex;\n";
		vssrc += "in vec2 texture;\n";
		vssrc += "out vec2 vtx_texture;\n";
		vssrc += "uniform mat4 projection;\n";
		vssrc += "uniform mat4 view;\n";
		vssrc += "\n";
		vssrc += "void main()\n";
		vssrc += "{\n";
		vssrc += "    gl_Position = ( view * projection ) * vertex;\n";
		vssrc += "    vtx_texture = texture;\n";
		vssrc += "}\n";
		GLuint vs = DoCreateShader( vssrc, GL2D_GL_SHADER_TYPE_VERTEX );

		std::string fssrc;
		fssrc += "#version 130\n";
		fssrc += "\n";
		fssrc += "uniform sampler2D diffuse;\n";
		fssrc += "in vec2 vtx_texture;\n";
		fssrc += "out vec4 pxl_fragColor;\n";
		fssrc += "\n";
		fssrc += "void main()\n";
		fssrc += "{\n";
		fssrc += "    pxl_fragColor = texture( diffuse, vtx_texture );\n";
		fssrc += "}\n";
		GLuint fs = DoCreateShader( fssrc, GL2D_GL_SHADER_TYPE_FRAGMENT );

		HRESULT hr = ( fs != GL_INVALID_INDEX && vs != GL_INVALID_INDEX ) ? S_OK : E_FAIL;

		if ( hr == S_OK )
		{
			m_program = glCreateProgram();
			hr = glGetLastError( "glCreateProgram" );
		}

		if ( hr == S_OK )
		{
			glAttachShader( m_program, vs );
			hr = glGetLastError( "glAttachShader" );
		}

		if ( hr == S_OK )
		{
			glAttachShader( m_program, fs );
			hr = glGetLastError( "glAttachShader" );
		}

		if ( hr == S_OK )
		{
			glLinkProgram( m_program );
			hr = glGetLastError( "glLinkProgram" );
		}

		if ( hr == S_OK )
		{
			int linked = 0;
			glGetProgramiv( m_program, GL2D_GL_PROGRAM_QUERY_LINK_STATUS, &linked );
			hr = glGetLastError( "glGetProgramiv" );
			int infologLength = 0;
			int charsWritten  = 0;
			glGetProgramiv( m_program, GL2D_GL_PROGRAM_QUERY_INFO_LOG_LENGTH, &infologLength );
			hr = glGetLastError( "glGetProgramiv" );

			if ( infologLength > 0 )
			{
				char * infoLog = new char[infologLength];
				glGetProgramInfoLog( m_program, infologLength, &charsWritten, infoLog );

				if ( strlen( infoLog ) > 0 && strcmp( "No errors.\n", infoLog ) )
				{
					hr = glGetLastError( "glGetProgramInfoLog" );
					std::cout << infoLog << std::endl;
				}

				delete [] infoLog;
			}
		}

		if ( hr == S_OK )
		{
			m_sampler = glGetUniformLocation( m_program, "diffuse" );
			hr = glGetLastError( "glGetUniformLocation" );
		}

		if ( hr == S_OK )
		{
			m_projection = glGetUniformLocation( m_program, "projection" );
			hr = glGetLastError( "glGetUniformLocation" );
		}

		if ( hr == S_OK )
		{
			m_view = glGetUniformLocation( m_program, "view" );
			hr = glGetLastError( "glGetUniformLocation" );
		}

		if ( hr == S_OK )
		{
			m_vertex = glGetAttribLocation( m_program, "vertex" );
			hr = glGetLastError( "glGetAttribLocation" );
		}

		if ( hr == S_OK )
		{
			m_texture = glGetAttribLocation( m_program, "texture" );
			hr = glGetLastError( "glGetAttribLocation" );
		}

		if ( vs != GL_INVALID_INDEX )
		{
			glDeleteShader( vs );
		}

		if ( fs != GL_INVALID_INDEX )
		{
			glDeleteShader( fs );
		}

		return hr;
	}

	HRESULT CContext::DoLoadBuffer()
	{
		HRESULT hr = GenBuffers( 1, &m_buffer );

		if ( hr == S_OK )
		{
			hr = BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );
		}

		if ( hr == S_OK )
		{
			float quad[] =
			{
				0, 2, 0, 0, 0,
				0, 0, 0, 1, 0,
				2, 0, 1, 1, 0,
				0, 2, 0, 0, 0,
				2, 0, 1, 1, 0,
				2, 2, 1, 0, 0,
			};

			hr = BufferData( GL2D_GL_BUFFER_TARGET_ARRAY, sizeof( quad ), quad, GL2D_GL_BUFFER_USAGE_STATIC_DRAW );
			BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, 0 );
		}

		if ( hr == S_OK && glGenVertexArrays )
		{
			glGenVertexArrays( 1, &m_vao );
			hr = glGetLastError( "glGenVertexArrays" );

			if ( hr == S_OK )
			{
				glBindVertexArray( m_vao );
				glBindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );

				if ( m_texture != GL_INVALID_INDEX )
				{
					glVertexAttribPointer( m_texture, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), BUFFER_OFFSET( 0 ) );
				}

				if ( m_vertex != GL_INVALID_INDEX )
				{
					glVertexAttribPointer( m_vertex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), BUFFER_OFFSET( 2 * sizeof( float ) ) );
				}

				glBindVertexArray( 0 );
				hr = glGetLastError( "glBindVertexArray" );
			}
		}

		return hr;
	}
}
