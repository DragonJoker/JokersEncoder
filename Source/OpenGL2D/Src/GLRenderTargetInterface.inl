#include "GLBitmapRenderTarget.h"
#include "GLBitmap.h"
#include "GLHelper.h"
#include "GLContext.h"

namespace GL2D
{
	static inline uint32_t GetBytesPerPixel( GL2D_PIXEL_FORMAT format )
	{
		switch ( format.internal )
		{
		case GL2D_GL_INTERNAL_LUMINANCE:
			return 1;

		case GL2D_GL_INTERNAL_ALPHA8:
			return 1;

		case GL2D_GL_INTERNAL_ALPHA16:
			return 2;

		case GL2D_GL_INTERNAL_LUMINANCE8:
			return 1;

		case GL2D_GL_INTERNAL_LUMINANCE16:
			return 2;

		case GL2D_GL_INTERNAL_LUMINANCE8_ALPHA8:
			return 2;

		case GL2D_GL_INTERNAL_LUMINANCE16_ALPHA16:
			return 4;

		case GL2D_GL_INTERNAL_INTENSITY8:
			return 1;

		case GL2D_GL_INTERNAL_INTENSITY16:
			return 2;

		case GL2D_GL_INTERNAL_RGB8:
			return 3;

		case GL2D_GL_INTERNAL_RGB16:
			return 6;

		case GL2D_GL_INTERNAL_RGBA8:
			return 4;

		case GL2D_GL_INTERNAL_RGBA16:
			return 8;

		case GL2D_GL_INTERNAL_DEPTH_COMPONENT16:
			return 2;

		case GL2D_GL_INTERNAL_DEPTH_COMPONENT24:
			return 3;

		case GL2D_GL_INTERNAL_DEPTH_COMPONENT32:
			return 4;

		case GL2D_GL_INTERNAL_R8:
			return 1;

		case GL2D_GL_INTERNAL_RG8:
			return 2;

		case GL2D_GL_INTERNAL_RG16:
			return 4;

		case GL2D_GL_INTERNAL_R32F:
			return 4;

		case GL2D_GL_INTERNAL_RG32F:
			return 8;

		case GL2D_GL_INTERNAL_RGBA32F:
			return 16;

		case GL2D_GL_INTERNAL_RGB32F:
			return 12;

		case GL2D_GL_INTERNAL_DEPTH24_STENCIL8:
			return 4;

		case GL2D_GL_INTERNAL_DEPTH_COMPONENT32F:
			return 4;

		case GL2D_GL_INTERNAL_STENCIL_INDEX1:
			return 1;

		case GL2D_GL_INTERNAL_STENCIL_INDEX4:
			return 1;

		case GL2D_GL_INTERNAL_STENCIL_INDEX8:
			return 1;

		case GL2D_GL_INTERNAL_STENCIL_INDEX16:
			return 2;
		}

		return 0;
	}

	template< typename Object, typename Interface >
	CRenderTargetInterface< Object, Interface >::CRenderTargetInterface( IGL2DFactory * factory )
		: CResource< Object, Interface >( factory )
	{
	}

