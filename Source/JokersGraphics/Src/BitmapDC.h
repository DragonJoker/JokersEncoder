#pragma once

#include "Colour.h"

namespace Joker
{
	/*!
	Classe d'aide pour les HDC auxquels on attache un HBITMAP (pour le double buffering et autres)
	Inclut quelques fonctions de dessin de texte et de rectangle
	2 méthodes : Créer le HBITMAP en interne via la fonction CreateBitmap, ou utiliser un HBITMAP existant via le couple Attach / Detach
	\author Sylvain DOREMUS
	\date 13/11/2011
	*/
	class JGRA_API CBitmapDC
	{
	public:
		/**@name Construction / Destruction */
		//@{
		CBitmapDC( HDC hDC );
		virtual ~CBitmapDC();
		//@}
		/**
		 *@remark N'effectue pas réellement une copie mais crée un CBitmapDC en utilisant bmpDC.m_hDC en tant que DC de base
		 */
		CBitmapDC( CBitmapDC const & bmpDC );
		/**
		 *@remark N'effectue pas réellement une copie mais crée un CBitmapDC en utilisant bmpDC.m_hDC en tant que DC de base
		 */
		CBitmapDC & operator =( CBitmapDC const & bmpDC );
		/**
		 * Attache un HBITMAP existant à ce DC
		 *@param hBitmap : [in] Le HBITMAP à attacher
		 */
		void Attach( HBITMAP hBitmap );
		/**
		 * Détache le HBITMAP précédemment attaché à ce DC
		 *@return Le HBITMAP qui était attaché
		 */
		HBITMAP Detach();
		/**
		 * Crée un HBITMAP et l'attache au DC (avec SelectObject)
		 *@param rcRect : [in] La taille du HBITMAP à créer
		 */
		void CreateBitmap( CRect const & rcRect );
		/**
		 * Remplit le rectangle donné avec la couleur donnée
		 *@param crColour : [in] La couleur de remplissage
		 *@param rcRect : [in] Le rectangle à remplir
		 */
		void FillSolidRect( CColour clColour, CRect rcRect );
		/**
		 * Dessine un texte avec la police et la couleur donnés
		 *@param hFont : [in] La police de dessin
		 *@param crColour : [in] La couleur du texte
		 *@param csText : [in] Le texte
		 *@param rcRect : [in] Le rectangle où le texte doit être dessiné
		 *@param dwStyle : [in] Le style du texte (cf. CDC::DrawText)
		 */
		void DrawSolidText( HFONT hFont, LOGFONT logFont, CColour clColour, CString const & csText, CRect rcRect, DWORD dwStyle );
		/**
		 * Dessine le contour d'un rectangle
		 *@param rcRect : [in] Le rectangle
		 *@param crColour : [in] La couleur du trait
		 *@param iWidth : [in] L'épaisseur du trait
		 *@param uiStyle : [in] Le style de trait (cf. styles de LOGPEN)
		 */
		void FrameRect( CRect const & rcRect, CColour clColour, int iWidth = 1, UINT uiStyle = PS_SOLID );
		/**
		 * Alpha blend d'un HDC vers celui-ci
		 *@param rcDest : [in] Le rectangle de destination
		 *@param hSrcDC : [in] Le HDC source
		 *@param rcSrc : [in] Le rectangle de source
		 *@param blendFunc : [in] La fonction de blending
		 */
		void AlphaBlend( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, BLENDFUNCTION blendFunc );
		/**
		 * Blit un dc dans celui-ci
		 *@param rcDest : [in] La section de la destination
		 *@param srcDC : [in] Le DC source
		 *@param rcSrc : [in] La section de la source
		 */
		void BitBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, DWORD dwRop );
		/**
		 * Stretch Blit un dc dans celui-ci
		 *@param rcDest : [in] La section de la destination
		 *@param srcDC : [in] Le DC source
		 *@param rcSrc : [in] La section de la source
		 */
		void StretchBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, DWORD dwRopt );
		/**
		 * Transparent Blit un dc dans celui-ci
		 *@param rcDest : [in] La section de la destination
		 *@param srcDC : [in] Le DC source
		 *@param rcSrc : [in] La section de la source
		 */
		void TransparentBlt( CRect const & rcDest, CBitmapDC & srcDC, CRect const & rcSrc, CColour const & clTransparent );
		void DrawBitmap( CRect const & rcDest, HBITMAP hBitmap, CRect const & rcBitmap );
		/**@name Opérateurs de conversion */
		//@{
		inline operator HDC()const
		{
			return m_hDC;
		}
		inline operator HBITMAP()const
		{
			return m_hBitmap;
		}
		//@}

	protected:
		void Release();
		void ReleaseBitmap();
		void SelectBitmap();

	private:
		HDC m_hBaseDC;
		HDC m_hDC;
		HBITMAP m_hBitmap;
		bool m_bOwnBitmap;
	};
}