#pragma once

#include "TransparentCtrl.h"
#include "Cursor.h"

namespace Joker
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Enum�ration des �tats possibles pour un bouton
	*/
	typedef enum
	{
		eBTN_STATE_DISABLED,	//!< Bouton d�sactiv�
		eBTN_STATE_ENABLED,		//!< Bouton activ�
		eBTN_STATE_HIGHLIGHTED,	//!< Bouton au-dessus duquel se trouve la souris
		eBTN_STATE_PUSHED,		//!< Bouton cliqu�
		eBTN_STATE_HOVERED,		//!< Souris reste au-dessus du bouton
		eBTN_STATE_COUNT
	}	eBTN_STATE;
	/*!
	\author		Sylvain DOREMUS
	\date		13/11/2011
	\brief		Sp�cialisation de CTransparentCtrl pour les CButton
	\remark		Permet d'ajouter les effets de relief par �tat.
				<br />G�re les �tats Enabled, Hovered, Focused, Pushed, Disabled
	*/
	template< eRENDERER Renderer >
	class CTransparentButton
		: public CTransparentCtrlT< CCursor< CButton >, Renderer >
	{
	public:
		typedef CTransparentCtrlT< CCursor< CButton >, Renderer > BaseType;

	public:
		/**
		 *\brief		Constructeur
		 */
		CTransparentButton();
		/**
		 *\brief		Desstructeur
		 */
		virtual ~CTransparentButton();
		/**
		 *\brief		Cr�e un brush de type solid pour l'�tat donn�.
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	crColour	La couleur
		 *\param[in]	bRedraw		Dit si on force le redessin
		 */
		void SetSolidBrush( eBTN_STATE eState, CColour const & clColour, BOOL bRedraw = TRUE );
		/**
		 *\brief		D�finit des brushes de type solid, pour chaque �tat
		 *\param[in]	clEnable	La couleur du bouton actif
		 *\param[in]	clHighlt	La couleur du bouton survol�
		 *\param[in]	clPushed	La couleur du bouton cliqu�
		 *\param[in]	clDisabl	La couleur du bouton inactif
		 */
		void SetSolidBrushes( CColour const & clEnable, CColour const & clHighlt, CColour const & clPushed, CColour const & clDisabl );
		/**
		 *\brief		Cr�e un brush de type solid pour l'�tat donn�.
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
						<br />Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	crColour	La couleur
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	bRedraw		Dit si on force le redessin
		 */
		inline void SetBrush( COLORREF clColour, eBTN_STATE eState = eBTN_STATE_COUNT, BOOL bRedraw = TRUE )
		{
			SetSolidBrush( eState, CColour::FromCOLORREF( clColour ), bRedraw );
		}
		/**
		 *\brief		D�finit des brushes de type solid, pour chaque �tat
		 *\remark		Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	crEnable	La couleur du bouton actif
		 *\param[in]	crHighlt	La couleur du bouton survol�
		 *\param[in]	crPushed	La couleur du bouton cliqu�
		 *\param[in]	crDisabl	La couleur du bouton inactif
		 */
		inline void SetBrushes( COLORREF crEnable, COLORREF crHighlt, COLORREF crPushed, COLORREF crDisabl )
		{
			SetSolidBrushes( CColour::FromCOLORREF( crEnable ), CColour::FromCOLORREF( crHighlt ), CColour::FromCOLORREF( crPushed ), CColour::FromCOLORREF( crDisabl ) );
		}
		/**
		 *\brief		Cr�e un brush de type pattern pour l'�tat donn�.
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	imgPattern	L'image contenant le pattern
		 */
		void SetPatternBrush( eBTN_STATE eState, HBITMAP hPattern, CRect const & rcPattern, BOOL bRedraw = TRUE );
		/**
		 *\brief		Cr�e un brush de type pattern ayant pour pattern un d�grad�, pour l'�tat donn�.
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	iType		Le type de d�grad�
		 *\param[in]	crDebut		La couleur de d�but( en haut )
		 *\param[in]	crMilieu	La couleur du milieu( au milieu )
		 *\param[in]	crFin		La couleur de fin( en bas )
		 *\param[in]	iSteps		Le nombre d'�tapes( d�termine le nombre de pixels de hauteur du d�grad� )
		 */
		void SetGradientBrush( eBTN_STATE eState, int iType, CColour const & clDebut, CColour const & clMilieu, CColour const & clFin, int iSteps, BOOL bRedraw = TRUE );
		/**
		 *\brief		D�finit la couleur du texte, pour l'�tat donn�
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	clColour	La couleur
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		void SetTextColour( eBTN_STATE eState, CColour const & clColour, BOOL bRedraw = TRUE );
		/**
		 *\brief		D�finit la couleur du texte, pour l'�tat donn�, utilise le CColourManager pour r�cup�rer la couleur
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	uiId		L'id de la couleur
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		void SetTextColour( eBTN_STATE eState, UINT uiId, BOOL bRedraw = TRUE );
		/**
		 *\brief		D�finit la couleur du texte, pour l'�tat donn�
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
						<br />Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	crColour	La couleur
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		inline void SetTextColour( COLORREF crColour, eBTN_STATE eState = eBTN_STATE_COUNT, BOOL bRedraw = TRUE )
		{
			SetTextColour( eState, CColour::FromCOLORREF( crColour ), bRedraw );
		}
		/**
		 *\brief		D�finit la couleur du texte, pour l'�tat donn�
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
						<br />Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	eColour		La couleur
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		inline void SetTextColour( CColour::ePREDEFINED eColour, eBTN_STATE eState = eBTN_STATE_COUNT, BOOL bRedraw = TRUE )
		{
			SetTextColour( eState, CColour( eColour ), bRedraw );
		}
		/**
		 *\brief		D�finit la couleur du texte, pour chaque �tat
		 *\param[in]	clEnabled	La couleur du bouton actif
		 *\param[in]	clHighlight	La couleur du bouton survol�
		 *\param[in]	clPush		La couleur du bouton cliqu�
		 *\param[in]	clDisabled	La couleur du bouton inactif
		 */
		void SetTextColours( CColour const & clEnabled, CColour const & clHighlight, CColour const & clPush, CColour const & clDisabled );
		/**
		 *\brief		D�finit la couleur du texte, pour chaque �tat
		 *\remark		Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	uiEnable	La couleur du bouton actif
		 *\param[in]	uiHighlt	La couleur du bouton survol�
		 *\param[in]	uiPushed	La couleur du bouton cliqu�
		 *\param[in]	uiDisabl	La couleur du bouton inactif
		 */
		void SetTextColours( UINT uiEnable, UINT uiHighlt, UINT uiPushed, UINT uiDisabl, BOOL bFromResources = FALSE );
		/**
		 *\brief		D�finit la police du texte, pour l'�tat donn�
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	pFont		La police
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		void SetFont( eBTN_STATE eState, FontPtr pFont, BOOL bRedraw = TRUE );
		/**
		 *\brief		D�finit la police du texte, pour l'�tat donn�
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
						<br />Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	pFont		La police
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		void SetFont( FontPtr pFont, eBTN_STATE eState = eBTN_STATE_COUNT, BOOL bRedraw = TRUE )
		{
			SetFont( eState, pFont, bRedraw );
		}
		/**
		 *\brief		D�finit la police du texte, pour l'�tat donn�, passe par le CFontManager pour r�cuperer la police
		 *\remark		Si eState vaut eBTN_STATE_COUNT, tous les �tats sont affect�s
		 *\param[in]	eState		L'�tat � affecter
		 *\param[in]	uiId		L'id de la police
		 *\param[in]	bRedraw		Pour forcer le redessin
		 */
		void SetFont( eBTN_STATE eState, UINT uiId, BOOL bRedraw = TRUE );
		/**
		 *\brief		D�finit les polices utilis�es dans les diff�rents �tats du bouton
		 *\param[in]	pEnabledFont	La police du bouton actif
		 *\param[in]	pHighlightFont	La police du bouton survol�
		 *\param[in]	pPushFont		La police du bouton cliqu�
		 *\param[in]	pDisabledFont	La police du bouton inactif
		 */
		void SetFonts( FontPtr pEnabledFont, FontPtr pHighlightFont, FontPtr pDownFont, FontPtr pDisabledFont );
		/**
		 *\brief		D�finit les polices utilis�es dans les diff�rents �tats du bouton, passe par le CFontManager pour r�cuperer les polices
		 *\param[in]	iEnabledIndex	L'id de la police du bouton actif
		 *\param[in]	iHighlightIndex	L'id de la police du bouton survol�
		 *\param[in]	iDownIndex		L'id de la police du bouton cliqu�
		 *\param[in]	iDisabledIndex	L'id de la police du bouton inactif
		 */
		void SetFonts( int iEnabledIndex, int iHighlightIndex, int iDownIndex, int iDisabledIndex );
		/**
		 *\brief		Active ou desactive le bouton
		 *\param[in]	bEnable	Dit si on active ou d�sactive le bouton
		 *\return		L'�tat pr�c�dent l'appel � cette fonction
		 */
		virtual BOOL EnableWindow( BOOL bEnable = TRUE );
		/**
		 *\brief		D�finit l'image (pattern brush) de chaque �tat du bouton, utilise le CImageManager pour charger les images
		 *\remark		Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	iEnabled		L'id de l'image du bouton actif
		 *\param[in]	iHighlight		L'id de l'image du bouton survol�
		 *\param[in]	iPush			L'id de l'image du bouton cliqu�
		 *\param[in]	iDisabled		L'id de l'image du bouton inactif
		 *\param[in]	rcFixed			La taille fixe du bouton
		 *\param[in]	bFromResources	Dit si les id viennent des ressources ou pas
		 *\return
		 */
		void SetImages( int iEnabled, int iHighlight, int iPush, int iDisabled, CRect const & rcFixed = CRect( 0, 0, 0, 0 ), BOOL bFromResources = FALSE );
		/**
		 *\brief		D�finit l'image (pattern brush) de chaque �tat du bouton, utilise le CImageManager pour charger les images
		 *\remark		Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	iEnabled		L'id de l'image du bouton actif
		 *\param[in]	iHighlight		L'id de l'image du bouton survol�
		 *\param[in]	iPush			L'id de l'image du bouton cliqu�
		 *\param[in]	iDisabled		L'id de l'image du bouton inactif
		 *\param[in]	rcFixed			La taille fixe du bouton
		 *\param[in]	bFromResources	Dit si les id viennent des ressources ou pas
		 *\return
		 */
		void SetImage( int nResourceID, CRect const & rcFixed = CRect( 0, 0, 0, 0 ), eBTN_STATE eState = eBTN_STATE_COUNT, BOOL bRedraw = TRUE );
		/**
		 *\brief		Fonction d�finissant le texte du bouton
		 *\remark		Ecrite pour une meilleure interchangeabilit� entre CA2iButton et CTransparentButton
		 *\param[in]	strText	Le texte
		 */
		void SetText( String const & strText );
		/**
		 *\brief		D�finit l'alignement du texte du bouton
		 *\param[in]	dwAlign	L'alignement
		 */
		inline void SetTextAlign( DWORD dwAlign )
		{
			m_dwAlign = dwAlign;
		}
		/**
		 *\brief		R�cup�re l'�tat courant
		 *\return		L'�tat courant
		 */
		inline eBTN_STATE	GetState()const
		{
			return m_eState;
		}
		/**
		 *\brief		D�finit les tailles fixes
		 *\param[in]	Les tailles fixes
		 */
		inline void SetFixedSizes( CRect const & rcVal )
		{
			m_rcFixedSizes = rcVal;
		}
		/**
		 *\brief		Definit si on veut afficher le masque de focus ou pas
		 *\param[in]	bShow	\p TRUE pour afficher, \p FALSE sinon
		 */
		inline void ShowFocus( BOOL bShow )
		{
			m_bDrawFocus = bShow;
		}
		/**
		 *\brief		Definit si on veut afficher le contour ou pas
		 *\param[in]	bShow	\p TRUE pour afficher, \p FALSE sinon
		 */
		inline void ShowBorder( BOOL bShow )
		{
			m_bDrawBorder = bShow;
		}

	private:
		virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
		virtual void DoRelease();
		virtual void DoDrawBackground( CRect const & rcRect );
		virtual void DoDrawForeground( CRect const & rcRect );

		DECLARE_MESSAGE_MAP()
		afx_msg void OnMouseMove( UINT nFlags, CPoint point );
		afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );
		afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
		afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
		afx_msg void OnSetFocus( CWnd * pOldWnd );
		afx_msg void OnKillFocus( CWnd * pNewWnd );

	protected:
		//! Les masques du bouton (contiennent les images)
		CTransparentBrush m_brushes[eBTN_STATE_COUNT];
		//! Les couleurs des textes
		CColour m_textColours[eBTN_STATE_COUNT];
		//! Les fonts
		FontPtr m_pFonts[eBTN_STATE_COUNT];
		//! L'�tat courant
		eBTN_STATE m_eState;
		//! L'alignement du texte
		DWORD m_dwAlign;
		//! Les dimensions fixes (non stretch�es)
		CRect m_rcFixedSizes;
		//! Dit si on dessine le contour
		BOOL m_bDrawBorder;
		//! Dit si on dessine le masque de focus
		BOOL m_bDrawFocus;
	};
	/**
	 *\brief		Macro pour simplifier l'initialisation du bouton
	 *\param[in]	btnCtrl		Le bouton � initialiser
	 *\param[in]	ImgName		Le nom utilis� comme base pour les noms des images
	 *\param[in]	TxtName		Le nom utilis� comme base pour les noms des textes
	 *\param[in]	FntName		Le nom utilis� comme base pour les noms des polices
	 *\param[in]	iRatio		Le ratio pour les dimensions fixes
	 *\param[in]	tszCaption	Le libell� du bouton
	 *\param[in]	uiAlign		L'alignement des textes du bouton
	 *\param[in]	uiCursor	Le curseur utilis� lors du survol du bouton
	 *\param[in]	bFocus		Dit si on veut dessiner le masque de focus du bouton
	 */
