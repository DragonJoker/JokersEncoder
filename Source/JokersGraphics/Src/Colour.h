#pragma once

#include "JokersGraphicsPrerequisites.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Enum�ration de couleurs pr�d�finies
	*/
	typedef enum
	{	eCOLOUR_BLACK				= RGB(   0,   0,   0 )	//!< Noir
	,	eCOLOUR_DARK_RED			= RGB( 127,   0,   0 )	//!< Rouge fonc�
	,	eCOLOUR_RED					= RGB( 255,   0,   0 )	//!< Rouge pur
	,	eCOLOUR_DARK_ORANGE			= RGB( 127,  63,   0 )	//!< Orange fonc�
	,	eCOLOUR_ORANGE				= RGB( 255, 127,   0 )	//!< Orange
	,	eCOLOUR_DARK_GREEN			= RGB(   0, 127,   0 )	//!< Vert fonc�
	,	eCOLOUR_GREEN				= RGB(   0, 255,   0 )	//!< Vert pur
	,	eCOLOUR_YELLOW				= RGB( 255, 255,   0 )	//!< Jaune
	,	eCOLOUR_TRANSPARENT			= RGB(   1,   1,   1 )	//!< Transparent (pour les TransparentBlt)
	,	eCOLOUR_GREEN_SEL			= RGB(  32, 128,  32 )	//!< Vert s�lection
	,	eCOLOUR_DARK_BLUE			= RGB(   0,   0, 127 )	//!< Bleu fonc�
	,	eCOLOUR_GREY				= RGB( 127, 127, 127 )	//!< Gris
	,	eCOLOUR_LIGHT_GREY2			= RGB( 160, 160, 160 )	//!< Gris clair
	,	eCOLOUR_STATICS				= RGB( 251, 212, 180 )	//!< Rose moche
	,	eCOLOUR_PURPLE				= RGB( 192,   0, 192 )	//!< Violet
	,	eCOLOUR_LIGHT_GREY			= RGB( 192, 192, 192 )	//!< Gris tr�s clair
	,	eCOLOUR_GBLUE				= RGB(  98, 154, 201 )	//!< Bleu s�lection
	,	eCOLOUR_BLUE				= RGB(   0,   0, 255 )	//!< Bleu pur
	,	eCOLOUR_LIGHT_PURPLE		= RGB( 255, 192, 255 )	//!< Violet clair
	,	eCOLOUR_BLUE_SEL			= RGB(   0, 255, 255 )	//!< Cyan pur
	,	eCOLOUR_WHITE				= RGB( 255, 255, 255 )	//!< Blanc
	,	eCOLOUR_TRUE_TRANSPARENT	= 0xFF000000			//!< Transparent
	}	eCOLOUR;

