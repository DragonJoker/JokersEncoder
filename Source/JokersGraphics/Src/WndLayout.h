#pragma once

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe de base de gestion de layout
	\remark		Permet de réorganiser les éléments lors d'un redimensionnement de fenêtre
	*/
	class JGRA_API CWndLayout
	{
	protected:
		HWND m_hParent;
		RECT m_rcOriginal;
		RECT m_rcCurrent;
		RECT m_rcFixedBorders;

	public:
		CWndLayout();
		virtual ~CWndLayout();

		void Create( HWND hParent, LPRECT rcFixedBorders=NULL );
		void Resize();

	protected:
		void DoUpdateSize();

		virtual void DoResize()=0;
	};
}