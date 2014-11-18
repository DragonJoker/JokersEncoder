#pragma once

#pragma warning( push )
#pragma warning( disable:4312 )

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\date 		23/05/2012
	\brief		Classe de base pour un contrôle avec curseur personnalisé
	*/
	class JGRA_API CCursorBase
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CCursorBase();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CCursorBase();
		/**
		 *\brief		Définit le curseur du contrôle
		 *\param[in]	hCursor	Le curseur
		 *\param[in]	bOwn	Dit si CCursor gère ce curseur
		 */
		virtual HCURSOR SetCursor( HCURSOR hCursor, BOOL bOwn = TRUE );
		/**
		 *\brief		Définit le curseur courant comme le curseur de base
		 */
		void RestoreCursor();
		/**
		 *\brief		Récupère le curseur courant
		 *\return		Le curseur
		 */
		inline HCURSOR GetCursor()
		{
			return m_hCurrentCursor;
		}

	protected:
		//! Le curseur de base (la flèche)
		HCURSOR m_hBasicCursor;
		//! Le curseur défini
		HCURSOR m_hCurrentCursor;
		//! Dit si le curseur est géré par CCursor ou par l'appelant
		BOOL m_bOwn;
	};
}

#include "Cursor.inl"

#pragma warning( pop )