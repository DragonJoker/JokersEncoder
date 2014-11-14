#include "stdafx.h"

#include "GLBitmap.h"
#include "GLRenderTarget.h"
#include "GLHelper.h"

#include <cmath>

namespace GL2D
{
	CComBitmap::CComBitmap()
		: CObject()
	{
	}

	CComBitmap::~CComBitmap()
	{
		CObject::Destroy();
	}
	
	void CComBitmap::Initialise( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props )
	{
		m_format = props.pixelFormat;
		m_size = size;
		glBindTexture( GL_TEXTURE_2D, m_name );
		HRESULT hr = glGetLastError( "BindTexture" );

		if ( hr == S_OK )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, m_format.internal, size.width, size.height, 0, m_format.format, m_format.type, data );
			hr = glGetLastError( "TexImage2D" );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}
	}
	
	void CComBitmap::Draw( const GL2D_RECT_F & rcDst, GL2D_BITMAP_INTERPOLATION_MODE mode, const GL2D_RECT_F & rcSrc )
	{
	}

	STDMETHODIMP_( GL2D_SIZE_F ) CComBitmap::GetSize()const
	{
		float x, y;
		GetDpi( &x, &y );
        return SizeF( m_size.width / x, m_size.height / y );
	}

	STDMETHODIMP_( GL2D_SIZE_U ) CComBitmap::GetPixelSize()const
	{
		return m_size;
	}

	STDMETHODIMP_( GL2D_PIXEL_FORMAT ) CComBitmap::GetPixelFormat()const
	{
		return m_format;
	}

	STDMETHODIMP_( void ) CComBitmap::GetDpi( float * dpiX, float * dpiY  )const
	{
		if ( dpiX && dpiY )
		{
			*dpiX = 96.0f;
			*dpiY = 96.0f;
		}
	}

	STDMETHODIMP CComBitmap::CopyFromBitmap( const GL2D_POINT_2U * destPoint, IGL2DBitmap * bitmap, const GL2D_RECT_U * srcRect )
	{
		GLvoid * srcData = NULL;
		CComBitmap * bmp = static_cast< CComBitmap * >( bitmap );
		glBindTexture( GL_TEXTURE_2D, bmp->m_name );
		HRESULT hr = glGetLastError( "BindTexture" );

		if ( hr == S_OK )
		{
			glGetTexImage( GL_TEXTURE_2D, 0, m_format.format, m_format.type, srcData );
			hr = glGetLastError( "GetTexImage" );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, m_name );
			hr = glGetLastError( "BindTexture" );
		}

		if ( hr == S_OK )
		{
			glTexSubImage2D( GL_TEXTURE_2D, 0, destPoint->x, destPoint->y, srcRect->right - srcRect->left, srcRect->bottom - srcRect->top, m_format.format, m_format.type, srcData );
			hr = glGetLastError( "TexSubImage2D" );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		return hr;
	}

	STDMETHODIMP CComBitmap::CopyFromRenderTarget( const GL2D_POINT_2U * destPoint, IGL2DRenderTarget * renderTarget, const GL2D_RECT_U * srcRect )
	{
		GLvoid * srcData = NULL;
		CRenderTarget * rt = static_cast< CRenderTarget * >( renderTarget );
		CContext * context = rt->GetContext().get();
		HRESULT hr = rt->GetFrameBuffer()->Bind( GL2D_GL_FRAMEBUFFER_MODE_READ );

		if ( hr == S_OK )
		{
			int componentSize = 0;

			switch( m_format.type )
			{
			case GL2D_GL_TYPE_BYTE:
			case GL2D_GL_TYPE_UNSIGNED_BYTE:
				componentSize = 1;
				break;
			case GL2D_GL_TYPE_SHORT:
			case GL2D_GL_TYPE_UNSIGNED_SHORT:
				componentSize = 2;
				break;
			case GL2D_GL_TYPE_INT:
			case GL2D_GL_TYPE_UNSIGNED_INT:
			case GL2D_GL_TYPE_FLOAT:
				componentSize = 4;
				break;
			case GL2D_GL_TYPE_DOUBLE:
				componentSize = 8;
				break;
			}

			int componentCount = 0;

			switch( m_format.format )
			{
			case GL2D_GL_FORMAT_STENCIL:
			case GL2D_GL_FORMAT_DEPTH:
			case GL2D_GL_FORMAT_RED:
			case GL2D_GL_FORMAT_GREEN:
			case GL2D_GL_FORMAT_BLUE:
			case GL2D_GL_FORMAT_ALPHA:
			case GL2D_GL_FORMAT_LUMINANCE:
				componentCount = 1;
				break;
			case GL2D_GL_FORMAT_LUMINANCE_ALPHA:
			case GL2D_GL_FORMAT_RG:
			case GL2D_GL_FORMAT_DEPTH_STENCIL:
				componentCount = 2;
				break;
			case GL2D_GL_FORMAT_RGB:
			case GL2D_GL_FORMAT_BGR:
				componentCount = 3;
				break;
			case GL2D_GL_FORMAT_RGBA:
			case GL2D_GL_FORMAT_BGRA:
				componentCount = 4;
				break;
			}

			srcData = new uint8_t[componentSize * componentCount * std::abs( int( srcRect->right - srcRect->left ) ) * std::abs( int( srcRect->bottom - srcRect->top ) )];
			glReadPixels( srcRect->left, srcRect->top, srcRect->right - srcRect->left, srcRect->bottom - srcRect->top, m_format.format, m_format.type, srcData );
			hr = glGetLastError( "ReadPixels" );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, m_name );
			hr = glGetLastError( "BindTexture" );
		}

		if ( hr == S_OK )
		{
			glTexSubImage2D( GL_TEXTURE_2D, 0, destPoint->x, destPoint->y, srcRect->right - srcRect->left, srcRect->bottom - srcRect->top, m_format.format, m_format.type, srcData );
			hr = glGetLastError( "TexSubImage2D" );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		return hr;
	}

	STDMETHODIMP CComBitmap::CopyFromMemory( const GL2D_RECT_U * dstRect, const void * srcData, uint32_t pitch )
	{
		glBindTexture( GL_TEXTURE_2D, m_name );
		HRESULT hr = glGetLastError( "BindTexture" );

		if ( hr == S_OK )
		{
			glTexSubImage2D( GL_TEXTURE_2D, 0, dstRect->left, dstRect->top, dstRect->right - dstRect->left, dstRect->bottom - dstRect->top, m_format.format, m_format.type, srcData );
			hr = glGetLastError( "TexSubImage2D" );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		return hr;
	}
}