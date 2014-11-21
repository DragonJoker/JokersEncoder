#pragma once

#include <map>
#include <memory>


namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe de police
	\remark		Permet l'impression en intégrant un ratio
	*/
	class JGRA_API CFont
	{
	public:
		/**
		 *\brief		Constructeur
		 *\param[in]	szFace		Le nom de la police
		 *\param[in]	iHeight		La hauteur de la police
		 *\param[in]	iWeight		Le poids de la police
		 *\param[in]	bItalic		Dit si la police est italique
		 *\param[in]	bUnderlined	Dit si la police est soulignée
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		CFont( LPCTSTR szFace = _T( "Arial" ), int iHeight = 20, int iWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderlined = FALSE, double dRatio = 1 );
		/**
		 *\brief		Constructeur par copie
		 *\param[in]	font	La police à copier
		 */
		CFont( const CFont & font );
		/**
		 *\brief		Opérateur d'affectation par copie
		 *\param[in]	font	La police à copier
		 */
		CFont & operator =( const CFont & font );
		/**
		 *\brief		Constructeur à partir d'une CFont
		 *\param[in]	pFont	La police dont on doit récupérer les infos
		 */
		CFont( ::CFont * pFont );
		/**
		 *\brief		Constructeur à partir d'un LOGFONT
		 *\param[in]	lfLogFont	Les informations de la police
		 */
		CFont( LOGFONT const & lfLogFont );
		/**
		 *\brief		Constructeur à partir d'un HFONT
		 *\param[in]	hFont	La police dont on doit récupérer les infos
		 */
		CFont( HFONT hFont );
		/**
		 *\brief		Destructeur
		 */
		~CFont();
		/**
		 *\brief		Charge la police à partir d'informations
		 *\remark		Supprime la police actuellement chargée
		 *\param[in]	szFace		Le nom de la police
		 *\param[in]	iHeight		La hauteur de la police
		 *\param[in]	iWeight		Le poids de la police
		 *\param[in]	bItalic		Dit si la police est italique
		 *\param[in]	bUnderlined	Dit si la police est soulignée
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		void Load( LPCTSTR szFace = _T( "Arial" ), int iHeight = 20, int iWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderlined = FALSE, double dRatio = 1 );
		/**
		 *\brief		Définit cette police comme police courante du DC donné
		 *\param[in]	hDC	Le DC pour lequel cette police devient la courant
		 */
		void Select( HDC hDC );
		/**
		 *\brief		Redéfinit l'ancienne police pour le DC donné
		 *\param[in]	hDC	Le DC pour lequel cette police était la courante
		 */
		void Deselect( HDC hDC );
		/**
		 *\brief		Récupère les informations de cette police
		 *\param[out]	pLogFont	Reçoit les informations de la police
		 */
		void GetLogFont( LOGFONT * pLogFont );
		/**
		 *\brief		Définit la police à partir d'un LOGFONT
		 *\param[in]	logFont	Le LOGFONT
		 */
		void SetLogFont( const LOGFONT & logFont );
		/**
		 *\brief		Opérateur de conversion implicite vers HFONT
		 */
		operator HFONT();
		/**
		 *\brief		Récupère la hauteur de la police
		 *\return		La hauteur de la police
		 */
		inline int GetHeight()const
		{
			return m_lfLogFont.lfHeight;
		}
		/**
		 *\brief		Récupère si la police est en italique
		 *\return		\p FALSE si pas italique
		 */
		inline BOOL IsItalic()const
		{
			return m_lfLogFont.lfItalic;
		}
		/**
		 *\brief		Récupère si la police est soulignée
		 *\return		\p FALSE si pas soulignée
		 */
		inline BOOL IsUnderlined()const
		{
			return m_lfLogFont.lfUnderline;
		}
		/**
		 *\brief		Récupère le poids de la police
		 *\return		Le poids de la police
		 */
		inline int GetWeight()const
		{
			return m_lfLogFont.lfWeight;
		}
		/**
		 *\brief		Récupère le nom de la police
		 *\return		Le nom de la police
		 */
		inline String GetFaceName()const
		{
			return m_lfLogFont.lfFaceName;
		}
		/**
		 *\brief		Définit la hauteur de la police
		 *\remark		La police est recréée ensuite
		 *\param[in]	iVal	La nouvelle valeur
		 */
		inline void SetHeight( int iVal )
		{
			m_lfLogFont.lfHeight = iVal;
			DoCreate();
		}
		/**
		 *\brief		Définit le poids de la police
		 *\remark		La police est recréée ensuite
		 *\param[in]	iVal	La nouvelle valeur
		 */
		inline void SetWeight( int iVal )
		{
			m_lfLogFont.lfWeight = iVal;
			DoCreate();
		}
		/**
		 *\brief		Définit si la police est italique
		 *\remark		La police est recréée ensuite
		 *\param[in]	bVal	La nouvelle valeur
		 */
		inline void SetItalic( BOOL bVal )
		{
			m_lfLogFont.lfItalic = BYTE( bVal );
			DoCreate();
		}
		/**
		 *\brief		Définit si la police est soulignée
		 *\remark		La police est recréée ensuite
		 *\param[in]	bVal	La nouvelle valeur
		 */
		inline void SetUnderlined( BOOL bVal )
		{
			m_lfLogFont.lfUnderline = BYTE( bVal );
			DoCreate();
		}
		/**
		 *\brief		Dit si la police est chargée
		 *\return		\p FALSE si la police n'est pas initialisée
		 */
		inline BOOL IsLoaded()
		{
			return m_hFont != NULL ? TRUE : FALSE;
		}

	protected:
		void DoDelete();
		void DoCreate();

	protected:
		//! Les informations de la police
		LOGFONT m_lfLogFont;
		//! Le ratio de création
		double m_dRatio;
		//! La police
		HFONT m_hFont;
		//! Dit si on a la charge de la destruction de la police
		BOOL m_bOwnFont;
		//! L'ancienne police (pour les fonctions Select/Deselect)
		HFONT m_hOldFont;
	};

	typedef std::shared_ptr< Joker::CFont > FontPtr;
}