#if DEF_USING_OGL
#	define eDEFAULT_RENDERER eRENDERER_OGL
#elif DEF_USING_D2D
#	define eDEFAULT_RENDERER eRENDERER_D2D
#else
#	define eDEFAULT_RENDERER eRENDERER_GDI
#endif
	/*!
	\author 	Sylvain DOREMUS
	\brief		Classe de gestion de couleurs
	\remark		Prend en compte la transparence
	*/
	class JGRA_API CColour
	{
	public:
		/*!
		\author 	Sylvain DOREMUS
		\brief		Enum�ration des couleurs pr�d�finies
		*/
		typedef enum
		{	Transparent				= 0x00000000
		,	LowAlphaBlack			= 0x00000040,	MediumAlphaBlack		= 0x0000007F,	HighAlphaBlack			= 0x000000BF,	FullAlphaBlack			= 0x000000FF
		,	LowAlphaDarkBlue		= 0x00007F40,	MediumAlphaDarkBlue		= 0x00007F7F,	HighAlphaDarkBlue		= 0x00007FBF,	FullAlphaDarkBlue		= 0x00007FFF
		,	LowAlphaBlue			= 0x0000FF40,	MediumAlphaBlue			= 0x0000FF7F,	HighAlphaBlue			= 0x0000FFBF,	FullAlphaBlue			= 0x0000FFFF
		,	LowAlphaDarkGreen		= 0x007F0040,	MediumAlphaDarkGreen	= 0x007F007F,	HighAlphaDarkGreen		= 0x007F00BF,	FullAlphaDarkGreen		= 0x007F00FF
		,	LowAlphaGreen			= 0x00FF0040,	MediumAlphaGreen		= 0x00FF007F,	HighAlphaGreen			= 0x00FF00BF,	FullAlphaGreen			= 0x00FF00FF
		,	LowAlphaDarkGrey		= 0x40404040,	MediumAlphaDarkGrey		= 0x4040407F,	HighAlphaDarkGrey		= 0x404040BF,	FullAlphaDarkGrey		= 0x404040FF
		,	LowAlphaDarkRed			= 0x7F000040,	MediumAlphaDarkRed		= 0x7F00007F,	HighAlphaDarkRed		= 0x7F0000BF,	FullAlphaDarkRed		= 0x7F0000FF
		,	LowAlphaGrey			= 0x7F7F7F40,	MediumAlphaGrey			= 0x7F7F7F7F,	HighAlphaGrey			= 0x7F7F7FBF,	FullAlphaGrey			= 0x7F7F7FFF
		,	LowAlphaLightBlue		= 0x7F7FFF40,	MediumAlphaLightBlue	= 0x7F7FFF7F,	HighAlphaLightBlue		= 0x7F7FFFBF,	FullAlphaLightBlue		= 0x7F7FFFFF
		,	LowAlphaLightGreen		= 0x7FFF7F40,	MediumAlphaLightGreen	= 0x7FFF7F7F,	HighAlphaLightGreen		= 0x7FFF7FBF,	FullAlphaLightGreen		= 0x7FFF7FFF
		,	LowAlphaLightGrey		= 0xBFBFBF40,	MediumAlphaLightGrey	= 0xBFBFBF7F,	HighAlphaLightGrey		= 0xBFBFBFBF,	FullAlphaLightGrey		= 0xBFBFBFFF
		,	LowAlphaRed				= 0xFF000040,	MediumAlphaRed			= 0xFF00007F,	HighAlphaRed			= 0xFF0000BF,	FullAlphaRed			= 0xFF0000FF
		,	LowAlphaLightRed		= 0xFF7F7F40,	MediumAlphaLightRed		= 0xFF7F7F7F,	HighAlphaLightRed		= 0xFF7F7FBF,	FullAlphaLightRed		= 0xFF7F7FFF
		,	LowAlphaWhite			= 0xFFFFFF40,	MediumAlphaWhite		= 0xFFFFFF7F,	HighAlphaWhite			= 0xFFFFFFBF,	FullAlphaWhite			= 0xFFFFFFFF
		}	ePREDEFINED;

	public:
		/**
		 *\brief		Constructeur par d�faut
		 *\remark		Initialise la couleur � noire
		 */
		CColour();
		/**
		 *\brief		Constructeur � partir d'une pr�d�finie
		 *\param[in]	eColour	La couleur pr�d�finie
		 */
		explicit CColour( ePREDEFINED eColour );
		/**
		 *\brief		Constructeur par recopie
		 *\param[in]	colour	La couleur � copier
		 */
		CColour( CColour const & colour );
		/**
		 *\brief		Op�rateur d'affectation par recopie
		 *\param[in]	colour	La couleur � copier
		 *\return		Une r�f�rence sur cette CColour
		 */
		CColour & operator =( CColour const & colour );
		/**
		 *\brief		Op�rateur d'affectation par addition
		 *\remark		Effectue la synth�se additive des 2 couleurs
		 *\param[in]	colour	La couleur � ajouter
		 *\return		Une r�f�rence sur cette CColour
		 */
		CColour & operator +=( CColour const & colour );
		/**
		 *\brief		Op�rateur d'affectation par soustraction
		 *\remark		Effectue la synth�se soustractive des 2 couleurs
		 *\param[in]	colour	La couleur � ajouter
		 *\return		Une r�f�rence sur cette CColour
		 */
		CColour & operator -=( CColour const & colour );
		/**
		 *\brief		Constructeur nomm� � partir d'un COLORREF
		 *\param[in]	crColour	Le COLORREF
		 *\param[in]	byAlpha		L'alpha voulu
		 *\return		La CColour cr��e
		 */
		static CColour FromCOLORREF( COLORREF crColour, BYTE byAlpha=255 );
		/**
		 *\brief		Constructeur nomm� � partir d'un D2D1::ColorF
		 *\param[in]	clfColour	Le D2D1::ColorF
		 *\return		La CColour cr��e
		 */
		static CColour 	FromD2DColor( D2D1::ColorF clfColour );
		/**
		 *\brief		Constructeur nomm� � partir des 4 composantes
		 *\param[in]	byR, byG, byB, byA	Les composantes
		 *\return		La CColour cr��e
		 */
		static CColour FromComponents( BYTE byR, BYTE byG, BYTE byB, BYTE byA );
		/**
		 *\brief		Constructeur nomm� � partir d'un entier repr�sentant une couleur RGB
		 *\param[in]	dwColour	La couleur RGB
		 *\return		La CColour cr��e
		 */
		static CColour FromRGB( DWORD dwColour );
		/**
		 *\brief		Constructeur nomm� � partir d'un entier repr�sentant une couleur BGR
		 *\param[in]	dwColour	La couleur BGR
		 *\return		La CColour cr��e
		 */
		static CColour FromBGR( DWORD dwColour );
		/**
		 *\brief		Constructeur nomm� � partir d'un entier repr�sentant une couleur ARGB
		 *\param[in]	dwColour	La couleur ARGB
		 *\return		La CColour cr��e
		 */
		static CColour FromARGB( DWORD dwColour );
		/**
		 *\brief		Constructeur nomm� � partir d'un entier repr�sentant une couleur RGBA
		 *\param[in]	dwColour	La couleur RGBA
		 *\return		La CColour cr��e
		 */
		static CColour FromRGBA( DWORD dwColour );
		/**
		 *\brief		Constructeur nomm� � partir d'un entier repr�sentant une couleur ABGR
		 *\param[in]	dwColour	La couleur ABGR
		 *\return		La CColour cr��e
		 */
		static CColour FromABGR( DWORD dwColour );
		/**
		 *\brief		Constructeur nomm� � partir d'un entier repr�sentant une couleur BGRA
		 *\param[in]	dwColour	La couleur BGRA
		 *\return		La CColour cr��e
		 */
		static CColour 	FromBGRA( DWORD dwColour );
		/**
		 *\brief		Fonction de conversion vers un COLORREF
		 *\return		Le COLORREF
		 */
		COLORREF ToCOLORREF()const;
#if DEF_USING_D2D
		/**
		 *\brief		Fonction de conversion vers un D2D1::ColorF
		 *\return		Le D2D1::ColorF
		 */
		D2D1::ColorF ToD2DColor()const;
#endif
#if DEF_USING_OGL
		/**
		 *\brief		Fonction de conversion vers un D2D1::ColorF
		 *\return		Le D2D1::ColorF
		 */
		GL2D::ColorF ToGL2DColor()const;
#endif
		/**
		 *\brief		Fonction de conversion vers un entier repr�sentant une couleur RGB
		 *\return		La couleur RGB
		 */
		DWORD ToRGB()const;
		/**
		 *\brief		Fonction de conversion vers un entier repr�sentant une couleur BGR
		 *\return		La couleur BGR
		 */
		DWORD ToBGR()const;
		/**
		 *\brief		Fonction de conversion vers un entier repr�sentant une couleur ARGB
		 *\return		La couleur ARGB
		 */
		DWORD ToARGB()const;
		/**
		 *\brief		Fonction de conversion vers un entier repr�sentant une couleur RGBA
		 *\return		La couleur RGBA
		 */
		DWORD ToRGBA()const;
		/**
		 *\brief		Fonction de conversion vers un entier repr�sentant une couleur ABGR
		 *\return		La couleur ABGR
		 */
		DWORD ToABGR()const;
		/**
		 *\brief		Fonction de conversion vers un entier repr�sentant une couleur BGRA
		 *\return		La couleur BGRA
		 */
		DWORD ToBGRA()const;
		//@}

	public:
		BYTE r;	//!< Composante Rouge de la couleur
		BYTE g;	//!< Composante Verte de la couleur
		BYTE b;	//!< Composante Bleue de la couleur
		BYTE a;	//!< Composante Alpha de la couleur
	};

	/**
	 *\brief		Op�rateur d'addition entre 2 couleurs
	 *\param[in]	colourA, colourB	Les 2 couleurs � additionner
	 *\return		La synth�se additive (lumi�re) des 2 couleurs
	 */
	CColour operator +( CColour const & colourA, CColour const & colourB );
	/**
	 *\brief		Op�rateur d'addition entre 2 couleurs
	 *\param[in]	colourA, colourB	Les 2 couleurs � additionner
	 *\return		La synth�se soustractive (peinture) des 2 couleurs
	 */
	CColour operator -( CColour const & colourA, CColour const & colourB );
}
