#include "stdafx.h"

#include "JokersEncoder.h"
#include "JokersEncoderDlg.h"
#include "BmpImageHandler.h"
#include "PngImageHandler.h"

#include <Image.h>

using namespace Joker;

#if !defined( VLD_AVAILABLE )
#	ifdef _DEBUG
#		define new DEBUG_NEW
#		undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#	endif
#endif

CJokersEncoderApp theApp;

BEGIN_MESSAGE_MAP( CJokersEncoderApp, CWinApp )
	ON_COMMAND( ID_HELP, &CWinApp::OnHelp )
END_MESSAGE_MAP()

CJokersEncoderApp::CJokersEncoderApp()
{
}

BOOL CJokersEncoderApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof( InitCtrls );
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx( &InitCtrls );
	CWinApp::InitInstance();

	DWORD length = ::GetCurrentDirectory( 0, NULL );
	TCHAR * directory = new TCHAR[length];
	::GetCurrentDirectory( length, directory );
	Joker::CLogger::SetFileName( String( directory ) + _T( "\\JokersEncoder.log" ), eLOG_TYPE_COUNT );
	delete [] directory;

	CShellManager * pShellManager = new CShellManager;
	Joker::CImage::AddHandler( eIMAGE_TYPE_BITMAP, new CBmpImageHandler() );
	Joker::CImage::AddHandler( eIMAGE_TYPE_PNG, new CPngImageHandler() );

	SetRegistryKey( _T( "Applications locales générées par AppWizard" ) );

	CJokersEncoderDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if ( pShellManager != NULL )
	{
		delete pShellManager;
	}

	Joker::CImage::DeleteHandlers();

	return FALSE;
}

int CJokersEncoderApp::ExitInstance()
{
	Joker::CLogger::Cleanup();
	return 0;
}

#if DEF_USING_D2D
#	pragma comment( lib, "d2d1.lib" )
#endif
