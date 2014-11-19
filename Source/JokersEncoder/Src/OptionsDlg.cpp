#include "stdafx.h"

#include "JokersEncoder.h"
#include "OptionsDlg.h"
#include "FontManager.h"

#include <afxdialogex.h>
#include <Image.h>
#include <ImageManager.h>

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

using namespace Joker;

IMPLEMENT_DYNAMIC( COptionsDlg, BaseType )

COptionsDlg::COptionsDlg( CWnd * pParent )
	:	BaseType( COptionsDlg::IDD, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange( CDataExchange * pDX )
{
	BaseType::DoDataExchange( pDX );
	DDX_Control( pDX, IDOK,		m_buttonOK );
	DDX_Control( pDX, IDCANCEL,	m_buttonCancel );
}


BOOL COptionsDlg::OnInitDialog()
{
	BaseType::OnInitDialog();
	SetIcon( m_hIcon, TRUE );
	SetIcon( m_hIcon, FALSE );
	CRect rcRect;
	GetClientRect( rcRect );
	ImagePtr img = CImageManager::AddImage( IDB_BMP_DRAGON );
	this->GetMaskBrush().SetPatternBrush( *img, CRect( 0, 0, img->GetWidth(), img->GetHeight() ) );

	LOGFONT logfont;
	::CFont * pFont = this->GetFont();
	pFont->GetLogFont( &logfont );
	Joker::FontPtr font = CFontManager::GetFont( CFontManager::AddFont( logfont.lfFaceName, logfont.lfHeight, logfont.lfWeight, logfont.lfItalic, logfont.lfUnderline ), true );

	CColour clrTrnspt = CColour( CColour::Transparent );
	CColour clrApGrey = CColour( CColour::LowAlphaGrey );
	CColour clrSBlack = CColour( CColour::HighAlphaBlack );
	CColour clrLtTrsp = CColour::FromComponents( 30, 30, 30, 0 );
	CColour clrLtGrey = CColour::FromComponents( 157, 157, 157, 64 );
	CColour clrLtBlak = CColour::FromComponents( 30, 30, 30, 191 );

	m_buttonOK.SetTextColour( CColour::FullAlphaBlack );
	m_buttonOK.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_buttonOK.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_buttonOK.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_buttonOK.SetGradientBrush( eBTN_STATE_PUSHED,			0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_buttonOK.SetFonts( font, font, font, font );

	m_buttonCancel.SetTextColour( CColour::FullAlphaBlack );
	m_buttonCancel.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_buttonCancel.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_buttonCancel.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_buttonCancel.SetGradientBrush( eBTN_STATE_PUSHED,			0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_buttonCancel.SetFonts( font, font, font, font );
	return TRUE;
}

BEGIN_MESSAGE_MAP( COptionsDlg, COptionsDlg::BaseType )
END_MESSAGE_MAP()


// Gestionnaires de messages de COptionsDlg
