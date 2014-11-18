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
	\remark	Permet de sp�cialiser le comportement d'un dessinateur selon qu'on dessine dans un DC, pdf ou autre
			<br />Classe virtuelle pure
	*/
	class JGRA_API CDrawerBase
	{
	public:
		/**
		 *\brief		Constructeur par d�faut
		 */
		CDrawerBase() {}
		/**
		 *\brief		Constructeur sp�cifi�
		 *\param[in]	rcRect	Le rectangle concern� par le dessin
		 */
		CDrawerBase( CRect const & rcRect ) : m_rcRect( rcRect ) {}
		/**
		 *\brief		Constructeur par copie
		 *\param[in]	drawer	Le dessinateur � copier
		 */
		CDrawerBase( CDrawerBase const & drawer ) : m_rcRect( drawer.m_rcRect ) {}
		/**
		 *\brief		Destructeur
		 */
		virtual ~CDrawerBase() {}
		/**
		 *\brief		Cr�e un buffer temporaire dans lequel les op�rations seront effectu�es
		 *\remark		Pour que les modifications soient appliqu�es au contexte de rendu, il faut appeler Finalise
		 *\param[in]	rcRect	Les dimensions du buffer temporaire
		 */
		virtual void CreateBackbuffer( CRect const & rcRect ) = 0;
		/**
		 *\brief		Applique les op�rations du backbuffer au contexte de rendu, d�truit le backbuffer
		 *\remark		Pour que cette fonction ait un effet, il faut que CreateBackbuffer ait �t� appel�e
		 */
		virtual void Finalise() = 0;
		/**
		 *\brief		Formatte un texte en fonction d'une largeur maximale, d'une police et d'un ratio. remplit les variables rcRect et strFormatted
		 *\param[out]	rcRect			Re�oit le rectangle contenant le texte
		 *\param[in]	iWidth			La largeur maximale du texte
		 *\param[in]	strUnformatted	Le texte avant formattage
		 *\param[out]	strFormatted	Re�oit le texte formatt�
		 *\param[in]	cFont			La police � utiliser pour calculer la taille
		 *\param[in]	dRatio			Le ratio d'affichage (1 dans une fen�tre, plus quand on imprime)
		 *\param[in]	uiFormat		Le type de d�coupe si DT_WORDBREAK, d�coupe par mot, sinon d�coupe par lettre (par d�faut vaut DT_WORDBREAK)
		 *\return		Le nombre de lignes du texte formatt�
		 */
		virtual int FormatText( CRect & rcRect, int iWidth, String const & strUnformatted, String & strFormatted, Joker::CFont & cFont, double dRatio, UINT uiFormat = DT_WORDBREAK );
		/**
		 *\brief		R�cup�re les dimensions maximales du texte pass� en argument dans le contexte donn�.
		 *\remark		Ne tient pas compte des lignes, utilise la police courante
		 *\param[in]	strText		Le texte dont on veut avoir les dimensions
		 *\param[out]	sizeText	Re�oit la taille du texte
		 */
		virtual void GetTextExtent( String const & strText, CSize & sizeText );
		/**
		 *\brief		R�cup�re les dimensions maximales du texte pass� en argument dans le contexte donn� et la police donn�e.
		 *\remark		Prend les lignes en compte, utilise la police donn�e
		 *\param[in]	strText		Le texte dont on veut les dimensions
		 *\param[in]	iMaxWidth	La largeur maximale du texte
		 *\param[out]	sizeText	Re�oit la taille calcul�e
		 *\param[in]	cFont		La police � utiliser pour calculer la taille
		 */
		virtual void GetFormattedTextExtent( String const & strText, int iMaxWidth, CSize & sizeText, Joker::CFont & cFont );
		/**
		 *\brief		Dessine un texte
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	cFont			La police utilis�e pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte � dessiner
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limit�
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual CSize DrawFormattedText( Joker::CFont & cFont, COLORREF cTextColour, String const & strText, CRect const & rcRect, UINT uiFormat, double dRatio = 1 );
		/**
		 *\brief		Dessine un texte
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Le texte est centr� verticalement si possible (DT_VCENTER est ajout� au format)
		 *\param[in]	cFont			La police utilis�e pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte � dessiner
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limit�
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual CSize DrawNudeText( Joker::CFont & cFont, COLORREF cTextColour, String const & strText, CRect const & rcRect, UINT uiFormat, double dRatio = 1 );
		/**
		 *\brief		Dessine un texte encadr� d'un rectangle inscrit dans le rectangle donn�
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	cFont			La police utilis�e pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte � dessiner
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limit�
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawTextBox( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, Joker::CFont & cFont, COLORREF cTextColour, String const & strText, UINT uiFormat, CRect const & rcRect, double dRatio = 1 );
		/**
		 *\brief		Dessine un texte multiligne encadr� d'un rectangle inscrit dans le rectangle donn�
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	cFont			La police utilis�e pour dessiner le texte
		 *\param[in]	cTextColour		La couleur du texte
		 *\param[in]	strText			Le texte � dessiner
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limit�
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawFormattedTextBox( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, Joker::CFont & cFont, COLORREF cTextColour, String const & strText, UINT uiFormat, CRect const & rcRect, double dRatio = 1 );
		/**
		 *\brief		Dessine une checkbox grossi�re (un carr� avec une croix si coch�e)
		 *\remark		Utilise un ratio pour calculer les position et dimensions finales
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	x, y			Les coordonn�es de la checkbox (hors ratio)
		 *\param[in]	iSize			La taille d'un c�t� de la case (hors ratio) (c'est un carr� hein !)
		 *\param[in]	bChecked		D�termine si la case est ... (je vous le donne en 1000) ... coch�e ou non
		 *\param[in]	dRatio			Le ratio d'affichage
		 *\return
		 */
		virtual void DrawCheckBox( int iPenHeight, COLORREF crPenColour, COLORREF crBrushColour, int x, int y, int iSize, BOOL bChecked = FALSE, double dRatio = 1 );
		/**
		 *\brief		Dessine un trait
		 *\param[in]	iPenHeight	La taille du crayon
		 *\param[in]	cPenColour	La couleur du crayon
		 *\param[in]	ptOrigin	Le point de d�part du trait
		 *\param[in]	ptDest		Le point d'arriv�e du trait
		 *\param[in]	iPenStyle	Le type de dessin du crayon (PS_SOLID par d�faut)
		 */
		virtual void DrawLine( int iPenHeight, COLORREF cPenColour, CPoint const & ptOrigin, CPoint const & ptDest, int iPenStyle = PS_SOLID ) = 0;
		/**
		 *\brief		Dessine un trait
		 *\remark		Utilise le crayon et sa couleur courants
						<br />Utilise un ratio pour calculer les positions finales
		 *\param[in]	ptOrigin	Le point de d�part du trait
		 *\param[in]	ptDest		Le point d'arriv�e du trait
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		virtual void DrawLine( CPoint const & ptOrign, CPoint const & ptDest, double dRatio = 1 ) = 0;
		/**
		 *\brief		Dessine et remplit un rectangle, inscrit dans le rectangle donn�
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	cBrushColour	La couleur du pinceau de remplissage
		 *\param[in]	rcRect			Le rectangle � dessiner (hors ratio)
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawRect( int iPenHeight, COLORREF cPenColour, COLORREF cBrushColour, CRect const & rcRect, double dRatio = 1 ) = 0;
		/**
		 *\brief		Dessine un rectangle, inscrit dans le rectangle donn�
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
		 *\param[in]	iPenHeight		La taille du crayon
		 *\param[in]	cPenColour		La couleur du crayon
		 *\param[in]	rcRect			Le rectangle � dessiner (hors ratio)
		 *\param[in]	dRatio			Le ratio d'affichage
		 */
		virtual void DrawVoidRect( int iPenHeight, COLORREF cPenColour, CRect const & rcRect, double dRatio ) = 0;
		/**
		 *\brief		Dessine un texte
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise la police et la couleur de premier plan courantes
		 *\param[in]	strText			Le texte � dessiner
		 *\param[in]	rcRect			Le rectangle dans lequel le texte est limit�
		 *\param[in]	uiFormat		Le format du texte (DT_CENTER, ... )
		 *\param[in]	dRatio			Le ratio d'affichage
		 *\return		La heauteur du texte
		 */
		virtual LONG DrawText( String const & strText, LPRECT pRect, UINT uiFormat, double dRatio = 1 ) = 0;
		/**
		 *\brief		S�lectionne la police donn�e comme courante
		 *\param[in]	cFont	La police
		 */
		virtual void SetFont( Joker::CFont & ca2iFont ) = 0;
		/**
		 *\brief		D�s�lectionne la police donn�e comme courante
		 *\param[in]	cFont	La police
		 */
		virtual void UnsetFont( Joker::CFont & ca2iFont ) = 0;
		/**
		 *\brief		S�lectionne le HPEN donn� comme courant
		 *\param[in]	hPen	Le HPEN
		 *\return		Le HPEN pr�c�demment s�lectionn�
		 */
		virtual HPEN SetPen( HPEN hPen ) = 0;
		/**
		 *\brief		S�lectionne le HBRUSH donn� comme courant
		 *\param[in]	hBrush	Le HBRUSH
		 *\return		Le HBRUSH pr�c�dent
		 */
		virtual HBRUSH SetBrush( HBRUSH hBrush ) = 0;
		/**
		 *\brief		S�lectionne le HBITMAP donn� comme courant
		 *\param[in]	hBitmap	Le HBITMAP
		 *\return		Le HBITMAP pr�c�dent
		 */
		virtual HBITMAP SetBitmap( HBITMAP hBitmap ) = 0;
		/**
		 *\brief		D�finit la couleur de premier plan
		 *\param[in]	crColour	La couleur
		 *\return		L'ancienne couleur de premier plan
		 */
		virtual COLORREF SetForegroundColour( COLORREF crColour ) = 0;
		/**
		 *\brief		D�finit la couleur d'arri�re plan
		 *\param[in]	crColour	La couleur
		 *\return		L'ancienne couleur d'arri�re plan
		 */
		virtual COLORREF SetBackgroundColour( COLORREF crColour ) = 0;
		/**
		 *\brief		Fait une copie des pixels du drawer donn� dans ce drawer ci
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	pDrawer				La source
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	dwRop				L'op�rateur utilis� lors du blit
		 */
		virtual void BitBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, DWORD dwRop ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels du drawer donn� dans ce drawer ci
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	pDrawer				La source
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	dwRop				L'op�rateur utilis� lors du blit
		 */
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels du drawer donn� dans ce drawer ci, en utilisant une couleur particuli�re comme couleur transparente
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	pDrawer				La source
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	crTransparent		La couleur qui appara�tra comme transparente
		 */
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, CDrawerBase * pDrawer, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent ) = 0;
		/**
		 *\brief		D�finit l'image source courante
		 *\param[in]	pImage	L'image
		 */
		virtual void AttachImage( ImagePtr pImage ) = 0;
		/**
		 *\brief		Enl�ve l'image source courante
		 */
		virtual void DetachImage() = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	dwRop				L'op�rateur utilis� lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( CRect const & rcDest, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	dwRop				L'op�rateur utilis� lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	rcOrigin			Le rectangle de source
		 *\param[in]	dwRop				L'op�rateur utilis� lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( CRect const & rcDest, CRect const & rcOrigin, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	dwRop				L'op�rateur utilis� lors du blit
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void StretchBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, DWORD dwROP, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer, en utilisant une couleur particuli�re comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	crTransparent		La couleur qui appara�tra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( CRect const & rcDest, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer, en utilisant une couleur particuli�re comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	crTransparent		La couleur qui appara�tra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer, en utilisant une couleur particuli�re comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	rcDest				Le rectangle de destination
		 *\param[in]	rcOrigin			Le rectangle de source
		 *\param[in]	crTransparent		La couleur qui appara�tra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( CRect const & rcDest, CRect const & rcOrigin, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait une copie redimensionn�e des pixels de l'image courante dans ce drawer, en utilisant une couleur particuli�re comme couleur transparente
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	crTransparent		La couleur qui appara�tra comme transparente
		 *\param[in]	dRatio				Le ratio
		 */
		virtual void TransparentBlt( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, COLORREF crTransparent, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	rcDest		Le rectangle de la destination
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		virtual void AlphaBlend( CRect const & rcDest, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend d'une portion de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	rcDest		Le rectangle de la destination
		 *\param[in]	rcSource	Le rectangle de la source
		 *\param[in]	dRatio		Le ratio d'affichage
		 */
		virtual void AlphaBlend( CRect const & rcDest, CRect const & rcSource, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	dRatio				Le ratio d'affichage
		 */
		virtual void AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, double dRatio = 1 ) = 0;
		/**
		 *\brief		Fait un alpha blend d'une portion de l'image courante dans le contexte courant
		 *\remark		Utilise un ratio pour calculer les position et dimensions du rectangle final
						<br />Utilise l'image pr�alablement attach�e avec AttachImage
		 *\param[in]	xDest, yDest		La position de destination
		 *\param[in]	cxDest, cyDest		La taille de destination
		 *\param[in]	xOrigin, yOrigin	La position de source
		 *\param[in]	cxOrigin, cyOrigin	La taille de source
		 *\param[in]	dRatio				Le ratio d'affichage
		 */
		virtual void AlphaBlend( int xDest, int yDest, int cxDest, int cyDest, int xOrigin, int yOrigin, int cxOrigin, int cyOrigin, double dRatio = 1 ) = 0;
		/**
		 *\brief		Remplit un rectangle avec un pinceau donn�
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
		 *\brief		Cr�e un drawer compatible (bitdepth, palette, ...) avec celui-ci
		 *\return		Le drawer cr��
		 */
		virtual CDrawerBase * CreateCompatibleDrawer() = 0;
		/**
		 *\brief		Cr�e un bitmap compatible avec le contexte du drawer
		 *\param[in]	iWidth	La largeur du bitmap
		 *\param[in]	iHeight	La hauteur du bitmap
		 *\return		Le HBITMAP
		 */
		virtual HBITMAP CreateCompatibleBitmap( int iWidth, int iHeight ) = 0;

	private:
		void DoGetFormattedTextExtent( String const & strText, int iMaxWidth, CSize & sizeText );

	protected:
		//! Le rectangle concern� par le dessin
		CRect m_rcRect;
	};
}