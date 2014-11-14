#include "stdafx.h"

#include "JokersEncoder.h"
#include "JokersEncoderDlg.h"
#include "OptionsDlg.h"
#include "FontManager.h"

#include <afxdialogex.h>
#include <Image.h>

#ifdef _DEBUG
#	define new DEBUG_NEW
#	undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Joker;

CJokersEncoderDlg::CJokersEncoderDlg( CWnd * pParent )
	: CDialogEx( CJokersEncoderDlg::IDD, pParent )
{
	CWnd::EnableD2DSupport( TRUE );
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CJokersEncoderDlg::DoDataExchange( CDataExchange * pDX )
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_LIST_FILES,	m_listFiles );
	DDX_Control( pDX, IDC_BACKGROUND,	m_staticBackground );
	DDX_Control( pDX, IDOK,				m_btnOk );
	DDX_Control( pDX, IDCANCEL,			m_btnCancel );
	DDX_Control( pDX, IDC_OPTIONS,		m_btnSettings );
	DDX_Control( pDX, IDC_FILE,			m_btnAddFile );
	DDX_Control( pDX, IDC_FOLDER,		m_btnAddFolder );
}

BOOL CJokersEncoderDlg::OnInitDialog()
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
	m_btnOk.SetTextColour( CColour::FullAlphaBlack );
	m_btnOk.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_btnOk.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_btnOk.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_btnOk.SetGradientBrush( eBTN_STATE_PUSHED,		0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_btnOk.SetFonts( font, font, font, font );

	m_btnCancel.SetTextColour( CColour::FullAlphaBlack );
	m_btnCancel.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_btnCancel.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_btnCancel.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_btnCancel.SetGradientBrush( eBTN_STATE_PUSHED,		0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_btnCancel.SetFonts( font, font, font, font );

	m_btnSettings.SetTextColour( CColour::FullAlphaBlack );
	m_btnSettings.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_btnSettings.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_btnSettings.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_btnSettings.SetGradientBrush( eBTN_STATE_PUSHED,		0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_btnSettings.SetFonts( font, font, font, font );

	m_btnAddFile.SetTextColour( CColour::FullAlphaBlack );
	m_btnAddFile.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_btnAddFile.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_btnAddFile.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_btnAddFile.SetGradientBrush( eBTN_STATE_PUSHED,		0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_btnAddFile.SetFonts( font, font, font, font );

	m_btnAddFolder.SetTextColour( CColour::FullAlphaBlack );
	m_btnAddFolder.SetBorderColour( CColour( CColour::FullAlphaWhite ) );
	m_btnAddFolder.SetGradientBrush( eBTN_STATE_ENABLED,		0, clrTrnspt, clrApGrey, clrSBlack, 50 );
	m_btnAddFolder.SetGradientBrush( eBTN_STATE_HIGHLIGHTED,	0, clrLtTrsp, clrLtGrey, clrLtBlak, 50 );
	m_btnAddFolder.SetGradientBrush( eBTN_STATE_PUSHED,			0, clrSBlack, clrApGrey, clrTrnspt, 50 );
	m_btnAddFolder.SetFonts( font, font, font, font );

	m_listFiles.AddString( _T( "01 - dfsugfugv" ) );
	m_listFiles.AddString( _T( "02 - dfsfgsugfugv" ) );
	m_listFiles.AddString( _T( "03 - dfsusqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "04 - dfzerezrggrhsugfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "05 - dfsurggsugfugv" ) );
	m_listFiles.AddString( _T( "06 - dfsuzergsqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "07 - dfsdgjsbfuilsvfgfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "08 - dfsdgjsbfuilsvfgzrgefugv" ) );
	m_listFiles.AddString( _T( "09 - dfsdgjsbfuilsvfgsgeugfugv" ) );
	m_listFiles.AddString( _T( "10 - dghdgjsbfuilsvfezfgfsusqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "11 - dfsdgjsbfuilsvfzergfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "12 - dfsdgjsbfuilsvfgfugv" ) );
	m_listFiles.AddString( _T( "13 - dfsdgjsbfuilsvfzerggergzsugfugv" ) );
	m_listFiles.AddString( _T( "14 - dfsdgjsbfuilsvfszergqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "15 - dfsdgjsbfuilsvfzeggfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "16 - dfsdgjsbfuilsvfgfugv" ) );
	m_listFiles.AddString( _T( "17 - dfsdgjsbfuilsvfgsugfugv" ) );
	m_listFiles.AddString( _T( "18 - dfsdgjsbfuilsvfqdfgqsdcvqlsqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "19 - dfzdgjsbfuilsvfqdfgqsdcvqlrezrggrhsugfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "20 - dfsdgjsbfuilsvfqdfgqsdcvqlrggsugfugv" ) );
	m_listFiles.AddString( _T( "21 - dfsdgjsbfuilsvfqdfgqsdcvqlzergsqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "22 - dfsdgjsbfuilsvfqdfgqsdcvqlgfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "23 - dfsdgjsbfuilsvfqdfgqsdcvqlgzrgefugv" ) );
	m_listFiles.AddString( _T( "24 - dfsdgjsbfuilsvfqdfgqsdcvqlgsgeugfugv" ) );
	m_listFiles.AddString( _T( "25 - dghdgjsbfuilsvfqdfgqsdcvqlezfgfsusqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "26 - dfsdgjsqsdgsfhdgbfuilsvfqdfgqsdcvqlzergfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.AddString( _T( "27 - dfsdgjsqsdgsfhdgbfuilsvfqdfgqsdcvqlgfugv" ) );
	m_listFiles.AddString( _T( "28 - dfsdgjsqsdgsfhdgbfuilsvfqdfgqsdcvqlzerggergzsugfugv" ) );
	m_listFiles.AddString( _T( "29 - dfsdgjsqsdgsfhdgbfuilsvfqdfgqsdcvqlszergqsfssjsjgfugv" ) );
	m_listFiles.AddString( _T( "30 - dfsdgjsqsdgsfhdgbfuilsvfqdfgqsdcvqlzeggfugdqsfslkkflhbqFGVv" ) );
	m_listFiles.SetItemTextColour( eLB_ITEM_STATUS_NORMAL, CColour( CColour::FullAlphaBlack ) );
	return TRUE;
}

BEGIN_MESSAGE_MAP( CJokersEncoderDlg, CDialogEx )
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_FILE,	& CJokersEncoderDlg::OnBnClickedFile	)
	ON_BN_CLICKED( IDC_FOLDER,	& CJokersEncoderDlg::OnBnClickedFolder	)
	ON_BN_CLICKED( IDC_OPTIONS,	& CJokersEncoderDlg::OnBnClickedOptions	)
	ON_BN_CLICKED( IDOK,		& CJokersEncoderDlg::OnBnClickedOk		)
	ON_BN_CLICKED( IDCANCEL,	& CJokersEncoderDlg::OnBnClickedCancel	)
END_MESSAGE_MAP()

int CJokersEncoderDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	int iReturn = CDialogEx::OnCreate( lpCreateStruct );

	if( iReturn == 0 )
	{
//		ModifyStyleEx( 0, WS_EX_LAYERED | WS_EX_TRANSPARENT);
//		SetLayeredWindowAttributes(0, 255 * 0.50, LWA_ALPHA);
	}

	return iReturn;
}

HBRUSH CJokersEncoderDlg::OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID)
{
	HBRUSH hRet = NULL;

	if( uiWinID == IDC_LIST_FILES )
	{
		hRet = HBRUSH( GetStockObject( HOLLOW_BRUSH ) );
	}

	return hRet;
}

void CJokersEncoderDlg::OnPaint()
{
	if( IsIconic() )
	{
		CPaintDC dc( this );
		SendMessage( WM_ICONERASEBKGND, reinterpret_cast< WPARAM >( dc.GetSafeHdc() ), 0 );
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( & rect );
		int x = ( rect.Width() - cxIcon + 1 ) / 2;
		int y = ( rect.Height() - cyIcon + 1 ) / 2;
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CJokersEncoderDlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CJokersEncoderDlg::OnBnClickedFile()
{
}

void CJokersEncoderDlg::OnBnClickedFolder()
{
}

void CJokersEncoderDlg::OnBnClickedOptions()
{
	COptionsDlg optDialog;
	optDialog.DoModal();
}

void CJokersEncoderDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CJokersEncoderDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}