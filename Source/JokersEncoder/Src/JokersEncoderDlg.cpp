#include "stdafx.h"

#include "JokersEncoder.h"
#include "JokersEncoderDlg.h"
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

CJokersEncoderDlg::CJokersEncoderDlg( CWnd * pParent )
	: BaseType( CJokersEncoderDlg::IDD, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
#if DEF_USING_D2D
	if ( GetRenderer() == eRENDERER_D2D )
	{
		BaseType::EnableD2DSupport( TRUE );
	}
#endif
}

CJokersEncoderDlg::~CJokersEncoderDlg()
{
}

void CJokersEncoderDlg::DoDataExchange( CDataExchange * pDX )
{
	BaseType::DoDataExchange( pDX );
#if !DEF_DEBUG_OGL
	DDX_Control( pDX, IDC_LIST_FILES,	m_listFiles );
	DDX_Control( pDX, IDOK,				m_btnOk );
	DDX_Control( pDX, IDCANCEL,			m_btnCancel );
	DDX_Control( pDX, IDC_OPTIONS,		m_btnSettings );
	DDX_Control( pDX, IDC_FILE,			m_btnAddFile );
	DDX_Control( pDX, IDC_FOLDER,		m_btnAddFolder );
#endif
}

BOOL CJokersEncoderDlg::OnInitDialog()
{
	BaseType::OnInitDialog();
	SetIcon( m_hIcon, TRUE );
	SetIcon( m_hIcon, FALSE );
	GetWindowRect( m_rcInitialRect );
	GetClientRect( m_rcRect );
	ScreenToClient( m_rcInitialRect );
	
	CRect rcRect;
	GetClientRect( rcRect );
	ImagePtr img = CImageManager::AddImage( IDB_BMP_DRAGON );
	this->GetMaskBrush().SetPatternBrush( *img, CRect( 0, 0, img->GetWidth(), img->GetHeight() ) );
	
#if !DEF_DEBUG_OGL
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
	m_listFiles.GetMaskBrush().SetSolidBrush( CColour( CColour::MediumAlphaWhite ) );
	m_listFiles.SetItemTextColour( eLB_ITEM_STATUS_NORMAL, CColour( CColour::FullAlphaBlack ) );
#endif
	m_layout.Create( m_hWnd, CRect() );
	m_layout.AddElement( IDC_LIST_FILES );
	m_layout.AddElement( IDOK, false, eHORIZ_ALIGN_RIGHT, eVERTIC_ALIGN_BOTTOM );
	m_layout.AddElement( IDCANCEL, false, eHORIZ_ALIGN_RIGHT, eVERTIC_ALIGN_BOTTOM );
	m_layout.AddElement( IDC_OPTIONS, false, eHORIZ_ALIGN_LEFT, eVERTIC_ALIGN_BOTTOM );
	m_layout.AddElement( IDC_FILE, false, eHORIZ_ALIGN_RIGHT, eVERTIC_ALIGN_TOP );
	m_layout.AddElement( IDC_FOLDER, false, eHORIZ_ALIGN_RIGHT, eVERTIC_ALIGN_TOP );

	return TRUE;
}

BEGIN_MESSAGE_MAP( CJokersEncoderDlg, CJokersEncoderDlg::BaseType )
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_FILE,	& CJokersEncoderDlg::OnBnClickedFile )
	ON_BN_CLICKED( IDC_FOLDER,	& CJokersEncoderDlg::OnBnClickedFolder )
	ON_BN_CLICKED( IDC_OPTIONS,	& CJokersEncoderDlg::OnBnClickedOptions )
	ON_BN_CLICKED( IDOK,		& CJokersEncoderDlg::OnBnClickedOk )
	ON_BN_CLICKED( IDCANCEL,	& CJokersEncoderDlg::OnBnClickedCancel )
END_MESSAGE_MAP()

int CJokersEncoderDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	int iReturn = BaseType::OnCreate( lpCreateStruct );

	if ( iReturn == 0 )
	{/*
		BOOL res = ModifyStyleEx( 0, WS_EX_COMPOSITED | WS_EX_TRANSPARENT );

		if ( res )
		{
			SetLayeredWindowAttributes( 0, 255, LWA_ALPHA );
		}*/
	}

	return iReturn;
}

BOOL CJokersEncoderDlg::OnEraseBkgnd( CDC * pDC )
{
	BaseType::OnEraseBkgnd( pDC );
	return TRUE;
}

void CJokersEncoderDlg::OnPaint()
{
	if ( IsIconic() )
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
		BaseType::OnPaint();
	}
}

void CJokersEncoderDlg::OnSize( UINT uiType, int cx, int cy )
{
	LockWindowUpdate();
	BaseType::OnSize( uiType, cx, cy );
	m_layout.Resize();
	GetClientRect( m_rcRect );
	UnlockWindowUpdate();
}

void CJokersEncoderDlg::OnSizing(  UINT nSide, LPRECT lpRect )
{
	CRect rect( *lpRect );

	if ( rect.Width() < m_rcInitialRect.Width() )
	{
		lpRect->right = lpRect->left + m_rcInitialRect.Width();
	}

	if ( rect.Height() < m_rcInitialRect.Height() )
	{
		lpRect->bottom = lpRect->top + m_rcInitialRect.Height();
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
	BaseType::OnOK();
}

void CJokersEncoderDlg::OnBnClickedCancel()
{
	BaseType::OnCancel();
}