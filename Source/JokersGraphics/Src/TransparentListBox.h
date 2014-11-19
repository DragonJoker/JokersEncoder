#pragma once

#include "AlphaLBItem.h"
#include "TransparentCtrl.h"
#include <vector>

namespace Joker
{
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Spécialisation de CTransparentCtrl pour les CListBox.
	\remark		En plus de la transparence de base de CTransparentCtrl, les items sont eux aussi personnalisables, par type( cf. eLB_ITEM_STATUS ).
				<br />Leur personnalisation est possible via la classe CAlphaLBItem.
	*/
	template< eRENDERER Renderer >
	class CTransparentListBox
		: public CTransparentCtrlT< CListBox, Renderer >
	{
	public:
		typedef CTransparentCtrlT< CListBox, Renderer > BaseType;

	private:
		CAlphaLBItem		m_itemColours[eLB_ITEM_STATUS_COUNT];	//!< Les couleurs des items, selon l'état
		short				m_sItemHeight;							//!< La hauteur des items
		int					m_iFocusedItem;							//!< L'index de l'item ayant le focus
		CColour				m_clFocusBorder;						//!< La couleur du contour de focus
		int					m_iFocusBorderStyle;					//!< Le style du contour de focus
		bool				m_bMouseLDown;							//!< Dit si le bouton gauche de la souris est appuyé
		CRect				m_rcMouse;								//!< Le rectangle défini par la souris en mode sélection
		CTransparentBrush	m_brushMouse;							//!< Le brush du rectangle de sélection
		CColour				m_clMouseLine;							//!< La couleur de la ligne de contour du rectangle de sélection
		int					m_iMouseLineStyle;						//!< Le style de la ligne de contour du rectangle de sélection
		int					m_iScrollPos;							//!< La position courante, en fonction du scroll

	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentListBox();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentListBox();
		/**
		 *\brief		Définit la nouvelle taille des items
		 *\remark		La liste est invalidée
		 *\param[in]	sHeight	La nouvelle taille
		 */
		virtual void SetItemHeight( short sHeight );
		/**
		 *\brief		Définit la couleur du texte du type d'item choisi
		 *\remark		La liste est invalidée
		 *\param[in]	eStatus		Le type d'item affecté
		 *\param[in]	crColour	La nouvelle couleur du texte
		 */
		virtual void SetItemTextColour( eLB_ITEM_STATUS eStatus, CColour const & clColour );
		/**
		 *\brief		Définit la couleur du contour du type d'item choisi
		 *\remark		La liste est invalidée
		 *\param[in]	eStatus		Le type d'item affecté
		 *\param[in]	crColour	La couleur de la ligne
		 */
		virtual void SetItemLineColour( eLB_ITEM_STATUS eStatus, CColour const & clColour );
		/**
		 *\brief		Définit le style de dessin du contour du type d'item choisi
		 *\remark		La liste est invalidée
		 *\param[in]	eStatus		Le type d'item affecté
		 *\param[in]	iLineStyle	Le style de la ligne( cf. styles des LOGPEN )
		 */
		virtual void SetItemLineStyle( eLB_ITEM_STATUS eStatus, int iLineStyle );
		/**
		 *\return		La hauteur des items
		 */
		virtual short GetItemHeight()const
		{
			return m_sItemHeight;
		}
		/**
		 *\param[in]	eStatus	Le type d'item affecté
		 *\return		La couleur du texte des items du type demandé
		 */
		virtual CColour GetItemTextColour( eLB_ITEM_STATUS eStatus )const
		{
			return m_itemColours[eStatus].GetTextColour();
		}
		/**
		 *\param[in]	eStatus	Le type d'item affecté
		 *\return		La couleur du contour des items du type demandé
		 */
		virtual CColour GetItemLineColour( eLB_ITEM_STATUS eStatus )const
		{
			return m_itemColours[eStatus].GetLineColour();
		}
		/**
		 *\param[in]	eStatus	Le type d'item affecté
		 *\return		Le brush des items du type demandé
		 */
		virtual CTransparentBrush & GetItemBrush( eLB_ITEM_STATUS eStatus )
		{
			return m_itemColours[eStatus].GetBrush();
		}
		/**
		 *\param[in]	eStatus	Le type d'item affecté
		 *\return		Le brush des items du type demandé
		 */
		virtual CTransparentBrush const & GetItemBrush( eLB_ITEM_STATUS eStatus )const
		{
			return m_itemColours[eStatus].GetBrush();
		}
		/**
		 *\return		La couleur du contour de l'item ayant le focus
		 */
		inline CColour GetFocusBorderColour()const
		{
			return m_clFocusBorder;
		}
		/**
		 *\return		Le style du contour de l'item ayant le focus
		 */
		inline int GetFocusBorderStyle()const
		{
			return m_iFocusBorderStyle;
		}
		/**
		 *\brief		Définit le style du contour de l'item ayant le focus
		 *\param[in]	val	Le style du contour
		 */
		inline void SetFocusBorderStyle( int val )
		{
			m_iFocusBorderStyle = val;
		}
		/**
		 *\brief		Définit la couleur du contour de l'item ayant le focus
		 *\param[in]	val	La couleur du contour
		 */
		inline void SetFocusBorderColour( CColour const & val )
		{
			m_clFocusBorder = val;
		}
		//@}
	protected:
		/**
		 *\brief		Récupère l'item à l'état donné
		 *\remark		Pour les utilisateurs voulant dériver cette classe
		 *\param[in]	eStatus	L'état de l'item voulu
		 *\return		Une référence non constante sur l'item
		 */
		inline CAlphaLBItem		&	GetItem( eLB_ITEM_STATUS eStatus )
		{
			return m_itemColours[eStatus];
		}
		/**
		 *\brief		Récupère l'item à l'état donné
		 *\remark		Pour les utilisateurs voulant dériver cette classe
		 *\param[in]	eStatus	L'état de l'item voulu
		 *\return		Une référence constante sur l'item
		 */
		inline CAlphaLBItem	const &	GetItem( eLB_ITEM_STATUS eStatus )const
		{
			return m_itemColours[eStatus];
		}

	protected:
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoRelease() {}
		/**
		 *\brief		Fonction de dessin de l'arrière plan
		 *\param[in]	rcRect	Rectangle affecté par le dessin
		 */
		virtual void DoDrawBackground( CRect const & rcRect );
		/**
		 *\brief		Fonction de dessin du premier plan
		 *\param[in]	rcRect	Rectangle affecté par le dessin
		 */
		virtual void DoDrawForeground( CRect const & rcRect );
		/**
		 *\brief		Fonction de dessin d'un item
		 *\param[in]	iItem			L'index de l'item à dessiner
		 *\param[in]	arraySelected	Le tableau des items sélectionnés, au cas où celui-ci le serait
		 */
		void DrawItem( int iItem, CRect rcRect, std::vector< int > const & arraySelected );
		/**
		 *\brief		Fonction de scroll
		 */
		void ScrollList();
		/**
		 *\brief		Fonction de dessin d'un item
		 *\remark		Ne dessine pas mais met à jour le statut de l'item qui a le focus
		 */
		virtual void DrawItem( LPDRAWITEMSTRUCT );
		/**
		 *\brief		Fonction qui définit la hauteur d'une ligne
		 */
		virtual void MeasureItem( LPMEASUREITEMSTRUCT );
		/**
		 *\brief		Fonction de rien du tout, et en plus ne fait rien
		 */
		virtual int CompareItem( LPCOMPAREITEMSTRUCT );

	private:
		DECLARE_MESSAGE_MAP()
		afx_msg void	OnVScroll( UINT nSBCode, UINT nPos, CScrollBar * pScrollBar );
		afx_msg void	OnMouseMove( UINT nFlags, CPoint point );
		afx_msg void	OnLButtonDown( UINT nFlags, CPoint point );
		afx_msg void	OnLButtonUp( UINT nFlags, CPoint point );
	};
}

#include "TransparentListBox.inl"