#	define InitialiseTransparentButtonComplete( btnCtrl, ImgName, TxtName, FntName, iRatio, tszCaption, uiAlign, uiCursor, bFocus ) \
	{\
		(btnCtrl).SetImages(		eIMAGE_INDEX_##ImgName,		eIMAGE_INDEX_##ImgName##HIGHLIGHT,	eIMAGE_INDEX_##ImgName##DOWN,	eIMAGE_INDEX_##ImgName##DISABLE,	CRect( iRatio, 0, iRatio, 0 )	);\
		(btnCtrl).SetTextColours(	eCOLOUR_INDEX_##TxtName,	eCOLOUR_INDEX_##TxtName##HIGHLIGHT,	eCOLOUR_INDEX_##TxtName##DOWN,	eCOLOUR_INDEX_##TxtName##DISABLED									);\
		(btnCtrl).SetFonts(			eFONT_INDEX_##FntName,		eFONT_INDEX_##FntName##HIGHLIGHT,	eFONT_INDEX_##FntName##DOWN,	eFONT_INDEX_##FntName##DISABLED										);\
		(btnCtrl).SetText(			(tszCaption)																																						);\
		(btnCtrl).SetTextAlign(		(uiAlign)																																							);\
		(btnCtrl).SetCursor(		::LoadCursor( NULL, (uiCursor) )																																	);\
		(btnCtrl).ShowFocus(		(bFocus)																																							);\
	}
	/**
	 *\brief		Macro pour simplifier l'initialisation du bouton
	 *\remark		Utilise InitialiseTransparentButtonComplete
	 *\param[in]	btnCtrl			Le bouton � initialiser
	 *\param[in]	ImgTxtFntName	Le nom utilis� comme base pour les noms des images, des textes et des polices
	 *\param[in]	iRatio			Le ratio pour les dimensions fixes
	 *\param[in]	tszCaption		Le libell� du bouton
	 *\param[in]	uiAlign			L'alignement des textes du bouton
	 *\param[in]	uiCursor		Le curseur utilis� lors du survol du bouton
	 */
#	define InitialiseTransparentButton( btnCtrl, ImgTxtFntName, iRatio, tszCaption, uiAlign, uiCursor ) InitialiseTransparentButtonComplete( btnCtrl, ImgTxtFntName, ImgTxtFntName, ImgTxtFntName, iRatio , tszCaption, uiAlign, uiCursor, FALSE )
	/**
	 *\brief		Macro pour simplifier l'initialisation du bouton
	 *\remark		Utilise InitialiseTransparentButtonComplete
					<br />Le bouton affichera le masque de focus
	 *\param[in]	btnCtrl			Le bouton � initialiser
	 *\param[in]	ImgTxtFntName	Le nom utilis� comme base pour les noms des images, des textes et des polices
	 *\param[in]	iRatio			Le ratio pour les dimensions fixes
	 *\param[in]	tszCaption		Le libell� du bouton
	 *\param[in]	uiAlign			L'alignement des textes du bouton
	 *\param[in]	uiCursor		Le curseur utilis� lors du survol du bouton
	 */
#	define InitialiseTransparentButtonFocused( btnCtrl, ImgTxtFntName, iRatio, tszCaption, uiAlign, uiCursor ) InitialiseTransparentButtonComplete( btnCtrl, ImgTxtFntName, ImgTxtFntName, ImgTxtFntName, iRatio , tszCaption, uiAlign, uiCursor, TRUE )
	/**
	 *\brief		Macro pour simplifier l'initialisation du bouton
	 *\remark		Le texte du bouton sera centr� verticalement et horizontalement
					<br />Utilise InitialiseTransparentButtonComplete
	 *\param[in]	btnCtrl			Le bouton � initialiser
	 *\param[in]	ImgTxtFntName	Le nom utilis� comme base pour les noms des images, des textes et des polices
	 *\param[in]	iRatio			Le ratio pour les dimensions fixes
	 *\param[in]	tszCaption		Le libell� du bouton
	 *\param[in]	uiCursor		Le curseur utilis� lors du survol du bouton
	 */
#	define InitialiseTransparentButtonCentered( btnCtrl, ImgTxtFntName, iRatio, tszCaption, uiCursor ) InitialiseTransparentButtonComplete( btnCtrl, ImgTxtFntName, ImgTxtFntName, ImgTxtFntName, iRatio , tszCaption, DT_CENTER | DT_VCENTER, uiCursor, FALSE )
	/**
	 *\brief		Macro pour simplifier l'initialisation du bouton
	 *\remark		Le texte du bouton sera centr� verticalement et horizontalement
					<br />Utilise InitialiseTransparentButtonComplete
	 *\param[in]	btnCtrl		Le bouton � initialiser
	 *\param[in]	ImgName		Le nom utilis� comme base pour les noms des images
	 *\param[in]	TxtFntName	Le nom utilis� comme base pour les noms des textes et des polices
	 *\param[in]	iRatio		Le ratio pour les dimensions fixes
	 *\param[in]	tszCaption	Le libell� du bouton
	 *\param[in]	uiCursor	Le curseur utilis� lors du survol du bouton
	 */
#	define InitialiseTransparentButtonCenteredColoured( btnCtrl, ImgName, TxtFntName, iRatio, tszCaption, uiCursor ) InitialiseTransparentButtonComplete( btnCtrl, ImgName, TxtFntName, TxtFntName, iRatio , tszCaption, DT_CENTER | DT_VCENTER, uiCursor, FALSE )
	/**
	 *\brief		Macro pour simplifier l'initialisation du bouton
	 *\remark		Le texte du bouton sera centr� verticalement et horizontalement
					<br />Utilise InitialiseTransparentButtonComplete
	 *\param[in]	btnCtrl		Le bouton � initialiser
	 *\param[in]	ImgTxtName	Le nom utilis� comme base pour les noms des images et des textes
	 *\param[in]	FntName		Le nom utilis� comme base pour les noms des polices
	 *\param[in]	iRatio		Le ratio pour les dimensions fixes
	 *\param[in]	tszCaption	Le libell� du bouton
	 *\param[in]	uiCursor	Le curseur utilis� lors du survol du bouton
	 */
#	define InitialiseTransparentButtonCenteredFont( btnCtrl, ImgTxtName, FntName, iRatio, tszCaption, uiCursor ) InitialiseTransparentButtonComplete( btnCtrl, ImgTxtName, ImgTxtName, FntName, iRatio , tszCaption, DT_CENTER | DT_VCENTER, uiCursor, FALSE )
}

#include "TransparentButton.inl"