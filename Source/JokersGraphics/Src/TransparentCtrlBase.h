#pragma once

#if defined( DrawText )
#	undef DrawText
#endif

#include "Drawer.h"
#include "BitmapDC.h"
#include "TransparentBrush.h"
#include "Font.h"
#include "Logger.h"

#include <algorithm>

#if defined( min )
#	undef min
#endif

#if defined( max )
#	undef max
#endif

namespace Joker
{
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Impl�mentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	*/
	class JGRA_API CTransparentCtrlBase
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlBase();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentCtrlBase();
		/**
		 *\brief		D�finit la couleur du contour
		 *\remark		Le contr�le est invalid�
		 *\param[in]	crColour	La nouvelle couleur
		 */
		void SetBorderColour( CColour const & clColour );
		/**
		 *\brief		D�finit la couleur du texte
		 *\remark		Le contr�le est invalid�
		 *\param[in]	crColour	La nouvelle couleur
		 */
		void SetTextColour( CColour const & clColour );
		/**
		 *\brief		R�cup�re le rectangle relatif de la liste par rapport � son parent
		 *\param[out]	rcRect	Le rectangle qui re�oit les dimension et position de la liste
		 */
		void GetRelativeRect( CRect & rcRect );
		/**
		 *\brief		D�finit la position du contr�le
		 *\param[in]	pWndInsertAfter	La fen�tre suivante dans l'ordre de tabulation
		 *\param[in]	x, y				La position
		 *\param[in]	cx, cy				Les dimensions
		 *\param[in]	nFlags				Combinaison de flags
		 *\return		\p FALSE si probl�me
		 */
		BOOL SetWindowPosition( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags );
		/**
		 *\brief		Fonction d'initialisation
		 */
		void Initialise();
		/**
		 *\brief		Fonction de nettoyage
		 */
		void Cleanup();
		/**
		 *\return		La couleur du masque de transparence
		 */
		inline CColour GetBorderColour()const
		{
			return m_clBorder;
		}
		/**
		 *\return		La couleur du masque de transparence
		 */
		inline CColour GetTextColour()const
		{
			return m_clText;
		}
		/**
		 *\return		Le type d'interface de rendu
		 */
		virtual eRENDERER GetRenderer()const = 0;
		/**
		 *\return		L'alpha du masque de transparence
		 */
		inline BYTE GetMaskAlpha()const
		{
			return m_brushMask.GetAlpha();
		}
		/**
		 *\return		L'alpha du masque de transparence
		 */
		inline bool IsPainting()const
		{
			return m_bPainting;
		}
		/**
		 *\brief		R�cup�re le masque
		 *\return		Une r�f�rence non constante sur le masque
		 */
		inline CTransparentBrush & GetMaskBrush()
		{
			return m_brushMask;
		}
		/**
		 *\brief		R�cup�re le masque
		 *\return		Une r�f�rence constante sur le masque
		 */
		inline CTransparentBrush const & GetMaskBrush()const
		{
			return m_brushMask;
		}
		/**
		 *\brief		D�finit si le contr�le a un contour ou pas
		 *\param[in]	bBorder	La valeur
		 */
		inline void SetBorder( bool bBorder )
		{
			m_bHasBorder = bBorder;
		}
		/**
		 *\brief		R�cup�re les informations d'un bitmap donn�
		 *\param[in]	hDC			Le HDC utilis� pour d�terminer les informations du HBITMAP
		 *\param[in]	hBitmap		Le bitmap dont on veut les informations
		 *\param[in]	size		Les dimensions du bitmap
		 *\param[in]	arrayBits	Les pixels du bitmap
		 */
		virtual bool GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits ) = 0;
		/**
		 *\brief		Dessine un bitmap dans le HDC donn�
		 *\param[in]	rcDst		Le rectangle dans lequel le bitmap doit �tre dessin�
		 *\param[in]	hBitmap		Le bitmap � dessiner
		 *\param[in]	rcSrc		Le rectangle du bitmap � dessiner
		 *\param[in]	bSrcAlpha	D�termine si on utilise l'alpha de la source ou pas
		 */
		virtual void DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL bSrcAlpha = TRUE ) = 0;
		/**
		 *\brief		Dessine le contour d'un rectangle
		 *\param[in]	rcRect		Le rectangle
		 *\param[in]	crColour	La couleur du trait
		 *\param[in]	iWidth		L'�paisseur du trait
		 *\param[in]	uiStyle		Le style de trait( cf. styles de LOGPEN )
		 */
		virtual void FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth = 1, UINT uiStyle = PS_SOLID ) = 0;
		/**
		 *\brief		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	hFont		La police de dessin
		 *\param[in]	crColour	La couleur du texte
		 *\param[in]	csText		Le texte
		 *\param[in]	rcRect		Le rectangle o� le texte doit �tre dessin�
		 *\param[in]	dwStyle		Le style du texte( cf. CDC::DrawText )
		 */
		virtual void DrawSolidText( HFONT hFont, LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle ) = 0;
		/**
		 *\brief		Remplit le rectangle donn� avec la couleur donn�e
		 * Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	crColour	La couleur de remplissage
		 *\param[in]	rcRect		Le rectangle � remplir
		 */
		virtual void FillSolidRect( CColour const & clColour, CRect rcRect ) = 0;
		/**
		 *\brief		Transparent Blit un dc dans celui-ci
		 * Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	rcDest	La section de la destination
		 *\param[in]	srcDC	Le DC source
		 *\param[in]	rcSrc	La section de la source
		 */
		virtual void TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent ) = 0;
		/**
		 *\brief		Alpha blend d'un HDC vers celui-ci
		 *\remark		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	rcDest		Le rectangle de destination
		 *\param[in]	hSrcDC		Le HDC source
		 *\param[in]	rcSrc		Le rectangle de source
		 *\param[in]	blendFunc	La fonction de blending
		 */
		virtual void AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc ) = 0;

	protected:
		/**
		 *\brief		Initialise l'arri�re plan, pour la transparence
		 */
		void DoInitialiseBackground();
		BOOL DoDrawParentBackground( CDC * pDC, CRect const & rect );
		/**
		 *\brief		Fonction d'initialisation
		 */
		virtual void DoInitialise() = 0;
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoCleanup() = 0;
		/**
		 *\brief		Fonction de dessin de l'arri�re plan
		 *\param[in]	rcRect	Rectangle affect� par le dessin
		 */
		virtual void DoDrawBackground( CRect const & rcRect ) = 0;
		/**
		 *\brief		Fonction de dessin du premier plan
		 *\param[in]	rcRect	Rectangle affect� par le dessin
		 */
		virtual void DoDrawForeground( CRect const & rcRect ) = 0;
		/**
		 *\brief		Fonction de dessin
		 */
		virtual void DoDraw() = 0;

	protected:
		//! Le masque de transparence (pour le distinguer du fond)
		CTransparentBrush m_brushMask;
		//! La couleur du texte (si texte il y a)
		CColour m_clText;
		//! La couleur du contour (si contour il y a)
		CColour m_clBorder;
		//! Dit qu'on est en train de dessiner le contr�le
		bool m_bPainting;
		//! Dit si l'arri�re plan a �t� d�fini
		bool m_bHasBackground;
		//! L'image contenant l'arri�re plan
		CBitmap m_bmpBackground;
		//! Dit si la souris est au-dessus de ce contr�le
		bool m_bMouseOver;
		//! Dit si ce contr�le a le focus
		bool m_bFocused;
		//! Dit s'il faut r�initialiser l'arri�re plan
		bool m_bReinitBackground;
		//! Le HDC du contr�le
		HDC m_hDC;
		//! Dit si le contr�le a un contour ou pas
		bool m_bHasBorder;
		//! Le contr�le
		CWnd * m_ctrl;
	};
