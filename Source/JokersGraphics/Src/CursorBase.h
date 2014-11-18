#pragma once

#pragma warning( push )
#pragma warning( disable:4312 )

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\date 		23/05/2012
	\brief		Classe de base pour un contr�le avec curseur personnalis�
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
		 *\brief		D�finit le curseur du contr�le
		 *\param[in]	hCursor	Le curseur
		 *\param[in]	bOwn	Dit si CCursor g�re ce curseur
		 */
		virtual HCURSOR SetCursor( HCURSOR hCursor, BOOL bOwn = TRUE );
		/**
		 *\brief		D�finit le curseur courant comme le curseur de base
		 */
		void RestoreCursor();
		/**
		 *\brief		R�cup�re le curseur courant
		 *\return		Le curseur
		 */
		inline HCURSOR GetCursor()
		{
			return m_hCurrentCursor;
		}

	protected:
		//! Le curseur de base (la fl�che)
		HCURSOR m_hBasicCursor;
		//! Le curseur d�fini
		HCURSOR m_hCurrentCursor;
		//! Dit si le curseur est g�r� par CCursor ou par l'appelant
		BOOL m_bOwn;
	};
}

#include "Cursor.inl"

#pragma warning( pop )