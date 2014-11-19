#include "Image.h"
#include "ImageManager.h"
#include "Logger.h"

namespace Joker
{
    template< eRENDERER Renderer >
	CTransparentImageCtrl< Renderer >::CTransparentImageCtrl()
		:	m_crColour( 0 )
	{
	}
    
    template< eRENDERER Renderer >
	CTransparentImageCtrl< Renderer >::~CTransparentImageCtrl()
	{
	}
    
    template< eRENDERER Renderer >
	void CTransparentImageCtrl< Renderer >::SetImage( CString const & p_csImageFilePath )
	{
		m_pImage = CImageManager::AddImage( CString::PCXSTR( p_csImageFilePath ) );
		Invalidate();
	}
    
    template< eRENDERER Renderer >
	void CTransparentImageCtrl< Renderer >::SetImage( UINT uiResourceId )
	{
		m_pImage = CImageManager::AddImage( uiResourceId );
		Invalidate();
	}
    
    template< eRENDERER Renderer >
	void CTransparentImageCtrl< Renderer >::SetBkColor( COLORREF clrColour )
	{
		m_crColour = clrColour;
		m_brush.SetSolidBrush( CColour::FromCOLORREF( m_crColour ) );
		Invalidate();
	}
    
    template< eRENDERER Renderer >
	void CTransparentImageCtrl< Renderer >::DoDrawBackground( CRect const & rcRect )
	{
		BaseType::DrawBitmap( rcRect, m_brush, rcRect );

		if ( m_pImage )
		{
			BaseType::DrawBitmap( rcRect, *m_pImage, CRect( 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight() ), FALSE );
		}
	}

	PTM_WARNING_DISABLE
    template< eRENDERER Renderer >
	const AFX_MSGMAP * CTransparentImageCtrl< Renderer >::GetMessageMap() const
	{
		return GetThisMessageMap();
	}
    
    template< eRENDERER Renderer >
	const AFX_MSGMAP * PASCAL CTransparentImageCtrl< Renderer >::GetThisMessageMap()
	{
		typedef CTransparentImageCtrl< Renderer > ThisClass;
		typedef ThisClass::BaseType TheBaseClass;
		static const AFX_MSGMAP_ENTRY _messageEntries[] =
		{
			ON_WM_ERASEBKGND()
			ON_WM_PAINT()
			{
				0, 0, 0, 0, AfxSig_end, ( AFX_PMSG )0
			}
		};
		static const AFX_MSGMAP messageMap =
		{
			& TheBaseClass::GetThisMessageMap, &_messageEntries[0]
		};
		return &messageMap;
	}
	PTM_WARNING_RESTORE
    
    template< eRENDERER Renderer >
	BOOL CTransparentImageCtrl< Renderer >::OnEraseBkgnd( CDC * pDC )
	{
		return BaseType::OnEraseBkgnd( pDC );
	}
    
    template< eRENDERER Renderer >
	void CTransparentImageCtrl< Renderer >::OnPaint()
	{
		return BaseType::OnPaint();
	}
}