#if DEF_USING_D2D
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Impl�mentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	*/
	class JGRA_API CTransparentCtrlBaseD2D
		: public CTransparentCtrlBase
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlBaseD2D();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentCtrlBaseD2D();
		/**
		 *\return		Le type d'interface de rendu
		 */
		virtual eRENDERER GetRenderer()const
		{
			return eRENDERER_D2D;
		}

	protected:
		/**
		 *\brief		Fonction d'initialisation
		 */
		virtual void DoInitialise();
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoCleanup();
		/**
		 *\brief		Initialise les donn�es ind�pendantes du contr�le
		 */
		void DoInitialiseDeviceIndependent();
		/**
		 *\brief		Nettoie les donn�es ind�pendantes du contr�le
		 */
		void DoCleanupDeviceIndependent();
		/**
		 *\brief		Initialise les donn�es d�pendantes du contr�le
		 */
		virtual void DoInitialiseDeviceDependent() = 0;
		/**
		 *\brief		Nettoie les donn�es d�pendantes du contr�le
		 */
		virtual void DoCleanupDeviceDependent() = 0;

	protected:
		//! Le nombre d'instanciations
		static int m_iReferences;
		//! La factory de cr�ation de bitmap
		static IDWriteFactory * m_pWriteFactory;
		//! La factory de cr�ation de cibles de rendu
		static ID2D1Factory * m_pFactory;
		//! Le nombre de bitmas cr��s
		static std::map< HBITMAP, ID2D1Bitmap * > m_bitmaps;
	};
#endif
#if DEF_USING_OGL
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Impl�mentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	*/
	class JGRA_API CTransparentCtrlBaseOGL
		: public CTransparentCtrlBase
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlBaseOGL();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentCtrlBaseOGL();
		/**
		 *\return		Le type d'interface de rendu
		 */
		virtual eRENDERER GetRenderer()const
		{
			return eRENDERER_OGL;
		}

	protected:
		/**
		 *\brief		Fonction d'initialisation
		 */
		virtual void DoInitialise();
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoCleanup();
		/**
		 *\brief		Initialise les donn�es ind�pendantes du contr�le
		 */
		void DoInitialiseDeviceIndependent();
		/**
		 *\brief		Nettoie les donn�es ind�pendantes du contr�le
		 */
		void DoCleanupDeviceIndependent();
		/**
		 *\brief		Initialise les donn�es d�pendantes du contr�le
		 */
		virtual void DoInitialiseDeviceDependent() = 0;
		/**
		 *\brief		Nettoie les donn�es d�pendantes du contr�le
		 */
		virtual void DoCleanupDeviceDependent() = 0;

	protected:
		//! Le nombre d'instanciations
		static int m_iReferences;
		//! La factory de cr�ation de bitmap
		static IDWriteFactory * m_pWriteFactory;
		//! La factory de cr�ation de cibles de rendu
		static IGL2DFactory * m_pFactory;
		//! Le nombre de bitmas cr��s
		static std::map< HBITMAP, IGL2DBitmap * > m_bitmaps;
	};
#endif
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Impl�mentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	*/
	class JGRA_API CTransparentCtrlBaseGDI
		: public CTransparentCtrlBase
	{
	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlBaseGDI();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentCtrlBaseGDI();
		/**
		 *\return		Le type d'interface de rendu
		 */
		virtual eRENDERER GetRenderer()const
		{
			return eRENDERER_GDI;
		}

	protected:
		/**
		 *\brief		Fonction d'initialisation
		 */
		virtual void DoInitialise();
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoCleanup();
	};
}