	template< typename Object, typename Interface >
	CRenderTargetInterface< Object, Interface >::~CRenderTargetInterface()
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateBitmap( GL2D_SIZE_U size, const void * srcData, uint32_t pitch, const GL2D_BITMAP_PROPERTIES * bitmapProperties, IGL2DBitmap ** bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
			CBitmap * bmp = reinterpret_cast< CBitmap * >( CBitmap::CreateInstance( m_factory ) );
			hr = bmp->Initialise( size, srcData, pitch, *bitmapProperties );

			if ( hr == S_OK )
			{
				*bitmap = bmp;
			}
			else
			{
				bmp->Release();
			}
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateBitmapFromWicBitmap( IWICBitmapSource * wicBitmapSource, const GL2D_BITMAP_PROPERTIES * bitmapProperties, IGL2DBitmap ** bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
			*bitmap = NULL;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateSharedBitmap( REFIID riid, void * data, const GL2D_BITMAP_PROPERTIES * bitmapProperties, IGL2DBitmap ** bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
			*bitmap = NULL;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateBitmapBrush( IGL2DBitmap * bitmap, const GL2D_BITMAP_BRUSH_PROPERTIES * bitmapBrushProperties, const GL2D_BRUSH_PROPERTIES * brushProperties, IGL2DBitmapBrush ** bitmapBrush )
	{
		HRESULT hr = E_POINTER;

		if ( bitmapBrush )
		{
			*bitmapBrush = NULL;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateSolidColorBrush( const GL2D_COLOR_F * color, const GL2D_BRUSH_PROPERTIES * brushProperties, IGL2DSolidColorBrush ** solidColorBrush )
	{
		HRESULT hr = E_POINTER;

		if ( solidColorBrush )
		{
			*solidColorBrush = NULL;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateGradientStopCollection( const GL2D_GRADIENT_STOP * gradientStops, uint32_t gradientStopsCount, GL2D_GAMMA colorInterpolationGamma, GL2D_EXTEND_MODE extendMode, IGL2DGradientStopCollection ** gradientStopCollection )
	{
		HRESULT hr = E_POINTER;

		if ( gradientStopCollection )
		{
			*gradientStopCollection = NULL;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateLinearGradientBrush( const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES * linearGradientBrushProperties, const GL2D_BRUSH_PROPERTIES * brushProperties, IGL2DGradientStopCollection * gradientStopCollection, IGL2DLinearGradientBrush ** linearGradientBrush )
	{
		HRESULT hr = E_POINTER;

		if ( linearGradientBrush )
		{
			*linearGradientBrush = NULL;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateRadialGradientBrush( const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES * radialGradientBrushProperties, const GL2D_BRUSH_PROPERTIES * brushProperties, IGL2DGradientStopCollection * gradientStopCollection, IGL2DRadialGradientBrush ** radialGradientBrush )
	{
		HRESULT hr = E_POINTER;

		if ( radialGradientBrush )
		{
			*radialGradientBrush = NULL;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateCompatibleRenderTarget( const GL2D_SIZE_F * desiredSize, const GL2D_SIZE_U * desiredPixelSize, const GL2D_PIXEL_FORMAT * desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options, IGL2DBitmapRenderTarget ** bitmapRenderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( bitmapRenderTarget )
		{
			*bitmapRenderTarget = CBitmapRenderTarget::CreateInstance( m_factory );
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateLayer( const GL2D_SIZE_F * size, IGL2DLayer ** layer )
	{
		HRESULT hr = E_POINTER;

		if ( layer )
		{
			*layer = NULL;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::CreateMesh( IGL2DMesh ** mesh )
	{
		HRESULT hr = E_POINTER;

		if ( mesh )
		{
			*mesh = NULL;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawLine( GL2D_POINT_2F point0, GL2D_POINT_2F point1, IGL2DBrush * brush, float strokeWidth, IGL2DStrokeStyle * strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawRectangle( const GL2D_RECT_F * rect, IGL2DBrush * brush, float strokeWidth, IGL2DStrokeStyle * strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::FillRectangle( const GL2D_RECT_F * rect, IGL2DBrush * brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawRoundedRectangle( const GL2D_ROUNDED_RECT * roundedRect, IGL2DBrush * brush, float strokeWidth, IGL2DStrokeStyle * strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::FillRoundedRectangle( const GL2D_ROUNDED_RECT * roundedRect, IGL2DBrush * brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawEllipse( const GL2D_ELLIPSE * ellipse, IGL2DBrush * brush, float strokeWidth, IGL2DStrokeStyle * strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::FillEllipse( const GL2D_ELLIPSE * ellipse, IGL2DBrush * brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawGeometry( IGL2DGeometry * geometry, IGL2DBrush * brush, float strokeWidth, IGL2DStrokeStyle * strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::FillGeometry( IGL2DGeometry * geometry, IGL2DBrush * brush, IGL2DBrush * opacityBrush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::FillMesh( IGL2DMesh * mesh, IGL2DBrush * brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::FillOpacityMask( IGL2DBitmap * opacityMask, IGL2DBrush * brush, GL2D_OPACITY_MASK_CONTENT content, const GL2D_RECT_F * destinationRectangle, const GL2D_RECT_F * sourceRectangle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawBitmap( IGL2DBitmap * bitmap, const GL2D_RECT_F * destinationRectangle, float opacity, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F * sourceRectangle )
	{
		if ( bitmap )
		{
			CBitmap * bmp = reinterpret_cast< CBitmap * >( bitmap );
			GetContext()->DrawTexture( bmp->GetTexture(), *destinationRectangle, interpolationMode, *sourceRectangle );
		}
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawText( const WCHAR * string, uint32_t stringLength, IDWriteTextFormat * textFormat, const GL2D_RECT_F * layoutRect, IGL2DBrush * defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode )
	{
		if ( textFormat && defaultForegroundBrush && string && stringLength )
		{
			CTexture * texture = DoLoadFont( textFormat );
			float x = layoutRect->left;
			float y = layoutRect->top;
			IDWriteFontCollection * collection = NULL;
			UINT32 index = 0;
			BOOL exists = FALSE;
			textFormat->GetFontCollection( &collection );
			DWRITE_FONT_METRICS metrics = { 0 };

			if ( collection )
			{
				WCHAR * szName = new WCHAR[textFormat->GetFontFamilyNameLength() + 1];
				collection->FindFamilyName( szName, &index, &exists );

				if ( exists )
				{
					IDWriteFontFamily * family = NULL;
					collection->GetFontFamily( index, &family );

					if ( family )
					{
						IDWriteFont * font = NULL;
						family->GetFirstMatchingFont( textFormat->GetFontWeight(), textFormat->GetFontStretch(), textFormat->GetFontStyle(), &font );

						if ( font )
						{
							font->GetMetrics( &metrics );
							SafeRelease( font );
						}
					
						SafeRelease( family );
					}
				}

				SafeRelease( collection );
			}

			std::vector< SVertex > vertices;
			vertices.reserve( stringLength * 6 );
			float size = textFormat->GetFontSize();

			for ( uint32_t i = 0; i < stringLength; ++i )
			{
				WCHAR character = string[i];
				float uv_x = ( character % 16 ) / 16.0f;
				float uv_y = ( character / 16 ) / 16.0f;

				SVertex vertex_up_left		= SVertex( glm::vec2( x + i * size       , y + size ), glm::vec2( uv_x              , 1.0f - uv_y  ) );
				SVertex vertex_up_right		= SVertex( glm::vec2( x + i * size + size, y + size ), glm::vec2( uv_x + 1.0f /16.0f, 1.0f - uv_y ) );
				SVertex vertex_down_right	= SVertex( glm::vec2( x + i * size + size, y        ), glm::vec2( uv_x + 1.0f /16.0f, 1.0f - ( uv_y + 1.0f / 16.0f ) ) );
				SVertex vertex_down_left	= SVertex( glm::vec2( x + i * size       , y        ), glm::vec2( uv_x              , 1.0f - ( uv_y + 1.0f / 16.0f ) ) );
 
				vertices.push_back( vertex_up_left );
				vertices.push_back( vertex_down_left );
				vertices.push_back( vertex_up_right );

				vertices.push_back( vertex_down_right );
				vertices.push_back( vertex_up_right );
				vertices.push_back( vertex_down_left );
			}
		}
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawTextLayout( GL2D_POINT_2F origin, IDWriteTextLayout * textLayout, IGL2DBrush * defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::DrawGlyphRun( GL2D_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN * glyphRun, IGL2DBrush * foregroundBrush, DWRITE_MEASURING_MODE measuringMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SetTransform( const GL2D_MATRIX_3X2_F * transform )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::GetTransform( GL2D_MATRIX_3X2_F * transform ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SetAntialiasMode( GL2D_ANTIALIAS_MODE antialiasMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_ANTIALIAS_MODE ) CRenderTargetInterface< Object, Interface >::GetAntialiasMode() const
	{
		return GL2D_ANTIALIAS_MODE_ALIASED;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SetTextAntialiasMode( GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_TEXT_ANTIALIAS_MODE ) CRenderTargetInterface< Object, Interface >::GetTextAntialiasMode( ) const
	{
		return GL2D_TEXT_ANTIALIAS_MODE_ALIASED;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SetTextRenderingParams( IDWriteRenderingParams * textRenderingParams )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::GetTextRenderingParams( IDWriteRenderingParams ** textRenderingParams ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SetTags( GL2D_TAG tag1, GL2D_TAG tag2 )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::GetTags( GL2D_TAG * tag1, GL2D_TAG * tag2 ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::PushLayer( const GL2D_LAYER_PARAMETERS * layerParameters, IGL2DLayer * layer )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::PopLayer()
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetInterface< Object, Interface >::Flush( GL2D_TAG * tag1, GL2D_TAG * tag2 )
	{
		return E_NOTIMPL;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SaveDrawingState( IGL2DDrawingStateBlock * drawingStateBlock ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::RestoreDrawingState( IGL2DDrawingStateBlock * drawingStateBlock )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::PushAxisAlignedClip( const GL2D_RECT_F * clipRect, GL2D_ANTIALIAS_MODE antialiasMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::PopAxisAlignedClip()
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::Clear( const GL2D_COLOR_F * colour )
	{
		std::shared_ptr< CContext > context = GetContext();
		context->ClearColor( colour->r, colour->g, colour->b, colour->a );
		context->Clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_PIXEL_FORMAT ) CRenderTargetInterface< Object, Interface >::GetPixelFormat() const
	{
		return GL2D_PIXEL_FORMAT();
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::SetDpi( float dpiX, float dpiY )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetInterface< Object, Interface >::GetDpi( float * dpiX, float * dpiY ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_SIZE_F ) CRenderTargetInterface< Object, Interface >::GetSize() const
	{
		float x, y;
		GetDpi( &x, &y );
		return SizeF( m_size.width / x, m_size.height / y );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_SIZE_U ) CRenderTargetInterface< Object, Interface >::GetPixelSize() const
	{
		return m_size;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( uint32_t ) CRenderTargetInterface< Object, Interface >::GetMaximumBitmapSize() const
	{
		return GetContext()->GetInt( GL2D_GL_MAX_TEXTURE_BUFFER_SIZE );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( bool ) CRenderTargetInterface< Object, Interface >::IsSupported( const GL2D_RENDER_TARGET_PROPERTIES * renderTargetProperties ) const
	{
		return false;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( CTexture * ) CRenderTargetInterface< Object, Interface >::DoLoadFont( IDWriteTextFormat * textFormat )
	{
		return NULL;
	}
}