#pragma once

#include "TransparentCtrlBase.h"

namespace Joker
{
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Impl�mentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	*/
	template< typename T >
	class CTransparentCtrlT< T, eRENDERER_GDI >
		: public T
		, public CTransparentCtrlBase
	{
	protected:
		typedef T BaseType;

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
		 *\brief		R�cup�re les informations d'un bitmap donn�
		 *\param[in]	hDC			Le HDC utilis� pour d�terminer les informations du HBITMAP
		 *\param[in]	hBitmap		Le bitmap dont on veut les informations
		 *\param[in]	size		Les dimensions du bitmap
		 *\param[in]	arrayBits	Les pixels du bitmap
		 */
		virtual bool GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits );
		/**
		 *\brief		Dessine un bitmap dans le HDC donn�
		 *\param[in]	rcDst		Le rectangle dans lequel le bitmap doit �tre dessin�
		 *\param[in]	hBitmap		Le bitmap � dessiner
		 *\param[in]	rcSrc		Le rectangle du bitmap � dessiner
		 *\param[in]	bSrcAlpha	D�termine si on utilise l'alpha de la source ou pas
		 */
		virtual void DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL bSrcAlpha = TRUE );
		/**
		 *\brief		Dessine le contour d'un rectangle
		 *\param[in]	rcRect		Le rectangle
		 *\param[in]	crColour	La couleur du trait
		 *\param[in]	iWidth		L'�paisseur du trait
		 *\param[in]	uiStyle		Le style de trait( cf. styles de LOGPEN )
		 */
		virtual void FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth = 1, UINT uiStyle = PS_SOLID );
		/**
		 *\brief		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	hFont		La police de dessin
		 *\param[in]	crColour	La couleur du texte
		 *\param[in]	csText		Le texte
		 *\param[in]	rcRect		Le rectangle o� le texte doit �tre dessin�
		 *\param[in]	dwStyle		Le style du texte( cf. CDC::DrawText )
		 */
		virtual void DrawSolidText( HFONT hFont, LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle );
		/**
		 *\brief		Remplit le rectangle donn� avec la couleur donn�e
		 * Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	crColour	La couleur de remplissage
		 *\param[in]	rcRect		Le rectangle � remplir
		 */
		virtual void FillSolidRect( CColour const & clColour, CRect rcRect );
		/**
		 *\brief		Transparent Blit un dc dans celui-ci
		 * Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	rcDest	La section de la destination
		 *\param[in]	srcDC	Le DC source
		 *\param[in]	rcSrc	La section de la source
		 */
		virtual void TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent );
		/**
		 *\brief		Alpha blend d'un HDC vers celui-ci
		 *\remark		Dessine un texte avec la police et la couleur donn�s
		 *\param[in]	rcDest		Le rectangle de destination
		 *\param[in]	hSrcDC		Le HDC source
		 *\param[in]	rcSrc		Le rectangle de source
		 *\param[in]	blendFunc	La fonction de blending
		 */
		virtual void AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc );
		/**
		 *\brief		D�finit la position du contr�le
		 *\param[in]	pWndInsertAfter	La fen�tre suivante dans l'ordre de tabulation
		 *\param[in]	x, y				La position
		 *\param[in]	cx, cy				Les dimensions
		 *\param[in]	nFlags				Combinaison de flags
		 *\return		\p FALSE si probl�me
		 */
		BOOL SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags );

	protected:
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoRelease();
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
		 *\brief		Fonction de dessin
		 */
		virtual void DoDraw();

	protected:
		/**
		 *\brief		Fonction appel�e par le framework pour faire les sous-classements n�cessaire avant de sous-classer le contr�le
		 */
		virtual void PreSubclassWindow();

		DECLARE_MESSAGE_MAP()
		afx_msg BOOL OnEraseBkgnd( CDC * pDC );
		afx_msg void OnSize( UINT type, int cx, int cy );
		afx_msg void OnPaint();
		afx_msg void OnSetFocus( CWnd * pOldWnd );
		afx_msg void OnKillFocus( CWnd * pNewWnd );
		afx_msg void OnMouseMove( UINT nFlags, CPoint point );
		afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );

	protected:
		//! Le contenu du backbuffer
		CBitmapDC * m_pBackDC;
	};
}

#include "TransparentCtrlGDI.inl"
