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
		:	m_crColour( 0 )
	{
	}

	CImageCtrl::~CImageCtrl()
	{
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
		m_crColour = clrColour;
		m_brush.SetSolidBrush( CColour::FromCOLORREF( m_crColour ) );
		Invalidate();
	}

	void CImageCtrl::DoDrawBackground( CRect const & rcRect )
	{
		BaseType::DrawBitmap( rcRect, m_brush, rcRect );
		BaseType::DrawBitmap( rcRect, *m_pImage, CRect( 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight() ), FALSE );
	}

	BEGIN_MESSAGE_MAP( CImageCtrl, CImageCtrl::BaseType )
		ON_WM_ERASEBKGND()
		ON_WM_PAINT()
	END_MESSAGE_MAP()

	BOOL CImageCtrl::OnEraseBkgnd( CDC * pDC )
	{
		return BaseType::OnEraseBkgnd( pDC );
	}

	void CImageCtrl::OnPaint()
	{
		return BaseType::OnPaint();
	}
}
