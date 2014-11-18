#include "stdafx.h"

#include "JokersEncoder.h"
#include "OptionsDlg.h"
#include "FontManager.h"

#include <afxdialogex.h>
#include <Image.h>

using namespace Joker;

IMPLEMENT_DYNAMIC( COptionsDlg, CDialogEx )

COptionsDlg::COptionsDlg( CWnd * pParent )
	:	CDialogEx( COptionsDlg::IDD, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange( CDataExchange * pDX )
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_STATIC_BACKGROUND,	m_staticBackground );
	DDX_Control( pDX, IDOK,						m_buttonOK );
	DDX_Control( pDX, IDCANCEL,					m_buttonCancel );
}


BOOL COptionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon( m_hIcon, TRUE );
	SetIcon( m_hIcon, FALSE );
	CRect rcRect;
	GetClientRect( rcRect );
	m_staticBackground.SetWindowPos( NULL, 0, 0, rcRect.Width(), rcRect.Height(), SWP_SHOWWINDOW );
	m_staticBackground.SetImage( IDB_BMP_DRAGON );

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

BEGIN_MESSAGE_MAP( COptionsDlg, CDialogEx )
END_MESSAGE_MAP()


// Gestionnaires de messages de COptionsDlg
