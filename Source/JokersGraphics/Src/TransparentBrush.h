#pragma once

#include "BitmapDC.h"

namespace Joker
{
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Classe de base servant � g�rer la transparence pour les brushes.
	\remark		Cette transparence ainsi que la couleur du brush sont personnalisables.
				<br />Il est possible de passer un objet de cette classe � des fonctions prenant des HBRUSH( FillRect, ... ), des COLORREF( CreateSolidBrush, ... ) ou des BYTE( BLENDFUNCTION, ... ) gr�ce aux op�rateurs de conversion.
	*/
	class JGRA_API CTransparentBrush
	{
	protected:
		HBITMAP m_hPattern;
		CBitmapDC m_bmpPatternDC;
		CRect m_rcSrcPattern;

	public:
		/**
		 *\brief		Constructeur
		 */
		virtual ~CTransparentBrush();
		/**
		 *\brief		Constructeur � partir d'une couleur
		 *\remark		D�finit la couleur du brush
		 *\param[in]	crColour	La nouvelle couleur( ne change pas l'alpha )
		 */
		CTransparentBrush( CColour const & clColour = CColour( CColour::MediumAlphaBlack ) );
		/**
		 *\brief		Constructeur � partir d'un pattern
		 *\remark		D�finit le pattern du brush � partir d'une image
		 *\param[in]	imgPattern	L'image contenant le pattern
		 */
		CTransparentBrush( HBITMAP hPattern, CRect const & rcPattern );
		/**
		 *\brief		Cr�e un d�grad� d'une couleur � une autre, en passant par celle du milieu, en un nombre d'�tapes donn�
		 *\remark		Ce d�grad� est d�fini en tant que pattern de ce brush
		 *\param[in]	iType		Le type de d�grad�( 0 pour vertical, 1 pour horizontal )
		 *\param[in]	crDebut		La couleur de d�but( en haut ou � gauche )
		 *\param[in]	crMilieu	La couleur du milieu( au milieu )
		 *\param[in]	crFin		La couleur de fin( en bas ou � droite )
		 *\param[in]	iSteps		Le nombre d'�tapes( d�termine le nombre de pixels de hauteur du d�grad� )
		 */
		CTransparentBrush( int iType, CColour const & clDebut, CColour const & clMilieu, CColour const & clFin, int iSteps );
		/**
		 *\brief		Constructeur par copie
		 */
		CTransparentBrush( CTransparentBrush const & brush );
		/**
		 *\brief		D�finit la couleur du brush
		 *\param[in]	crColour	La nouvelle couleur( ne change pas l'alpha )
		 */
		void SetSolidBrush( CColour const & clColour );
		/**
		 *\brief		D�finit le pattern du brush � partir d'une image
		 *\param[in]	imgPattern	L'image contenant le pattern
		 */
		void SetPatternBrush( HBITMAP hPattern, CRect const & rcPattern );
		/**
		 *\brief		Cr�e un d�grad� d'une couleur � une autre, en passant par celle du milieu, en un nombre d'�tapes donn�
		 *\remark		Ce d�grad� est d�fini en tant que pattern de ce brush
		 *\param[in]	iType		Le type de d�grad�( 0 pour vertical, 1 pour horizontal )
		 *\param[in]	crDebut		La couleur de d�but( en haut ou � gauche )
		 *\param[in]	crMilieu	La couleur du milieu( au milieu )
		 *\param[in]	crFin		La couleur de fin( en bas ou � droite )
		 *\param[in]	iSteps		Le nombre d'�tapes( d�termine le nombre de pixels de hauteur du d�grad� )
		 */
		void SetGradientBrush( int iType, CColour const & clDebut, CColour const & clMilieu, CColour const & clFin, int iSteps );
		/**
		 *\brief		Copie la portion donn�e du bitmap donn�
		 *\param[in]	hPattern	Le bitmap � copier
		 *\param[in]	rcPattern	La portion � copier
		 */
		void CopyPattern( HBITMAP hPattern, CRect const & rcPattern );
		/**
		 *\return		Le HBITMAP contenant le pattern
		 */
		inline HBITMAP GetPattern()const
		{
			return m_hPattern;
		}
		/**
		 *\return		Le CBitmapDC du pattern
		 */
		inline CBitmapDC const & GetDC()const
		{
			return m_bmpPatternDC;
		}
		/**
		 *\return		Le CBitmapDC du pattern
		 */
		inline CBitmapDC & GetDC()
		{
			return m_bmpPatternDC;
		}
		/**
		 *\return		Le CRect du pattern
		 */
		inline CRect const & GetRect()const
		{
			return m_rcSrcPattern;
		}
		/**
		 *\return		Le CRect du pattern
		 */
		inline BYTE GetAlpha()const
		{
			return 255;
		}
		/**
		 *\brief		Op�rateur d'affectation
		 *\return		Une r�f�rence sur ce CTransparentBrush
		 */
		CTransparentBrush & operator =( CTransparentBrush const & brush );
		/**
		 *\brief		Op�rateur de conversion implicite vers HBITMAP
		 *\return		Le pattern de ce CTransparentBrush
		 */
		inline operator HBITMAP()const
		{
			return m_hPattern;
		}
		//@}

	protected:
		void CreateBitmap( int iWidth, int iHeight, BYTE ** pBits );
		virtual void Release();
	};
}