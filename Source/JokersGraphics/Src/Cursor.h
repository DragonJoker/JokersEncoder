#pragma once

#pragma warning( push )
#pragma warning( disable:4312 )

#include "CursorBase.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\date 		23/05/2012
	\brief		Classe modèle de curseur
	\remark		Étend l'argument template en plus de CCursorBase
	*/
	template< class T >
	class CCursor
		:	public T
		,	public CCursorBase
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CCursor()
		{
		}
		/**
		 *\brief		Destructeur
		 */
		virtual ~CCursor()
		{
		}
		/**
		 *\brief		Définit le curseur du contrôle
		 *\param[in]	hCursor	Le curseur
		 *\param[in]	bOwn	Dit si CCursor gère ce curseur
		 */
		virtual HCURSOR SetCursor( HCURSOR hCursor, BOOL bOwn=TRUE )
		{
			return CCursorBase::SetCursor( hCursor, bOwn );
		}
		/**
		 *\brief		Fonction appelée par le framework pour faire les sous-classements nécessaire avant de sous-classer le contrôle
		 *\remark		Sert à récupérer le curseur de base de la classe template et à initialiser le curseur courant comme celui de base
		 */
		virtual void PreSubclassWindow()
		{
			T::PreSubclassWindow();

			m_hBasicCursor = HCURSOR( GetClassLongPtr( m_hWnd, GCLP_HCURSOR ) );
			m_hCurrentCursor = m_hBasicCursor;
		}

	private:
		DECLARE_MESSAGE_MAP()
		afx_msg BOOL OnSetCursor( CWnd * pWnd, UINT nHitTest, UINT message )
		{
			BOOL bReturn = TRUE;

			if ( pWnd == this )
			{
				::SetCursor( m_hCurrentCursor );
			}
			else
			{
				bReturn = T::OnSetCursor( pWnd, nHitTest, message );
			}

			return bReturn;
		}
	};

	BEGIN_TEMPLATE_MESSAGE_MAP( CCursor, T, T )
		ON_WM_SETCURSOR ()
	END_MESSAGE_MAP()
}

#include "Cursor.inl"

#pragma warning( pop )