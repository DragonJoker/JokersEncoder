#ifndef ___OGL2D_OPENGL_2D_PREREQUISITES_H___
#define ___OGL2D_OPENGL_2D_PREREQUISITES_H___

#include "GL2D.h"
#include <memory>

namespace GL2D
{
	template< typename Object, const GUID * Clsid >
	class CUnknown;
	template< typename Object, typename Interface >
	class CResource;
	template< typename Object, typename Interface >
	class CImage;
	template< typename Object, typename Interface >
	class CRenderTargetBase;

	class CComBitmap;
	class CComStrokeStyle;
	class CComBrush;
	class CComSolidColorBrush;
	class CComFactory;
	class CComBitmapBrush;
	class CComLinearGradientBrush;
	class CComRadialGradientBrush;
	class CComLayer;
	class CComMesh;
	class CComGeometry;
	class CComDrawingStateBlock;
	class CComRenderTarget;
	class CComHwndRenderTarget;
	class CComBitmapRenderTarget;
	class CComGradientStopCollection;

	typedef CImage< CComBitmap, IGL2DBitmap > CBitmap;
	typedef CResource< CComStrokeStyle, IGL2DStrokeStyle > CStrokeStyle;
	typedef CResource< CComBrush, IGL2DBrush > CBrush;
	typedef CResource< CComSolidColorBrush, IGL2DSolidColorBrush > CSolidColorBrush;
	typedef CResource< CComFactory, IGL2DFactory > CFactory;
	typedef CResource< CComBitmapBrush, IGL2DBitmapBrush > CBitmapBrush;
	typedef CResource< CComLinearGradientBrush, IGL2DLinearGradientBrush > CLinearGradientBrush;
	typedef CResource< CComRadialGradientBrush, IGL2DRadialGradientBrush > CRadialGradientBrush;
	typedef CResource< CComLayer, IGL2DLayer > CLayer;
	typedef CResource< CComMesh, IGL2DMesh > CMesh;
	typedef CResource< CComGeometry, IGL2DGeometry > CGeometry;
	typedef CResource< CComDrawingStateBlock, IGL2DDrawingStateBlock > CDrawingStateBlock;
	typedef CResource< CComGradientStopCollection, IGL2DGradientStopCollection > CGradientStopCollection;
	typedef CRenderTargetBase< CComRenderTarget, IGL2DRenderTarget > CRenderTarget;
	typedef CRenderTargetBase< CComHwndRenderTarget, IGL2DHwndRenderTarget > CHwndRenderTarget;
	typedef CRenderTargetBase< CComBitmapRenderTarget, IGL2DBitmapRenderTarget > CBitmapRenderTarget;

	class CContext;

	HRESULT glGetLastError( char const * const name );
}

#if !DEF_HAS_MAKE_UNIQUE
namespace std
{
	template< class T >
	unique_ptr< T > make_unique()
	{
		return unique_ptr< T >( new T );
	}
	template< class T, typename Arg1 >
	unique_ptr< T > make_unique( Arg1 && arg1 )
	{
		return unique_ptr< T >( new T( arg1 ) );
	}
	template< class T, typename Arg1, typename Arg2 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2 )
	{
		return unique_ptr< T >( new T( arg1, arg2 ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3 )
	{
		return unique_ptr< T >( new T( arg1, arg2, arg3 ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4 )
	{
		return unique_ptr< T >( new T( arg1, arg2, arg3, arg4 ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5 )
	{
		return unique_ptr< T >( new T( arg1, arg2, arg3, arg4, arg5 ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5, Arg6 && arg6 )
	{
		return unique_ptr< T >( new T( arg1, arg2, arg3, arg4, arg5, arg6 ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5, Arg6 && arg6, Arg7 && arg7 )
	{
		return unique_ptr< T >( new T( arg1, arg2, arg3, arg4, arg5, arg6, arg7 ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5, Arg6 && arg6, Arg7 && arg7, Arg8 && arg8 )
	{
		return unique_ptr< T >( new T( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 ) );
	}
}
#endif

#endif
