#pragma once

#include "StrUtils.h"

#include <mutex>
#include <thread>
#include <condition_variable>
#include <fstream>

#pragma warning( push)
#pragma warning( disable:4290)

#define	DEF_MT_LOGGER	0

namespace Joker
{
	/*!
	\author Sylvain DOREMUS
	\version 0.6.1.0
	\date 19/10/2011
	\brief Définit les différents types de log
	*/
	typedef enum
	{	eLOG_TYPE_DEBUG		//!<Log de type debug
	,	eLOG_TYPE_MESSAGE	//!<Log de type message
	,	eLOG_TYPE_WARNING	//!<Log de type avertissement
	,	eLOG_TYPE_ERROR		//!<Log de type erreur
	,	eLOG_TYPE_COUNT		//!<Compte des logs
	}	eLOG_TYPE;
	/*!
	\author Sylvain DOREMUS
	\version 0.6.1.0
	\date 19/10/2011
	\brief Classe contenant les informations de la console
	*/
	class CConsoleInfo
	{
	private:
		unsigned int			m_uiOldCP;
		HANDLE					m_hScreenBuffer;
		PCONSOLE_FONT_INFOEX	m_pOldInfos;

	public:
		CConsoleInfo();
		virtual ~CConsoleInfo();
		virtual void Print( eLOG_TYPE p_eLogType, String const & p_strToLog );

	private:
		static BOOL __stdcall DoCodePageProc( TCHAR * pszCodePageString );
	};
	/*!
	\author Sylvain DOREMUS
	\version 0.6.1.0
	\date 19/10/2011
	\brief Classe de gestion de la console de debug
	*/
	class CDebugConsole
	{
	private:
#if ! defined( NDEBUG )
		CConsoleInfo * m_pConsoleInfo;
#endif

	public:
		CDebugConsole();
		~CDebugConsole();

		void Print( eLOG_TYPE p_eLogType, String const & p_strToLog );
	};
	//!Fonction de callback de log
	typedef void (LogCallback)( void * p_pThis, String const & p_strLog, eLOG_TYPE p_eLogType );
	//!Typedef d'un pointeur sur la fonction de callback de log
	typedef LogCallback * PLogCallback;
	/*!
	\author Sylvain DOREMUS
	\version 0.6.1.0
	\date 19/10/2011
	\brief Classe de gestion de logs
	\note Implémente les fonctions de logging. Initialise un log avec un nom de fichier puis écrit dedans
	*/
	class JGRA_API CLogger
	{
	private:
		static bool			m_bOwnInstance;
		static CLogger *	m_pSingleton;
#if DEF_MT_LOGGER
		HANDLE											m_hThread;
		HANDLE											m_hEventEndThread;
		HANDLE											m_hEventLog;
		CA2iRecursiveMutex								m_mutexLines;
		std::vector< std::pair< eLOG_TYPE, LPTSTR > >	m_lines;
#endif
		String					m_logFilePath[eLOG_TYPE_COUNT];
		String					m_strHeaders[eLOG_TYPE_COUNT];
		std::stringstream		m_cout;
		std::stringstream		m_cerr;
		std::stringstream		m_clog;
		std::recursive_mutex	m_mutex;
		eLOG_TYPE				m_eCurrentLogType;
		PLogCallback			m_pfnCallback;
		void *					m_pThis;
		CDebugConsole			m_console;
		std::thread				m_outThread;
		std::mutex				m_outMutex;
        std::condition_variable	m_end;

	private:
		/**@name Construction / Destruction */
		//@{
		CLogger();
		~CLogger();
		//@}

