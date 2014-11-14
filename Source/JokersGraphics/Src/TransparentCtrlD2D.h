#pragma once

#ifdef DrawText
#	undef DrawText
#endif

#include "Drawer.h"
#include "BitmapDC.h"
#include "TransparentBrush.h"
#include "Font.h"
#include "Logger.h"

#include <algorithm>

#ifdef min
#	undef min
#endif

#ifdef max
#	undef max
#endif

namespace Joker
{
#if DEF_USING_D2D
	/*!
	\brief		Impl�mentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	\author Sylvain DOREMUS
	\date 13/11/2011
	*/
	template< typename T >
	class CTransparentCtrlT< T, eRENDERER_D2D >
		: public T
	{
	protected:
		typedef T BaseType;

		CTransparentBrush			m_brushMask;			//!< Le masque de transparence (pour le distinguer du fond)
		CColour						m_clText;				//!< La couleur du texte (si texte il y a)
		CColour						m_clBorder;				//!< La couleur du contour (si contour il y a)
		bool						m_bPainting;			//!< Dit qu'on est en train de dessiner le contr�le
		bool						m_bHasBackground;		//!< Dit si l'arri�re plan a �t� d�fini
		CBitmap						m_bmpBackground;		//!< L'image contenant l'arri�re plan
		bool						m_bMouseOver;			//!< Dit si la souris est au-dessus de ce contr�le
		bool						m_bFocused;				//!< Dit si ce contr�le a le focus
		ID2D1Bitmap *				m_pBitmap;				//!< Le bitmap contenant le dessin
		ID2D1HwndRenderTarget *		m_pHwndRenderTarget;	//!< La cible du rendu
		ID2D1BitmapRenderTarget *	m_pBmpRenderTarget;		//!< La cible du rendu temporaire
		ID2D1RenderTarget *			m_pRenderTarget;		//!< Le contenu du backbuffer
		eRENDERER					m_eRenderer;			//!< Le type de rendu (GDI ou D2D)
		bool						m_bReinitBackground;	//!< Dit s'il faut r�initialiser l'arri�re plan
		HDC							m_hDC;					//!< Le HDC du contr�le
		bool						m_bHasBorder;			//!< Dit si le contr�le a un contour ou pas

		static int					m_iReferences;			//!< Le nombre d'instanciations
		static IDWriteFactory *		m_pWriteFactory;		//!< La factory de cr�ation de bitmap
		static ID2D1Factory *		m_pFactory;				//!< La factory de cr�ation de cibles de rendu

	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlT();
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentCtrlT();
		/**
		 *\brief		D�finit la couleur du contour
		 *\remark		Le contr�le est invalid�
		 *\param[in]	crColour	La nouvelle couleur
		 */
		inline void SetBorderColour( CColour const & clColour );
		/**
		 *\brief		D�finit la couleur du texte
		 *\remark		Le contr�le est invalid�
		 *\param[in]	crColour	La nouvelle couleur
		 */
		inline void SetTextColour( CColour const & clColour );
		/**
		 *\brief		R�cup�re le rectangle relatif de la liste par rapport � son parent
		 *\param[out]	rcRect	Re�oit les dimension et position de la liste
		 */
		inline void	GetRelativeRect( CRect & rcRect );
		/**
		 *\return		La couleur du masque de transparence
		 */
		inline CColour GetBorderColour()const { return m_clBorder; }
		/**
		 *\return		La couleur du masque de transparence
		 */
		inline CColour GetTextColour()const { return m_clText; }
		/**
		 *\return		L'alpha du masque de transparence
		 */
		inline BYTE GetMaskAlpha()const { return m_brushMask.GetAlpha(); }
		/**
		 *\return		L'alpha du masque de transparence
		 */
		inline bool IsPainting()const { return m_bPainting; }
		/**
		 *\brief		R�cup�re le masque
		 *\return		Une r�f�rence non constante sur le masque
		 */
		inline CTransparentBrush & GetMaskBrush() { return m_brushMask; }
		/**
		 *\brief		R�cup�re le masque
		 *\return		Une r�f�rence constante sur le masque
		 */
		inline CTransparentBrush const & GetMaskBrush()const { return m_brushMask; }
		/**
		 *\brief		R�cup�re les informations d'un bitmap donn�
		 *\param[in]	hDC			Le HDC utilis� pour d�terminer les informations du HBITMAP
		 *\param[in]	hBitmap		Le bitmap dont on veut les informations
		 *\param[in]	size		Les dimensions du bitmap
		 *\param[in]	arrayBits	Les pixels du bitmap
		 */
		bool GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits );
		/**
		 *\brief		Dessine un bitmap dans le HDC donn�
		 *\param[in]	hDC			Le HDC de destination
		 *\param[in]	rcDst		Le rectangle dans lequel le bitmap doit �tre dessin�
		 *\param[in]	hBitmap		Le bitmap � dessiner
		 *\param[in]	rcSrc		Le rectangle du bitmap � dessiner
		 *\param[in]	bSrcAlpha	D�termine si on utilise l'alpha de la source ou pas
		 */
		void DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL bSrcAlpha=TRUE );
		/**
		 *\brief		Dessine le contour d'un rectangle
		 *\param[in]	rcRect		Le rectangle
		 *\param[in]	crColour	La couleur du trait
		 *\param[in]	iWidth		L'�paisseur du trait
		 *\param[in]	uiStyle		Le style de trait( cf. styles de LOGPEN )
		 */
		void FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth = 1, UINT uiStyle = PS_SOLID );
		/**
		 *\brief		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	hFont		La police de dessin
		 *\param[in]	crColour	La couleur du texte
		 *\param[in]	csText		Le texte
		 *\param[in]	rcRect		Le rectangle o� le texte doit �tre dessin�
		 *\param[in]	dwStyle		Le style du texte( cf. CDC::DrawText )
		 */
		void DrawSolidText( HFONT hFont, LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle );
		/**
		 *\brief		Remplit le rectangle donn� avec la couleur donn�e
		 *\remark		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	crColour	La couleur de remplissage
		 *\param[in]	rcRect		Le rectangle � remplir
		 */
		void FillSolidRect( CColour const & clColour, CRect rcRect );
		/**
		 *\brief		Transparent Blit un dc dans celui-ci
		 *\remark		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	rcDest	La section de la destination
		 *\param[in]	srcDC	Le DC source
		 *\param[in]	rcSrc	La section de la source
		 */
		void TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent );
		/**
		 *\brief		Alpha blend d'un HDC vers celui-ci
		 *\remark		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	rcDest		Le rectangle de destination
		 *\param[in]	hSrcDC		Le HDC source
		 *\param[in]	rcSrc		Le rectangle de source
		 *\param[in]	blendFunc	La fonction de blending
		 */
		void AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc );
		/**
		 *\brief		D�finit la position du contr�le
		 *\param[in]	pWndInsertAfter	La fen�tre suivante dans l'ordre de tabulation
		 *\param[in]	x, y				La position
		 *\param[in]	cx, cy				Les dimensions
		 *\param[in]	nFlags				Combinaison de flags
		 *\return		\p FALSE si probl�me
		 */
		BOOL SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags );
		/**
		 *\brief		D�finit si le contr�le a un contour ou pas
		 *\param[in]	bBorder	La valeur
		 */
		void SetBorder( bool bBorder ) { m_bHasBorder = bBorder; }

	private:
		void DoInitDeviceIndependent();
		void DoCleanupDeviceIndependent();
		void DoInitDeviceDependent();
		void DoCleanupDeviceDependent();

	protected:
		/**
		 *\brief		Fonction de nettoyage
		 */
		inline void Release();
		/**
		 *\brief		Initialise l'arri�re plan, pour la transparence
		 */
		void DoInitialiseBackground();
		/**
		 *\brief		Fonction de nettoyage (effective)
		 */
		virtual void DoRelease(){}
		/**
		 *\brief		Fonction de dessin de l'arri�re plan
		 *\param[in]	rcRect	Rectangle affect� par le dessin
		 */
		virtual void DoDrawBackground( CRect const & rcRect );
		/**
		 *\brief		Fonction de dessin du premier plan
		 *\param[in]	rcRect	Rectangle affect� par le dessin
		 */
		virtual void DoDrawForeground( CRect const & rcRect );
		/**
		 *\brief		Fonction appel�e par le framework pour faire les sous-classements n�cessaire avant de sous-classer le contr�le
		 */
		virtual void	PreSubclassWindow	();

		DECLARE_MESSAGE_MAP()
		afx_msg BOOL	OnEraseBkgnd		( CDC * pDC );
		afx_msg void	OnDestroy			();
		afx_msg void	OnPaint				();
		afx_msg void	OnSize				( UINT type, int cx, int cy );
		afx_msg LRESULT	OnDisplayChange		( WPARAM, LPARAM );
		afx_msg void	OnSetFocus			( CWnd * pOldWnd );
		afx_msg void	OnKillFocus			( CWnd * pNewWnd );
		afx_msg void	OnMouseMove			( UINT nFlags, CPoint point );
		afx_msg LRESULT	OnMouseLeave		( WPARAM wParam, LPARAM lParam );

	protected:
		/**
		 *\brief		Fonction de dessin
		 */
		inline void Draw();
	};
#endif
}

#include "TransparentCtrlD2D.inl"
