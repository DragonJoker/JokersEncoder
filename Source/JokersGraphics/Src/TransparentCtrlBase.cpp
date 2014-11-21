#include "stdafx.h"

#include "TransparentCtrlBase.h"

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

namespace Joker
{
	CTransparentCtrlBase::CTransparentCtrlBase()
		:	m_bPainting( false )
		,	m_bHasBackground( false )
		,	m_brushMask( CColour( CColour::Transparent ) )
		,	m_clText( CColour( CColour::FullAlphaBlack ) )
		,	m_clBorder( CColour( CColour::FullAlphaBlack ) )
		,	m_bFocused( false )
		,	m_bMouseOver( false )
		,	m_bHasBorder( true )
		,	m_bReinitBackground( false )
	{
	}

	CTransparentCtrlBase::~CTransparentCtrlBase()
	{
	}

	void CTransparentCtrlBase::SetBorderColour( CColour const & clColour )
	{
		m_clBorder = clColour;
		m_ctrl->RedrawWindow();
	}

	void CTransparentCtrlBase::SetTextColour( CColour const & clColour )
	{
		m_clText = clColour;
		m_ctrl->RedrawWindow();
	}

	void CTransparentCtrlBase::GetRelativeRect( CRect & rcRect )
	{
		CRect l_rcRect1, l_rcRect2;
		m_ctrl->GetWindowRect( l_rcRect1 );
		CWnd * pParent = m_ctrl->GetParent();

		if ( pParent )
		{
			pParent->GetWindowRect( l_rcRect2 );
		}

		rcRect.left = l_rcRect1.left - l_rcRect2.left;
		rcRect.top = l_rcRect1.top - l_rcRect2.top;
		rcRect.right = rcRect.left + l_rcRect1.Width();
		rcRect.bottom = rcRect.top + l_rcRect1.Height();
	}

	BOOL CTransparentCtrlBase::SetWindowPosition( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags )
	{
		m_bReinitBackground = true;
		return m_ctrl->SetWindowPos( pWndInsertAfter, x, y, cx, cy, uiFlags );
	}

	void CTransparentCtrlBase::Initialise()
	{
		DoInitialise();
	}

	void CTransparentCtrlBase::Cleanup()
	{
		DoCleanup();
	}

	BOOL CTransparentCtrlBase::DoDrawParentBackground( CDC * pDC, CRect const & rect )
	{
		ASSERT_VALID( pDC );
		BOOL result = FALSE;
		CRgn rgn;
		CWnd * pParent = m_ctrl->GetParent();

		rgn.CreateRectRgnIndirect( rect );
		pDC->SelectClipRgn( &rgn );

		if ( pParent )
		{
			if ( !result )
			{
				CPoint pt( 0, 0 );
				m_ctrl->MapWindowPoints( pParent, &pt, 1 );
				pt = pDC->OffsetWindowOrg( pt.x, pt.y );
				result = BOOL( pParent->SendMessage( WM_ERASEBKGND, WPARAM( pDC->m_hDC ) ) );
				pDC->SetWindowOrg( pt.x, pt.y );

				int iWidth = rect.Width();
				int iHeight = rect.Height();

				CDC memdc;
				m_bmpBackground.DeleteObject();
				m_bmpBackground.CreateCompatibleBitmap( pDC, iWidth, iHeight );
				memdc.CreateCompatibleDC( pDC );
				CBitmap * pOldbmp = memdc.SelectObject( &m_bmpBackground );
				memdc.BitBlt( 0, 0, iWidth, iHeight, pDC, rect.left, rect.top, SRCCOPY );
				memdc.SelectObject( pOldbmp );

				CImage img;
				img.Attach( m_bmpBackground );
				CString csFileName;
				csFileName.Format( _T( "BackgroundBitmap_0x%08X_0x%08X.bmp" ), pParent->GetDlgCtrlID(), m_ctrl->GetDlgCtrlID() );
				img.Save( csFileName, Gdiplus::ImageFormatBMP );
				img.Detach();
			}
		}

		return result;
	}

