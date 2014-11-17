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

	template< typename T >
	void Delete( T pPointer )
	{
		Deleter< T > deleter;
		deleter( pPointer );
	}

	//*************************************************************************************************

	CTransparentImageCtrl::CTransparentImageCtrl()
		:	m_crColour( 0 )
	{
	}

	CTransparentImageCtrl::~CTransparentImageCtrl()
	{
	}

	void CTransparentImageCtrl::SetImage( CString const & p_csImageFilePath )
	{
		m_pImage = CImageManager::GetSingleton().AddImage( CString::PCXSTR( p_csImageFilePath ) );
		Invalidate();
	}

	void CTransparentImageCtrl::SetImage( UINT uiResourceId )
	{
		m_pImage = CImageManager::GetSingleton().AddImage( uiResourceId );
		Invalidate();
	}

	void CTransparentImageCtrl::SetBkColor( COLORREF clrColour )
	{
		m_crColour = clrColour;
		m_brush.SetSolidBrush( CColour::FromCOLORREF( m_crColour ) );
		Invalidate();
	}

	void CTransparentImageCtrl::DoDrawBackground( CRect const & rcRect )
	{
		BaseType::DrawBitmap( rcRect, m_brush, rcRect );
		BaseType::DrawBitmap( rcRect, *m_pImage, CRect( 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight() ), FALSE );
	}

	BEGIN_MESSAGE_MAP( CTransparentImageCtrl, CTransparentImageCtrl::BaseType )
		ON_WM_ERASEBKGND()
		ON_WM_PAINT()
	END_MESSAGE_MAP()

	BOOL CTransparentImageCtrl::OnEraseBkgnd( CDC * pDC )
	{
		return BaseType::OnEraseBkgnd( pDC );
	}

	void CTransparentImageCtrl::OnPaint()
	{
		return BaseType::OnPaint();
	}
}
