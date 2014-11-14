#include "stdafx.h"

#include "Logger.h"

#pragma warning( push )
#pragma warning( disable:4290 )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Joker
{
	CConsoleInfo::CConsoleInfo()
		:	m_uiOldCP			( 0						)
		,	m_hScreenBuffer		( INVALID_HANDLE_VALUE	)
		,	m_pOldInfos			( NULL					)
	{
		if ( ::AllocConsole() )
		{
			m_hScreenBuffer = ::CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );

			if ( m_hScreenBuffer != INVALID_HANDLE_VALUE && ::SetConsoleActiveScreenBuffer( m_hScreenBuffer ) )
			{
				m_pOldInfos = new CONSOLE_FONT_INFOEX;
				PCONSOLE_FONT_INFOEX l_pOldInfos = PCONSOLE_FONT_INFOEX( m_pOldInfos );
				l_pOldInfos->cbSize = sizeof( CONSOLE_FONT_INFOEX );

				if ( ::GetCurrentConsoleFontEx( m_hScreenBuffer, FALSE, l_pOldInfos ) )
				{
					CONSOLE_FONT_INFOEX l_infos = { 0 };
					l_infos.cbSize = sizeof( CONSOLE_FONT_INFOEX );
					l_infos.dwFontSize = l_pOldInfos->dwFontSize;
					l_infos.FontWeight = l_pOldInfos->FontWeight;
					l_infos.nFont = 6;
					l_infos.FontFamily = 54;
					wcscpy_s( l_infos.FaceName, LF_FACESIZE, L"Lucida Console" );
					::SetCurrentConsoleFontEx( m_hScreenBuffer, FALSE, & l_infos );
				}
				else
				{
					delete m_pOldInfos;
					m_pOldInfos = NULL;
				}
			}

			m_uiOldCP = ::GetConsoleOutputCP();
			::EnumSystemCodePages( & DoCodePageProc, CP_INSTALLED );

			FILE * l_dump;
			freopen_s( & l_dump, "conout$", "w", stdout );
			freopen_s( & l_dump, "conout$", "w", stderr );
		}
	}

	CConsoleInfo::~CConsoleInfo()
	{
		if ( m_pOldInfos )
		{
			::SetCurrentConsoleFontEx( m_hScreenBuffer, FALSE, PCONSOLE_FONT_INFOEX( m_pOldInfos ) );
		}

		delete m_pOldInfos;
		::CloseHandle( m_hScreenBuffer );
		::SetConsoleOutputCP( m_uiOldCP );
		::FreeConsole();
	}

	void CConsoleInfo::Print( eLOG_TYPE p_eLogType, String const & p_strToLog )
	{
		WORD l_wAttributes;

		switch( p_eLogType )
		{
		case eLOG_TYPE_DEBUG	:	l_wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;										break;
		case eLOG_TYPE_MESSAGE	:	l_wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;	break;
		case eLOG_TYPE_WARNING	:	l_wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;					break;
		case eLOG_TYPE_ERROR	:	l_wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;										break;
		default:					l_wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;	break;
		}

		::SetConsoleTextAttribute( m_hScreenBuffer, l_wAttributes );
		::OutputDebugString( p_strToLog.c_str() );
		::OutputDebugString( _T( "\n" ) );

		DWORD l_dwWritten;
		::WriteConsoleW( m_hScreenBuffer, CStrUtils::ToWStr( p_strToLog ).c_str(), p_strToLog.size(), & l_dwWritten, NULL );

		CONSOLE_SCREEN_BUFFER_INFO l_csbiInfo;

		if ( ::GetConsoleScreenBufferInfo( m_hScreenBuffer, & l_csbiInfo ) )
		{
			l_csbiInfo.dwCursorPosition.X = 0;

			if ( (l_csbiInfo.dwSize.Y-1) == l_csbiInfo.dwCursorPosition.Y )
			{
				SMALL_RECT l_srctScrollRect, l_srctClipRect;
				CHAR_INFO l_chiFill;
				COORD l_coordDest;

				l_srctScrollRect.Left = 0;
				l_srctScrollRect.Top = 1;
				l_srctScrollRect.Right = l_csbiInfo.dwSize.X - SHORT( 1 );
				l_srctScrollRect.Bottom = l_csbiInfo.dwSize.Y - SHORT( 1 );
				// The destination for the scroll rectangle is one row up.
				l_coordDest.X = 0;
				l_coordDest.Y = 0;
				// The clipping rectangle is the same as the scrolling rectangle.
				// The destination row is left unchanged.
				l_srctClipRect = l_srctScrollRect;
				// Set the fill character and attributes.
				l_chiFill.Attributes = 0;
				l_chiFill.Char.AsciiChar = char( ' ' );
				// Scroll up one line.
				::ScrollConsoleScreenBuffer(  m_hScreenBuffer, & l_srctScrollRect, & l_srctClipRect, l_coordDest, & l_chiFill );
			}
			else
			{
				l_csbiInfo.dwCursorPosition.Y += 1;
			}

			::SetConsoleCursorPosition( m_hScreenBuffer, l_csbiInfo.dwCursorPosition );
		}
	}

	BOOL __stdcall CConsoleInfo::DoCodePageProc( TCHAR * pszCodePageString )
	{
		BOOL l_bReturn = TRUE;
		String l_strCP( pszCodePageString );
		int l_iCP = CStrUtils::ToInt( l_strCP );

		if ( l_iCP == CP_UTF8 )
		{
			::SetConsoleCP( l_iCP );
			::SetConsoleOutputCP( l_iCP );
			l_bReturn = FALSE;
		}

		return l_bReturn;
	}

	//*************************************************************************************************

	CDebugConsole::CDebugConsole()
	#if ! defined( NDEBUG )
		:	m_pConsoleInfo	( new CConsoleInfo )
	#endif
	{

	}

	CDebugConsole::~CDebugConsole()
	{
	#if ! defined( NDEBUG )
		delete m_pConsoleInfo;
	#endif
	}

	void CDebugConsole::Print( eLOG_TYPE p_eLogType, String const & p_strToLog )
	{
	#if ! defined( NDEBUG )
		m_pConsoleInfo->Print( p_eLogType, p_strToLog );
	#endif
	}

	//*************************************************************************************************

	CLogger *	CLogger::m_pSingleton		= NULL;
	bool		CLogger::m_bOwnInstance	= true;

	CLogger::CLogger()
		:	m_eCurrentLogType	( eLOG_TYPE_COUNT		)
		,	m_pfnCallback		( NULL					)
		,	m_pThis				( NULL					)
	#if DEF_MT_LOGGER
		,	m_hThread			( NULL					)
		,	m_hEventEndThread	( NULL					)
	#endif
	{
		std::unique_lock<std::recursive_mutex > lock( m_mutex );
		m_strHeaders[eLOG_TYPE_DEBUG	] = _T( "***DEBUG*** " );
		m_strHeaders[eLOG_TYPE_MESSAGE	] = _T( "" );
		m_strHeaders[eLOG_TYPE_WARNING	] = _T( "***WARNING*** " );
		m_strHeaders[eLOG_TYPE_ERROR	] = _T( "***ERROR*** ");
	}

	CLogger::~CLogger()
	{
	#if DEF_MT_LOGGER
		if ( m_hThread != NULL )
		{
			if ( ::WaitForSingleObject( m_hThread, 100 ) == WAIT_TIMEOUT && m_hThread )
			{
				assert( false );
				::TerminateThread( m_hThread, 0xFFFFFFFF );
			}
		}

		if ( m_hThread != NULL )
		{
			::CloseHandle( m_hThread );
			m_hThread = NULL;
		}

		if ( m_hEventEndThread != NULL )
		{
			::CloseHandle( m_hEventEndThread );
			m_hEventEndThread = NULL;
		}
	#endif
	}

	void CLogger::InitInstance( CLogger * p_pLogger )
	{
		Cleanup();
		m_bOwnInstance = false;
		m_pSingleton = p_pLogger;
	}

	void CLogger::SetFileName( String const & p_logFilePath, eLOG_TYPE p_eLogType )
	{
		GetSingleton().DoSetFileName( p_logFilePath, p_eLogType );
	#if DEF_MT_LOGGER
		GetSingleton().m_hEventEndThread	= ::CreateEvent( NULL, TRUE, FALSE, NULL );
		GetSingleton().m_hEventLog			= ::CreateEvent( NULL, TRUE, FALSE, NULL );
		GetSingleton().m_hThread			= ::CreateThread( NULL, 0, LPTHREAD_START_ROUTINE( RunCallback ), GetSingletonPtr(), 0, NULL );
	#endif
	}

	void CLogger::Cleanup()
	{
		if ( m_bOwnInstance && m_pSingleton )
		{
	#if DEF_MT_LOGGER
			::SetEvent( m_pSingleton->m_hEventEndThread );
	#endif
			delete m_pSingleton;
		}

		m_pSingleton = NULL;
	}

	void CLogger::SetCallback( PLogCallback p_pfnCallback, void * p_pThis )
	{
		GetSingleton().DoSetCallback( p_pfnCallback, p_pThis );
	}

	void CLogger::LogDebug( char const * p_pFormat, ... )
	{
	#if ! defined( NDEBUG )
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				USES_CONVERSION;
				if ( A2W( p_pFormat ) )
				{
					vswprintf_s( l_pText, A2W( p_pFormat ), l_vaList );
				}
	#else
				vsnprintf_s( l_pText, 256, 256, p_pFormat, l_vaList );
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, l_pText );
	#endif
			}
			catch( ... )
			{
			}
		}
	#endif
	}

	void CLogger::LogDebug( std::string const & p_msg )
	{
		try
		{
	#if ! defined( NDEBUG )
	#if		defined( UNICODE )
		USES_CONVERSION;
	#		if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, A2W( p_msg.c_str() ) );
	#		else
 			GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, A2W( p_msg.c_str() ) );
	#		endif
	#	else
	#		if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, p_msg.c_str() );
	#		else
			GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, p_msg.c_str() );
	#		endif
	#	endif
	#endif
		}
		catch( ... )
		{
		}
	}

	void CLogger::LogDebug( wchar_t const * p_pFormat , ... )
	{
	#if ! defined( NDEBUG )
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				vswprintf_s( l_pText, p_pFormat, l_vaList );
	#else
				USES_CONVERSION;
				if ( W2A( p_pFormat ) )
				{
					vsnprintf_s( l_pText, 256, 256, W2A( p_pFormat ), l_vaList );
				}
	#endif
				va_end( l_vaList );
	#	if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, l_pText );
	#	else
				GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, l_pText );
	#	endif
			}
			catch( ... )
			{
			}
		}
	#endif
	}

	void CLogger::LogDebug( std::wstring const & p_msg )
	{
		try
		{
	#if ! defined( NDEBUG )
	#if		defined( UNICODE )
	#		if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, p_msg.c_str() );
	#		else
			GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, p_msg.c_str() );
	#		endif
	#	else
			USES_CONVERSION;
	#		if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, W2A( p_msg.c_str() ) );
	#		else
			GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, W2A( p_msg.c_str() ) );
	#		endif
	#	endif
	#endif
		}
		catch( ... )
		{
		}
	}

	void CLogger::LogMessage( char const * p_pFormat, ... )
	{
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				USES_CONVERSION;
				if ( A2W( p_pFormat ) )
				{
					vswprintf_s( l_pText, A2W( p_pFormat ), l_vaList );
				}
	#else
				vsnprintf_s( l_pText, 256, 256, p_pFormat, l_vaList );
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, l_pText );
	#endif
			}
			catch( ... )
			{
			}
		}
	}

	void CLogger::LogMessage( std::string const & p_msg )
	{
		try
		{
	#if	defined( UNICODE )
			USES_CONVERSION;
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, A2W( p_msg.c_str() ) );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, A2W( p_msg.c_str() ) );
	#	endif
	#else
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, p_msg.c_str() );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, p_msg.c_str() );
	#	endif
	#endif
		}
		catch( ... )
		{
		}
	}

	void CLogger::LogMessage( wchar_t const * p_pFormat , ... )
	{
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				vswprintf_s( l_pText, p_pFormat, l_vaList );
	#else
			USES_CONVERSION;
				if ( W2A( p_pFormat ) )
				{
					vsnprintf_s( l_pText, 256, 256, W2A( p_pFormat ), l_vaList );
				}
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, l_pText );
	#endif
			}
			catch ( ... )
			{

			}
		}
	}

	void CLogger::LogMessage( std::wstring const & p_msg )
	{
		try
		{
	#if	defined( UNICODE )
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, p_msg.c_str() );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, p_msg.c_str() );
	#	endif
	#else
			USES_CONVERSION;
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, W2A( p_msg.c_str() ) );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, W2A( p_msg.c_str() ) );
	#	endif
	#endif
		}
		catch( ... )
		{
		}
	}

	void CLogger::LogWarning( char const * p_pFormat, ... )
	{
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				USES_CONVERSION;
				if ( A2W( p_pFormat ) )
				{
					vswprintf_s( l_pText, A2W( p_pFormat ), l_vaList );
				}
	#else
				vsnprintf_s( l_pText, 256, 256, p_pFormat, l_vaList );
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, l_pText );
	#endif
			}
			catch ( ... )
			{
			}
		}
	}

	void CLogger::LogWarning( std::string const & p_msg )
	{
		try
		{
	#if	defined( UNICODE )
			USES_CONVERSION;
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, A2W( p_msg.c_str() ) );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, A2W( p_msg.c_str() ) );
	#	endif
	#else
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, p_msg.c_str() );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, p_msg.c_str() );
	#	endif
	#endif
		}
		catch( ... )
		{
		}
	}

	void CLogger::LogWarning( wchar_t const * p_pFormat , ... )
	{
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				vswprintf_s( l_pText, p_pFormat, l_vaList );
	#else
				USES_CONVERSION;
				if ( W2A( p_pFormat ) )
				{
					vsnprintf_s( l_pText, 256, 256, W2A( p_pFormat ), l_vaList );
				}
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, l_pText );
	#endif
			}
			catch ( ... )
			{

			}
		}
	}

	void CLogger::LogWarning( std::wstring const & p_msg )
	{
		try
		{
	#if	defined( UNICODE )
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, p_msg.c_str() );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, p_msg.c_str() );
	#	endif
	#else
			USES_CONVERSION;
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, W2A( p_msg.c_str() ) );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, W2A( p_msg.c_str() ) );
	#	endif
	#endif
		}
		catch( ... )
		{
		}
	}

	void CLogger::LogError( char const * p_pFormat, ... )
	{
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				USES_CONVERSION;
				if ( A2W( p_pFormat ) )
				{
					vswprintf_s( l_pText, A2W( p_pFormat ), l_vaList );
				}
	#else
				vsnprintf_s( l_pText, 256, 256, p_pFormat, l_vaList );
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_pText );
	#endif
			}
			catch ( ... )
			{

			}
		}
	}

	void CLogger::LogError( std::string const & p_msg, bool p_bThrow )throw( bool )
	{
		try
		{
	#if	defined( UNICODE )
			USES_CONVERSION;
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, A2W( p_msg.c_str() ) );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, A2W( p_msg.c_str() ) );
	#	endif
	#else
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, p_msg.c_str() );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, p_msg.c_str() );
	#	endif
	#endif
		}
		catch( ... )
		{
		}

		if ( p_bThrow )
		{
			throw false;
		}
	}

	void CLogger::LogError( wchar_t const * p_pFormat , ... )
	{
		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				vswprintf_s( l_pText, p_pFormat, l_vaList );
	#else
				USES_CONVERSION;
				if ( W2A( p_pFormat ) )
				{
					vsnprintf_s( l_pText, 256, 256, W2A( p_pFormat ), l_vaList );
				}
	#endif
				va_end( l_vaList );
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_pText );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_pText );
	#endif
			}
			catch ( ... )
			{

			}
		}
	}

	void CLogger::LogError( std::wstring const & p_msg, bool p_bThrow )throw( bool )
	{
		try
		{
	#if	defined( UNICODE )
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, p_msg.c_str() );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, p_msg.c_str() );
	#	endif
	#else
			USES_CONVERSION;
	#	if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, W2A( p_msg.c_str() ) );
	#	else
			GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, W2A( p_msg.c_str() ) );
	#	endif
	#endif
		}
		catch( ... )
		{
		}

		if ( p_bThrow )
		{
			throw false;
		}
	}

	void CLogger::LogLastError( char const * p_pFormat, ... )
	{
		String l_strError;
		DWORD l_dwError = ::GetLastError();
		LPTSTR l_szError = 0;

		if ( l_dwError != ERROR_SUCCESS && ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, l_dwError, 0, (LPTSTR)& l_szError, 0, NULL ) != 0 )
		{
			l_strError = l_szError;
			::LocalFree( l_szError );
		}

		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				USES_CONVERSION;
				if ( A2W( p_pFormat ) )
				{
					vswprintf_s( l_pText, A2W( p_pFormat ), l_vaList );
				}
	#else
				vsnprintf_s( l_pText, 256, 256, p_pFormat, l_vaList );
	#endif
				va_end( l_vaList );
				l_strError += String( _T( " - " ) ) + l_pText;
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#endif
			}
			catch ( ... )
			{

			}
		}
	}

	void CLogger::LogLastError( std::string const & p_msg, bool p_bThrow )throw( bool )
	{
		String l_strError;
		DWORD l_dwError = ::GetLastError();
		LPTSTR l_szError = 0;

		if ( l_dwError != ERROR_SUCCESS && ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, l_dwError, 0, (LPTSTR)& l_szError, 0, NULL ) != 0 )
		{
			l_strError = l_szError;
			::LocalFree( l_szError );
		}

		try
		{
	#if defined( UNICODE )
			USES_CONVERSION;
			l_strError += String( _T( " - " ) ) + A2W( p_msg.c_str() );
	#else
			l_strError += String( _T( " - " ) ) + p_msg;
	#endif
	#if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#else
			GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#endif
		}
		catch ( ... )
		{
		}

		if ( p_bThrow )
		{
			throw false;
		}
	}

	void CLogger::LogLastError( wchar_t const * p_pFormat , ... )
	{
		String l_strError;
		DWORD l_dwError = ::GetLastError();
		LPTSTR l_szError = 0;

		if ( l_dwError != ERROR_SUCCESS && ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, l_dwError, 0, (LPTSTR)& l_szError, 0, NULL ) != 0 )
		{
			l_strError = l_szError;
			::LocalFree( l_szError );
		}

		TCHAR l_pText[256];
		va_list l_vaList;

		if ( p_pFormat )
		{
			try
			{
				va_start( l_vaList, p_pFormat );
	#if defined( _UNICODE )
				vswprintf_s( l_pText, p_pFormat, l_vaList );
	#else
				USES_CONVERSION;
				if ( W2A( p_pFormat ) )
				{
					vsnprintf_s( l_pText, 256, 256, W2A( p_pFormat ), l_vaList );
				}
	#endif
				va_end( l_vaList );
				l_strError += String( _T( " - " ) ) + l_pText;
	#if DEF_MT_LOGGER
				GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#else
				GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#endif
			}
			catch ( ... )
			{
			}
		}
	}

	void CLogger::LogLastError( std::wstring const & p_msg, bool p_bThrow )throw( bool )
	{
		String l_strError;
		DWORD l_dwError = ::GetLastError();
		LPTSTR l_szError = 0;

		if ( l_dwError != ERROR_SUCCESS && ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, l_dwError, 0, (LPTSTR)& l_szError, 0, NULL ) != 0 )
		{
			l_strError = l_szError;
			::LocalFree( l_szError );
		}

		try
		{
	#if defined( UNICODE )
			l_strError += String( _T( " - " ) ) + p_msg.c_str();
	#else
			USES_CONVERSION;
			l_strError += String( _T( " - " ) ) + W2A( p_msg.c_str() );
	#endif
	#if DEF_MT_LOGGER
			GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#else
			GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#endif
		}
		catch ( ... )
		{
		}

		if ( p_bThrow )
		{
			throw false;
		}
	}
	#if DEF_USING_CSTRING
	void CLogger::LogDebug( CString const & p_msg )
	{
	#if ! defined( NDEBUG )
	#	if DEF_MT_LOGGER
		GetSingleton().DoPostMessage( eLOG_TYPE_DEBUG, p_msg );
	#	else
 		GetSingleton().DoLogMessage( eLOG_TYPE_DEBUG, p_msg );
	#	endif
	#endif
	}

	void CLogger::LogMessage( CString const & p_msg )
	{
	#	if DEF_MT_LOGGER
		GetSingleton().DoPostMessage( eLOG_TYPE_MESSAGE, p_msg );
	#else
		GetSingleton().DoLogMessage( eLOG_TYPE_MESSAGE, p_msg );
	#endif
	}

	void CLogger::LogWarning( CString const & p_msg )
	{
	#	if DEF_MT_LOGGER
		GetSingleton().DoPostMessage( eLOG_TYPE_WARNING, p_msg );
	#else
		GetSingleton().DoLogMessage( eLOG_TYPE_WARNING, p_msg );
	#endif
	}

	void CLogger::LogError( CString const & p_msg, bool p_bThrow )throw( bool )
	{
	#	if DEF_MT_LOGGER
		GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, p_msg );
	#else
		GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, p_msg );
	#endif

		if ( p_bThrow )
		{
			throw false;
		}
	}

	void CLogger::LogLastError( CString const & p_msg, bool p_bThrow )throw( bool )
	{

		String l_strError;
		DWORD l_dwError = ::GetLastError();
		LPTSTR l_szError = 0;

		if ( l_dwError != ERROR_SUCCESS && ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, l_dwError, 0, (LPTSTR)& l_szError, 0, NULL ) != 0 )
		{
			l_strError = l_szError;
			::LocalFree( l_szError );
		}

		l_strError += String( _T( " - " ) ) + LPCTSTR( p_msg );
	#	if DEF_MT_LOGGER
		GetSingleton().DoPostMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#	else
		GetSingleton().DoLogMessage( eLOG_TYPE_ERROR, l_strError.c_str() );
	#	endif

		if ( p_bThrow )
		{
			throw false;
		}
	}
	#endif
	CLogger & CLogger::GetSingleton()
	{
		if ( ! m_pSingleton )
		{
			m_bOwnInstance = true;
			m_pSingleton = new CLogger();
		}

		return * m_pSingleton;
	}

	CLogger * CLogger::GetSingletonPtr()
	{
		return & GetSingleton();
	}

	#if DEF_MT_LOGGER
	void CLogger::DoProcessMessages()
	{
		m_mutexLines.Lock();
		std::vector< std::pair< eLOG_TYPE, LPTSTR > >::iterator it = m_lines.begin();

		while ( m_lines.size() )
		{
			DoLogMessage( it->first, it->second );
			delete [] it->second;
			m_lines.erase( it );
			it = m_lines.begin();
		}

		m_mutexLines.Unlock();
		::ResetEvent( m_hEventLog );
	}

	void CLogger::DoPostMessage( eLOG_TYPE eLogType, LPCTSTR szText )
	{
		m_mutexLines.Lock();
		size_t uilength = _tcslen( strText );
		LPTSTR pszText = new TCHAR[uilength + 1];
		_tcscpy_s( pszText, uilength * sizeof( TCHAR ), szText );
		m_lines.push_back( std::make_pair( eLogType, pszText ) );
		m_mutexLines.Unlock();
		::SetEvent( m_hEventLog );
	}

	BOOL CLogger::IsStopped()
	{
		BOOL bReturn = TRUE;

		if ( m_hThread != NULL )
		{
			DWORD dwWaitResult = ::WaitForSingleObject( m_hThread, 0 );

			switch( dwWaitResult )
			{
			case WAIT_OBJECT_0:
				bReturn = TRUE;
				break;

			case WAIT_TIMEOUT:
				bReturn = FALSE;
				break;

			default:
				bReturn = TRUE;
				break;
			}
		}

		return bReturn;
	}

	DWORD CLogger::RunCallback( CLogger * pThis )
	{
		HANDLE arrayHandles[] = { pThis->m_hEventLog, pThis->m_hEventEndThread };
		DWORD dwCount = 2;
		BOOL bContinue;

		do
		{
			switch( ::WaitForMultipleObjects( dwCount, arrayHandles, FALSE, 10 ) )
			{
			case WAIT_OBJECT_0:		// Lignes de log en attente
				bContinue = TRUE;
				pThis->DoProcessMessages();
				break;

			case WAIT_OBJECT_0 + 1:	// Demande de fermeture
				bContinue = FALSE;
				break;

			case WAIT_TIMEOUT:		// RAF
				bContinue = TRUE;
				break;

			default:				// Thread en vrac
				bContinue = FALSE;
				break;
			}
		}
		while ( bContinue && ! pThis->IsStopped() );

		return 0;
	}
	#endif

	void CLogger::DoSetCallback( PLogCallback p_pfnCallback, void * p_pThis )
	{
		m_pfnCallback = p_pfnCallback;
		m_pThis = p_pThis;
	}

	void CLogger::DoSetFileName( String const & p_logFilePath, eLOG_TYPE p_eLogType )
	{
		std::unique_lock<std::recursive_mutex > lock( m_mutex );

		if ( p_eLogType >= eLOG_TYPE_COUNT )
		{
			for ( int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < eLOG_TYPE_COUNT ; GL2D_SIZE_I++ )
			{
				m_logFilePath[GL2D_SIZE_I] = p_logFilePath;
			}
		}
		else if ( p_eLogType >= 0 )
		{
			m_logFilePath[p_eLogType] = p_logFilePath;
		}

		FILE * l_pFile;
		_tfopen_s( & l_pFile, p_logFilePath.c_str(), _T( "w" ) );

		if ( l_pFile )
		{
			fclose( l_pFile);
		}
	}

	void CLogger::DoLogMessage( eLOG_TYPE p_eLogType, LPCTSTR p_szToLog )
	{
		std::unique_lock<std::recursive_mutex > lock( m_mutex );
		m_eCurrentLogType = p_eLogType;
		String l_strToLog;

		std::tm l_dtToday;
		time_t l_tTime;

		time( & l_tTime );
		localtime_s( & l_dtToday, & l_tTime );

		l_strToLog << (l_dtToday.tm_year + 1900) << _T( "-" );
		l_strToLog << (l_dtToday.tm_mon + 1 < 10 ? _T( "0" ) : _T( "" )) << (l_dtToday.tm_mon + 1) << _T( "-" ) << (l_dtToday.tm_mday < 10 ? _T( "0" ) : _T( "" )) << l_dtToday.tm_mday;
		l_strToLog << _T( " - " ) << (l_dtToday.tm_hour < 10 ? _T( "0" ) : _T( "" )) << l_dtToday.tm_hour << _T( ":" ) << (l_dtToday.tm_min < 10 ? _T( "0" ) : _T( "" )) << l_dtToday.tm_min << _T( ":" ) << (l_dtToday.tm_sec < 10 ? _T( "0" ) : _T( "" )) << l_dtToday.tm_sec << _T( "s" );
		l_strToLog << _T( " - " ) << m_strHeaders[m_eCurrentLogType];

		l_strToLog += p_szToLog;

		m_console.Print( p_eLogType, p_szToLog );

		FILE * l_pLogFile;
		_tfopen_s( & l_pLogFile, m_logFilePath[m_eCurrentLogType].c_str(), _T( "a" ) );

		if ( l_pLogFile )
		{
			_ftprintf_s( l_pLogFile, _T( "%s\n" ), l_strToLog.c_str() );

			if ( m_pfnCallback )
			{
				m_pfnCallback( m_pThis, l_strToLog, m_eCurrentLogType );
			}

			fclose( l_pLogFile );
		}
	}
}

#pragma warning( pop )
