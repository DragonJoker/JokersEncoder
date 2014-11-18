#pragma once

#include "TransparentButton.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\date 		23/05/2012
	\brief		Classe commune pour les boutons radio et checkbox
	\remark		Etend CTransparentButton
	*/
	class JGRA_API CTransparentRadioCheck
		: public CTransparentButton
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentRadioCheck();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentRadioCheck();
		/**
		 *\brief		R�cup�re le masque de surbrillance
		 *\param[in]	L'�tat dont on veut r�cup�rer le masque
		 *\return		Une r�f�rence constante sur le masque de l'�tat concern�
		 */
		inline const CTransparentBrush & GetBtnBrush( eBTN_STATE eState )const
		{
			return m_brushesCheck[eState];
		}
		/**
		 *\brief		R�cup�re le masque de surbrillance
		 *\param[in]	L'�tat dont on veut r�cup�rer le masque
		 *\return		Une r�f�rence non constante sur le masque de l'�tat concern�
		 */
		inline CTransparentBrush & GetBtnBrush( eBTN_STATE eState )
		{
			return m_brushesCheck[eState];
		}
		/**
		 *\brief		D�finit l'image du bouton coch�
		 *\param[in]	pImage	La nouvelle image
		 */
		inline void SetCheckImage( ImagePtr pImage )
		{
			m_pImgCheck = pImage;
		}
		/**
		 *\brief		D�finit l'image du bouton non coch�
		 *\param[in]	pImage	La nouvelle image
		 */
		inline void SetUncheckImage( ImagePtr pImage )
		{
			m_pImgUncheck = pImage;
		}
		/**
		 *\brief		D�finit l'image du bouton d�sactiv�
		 *\param[in]	pImage	La nouvelle image
		 */
		inline void SetDisableImage( ImagePtr pImage )
		{
			m_pImgDisable = pImage;
		}

	private:
		virtual void DoRelease();
		virtual void DoDrawBackground( CRect const & rcRect );
		virtual void DoDrawForeground( CRect const & rcRect );

	private:
		//! L'image du bouton coch�
		ImagePtr m_pImgCheck;
		//! L'image du bouton non coch�
		ImagePtr m_pImgUncheck;
		//! L'image du bouton d�sactiv�
		ImagePtr m_pImgDisable;
		//! Les masques de surbrillance en fonction e l'�tat
		CTransparentBrush m_brushesCheck[eBTN_STATE_COUNT];
	};
	/*!
	\author 	Sylvain DOREMUS
	\date 		23/05/2012
	\brief		Typedef sur CTransparentRadioCheck pour les boutons radio
	*/
	typedef CTransparentRadioCheck CTransparentRadio;
	/*!
	\author 	Sylvain DOREMUS
	\date 		23/05/2012
	\brief		Typedef sur CTransparentRadioCheck pour les cases � cocher
	*/
	typedef CTransparentRadioCheck CTransparentCheck;
}