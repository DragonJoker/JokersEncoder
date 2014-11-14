#include "stdafx.h"
#include "ImageCtrl.h"
#include "Image.h"
#include "ImageManager.h"
#include "Logger.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	template< typename T > struct Deleter;

	template <> struct Deleter< HBRUSH >
	{
		inline void operator()( HBRUSH hBrush )
		{
			if ( hBrush )
			{
				::DeleteObject( hBrush );
				hBrush = NULL;
			}
		}
	};

	template <> struct Deleter< HDC >
	{
		inline void operator()( HDC hDC )
		{
			if ( hDC )
			{
				::DeleteDC( hDC );
				hDC = NULL;
			}
		}
	};

	template <typename T>
	void Delete( T pPointer )
	{
		Deleter< T > deleter;
		deleter( pPointer );
	}

	//*************************************************************************************************

	CImageCtrl::CImageCtrl()
		:	m_crColour			( 0 )
	{
	}

	CImageCtrl::~CImageCtrl()
	{
		Delete( m_hBrush );
	}

	void CImageCtrl::SetImage( CString const & p_csImageFilePath )
	{
		m_pImage = CImageManager::GetSingleton().AddImage( CString::PCXSTR( p_csImageFilePath ) );
		Invalidate();
	}

	void CImageCtrl::SetImage( UINT uiResourceId )
	{
		m_pImage = CImageManager::GetSingleton().AddImage( uiResourceId );
		Invalidate();
	}

	void CImageCtrl::SetBkColor( COLORREF clrColour )
	{
		Delete( m_hBrush );
		m_crColour = clrColour;
		m_hBrush = CreateSolidBrush( m_crColour );
		Invalidate();
	}

	void CImageCtrl::DrawGDI( HDC hDC )
	{
		SetBkMode( hDC, TRANSPARENT );
		CRect rcRect;
		GetClientRect( & rcRect );

		if ( m_pImage != NULL && ! m_pImage->IsNull() )
		{
			SetStretchBltMode( hDC, HALFTONE );
			m_pImage->AlphaBlend( hDC, CRect( 0, 0, rcRect.Width(), rcRect.Height() ), CRect( 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight() ) );
		}
		else
		{
			FillRect( hDC, rcRect, m_hBrush );
		}
	}

	BEGIN_MESSAGE_MAP( CImageCtrl, CStatic )
		ON_WM_ERASEBKGND()
		ON_WM_CTLCOLOR()
		ON_WM_PAINT()
	END_MESSAGE_MAP()

	HBRUSH CImageCtrl::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiCtlId )
	{
		return m_hBrush;
	}

	BOOL CImageCtrl::OnEraseBkgnd( CDC * pDC )
	{
		BOOL bReturn = TRUE;
		return bReturn;
	}

	void CImageCtrl::OnPaint()
	{
		CPaintDC l_paintDC( this );
		DrawGDI( l_paintDC.m_hDC );
	}
}