	public:
		/**
		 * Initialise l'instance de ce Logger à une autre
		 *\param[in]	p_pLogger	Le logger
		 */
		static void InitInstance( CLogger * p_pLogger );
		/**
		 * Détruit l'instance du Logger
		 */
		static void Cleanup();
		/**
		 * Définit la callback de log
		 *\param[in]	p_pfnCallback	La callback
		 *\param[in]	p_pThis			Pointeur sur des données utilisateur
		 */
		static void SetCallback( PLogCallback p_pfnCallback, void * p_pThis );
		/**
		 * Définit le chemin du fichier de log
		 *\param[in]	p_logFilePath	Le chemin du fichier
		 *\param[in]	p_eLogType		Le type de log concerné
		 */
		static void SetFileName( String const & p_logFilePath, eLOG_TYPE p_eLogType=eLOG_TYPE_COUNT);
		/**
		 * Log un message debug dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogDebug( char const * p_format, ...);
		/**
		 * Log un message debug, à partir d'un std::string
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogDebug( std::string const & p_msg);
		/**
		 * Log un message unicode debug dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogDebug( wchar_t const * p_format , ...);
		/**
		 * Log un message debug, à partir d'un std::wstring
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogDebug( std::wstring const & p_msg);
		/**
		 * Log un message dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogMessage( char const * p_format, ...);
		/**
		 * Log un message, à partir d'un std::string
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogMessage( std::string const & p_msg);
		/**
		 * Log une ligne unicode dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogMessage( wchar_t const * p_format , ...);
		/**
		 * Log un message, à partir d'un std::wstring
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogMessage( std::wstring const & p_msg);
		/**
		 * Log un avertissement dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogWarning( char const * p_format, ...);
		/**
		 * Log un avertissement, à partir d'un std::string
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogWarning( std::string const & p_msg);
		/**
		 * Log un avertissement en unicode dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogWarning( wchar_t const * p_format , ...);
		/**
		 * Log un avertissement, à partir d'un std::wstring
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogWarning( std::wstring const & p_msg);
		/**
		 * Log une erreur dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogError( char const * p_format, ...);
		/**
		 * Log une erreur, à partir d'un std::string
		 *\param[in]	p_msg		La ligne à logger
		 *\param[in]	p_bThrow	Définit si cette fonction lance une exception
		 */
		static void LogError( std::string const & p_msg, bool p_bThrow=true)throw( bool);
		/**
		 * Log une erreur en unicode dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogError( wchar_t const * p_format , ...);
		/**
		 * Log une erreur, à partir d'un std::wstring
		 *\param[in]	p_msg		La ligne à logger
		 *\param[in]	p_bThrow	Définit si cette fonction lance une exception
		 */
		static void LogError( std::wstring const & p_msg, bool p_bThrow=true)throw( bool);
		/**
		 * Log une erreur dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogLastError( char const * p_format, ...);
		/**
		 * Log une erreur, à partir d'un std::string
		 *\param[in]	p_msg		La ligne à logger
		 *\param[in]	p_bThrow	Définit si cette fonction lance une exception
		 */
		static void LogLastError( std::string const & p_msg, bool p_bThrow=true)throw( bool);
		/**
		 * Log une erreur en unicode dans le fichier de log, en utilisant va_args
		 *\param[in]	p_format	Le format de la ligne
		 *\param[in]	...			Paramètres POD, utilise le format de printf
		 */
		static void LogLastError( wchar_t const * p_format , ...);
		/**
		 * Log une erreur, à partir d'un std::wstring
		 *\param[in]	p_msg		La ligne à logger
		 *\param[in]	p_bThrow	Définit si cette fonction lance une exception
		 */
		static void LogLastError( std::wstring const & p_msg, bool p_bThrow=true)throw( bool);
#if DEF_USING_CSTRING
		/**
		 * Log un message debug dans le fichier de log, à partir d'un CString
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogDebug( CString const & p_msg );
		/**
		 * Log un message, à partir d'un CString
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogMessage( CString const & p_msg);
		/**
		 * Log un avertissement, à partir d'un CString
		 *\param[in]	p_msg	La ligne à logger
		 */
		static void LogWarning( CString const & p_msg);
		/**
		 * Log une erreur, à partir d'un CString
		 *\param[in]	p_msg		La ligne à logger
		 *\param[in]	p_bThrow	Définit si cette fonction lance une exception
		 */
		static void LogError( CString const & p_msg, bool p_bThrow=true)throw( bool);
		/**
		 * Log une erreur, à partir d'un CString
		 *\param[in]	p_msg		La ligne à logger
		 *\param[in]	p_bThrow	Définit si cette fonction lance une exception
		 */
		static void LogLastError( CString const & p_msg, bool p_bThrow=true)throw( bool);
#endif
		/**
		 * Retourne une référence sur l'instance
		 *\return	L'instance
		 */
		static CLogger & GetSingleton();
		/**
		 * Retourne un pointeur sur l'instance
		 *\return	L'instance
		 */
		static CLogger * GetSingletonPtr();

	private:
#if DEF_MT_LOGGER
		void	DoProcessMessages	();
		void	DoPostMessage		( eLOG_TYPE eLogType, LPCTSTR szText );
		BOOL	IsStopped			();
#endif
		void	DoSetCallback		( PLogCallback p_pfnCallback, void * p_pThis );
		void	DoSetFileName		( String const & p_logFilePath, eLOG_TYPE p_eLogType=eLOG_TYPE_COUNT );
		void	DoLogMessage		( eLOG_TYPE p_eLogType, LPCTSTR p_szToLog );

		static DWORD RunCallback( CLogger * pThis );
	};
}

#pragma warning( pop)
