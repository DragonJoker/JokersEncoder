#include "stdafx.h"

#include "Font.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CFont::CFont( LPCTSTR szFace, int iHeight, int iWeight, BOOL bItalic, BOOL bUnderlined, double dRatio )
		:	m_lfLogFont		(			)
		,	m_dRatio		( dRatio	)
		,	m_hFont			( NULL		)
		,	m_bOwnFont		( TRUE		)
		,	m_hOldFont		( NULL		)
	{
		_tcscpy_s( m_lfLogFont.lfFaceName, szFace );
		m_lfLogFont.lfHeight	= iHeight;
		m_lfLogFont.lfWeight	= iWeight;
		m_lfLogFont.lfItalic	= BYTE( bItalic );
		m_lfLogFont.lfUnderline	= BYTE( bUnderlined );

		DoCreate();
	}

	CFont::CFont( const CFont & font )
		:	m_lfLogFont		(				)
		,	m_dRatio		( font.m_dRatio	)
		,	m_hFont			( NULL			)
		,	m_bOwnFont		( TRUE			)
		,	m_hOldFont		( NULL			)
	{
		_tcscpy_s( m_lfLogFont.lfFaceName, font.m_lfLogFont.lfFaceName );
		m_lfLogFont.lfHeight	= font.m_lfLogFont.lfHeight;
		m_lfLogFont.lfWeight	= font.m_lfLogFont.lfWeight;
		m_lfLogFont.lfItalic	= font.m_lfLogFont.lfItalic;
		m_lfLogFont.lfUnderline	= font.m_lfLogFont.lfUnderline;

		DoCreate();
	}

	CFont::CFont( ::CFont * pFont )
		:	m_lfLogFont		(		)
		,	m_dRatio		( 1		)
		,	m_hFont			( NULL	)
		,	m_bOwnFont		( TRUE	)
		,	m_hOldFont		( NULL	)
	{
		if ( pFont )
		{
			pFont->GetLogFont( &m_lfLogFont );
		}
		else
		{
			_tcscpy_s( m_lfLogFont.lfFaceName, _T( "Arial" ) );
			m_lfLogFont.lfHeight	= 14;
			m_lfLogFont.lfWeight	= FW_NORMAL;
			m_lfLogFont.lfItalic	= 0;
			m_lfLogFont.lfUnderline	= 0;
		}

		DoCreate();
	}

	CFont::CFont( LOGFONT const & lfLogFont )
		:	m_lfLogFont		(		)
		,	m_dRatio		( 1		)
		,	m_hFont			( NULL	)
		,	m_bOwnFont		( TRUE	)
		,	m_hOldFont		( NULL	)
	{
		_tcscpy_s( m_lfLogFont.lfFaceName, lfLogFont.lfFaceName );
		m_lfLogFont.lfHeight		= lfLogFont.lfHeight;
		m_lfLogFont.lfWeight		= lfLogFont.lfWeight;
		m_lfLogFont.lfItalic		= lfLogFont.lfItalic;
		m_lfLogFont.lfUnderline		= lfLogFont.lfUnderline;

		DoCreate();
	}

	CFont::CFont( HFONT hFont )
		:	m_lfLogFont		(		)
		,	m_dRatio		( 1		)
		,	m_hFont			( hFont	)
		,	m_bOwnFont		( FALSE	)
		,	m_hOldFont		( NULL	)
	{
		::GetObject( hFont, sizeof( LOGFONT ), &m_lfLogFont );
	}

	CFont::~CFont()
	{
		DoDelete();
	}

	void CFont::GetLogFont( LOGFONT * pLogFont )
	{
		::GetObject( m_hFont, sizeof( LOGFONT ), pLogFont );
	}

	CFont::operator HFONT()
	{
		return m_hFont;
	}

	void CFont::DoDelete()
	{
		if ( m_hFont != NULL && m_bOwnFont )
		{
			::DeleteObject( m_hFont );
		}

		m_hFont = NULL;
	}

	void CFont::Load( LPCTSTR szFace, int iHeight, int iWeight, BOOL bItalic, BOOL bUnderlined, double dRatio )
	{
		DoDelete();

		_tcscpy_s( m_lfLogFont.lfFaceName, szFace );
		m_lfLogFont.lfHeight		= iHeight;
		m_lfLogFont.lfWeight		= iWeight;
		m_lfLogFont.lfItalic		= BYTE( bItalic );
		m_lfLogFont.lfUnderline		= BYTE( bUnderlined );
		m_dRatio = dRatio;

		DoCreate();
	}

	void CFont::Select( HDC hDC )
	{
		if ( m_hFont )
		{
			m_hOldFont = HFONT( ::SelectObject( hDC, m_hFont ) );
		}
		else
		{
			ASSERT( FALSE );
		}
	}

	void CFont::Deselect( HDC hDC )
	{
		if ( m_hOldFont )
		{
			::SelectObject( hDC, m_hOldFont );
		}
	}

	CFont & CFont::operator =( const CFont & font )
	{
		DoDelete();

		_tcscpy_s( m_lfLogFont.lfFaceName, font.m_lfLogFont.lfFaceName );
		m_lfLogFont.lfHeight		= font.m_lfLogFont.lfHeight;
		m_lfLogFont.lfWeight		= font.m_lfLogFont.lfWeight;
		m_lfLogFont.lfItalic		= font.m_lfLogFont.lfItalic;
		m_lfLogFont.lfUnderline		= font.m_lfLogFont.lfUnderline;
		m_dRatio					= font.m_dRatio;

		DoCreate();

		return *this;
	}

	void CFont::DoCreate()
	{
		if ( m_lfLogFont.lfHeight != 0 && m_lfLogFont.lfWeight != 0 )
		{
			DoDelete();

			m_lfLogFont.lfQuality		= PROOF_QUALITY;
			m_lfLogFont.lfEscapement	= 0;
			m_lfLogFont.lfOrientation	= 0;

			m_hFont = ::CreateFontIndirect( &m_lfLogFont );
		}
	}
}
