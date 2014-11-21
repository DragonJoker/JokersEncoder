#include "stdafx.h"

#include "GLBitmap.h"
#include "GLRenderTargetInterface.h"
#include "GLRenderTarget.h"
#include "GLContext.h"
#include "GLHelper.h"

#include <cmath>

namespace GL2D
{
	CComBitmap::CComBitmap()
		: m_texture( std::make_unique< CTexture >() )
	{
	}

	CComBitmap::~CComBitmap()
	{
	}

	HRESULT CComBitmap::Initialise( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props )
	{
		m_size = size;
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		m_texture->Create(
			std::bind( &CContext::GenTextures, context.get(), std::placeholders::_1, std::placeholders::_2 ),
			std::bind( &CContext::DeleteTextures, context.get(), std::placeholders::_1, std::placeholders::_2 )
		);
		return m_texture->Initialise( size, data, pitch, props );
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
		return m_texture->GetPixelFormat();
	}

	STDMETHODIMP_( void ) CComBitmap::GetDpi( float * dpiX, float * dpiY )const
	{
		if ( dpiX && dpiY )
		{
			*dpiX = 96.0f;
			*dpiY = 96.0f;
		}
	}

	STDMETHODIMP CComBitmap::CopyFromBitmap( const GL2D_POINT_2U * destPoint, IGL2DBitmap * bitmap, const GL2D_RECT_U * srcRect )
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		GLvoid * srcData = NULL;
		CComBitmap * bmp = static_cast< CComBitmap * >( bitmap );
		HRESULT hr = bmp->m_texture->Bind( context );

		if ( hr == S_OK )
		{
			hr = bmp->m_texture->GetImage( context, GetPixelFormat(), srcData );
			bmp->m_texture->Unbind( context );
		}

		if ( hr == S_OK )
		{
			hr = m_texture->Bind( context );
		}

		if ( hr == S_OK )
		{
			hr = m_texture->Fill( context, srcData );
			m_texture->Unbind( context );
		}

		return hr;
	}

	STDMETHODIMP CComBitmap::CopyFromRenderTarget( const GL2D_POINT_2U * destPoint, IGL2DRenderTarget * renderTarget, const GL2D_RECT_U * srcRect )
	{
		GLvoid * srcData = NULL;
		CRenderTarget * rt = static_cast< CRenderTarget * >( renderTarget );
		std::shared_ptr< CContext > context = rt->GetContext();
		HRESULT hr = rt->GetFrameBuffer()->Bind( GL2D_GL_FRAMEBUFFER_MODE_READ );

		if ( hr == S_OK )
		{
			int componentSize = 0;

			switch ( GetPixelFormat().type )
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

			switch ( GetPixelFormat().format )
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
			hr = rt->GetFrameBuffer()->ReadPixels( context, *srcRect, GetPixelFormat(), srcData );
			delete [] srcData;
			rt->GetFrameBuffer()->Unbind();
		}

		if ( hr == S_OK )
		{
			hr = m_texture->Bind( context );
		}

		if ( hr == S_OK )
		{
			hr = m_texture->Fill( context, srcData );
			m_texture->Unbind( context );
		}

		return hr;
	}

	STDMETHODIMP CComBitmap::CopyFromMemory( const GL2D_RECT_U * dstRect, const void * srcData, uint32_t pitch )
	{
		std::shared_ptr< CContext > context = CContext::GetActiveContext();
		HRESULT hr = m_texture->Bind( context );

		if ( hr == S_OK )
		{
			hr = m_texture->Fill( context, srcData );
			m_texture->Unbind( context );
		}

		return hr;
	}
}