#include "stdafx.h"

#include "GLContext.h"
#include "GLTexture.h"
#include "GLShaderProgram.h"
#include "GLUniform.h"
#include "GLAttribute.h"
#include "GLGeometryBuffer.h"

#include <sstream>
#include <set>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	std::weak_ptr< CContext > CContext::m_main;
	std::map< std::thread::id, std::shared_ptr< CContext > > CContext::m_activeContexts;

	CContext::CContext( HWND window )
		: m_window( window )
		, m_previous( NULL )
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
		m_program.reset();
		m_buffer.reset();
		EndCurrent( GetDC() );
	}

	std::shared_ptr< CContext > CContext::CreateContext( HWND hWnd )
	{
		struct make_shared_enabler
			: public CContext
		{
			make_shared_enabler( HWND hWnd )
				: CContext( hWnd )
			{
			}
		};

		std::shared_ptr< CContext > result = std::make_shared< make_shared_enabler >( hWnd );

		if ( m_main.expired() )
		{
			m_main = result;
		}

		return result;
	}

	std::shared_ptr< CContext > CContext::GetMainContext()
	{
		return m_main.lock();
	}

	std::shared_ptr< CContext > CContext::GetActiveContext()
	{
		std::shared_ptr< CContext > result;
		m_mutex.lock();
		std::map< std::thread::id, std::shared_ptr< CContext > >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

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
		std::map< std::thread::id, std::shared_ptr< CContext > >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it != m_activeContexts.end() )
		{
			m_previous = it->second;
		}

		m_activeContexts[std::this_thread::get_id()] = shared_from_this();
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
			m_previous = nullptr;
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
		std::map< std::thread::id, std::shared_ptr< CContext > >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it == m_activeContexts.end() )
		{
			MakeCurrent( GetDC() );
		}

		GLint value = 0;
		glGetIntegerv( param, &value );
		HRESULT hr = glGetLastError( "glGetIntegerv" );

		if ( it == m_activeContexts.end() )
		{
			EndCurrent( GetDC() );
		}

		if ( hr != S_OK )
		{
			throw hr;
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
		return S_OK;
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
		uint32_t result = glCheckFramebufferStatus( target );
		HRESULT hr = glGetLastError( "glCheckFramebufferStatus" );

		if ( hr != S_OK )
		{
			throw hr;
		}

		return result;
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
		HRESULT hr = glGetLastError( "glMapBuffer" );

		if ( hr != S_OK )
		{
			throw hr;
		}

		return result;
	}

	bool CContext::UnmapBuffer( GL2D_GL_BUFFER_TARGET target )
	{
		GLboolean result = glUnmapBuffer( target );
		return result == GL_TRUE && glGetLastError( "glUnmapBuffer" ) == S_OK;
	}

	HRESULT CContext::BlendFuncSeparate( GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha )
	{
		glBlendFuncSeparate( srcRGB, dstRGB, srcAlpha, dstAlpha );
		return glGetLastError( "glBlendFuncSeparate" );
	}

	GLuint CContext::CreateShader( GLenum type )
	{
		GLuint shader = glCreateShader( type );
		HRESULT hr = glGetLastError( "glCreateShader" );

		if ( hr != S_OK )
		{
			throw hr;
		}

		return shader;
	}

	HRESULT CContext::AttachShader( GLuint name, GLuint shader )
	{
		glAttachShader( name, shader );
		return glGetLastError( "glAttachShader" );
	}

	HRESULT CContext::GetShaderiv( GLuint name, GLenum info, GLint * value )
	{
		glGetShaderiv( name, info, value );
		return glGetLastError( "glGetShaderiv" );
	}

	HRESULT CContext::GetShaderInfoLog( GLuint name, GLint length, GLint * written, char * log )
	{
		glGetShaderInfoLog( name, length, written, log );
		return glGetLastError( "glGetShaderInfoLog" );
	}

	HRESULT CContext::ShaderSource( GLuint name, GLsizei count, const char ** string, const GLint * length )
	{
		glShaderSource( name, count, string, length );
		return glGetLastError( "glShaderSource" );
	}

	HRESULT CContext::CompileShader( GLuint name )
	{
		glCompileShader( name );
		return glGetLastError( "glCompileShader" );
	}

	HRESULT CContext::DeleteShader( GLuint name )
	{
		glDeleteShader( name );
		return glGetLastError( "glDeleteShader" );
	}

	HRESULT CContext::UseProgram( GLuint name )
	{
		glUseProgram( name );
		return glGetLastError( "glUseProgram" );
	}

	GLuint CContext::CreateProgram()
	{
		GLuint result = glCreateProgram();
		HRESULT hr = glGetLastError( "glCreateProgram" );

		if ( hr != S_OK )
		{
			throw hr;
		}

		return result;
	}

	HRESULT CContext::LinkProgram( GLuint name )
	{
		glLinkProgram( name );
		return glGetLastError( "glLinkProgram" );
	}

	HRESULT CContext::GetProgramiv( GLuint name, GLenum info, GLint * value )
	{
		glGetProgramiv( name, info, value );
		return glGetLastError( "glGetProgramiv" );
	}

	HRESULT CContext::GetProgramInfoLog( GLuint name, GLint length, GLint * written, char * log )
	{
		glGetProgramInfoLog( name, length, written, log );
		return glGetLastError( "glGetProgramInfoLog" );
	}

	HRESULT CContext::DeleteProgram( GLuint name )
	{
		glDeleteProgram( name );
		return glGetLastError( "glDeleteProgram" );
	}

	HRESULT CContext::VertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer )
	{
		glVertexAttribPointer( index, size, type, normalized, stride, pointer );
		return glGetLastError( "glVertexAttribPointer" );
	}

	HRESULT CContext::EnableVertexAttribArray( GLuint index )
	{
		glEnableVertexAttribArray( index );
		return glGetLastError( "glEnableVertexAttribArray" );
	}

	HRESULT CContext::Uniform1i( GLuint location, GLint value )
	{
		glUniform1i( location, value );
		return glGetLastError( "glUniform1i" );
	}

	HRESULT CContext::UniformMatrix4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat * value )
	{
		glUniformMatrix4fv( location, count, transpose, value );
		return glGetLastError( "glUniformMatrix4fv" );
	}

	GLint CContext::GetUniformLocation( GLuint program, std::string const & name )
	{
		GLint result = glGetUniformLocation( program, name.c_str() );
		HRESULT hr = glGetLastError( "glGetUniformLocation" );

		if ( hr != S_OK )
		{
			throw hr;
		}

		return result;
	}

	GLint CContext::GetAttribLocation( GLuint program, std::string const & name )
	{
		GLint result = glGetAttribLocation( program, name.c_str() );
		HRESULT hr = glGetLastError( "glGetAttribLocation" );

		if ( hr != S_OK )
		{
			throw hr;
		}

		return result;
	}

	HRESULT CContext::GenVertexArrays( GLsizei n, GLuint * buffers )
	{
		glGenVertexArrays( n, buffers );
		return glGetLastError( "glGenVertexArrays" );
	}

	HRESULT CContext::DeleteVertexArrays( GLsizei n, GLuint const * buffers )
	{
		glDeleteVertexArrays( n, buffers );
		return glGetLastError( "glDeleteVertexArrays" );
	}

	HRESULT CContext::BindVertexArray( GLuint buffer )
	{
		glBindVertexArray( buffer );
		return glGetLastError( "glBindVertexArray" );
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

	HRESULT CContext::DrawTexture( CTexture * texture, const GL2D_RECT_F & destinationRectangle, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F & sourceRectangle )
	{
		std::shared_ptr< CContext > context = shared_from_this();
		HRESULT hr = m_program->Bind( context );

		if ( hr == S_OK )
		{
			if ( m_sampler )
			{
				hr = m_sampler->SetValue( context, 0 );
			}
			if ( hr == S_OK && m_mvp )
			{
				hr = m_mvp->SetValue( context, m_viewMtx.top() * m_projMtx.top() );
			}

			if ( hr == S_OK )
			{
				hr = ActiveTexture( GL_TEXTURE0 );
			}

			if ( hr == S_OK )
			{
				hr = texture->Bind( context );
			}

			if ( hr == S_OK )
			{
				GL2D_GL_TEXTURE_FILTER filter = GL2D_GL_TEXTURE_FILTER_NEAREST;

				if ( interpolationMode == GL2D_BITMAP_INTERPOLATION_MODE_LINEAR )
				{
					filter = GL2D_GL_TEXTURE_FILTER_LINEAR;
				}

				hr = texture->Interpolate( context, filter );

				if ( hr == S_OK )
				{
					hr = m_buffer->Bind( context );

					if ( hr == S_OK )
					{
						glDrawArrays( GL_TRIANGLES, 0, 6 );
						hr = glGetLastError( "glDrawArrays" );
					}

					m_buffer->Unbind( context );
				}

				texture->Unbind( context );
			}

			m_program->Unbind( context );
		}

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
			std::shared_ptr< CContext > main = m_main.lock();
			HGLRC context = NULL;

			if ( main && main.get() != this )
			{
				context = glCreateContextAttribs( m_dc, main->m_context, &attribList[0] );
			}
			else
			{
				context = glCreateContextAttribs( m_dc, NULL, &attribList[0] );
			}

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
		gl_api::GetFunction( "glEnableVertexAttribArray", "ARB", glEnableVertexAttribArray );
		gl_api::GetFunction( "glBlendFuncSeparate", "ARB", glBlendFuncSeparate );
	}

	HRESULT CContext::DoLoadProgram()
	{
		HRESULT hr = S_OK;
		std::string vssrc;
		vssrc += "#version 130\n";
		vssrc += "\n";
		vssrc += "in vec4 vertex;\n";
		vssrc += "in vec2 texture;\n";
		vssrc += "\n";
		vssrc += "uniform mat4 mvp;\n";
		vssrc += "\n";
		vssrc += "out vec2 vtx_texture;\n";
		vssrc += "\n";
		vssrc += "void main()\n";
		vssrc += "{\n";
		vssrc += "    gl_Position = mvp * vertex;\n";
		vssrc += "    vtx_texture = texture;\n";
		vssrc += "}\n";

		std::string fssrc;
		fssrc += "#version 130\n";
		fssrc += "\n";
		fssrc += "uniform sampler2D diffuse;\n";
		fssrc += "\n";
		fssrc += "in vec2 vtx_texture;\n";
		fssrc += "\n";
		fssrc += "out vec4 pxl_FragColor;\n";
		fssrc += "\n";
		fssrc += "void main()\n";
		fssrc += "{\n";
		fssrc += "    pxl_FragColor = texture( diffuse, vtx_texture );\n";
		fssrc += "}\n";

		try
		{
			m_program = std::make_unique< CShaderProgram >( vssrc, fssrc );
			m_sampler = m_program->GetUniform( shared_from_this(), "diffuse" );
			m_mvp = m_program->GetUniform( shared_from_this(), "mvp" );
			m_vertex = m_program->GetAttribute( shared_from_this(), "vertex" );
			m_texture = m_program->GetAttribute( shared_from_this(), "texture" );
		}
		catch( HRESULT exc )
		{
			hr = exc;
		}

		return hr;
	}

	HRESULT CContext::DoLoadBuffer()
	{
		SVertex quad[] =
		{
			{ { 0, 1 }, { 0, 0 } },
			{ { 0, 0 }, { 0, 1 } },
			{ { 1, 0 }, { 1, 1 } },
			{ { 0, 1 }, { 0, 0 } },
			{ { 1, 0 }, { 1, 1 } },
			{ { 1, 1 }, { 1, 0 } },
		};

		HRESULT hr = S_OK;

		try
		{
			m_buffer = std::make_unique< CGeometryBuffer >();

			hr = m_buffer->Initialise( shared_from_this(), m_vertex, m_texture );

			if ( hr == S_OK )
			{
				hr = m_buffer->Fill( shared_from_this(), quad );
			}
		}
		catch( HRESULT exc )
		{
			hr = exc;
		}

		return hr;
	}
}