	void CTransparentCtrlBase::DoInitialiseBackground()
	{
		CWnd * pParent = m_ctrl->GetParent();

		if ( pParent )
		{
			CRect rcRect;
			m_ctrl->GetWindowRect( &rcRect );
			pParent->ScreenToClient( &rcRect );

			CDC * pDC = pParent->GetDC();

			int iWidth = rcRect.Width();
			int iHeight = rcRect.Height();

			CDC memdc;
			m_bmpBackground.DeleteObject();
			m_bmpBackground.CreateCompatibleBitmap( pDC, iWidth, iHeight );
			memdc.CreateCompatibleDC( pDC );
			CBitmap * pOldbmp = memdc.SelectObject( &m_bmpBackground );
			memdc.BitBlt( 0, 0, iWidth, iHeight, pDC, rcRect.left, rcRect.top, SRCCOPY );
			memdc.SelectObject( pOldbmp );
			pParent->ReleaseDC( pDC );
			memdc.DeleteDC();
			m_bReinitBackground = false;
			m_bHasBackground = true;
		}
	}

#if DEF_USING_D2D
	int CTransparentCtrlBaseD2D::m_iReferences = 0;
	IDWriteFactory * CTransparentCtrlBaseD2D::m_pWriteFactory = NULL;
	ID2D1Factory * CTransparentCtrlBaseD2D::m_pFactory = NULL;
	std::map< HBITMAP, ID2D1Bitmap * > CTransparentCtrlBaseD2D::m_bitmaps;

	CTransparentCtrlBaseD2D::CTransparentCtrlBaseD2D()
	{
	}

	CTransparentCtrlBaseD2D::~CTransparentCtrlBaseD2D()
	{
	}

	inline void CTransparentCtrlBaseD2D::DoInitialise()
	{
		DoInitialiseDeviceIndependent();
		DoInitialiseDeviceDependent();
	}

	inline void CTransparentCtrlBaseD2D::DoCleanup()
	{
		DoCleanupDeviceIndependent();
		DoCleanupDeviceDependent();
	}

	void CTransparentCtrlBaseD2D::DoInitialiseDeviceIndependent()
	{
		m_iReferences++;

		if ( !m_pFactory )
		{
			::D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory );
		}

		if ( !m_pWriteFactory )
		{
			::DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof( IDWriteFactory ), reinterpret_cast< IUnknown ** >( &m_pWriteFactory ) );
		}
	}

	void CTransparentCtrlBaseD2D::DoCleanupDeviceIndependent()
	{
		m_iReferences--;

		if ( !m_iReferences )
		{
			std::for_each( m_bitmaps.begin(), m_bitmaps.end(), [&]( std::pair< HBITMAP, ID2D1Bitmap * > pair )
			{
				SafeRelease( pair.second );
			} );

			m_bitmaps.clear();

			SafeRelease( m_pFactory );
			SafeRelease( m_pWriteFactory );
		}
	}
#endif

#if DEF_USING_OGL
	int CTransparentCtrlBaseOGL::m_iReferences = 0;
	IDWriteFactory * CTransparentCtrlBaseOGL::m_pWriteFactory = NULL;
	IGL2DFactory * CTransparentCtrlBaseOGL::m_pFactory = NULL;
	std::map< HBITMAP, IGL2DBitmap * > CTransparentCtrlBaseOGL::m_bitmaps;

	CTransparentCtrlBaseOGL::CTransparentCtrlBaseOGL()
	{
	}

	CTransparentCtrlBaseOGL::~CTransparentCtrlBaseOGL()
	{
	}

	inline void CTransparentCtrlBaseOGL::DoInitialise()
	{
		DoInitialiseDeviceIndependent();
		DoInitialiseDeviceDependent();
	}

	inline void CTransparentCtrlBaseOGL::DoCleanup()
	{
		DoCleanupDeviceIndependent();
		DoCleanupDeviceDependent();
	}

	void CTransparentCtrlBaseOGL::DoInitialiseDeviceIndependent()
	{
		m_iReferences++;

		if ( !m_pFactory )
		{
			::GL2DCreateFactory( GL2D_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory );
		}

		if ( !m_pWriteFactory )
		{
			::DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof( IDWriteFactory ), reinterpret_cast< IUnknown ** >( &m_pWriteFactory ) );
		}
	}

	void CTransparentCtrlBaseOGL::DoCleanupDeviceIndependent()
	{
		m_iReferences--;

		if ( !m_iReferences )
		{
			std::for_each( m_bitmaps.begin(), m_bitmaps.end(), [&]( std::pair< HBITMAP, IGL2DBitmap * > pair )
			{
				SafeRelease( pair.second );
			} );

			m_bitmaps.clear();

			SafeRelease( m_pFactory );
			SafeRelease( m_pWriteFactory );
		}
	}
#endif
	CTransparentCtrlBaseGDI::CTransparentCtrlBaseGDI()
	{
	}

	CTransparentCtrlBaseGDI::~CTransparentCtrlBaseGDI()
	{
	}

	inline void CTransparentCtrlBaseGDI::DoInitialise()
	{
	}

	inline void CTransparentCtrlBaseGDI::DoCleanup()
	{
	}
}