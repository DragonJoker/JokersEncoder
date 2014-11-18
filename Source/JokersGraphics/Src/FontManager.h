#pragma once

#include <map>
#include <memory>

#include "Font.h"
#include "AutoSingleton.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe g�rant les polices cr��es, par index
	\remark		Permet de ne pas cr�er 50 fois la m�me police
	*/
	class JGRA_API CFontManager
		: public CAutoSingleton< CFontManager >
	{
	protected:
		friend class CAutoSingleton< CFontManager> ;
		typedef std::map< UINT,	FontPtr >	FontPtrUIntMap;

	protected:
		/**
		 *\brief		Constructeur par d�faut
		 */
		CFontManager();
		/**
		 *\brief		Destructeur
		 */
		~CFontManager();

	public:
		/**
		 *\brief		Supprime les polices cr��es
		 */
		static void DeleteFonts();
		/**
		 *\brief		Cr�e et ajoute une police � partir d'une cha�ne d'informations
		 *\remark		La cha�ne doit �tre constitu�e de la mani�re suivante :
						<br /><Nom de la police>,<hauteur>,<normal/bold>,<italique:false/true>,<soulign�:false/true>
						<br />Ex : Arial,14,normal,false,false
						<br />Il n'y a auucun espace
		 *\param[in]	uiIndex		L'index de la police � cr�er
		 *\param[in]	szFontInfos	La cha�ne de cr�ation
		 *\return		La police cr��e
		 */
		static FontPtr AddFont( UINT uiIndex, LPCTSTR szFontInfos );
		/**
		 *\brief		Cr�e et ajoute une police, sans donner d'index
		 *\param[in]	szFace		Le nom de la police
		 *\param[in]	iHeight		La hauteur de la police
		 *\param[in]	iWeight		Le poids de la police
		 *\param[in]	bItalic		Dit si la police est italique
		 *\param[in]	bUnderlined	Dit si la police est soulign�e
		 *\param[in]	dRatio		Le ratio d'affichage
		 *\return		L'index de la police cr��e
		 */
		static UINT AddFont( LPCTSTR szFace = _T( "Arial" ), int iHeight = 20, int iWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderlined = FALSE );
		/**
		 *\brief		R�cup�re la police � l'index donn�
		 *\param[in]	uiIndex	L'index de la police que l'on veut r�cup�rer
		 *\param[in]	bManual	Dit si on recherche parmi les polices manuelles ou pas
		 *\return
		 */
		static FontPtr	GetFont( UINT uiIndex, BOOL bManual = FALSE );

	private:
		void DoCleanup();
		FontPtr DoAddFont( UINT uiIndex, LPCTSTR szFont );
		UINT DoAddFont( LPCTSTR szFace = _T( "Arial" ), int iHeight = 20, int iWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderlined = FALSE );
		FontPtr DoGetFont( UINT uiIndex, BOOL bManual );

	protected:
		//! La map des polices dont on a donn� un index
		FontPtrUIntMap m_mapFonts;
		//! La map des polices dont on n'a pas donn� d'index
		FontPtrUIntMap m_mapManualFonts;
		//! L'index suivant pour les polices dont on n'a pas donn� d'index
		UINT m_uiManualID;
	};
}