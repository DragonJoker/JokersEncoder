#pragma once

#include <map>
#include <memory>

#include "AutoSingleton.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe gérant les couleurs créées, par index
	\remark		Permet de ne pas créer 50 fois la même couleur
	*/
	class JGRA_API CColourManager
		: public CAutoSingleton< CColourManager >
	{
	protected:
		friend class CAutoSingleton< CColourManager >;

	protected:
		/**
		 *\brief		Constructeur
		 */
		CColourManager();
		/**
		 *\brief		Destructeur
		 */
		~CColourManager();

	public:
		/**
		 *\brief		Supprime les couleurs gérées
		 */
		static void DeleteColours();
		/**
		 *\brief		Ajoute une couleur
		 *\param[in]	uiIndex		L'index de la couleur
		 *\param[in]	crColour	La couleur
		 */
		static void AddColour( UINT uiIndex, COLORREF crColour );
		/**
		 *\brief		Récupère la couleur à l'index donné
		 *\param[in]	uiIndex	L'index de la couleur à récupérer
		 *\return		La couleur récupérée, 0 si aucune
		 */
		static COLORREF GetColour( UINT uiIndex );

	private:
		void DoCleanup();
		void DoAddColour( UINT uiIndex, COLORREF crColour );
		COLORREF DoGetColour( UINT uiIndex );

	protected:
		//! La map des couleurs, rangées par index
		std::map <UINT, COLORREF> m_mapColours;
	};
}