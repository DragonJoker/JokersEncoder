#pragma once

#include <map>
#include <memory>

#include "AutoSingleton.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe g�rant les couleurs cr��es, par index
	\remark		Permet de ne pas cr�er 50 fois la m�me couleur
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
		 *\brief		Supprime les couleurs g�r�es
		 */
		static void DeleteColours();
		/**
		 *\brief		Ajoute une couleur
		 *\param[in]	uiIndex		L'index de la couleur
		 *\param[in]	crColour	La couleur
		 */
		static void AddColour( UINT uiIndex, COLORREF crColour );
		/**
		 *\brief		R�cup�re la couleur � l'index donn�
		 *\param[in]	uiIndex	L'index de la couleur � r�cup�rer
		 *\return		La couleur r�cup�r�e, 0 si aucune
		 */
		static COLORREF GetColour( UINT uiIndex );

	private:
		void DoCleanup();
		void DoAddColour( UINT uiIndex, COLORREF crColour );
		COLORREF DoGetColour( UINT uiIndex );

	protected:
		//! La map des couleurs, rang�es par index
		std::map <UINT, COLORREF> m_mapColours;
	};
}