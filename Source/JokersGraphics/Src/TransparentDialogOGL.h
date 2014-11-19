#pragma once

#include "TransparentCtrlBase.h"

namespace Joker
{
#if DEF_USING_OGL
	/*!
	\brief		Implémentation d'une classe de control transparent.
	\remark		La transparence de ce control est personnalisable( via le masque ), en couleur comme en alpha( plus ou moins transparente ).
				<br />Cette personnalisation est possible via la classe CTransparentBrush.
	\author Sylvain DOREMUS
	\date 13/11/2011
	*/
	template<>
	class JGRA_API CTransparentCtrlT< CDialog, eRENDERER_OGL >
		: public CDialog
		, public CTransparentCtrlBaseOGL
	{
	protected:
		typedef CDialog BaseType;

	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlT();
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlT( UINT nTemplate, CWnd * pParent );
		/**
		 *\brief		Constructeur
		 */
		CTransparentCtrlT( LPCTSTR szTemplate, CWnd * pParent );
		/**
		 *\brief		Destructeur
		 */
		virtual ~CTransparentCtrlT();
		/**
		 *\brief		Récupère les informations d'un bitmap donné
		 *\param[in]	hDC			Le HDC utilisé pour déterminer les informations du HBITMAP
		 *\param[in]	hBitmap		Le bitmap dont on veut les informations
		 *\param[in]	size		Les dimensions du bitmap
		 *\param[in]	arrayBits	Les pixels du bitmap
		 */
		virtual bool GetBitmapInfos( HDC hDC, HBITMAP hBitmap, CSize & size, std::vector< BYTE > & arrayBits );
		/**
		 *\brief		Dessine un bitmap dans le HDC donné
		 *\param[in]	hDC			Le HDC de destination
		 *\param[in]	rcDst		Le rectangle dans lequel le bitmap doit être dessiné
		 *\param[in]	hBitmap		Le bitmap à dessiner
		 *\param[in]	rcSrc		Le rectangle du bitmap à dessiner
		 *\param[in]	bSrcAlpha	Détermine si on utilise l'alpha de la source ou pas
		 */
		virtual void DrawBitmap( CRect const & rcDst, HBITMAP hBitmap, CRect const & rcSrc, BOOL bSrcAlpha = TRUE );
		/**
		 *\brief		Dessine le contour d'un rectangle
		 *\param[in]	rcRect		Le rectangle
		 *\param[in]	crColour	La couleur du trait
		 *\param[in]	iWidth		L'épaisseur du trait
		 *\param[in]	uiStyle		Le style de trait( cf. styles de LOGPEN )
		 */
		virtual void FrameRect( CRect const & rcRect, CColour const & clColour, int iWidth = 1, UINT uiStyle = PS_SOLID );
		/**
		 *\brief		Dessine un texte avec la police et la couleur donnés
		 *\param[in]	hFont		La police de dessin
		 *\param[in]	crColour	La couleur du texte
		 *\param[in]	csText		Le texte
		 *\param[in]	rcRect		Le rectangle où le texte doit être dessiné
		 *\param[in]	dwStyle		Le style du texte( cf. CDC::DrawText )
		 */
		virtual void DrawSolidText( HFONT hFont, LOGFONT logFont, CColour const & clColour, CString const & csText, CRect rcRect, DWORD dwStyle );
		/**
		 *\brief		Remplit le rectangle donné avec la couleur donnée
		 *\remark		Dessine un texte avec la police et la couleur donnés
		 *\param[in]	crColour	La couleur de remplissage
		 *\param[in]	rcRect		Le rectangle à remplir
		 */
		virtual void FillSolidRect( CColour const & clColour, CRect rcRect );
		/**
		 *\brief		Transparent Blit un dc dans celui-ci
		 *\remark		Dessine un texte avec la police et la couleur donnés
		 *\param[in]	rcDest	La section de la destination
		 *\param[in]	srcDC	Le DC source
		 *\param[in]	rcSrc	La section de la source
		 */
		virtual void TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent );
		/**
		 *\brief		Alpha blend d'un HDC vers celui-ci
		 *\remark		Dessine un texte avec la police et la couleur donnés
		 *\param[in]	rcDest		Le rectangle de destination
		 *\param[in]	hSrcDC		Le HDC source
		 *\param[in]	rcSrc		Le rectangle de source
		 *\param[in]	blendFunc	La fonction de blending
		 */
		virtual void AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc );
		/**
		 *\brief		Définit la position du contrôle
		 *\param[in]	pWndInsertAfter	La fenêtre suivante dans l'ordre de tabulation
		 *\param[in]	x, y				La position
		 *\param[in]	cx, cy				Les dimensions
		 *\param[in]	nFlags				Combinaison de flags
		 *\return		\p FALSE si problème
		 */
		BOOL SetWindowPos( const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT uiFlags );

	private:
		void DoInitDeviceDependent();
		void DoCleanupDeviceDependent();

	protected:
		/**
		 *\brief		Fonction de nettoyage
		 */
		virtual void DoRelease();
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
		 *\brief		Fonction de dessin
		 */
		virtual void DoDraw();

	protected:
		/**
		 *\brief		Fonction appelée par le framework pour faire les sous-classements nécessaire avant de sous-classer le contrôle
		 */
		virtual void PreSubclassWindow();

		DECLARE_MESSAGE_MAP()
		afx_msg BOOL OnEraseBkgnd( CDC * pDC );
		afx_msg HBRUSH OnCtlColor( CDC * pDC, CWnd * pWnd, UINT uiWinID );
		afx_msg void OnDestroy();
		afx_msg void OnPaint();
		afx_msg void OnSize( UINT type, int cx, int cy );
		afx_msg LRESULT OnDisplayChange( WPARAM, LPARAM );
		afx_msg void OnSetFocus( CWnd * pOldWnd );
		afx_msg void OnKillFocus( CWnd * pNewWnd );
		afx_msg void OnMouseMove( UINT nFlags, CPoint point );
		afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );

	protected:
		//! Le bitmap contenant le dessin
		IGL2DBitmap * m_pBitmap;
		//! La cible du rendu
		IGL2DHwndRenderTarget * m_pRenderTarget;
	};
#endif
}
