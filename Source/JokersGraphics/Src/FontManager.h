#pragma once

#include <map>
#include <memory>

#include "Font.h"
#include "AutoSingleton.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe gérant les polices créées, par index
	\remark		Permet de ne pas créer 50 fois la même police
	*/
	class JGRA_API CFontManager
		: public CAutoSingleton< CFontManager >
	{
	protected:
		friend class CAutoSingleton< CFontManager> ;
		typedef std::map< UINT,	FontPtr >	FontPtrUIntMap;

	protected:
		/**
		 *\brief		Constructeur par défaut
		 */
		CFontManager();
		/**
		 *\brief		Destructeur
		 */
		~CFontManager();

	public:
		/**
		 *\brief		Supprime les polices créées
		 */
		static void DeleteFonts();
		/**
		 *\brief		Crée et ajoute une police à partir d'une chaîne d'informations
		 *\remark		La chaîne doit être constituée de la manière suivante :
						<br /><Nom de la police>,<hauteur>,<normal/bold>,<italique:false/true>,<souligné:false/true>
						<br />Ex : Arial,14,normal,false,false
						<br />Il n'y a auucun espace
		 *\param[in]	uiIndex		L'index de la police à créer
		 *\param[in]	szFontInfos	La chaîne de création
		 *\return		La police créée
		 */
		static FontPtr AddFont( UINT uiIndex, LPCTSTR szFontInfos );
		/**
		 *\brief		Crée et ajoute une police, sans donner d'index
		 *\param[in]	szFace		Le nom de la police
		 *\param[in]	iHeight		La hauteur de la police
		 *\param[in]	iWeight		Le poids de la police
		 *\param[in]	bItalic		Dit si la police est italique
		 *\param[in]	bUnderlined	Dit si la police est soulignée
		 *\param[in]	dRatio		Le ratio d'affichage
		 *\return		L'index de la police créée
		 */
		static UINT AddFont( LPCTSTR szFace = _T( "Arial" ), int iHeight = 20, int iWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderlined = FALSE );
		/**
		 *\brief		Récupère la police à l'index donné
		 *\param[in]	uiIndex	L'index de la police que l'on veut récupérer
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
		//! La map des polices dont on a donné un index
		FontPtrUIntMap m_mapFonts;
		//! La map des polices dont on n'a pas donné d'index
		FontPtrUIntMap m_mapManualFonts;
		//! L'index suivant pour les polices dont on n'a pas donné d'index
		UINT m_uiManualID;
	};
}