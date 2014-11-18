#pragma once

#include "Colour.h"
#include "Font.h"
#include "Image.h"

#ifdef DrawText
#	undef DrawText
#endif

namespace Joker
{
	/*!
	\author Sylvain DOREMUS
	\date	21/02/2012
	\brief	Classe de base d'un dessinateur
	\remark	Permet de spécialiser le comportement d'un dessinateur selon qu'on dessine dans un DC, pdf ou autre
			<br />Classe virtuelle pure
	*/
	class JGRA_API CDrawerBase
	{
	public:
		/**
		 *\brief		Constructeur par défaut
		 */
		CDrawerBase() {}
		/**
		 *\brief		Constructeur spécifié
		 *\param[in]	rcRect	Le rectangle concerné par le dessin
		 */
		CDrawerBase( CRect const & rcRect ) : m_rcRect( rcRect ) {}
		/**
		 *\brief		Constructeur par copie
		 *\param[in]	drawer	Le dessinateur à copier
		 */
		CDrawerBase( CDrawerBase const & drawer ) : m_rcRect( drawer.m_rcRect ) {}
		/**
		 *\brief		Destructeur
		 */
		virtual ~CDrawerBase() {}
		/**
		 *\brief		Crée un buffer temporaire dans lequel les opérations seront effectuées
		 *\remark		Pour que les modifications soient appliquées au contexte de rendu, il faut appeler Finalise
		 *\param[in]	rcRect	Les dimensions du buffer temporaire
		 */
		virtual void CreateBackbuffer( CRect const & rcRect ) = 0;
		/**
		 *\brief		Applique les opérations du backbuffer au contexte de rendu, détruit le backbuffer
		 *\remark		Pour que cette fonction ait un effet, il faut que CreateBackbuffer ait été appelée
		 */
		virtual void Finalise() = 0;
		/**
		 *\brief		Formatte un texte en fonction d'une largeur maximale, d'une police et d'un ratio. remplit les variables rcRect et strFormatted
		 *\param[out]	rcRect			Reçoit le rectangle contenant le texte
		 *\param[in]	iWidth			La largeur maximale du texte
		 *\param[in]	strUnformatted	Le texte avant formattage
		 *\param[out]	strFormatted	Reçoit le texte formatté
		 *\param[in]	cFont			La police à utiliser pour calculer la taille
		 *\param[in]	dRatio			Le ratio d'affichage (1 dans une fenêtre, plus quand on imprime)
		 *\param[in]	uiFormat		Le type de découpe si DT_WORDBREAK, découpe par mot, sinon découpe par lettre (par défaut vaut DT_WORDBREAK)
		 *\return		Le nombre de lignes du texte formatté
		 */
		virtual int FormatText( CRect & rcRect, int iWidth, String const & strUnformatted, String & strFormatted, Joker::CFont & cFont, double dRatio, UINT uiFormat = DT_WORDBREAK );
		/**
		 *\brief		Récupère les dimensions maximales du texte passé en argument dans le contexte donné.
		 *\remark		Ne tient pas compte des lignes, utilise la police courante
		 *\param[in]	strText		Le texte dont on veut avoir les dimensions
		 *\param[out]	sizeText	Reçoit la taille du texte
		 */
		virtual void GetTextExtent( String const & strText, CSize & sizeText );
		/**
		 *\brief		Récupère les dimensions maximales du texte passé en argument dans le contexte donné et la police donnée.
		 *\remark		Prend les lignes en compte, utilise la police donnée
		 *\param[in]	strText		Le texte dont on veut les dimensions
		 *\param[in]	iMaxWidth	La largeur maximale du texte
		 *\param[out]	sizeText	Reçoit la taille calculée
		 *\param[in]	cFont		La police à utiliser pour calculer la taille
		 */
		virtual void GetFormattedTextExtent( String const & strText, int iMaxWidth, CSize & sizeText, Joker::CFont & cFont );
		/**
		 *\brief		Dessine un texte
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	cFont			La police utilisée pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte à dessiner
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limité
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual CSize DrawFormattedText( Joker::CFont & cFont, COLORREF cTextColour, String const & strText, CRect const & rcRect, UINT uiFormat, double dRatio = 1 );
		/**
		 *\brief		Dessine un texte
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Le texte est centré verticalement si possible (DT_VCENTER est ajouté au format)
		 *\param[in]	cFont			La police utilisée pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte à dessiner
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limité
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual CSize DrawNudeText( Joker::CFont & cFont, COLORREF cTextColour, String const & strText, CRect const & rcRect, UINT uiFormat, double dRatio = 1 );
		/**
		 *\brief		Dessine un texte encadré d'un rectangle inscrit dans le rectangle donné
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	cFont			La police utilisée pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte à dessiner
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limité
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawTextBox( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, Joker::CFont & cFont, COLORREF cTextColour, String const & strText, UINT uiFormat, CRect const & rcRect, double dRatio = 1 );
		/**
		 *\brief		Dessine un texte multiligne encadré d'un rectangle inscrit dans le rectangle donné
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	cFont			La police utilisée pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte à dessiner
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limité
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawFormattedTextBox( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, Joker::CFont & cFont, COLORREF cTextColour, String const & strText, UINT uiFormat, CRect const & rcRect, double dRatio = 1 );
		/**
		 *\brief		Dessine une checkbox grossière (un carré avec une croix si cochée)
		 *\remark		Utilise un ratio pour calculer les position et dimensions finales
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	x, y			Les coordonnées de la checkbox (hors ratio)
		 *\param[in]	iSize			La taille d'un côté de la case (hors ratio) (c'est un carré hein !)
		 *\param[in]	bChecked		Détermine si la case est ... (je vous le donne en 1000) ... cochée ou non
		 *\param[in]	dRatio			Le ratio d'affichage
		 *\return
		 */
		virtual void DrawCheckBox( int iPenHeight, COLORREF crPenColour, COLORREF crBrushColour, int x, int y, int iSize, BOOL bChecked = FALSE, double dRatio = 1 );
		/**
		 *\brief		Dessine un trait
		 *\param[in]	iPenHeight	La taille du crayon
		 *\param[in]	cPenColour	La couleur du crayon
		 *\param[in]	ptOrigin	Le point de départ du trait
		 *\param[in]	ptDest		Le point d'arrivée du trait
		 *\param[in]	iPenStyle	Le type de dessin du crayon (PS_SOLID par défaut)
		 */
		virtual void DrawLine( int iPenHeight, COLORREF cPenColour, CPoint const & ptOrigin, CPoint const & ptDest, int iPenStyle = PS_SOLID ) = 0;
		/**
		 *\brief		Dessine un trait
		 *\remark		Utilise le crayon et sa couleur courants
						<br />Utilise un ratio pour calculer les positions finales
		 *\param[in]	ptOrigin	Le point de départ du trait
		 *\param[in]	ptDest		Le point d'arrivée du trait
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		virtual void DrawLine( CPoint const & ptOrign, CPoint const & ptDest, double dRatio = 1 ) = 0;
		/**
		 *\brief		Dessine et remplit un rectangle, inscrit dans le rectangle donné
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	rcRect			Le rectangle à dessiner (hors ratio)
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawRect( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CRect const & rcRect, double dRatio = 1 ) = 0;
		/**
		 *\brief		Dessine un rectangle, inscrit dans le rectangle donné
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	rcRect			Le rectangle à dessiner (hors ratio)
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawVoidRect( int iPenHeight, COLORREF cPenColour, CRect const & rcRect, double dRatio ) = 0;
		/**
		 *\brief		Dessine un texte
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise la police et la couleur de premier plan courantes
		 *\param[in]	strText			Le texte à dessiner
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limité
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	dRatio			Le ratio d'affichage
		 *\return		La heauteur du texte
		 */
		virtual LONG DrawText( String const & strText, LPRECT pRect, UINT uiFormat, double dRatio = 1 ) = 0;
		/**
		 *\brief		Sélectionne la police donnée comme courante
		 *\param[in]	cFont	La police
		 */
		virtual void SetFont( Joker::CFont & ca2iFont ) = 0;
		/**
		 *\brief		Désélectionne la police donnée comme courante
		 *\param[in]	cFont	La police
		 */
		virtual void UnsetFont( Joker::CFont & ca2iFont ) = 0;
		/**
		 *\brief		Sélectionne le HPEN donné comme courant
		 *\param[in]	hPen	Le HPEN
		 *\return		Le HPEN précédemment sélectionné
		 */
		virtual HPEN SetPen( HPEN hPen ) = 0;
		/**
		 *\brief		Sélectionne le HBRUSH donné comme courant
		 *\param[in]	hBrush	Le HBRUSH
		 *\return		Le HBRUSH précédent
		 */
		virtual HBRUSH SetBrush( HBRUSH hBrush ) = 0;
		/**
		 *\brief		Sélectionne le HBITMAP donné comme courant
		 *\param[in]	hBitmap	Le HBITMAP
		 *\return		Le HBITMAP précédent
		 */
		virtual HBITMAP SetBitmap( HBITMAP hBitmap ) = 0;
		/**
		 *\brief		Définit la couleur de premier plan
		 *\param[in]	crColour	La couleur
		 *\return		L'ancienne couleur de premier plan
		 */
		virtual COLORREF SetForegroundColour( COLORREF crColour ) = 0;
		/**
		 *\brief		Définit la couleur d'arrière plan
		 *\param[in]	crColour	La couleur
		 *\return		L'ancienne couleur d'arrière plan
		 */
		virtual COLORREF SetBackgroundColour( COLORREF crColour ) = 0;
		/**
		 *\brief		Fait une copie des pixels du drawer donné dans ce drawer ci
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	pDrawer				La source
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	dwRop				L'opérateur utilisé lors du blit
		 */
		virtual void BitBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, DWORD dwRop ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels du drawer donné dans ce drawer ci
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	pDrawer				La source
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	dwRop				L'opérateur utilisé lors du blit
		 */
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels du drawer donné dans ce drawer ci, en utilisant une couleur particulière comme couleur transparente
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	pDrawer				La source
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	crTransparent		La couleur qui apparaîtra comme transparente
		 */
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent ) = 0;
		/**
		 *\brief		Définit l'image source courante
		 *\param[in]	pImage	L'image
		 */
		virtual void AttachImage( ImagePtr pImage ) = 0;
		/**
		 *\brief		Enlève l'image source courante
		 */
		virtual void DetachImage() = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	dwRop				L'opérateur utilisé lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( CRect const & rcDest, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	dwRop				L'opérateur utilisé lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	rcOrigin			Le rectangle de source
		 *\param[in]	dwRop				L'opérateur utilisé lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	dwRop				L'opérateur utilisé lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer, en utilisant une couleur particulière comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	crTransparent		La couleur qui apparaîtra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( CRect const & rcDest, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer, en utilisant une couleur particulière comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	crTransparent		La couleur qui apparaîtra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer, en utilisant une couleur particulière comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	rcOrigin			Le rectangle de source
		 *\param[in]	crTransparent		La couleur qui apparaîtra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( CRect const & rcDest, CRect const & rcOrigin, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionnée des pixels de l'image courante dans ce drawer, en utilisant une couleur particulière comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	crTransparent		La couleur qui apparaîtra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	rcDest		Le rectangle de la destination
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		virtual void AlphaBlend( CRect const & rcDest, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend d'une portion de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	rcDest		Le rectangle de la destination
		 *\param[in]	rcSource	Le rectangle de la source
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		virtual void AlphaBlend( CRect const & rcDest, CRect const & rcSource, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	dRatio				Le ratio d'affichage
		 */
		virtual void AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend d'une portion de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image préalablement attachée avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	dRatio				Le ratio d'affichage
		 */
		virtual void AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio = 1 ) = 0;
		/**
		 *\brief		Remplit un rectangle avec un pinceau donné
		 *\param[in]	pRect	Le rectangle
		 *\param[in]	hBrush	Le pinceau
		 */
		virtual void FillRect( RECT const * pRect, HBRUSH hBrush ) = 0;
		/**
		 *\brief		Dessine une ellipse
		 *\param[in]	left, top, right, bottom	Les dimensions de l'ellipse
		 */
		virtual void Ellipse( int left, int top, int right, int bottom ) = 0;
		/**
		 *\brief		Crée un drawer compatible (bitdepth, palette, ...) avec celui-ci
		 *\return		Le drawer créé
		 */
		virtual CDrawerBase * CreateCompatibleDrawer() = 0;
		/**
		 *\brief		Crée un bitmap compatible avec le contexte du drawer
		 *\param[in]	iWidth	La largeur du bitmap
		 *\param[in]	iHeight	La hauteur du bitmap
		 *\return		Le HBITMAP
		 */
		virtual HBITMAP CreateCompatibleBitmap( int iWidth, int iHeight ) = 0;

	private:
		void DoGetFormattedTextExtent( String const & strText, int iMaxWidth, CSize & sizeText );

	protected:
		//! Le rectangle concerné par le dessin
		CRect m_rcRect;
	};
}