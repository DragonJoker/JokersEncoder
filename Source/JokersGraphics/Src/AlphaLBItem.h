#pragma once

#include "JokersGraphicsPrerequisites.h"
#include "TransparentBrush.h"
#include <vector>

namespace Joker
{
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Enumeration des statuts d'items pour lesquels on peut modifier l'apparence
	*/
	typedef enum
	{	eLB_ITEM_STATUS_NORMAL		//!< Item normal
	,	eLB_ITEM_STATUS_SELECTED	//!< Item sélectionné
	,	eLB_ITEM_STATUS_COUNT		//!< Un compte
	}	eLB_ITEM_STATUS;
	/*!
	\author Sylvain DOREMUS
	\date 13/11/2011
	\brief		Représentation d'un item gérant la transparence pour une CTransparentListBox
	\remark		La transparence de l'item est personnalisable en couleur comme en alpha, gràce à la classe CTransparentBrush.
				<br />Il est aussi possible de personnaliser la couleur du texte et le contour( couleur et style )
	*/
	class JGRA_API CAlphaLBItem
	{
	private:
		CTransparentBrush	m_brushMask;	//!< Le masque de l'item
		CColour				m_clText;		//!< Le texte de l'item
		bool				m_bHasLine;		//!< Dit si l'item a un contour
		CColour				m_clLine;		//!< La couleur du contour de l'item
		int					m_iLineStyle;	//!< Le style du contour de l'item

	public:
		/**
		 *\brief		Constructeur
		 *\param[in]	clMaskColour	La couleur du masque
		 *\param[in]	clText			La couleur du texte
		 *\param[in]	bHasLine		Dit si l'item a un contour
		 *\param[in]	clLineColour	La couleur du contour
		 *\param[in]	iLineStyle		Le style du contour
		 *\return		
		 */
		CAlphaLBItem( CColour const & clMaskColour=CColour( CColour::FullAlphaBlack ), CColour const & clText=CColour( CColour::FullAlphaWhite ), bool bHasLine=false, CColour const & clLineColour=CColour( CColour::Transparent ), int iLineStyle=0 );
		/**
		 *\brief		Constructeur par recopie
		 */
		CAlphaLBItem( CAlphaLBItem const & item );
		/**
		 *\brief		Destructeur
		 */
		~CAlphaLBItem();
		/**
		 *\return		La couleur du contour
		 */
		inline CColour GetLineColour()const { return m_clLine; }
		/**
		 *\return		La couleur du texte
		 */
		inline CColour GetTextColour()const { return m_clText; }
		/**
		 *\return		true si un contour doit être dessiné, false sinon
		 */
		inline bool HasLine()const { return m_bHasLine; }
		/**
		 *\return		Le style de dessin du contour
		 */
		inline int GetLineStyle	()const { return m_iLineStyle; }
		/**
		 *\return		Le masque (non constant)
		 */
		inline CTransparentBrush & GetBrush() { return m_brushMask; }
		/**
		 *\return		Le masque (constant)
		 */
		inline CTransparentBrush const & GetBrush()const { return m_brushMask; }
		/**
		 *\brief		Définit la couleur du texte
		 *\param[in]	crColour	La nouvelle couleur
		 */
		inline void SetTextColour( CColour clColour ) { m_clText = clColour; }
		/**
		 *\brief		Définit la couleur du contour
		 *\param[in]	crColour	La nouvelle couleur
		 */
		inline void SetLineColour( CColour clColour ) { m_clLine = clColour;m_bHasLine = true; }
		/**
		 *\brief		Définit le style de dessin du contour( cf. styles des LOGPEN )
		 *\param[in]	iStyle	Le nouveau style
		 */
		inline void SetLineStyle( int iStyle ) { m_iLineStyle = iStyle;m_bHasLine = true; }
		/**
		 *\brief		Opérateur d'affectation
		 *\param[in]	item	L'item à copier
		 *\return		Une référence sur ce CAlphaLBItem
		 */
		CAlphaLBItem & operator =( CAlphaLBItem const & item );
		/**
		 *\brief		Alpha blend de cet item sur un HDC
		 *\param[in]	hDestDC	Le HDC de destination
		 *\param[in]	rcDest	Le rectangle de destination
		 */
		void AlphaBlend( CBitmapDC & bmpDC, CRect const & rcDest );
	};
}