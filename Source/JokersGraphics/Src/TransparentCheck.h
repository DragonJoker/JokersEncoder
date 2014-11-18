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
		 *\brief		Récupère le masque de surbrillance
		 *\param[in]	L'état dont on veut récupérer le masque
		 *\return		Une référence constante sur le masque de l'état concerné
		 */
		inline const CTransparentBrush & GetBtnBrush( eBTN_STATE eState )const
		{
			return m_brushesCheck[eState];
		}
		/**
		 *\brief		Récupère le masque de surbrillance
		 *\param[in]	L'état dont on veut récupérer le masque
		 *\return		Une référence non constante sur le masque de l'état concerné
		 */
		inline CTransparentBrush & GetBtnBrush( eBTN_STATE eState )
		{
			return m_brushesCheck[eState];
		}
		/**
		 *\brief		Définit l'image du bouton coché
		 *\param[in]	pImage	La nouvelle image
		 */
		inline void SetCheckImage( ImagePtr pImage )
		{
			m_pImgCheck = pImage;
		}
		/**
		 *\brief		Définit l'image du bouton non coché
		 *\param[in]	pImage	La nouvelle image
		 */
		inline void SetUncheckImage( ImagePtr pImage )
		{
			m_pImgUncheck = pImage;
		}
		/**
		 *\brief		Définit l'image du bouton désactivé
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
		//! L'image du bouton coché
		ImagePtr m_pImgCheck;
		//! L'image du bouton non coché
		ImagePtr m_pImgUncheck;
		//! L'image du bouton désactivé
		ImagePtr m_pImgDisable;
		//! Les masques de surbrillance en fonction e l'état
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
	\brief		Typedef sur CTransparentRadioCheck pour les cases à cocher
	*/
	typedef CTransparentRadioCheck CTransparentCheck;
}