#pragma once

#include "WndLayout.h"

namespace Joker
{
	typedef enum eHORIZ_ALIGN
	{
		eHORIZ_ALIGN_LEFT,
		eHORIZ_ALIGN_CENTER,
		eHORIZ_ALIGN_RIGHT
	}	eHORIZ_ALIGN;

	typedef enum eVERTIC_ALIGN
	{
		eVERTIC_ALIGN_TOP,
		eVERTIC_ALIGN_CENTER,
		eVERTIC_ALIGN_BOTTOM
	}	eVERTIC_ALIGN;

	class JGRA_API CScalableLayout
		: public CWndLayout
	{
	protected:
		class CElement
		{
		private:
			HWND m_hElement;
			POINT m_ptLTOriginal;
			POINT m_ptRBOriginal;
			SIZE m_sizeOriginal;
			LPRECT m_rcFixed;
			bool m_scalable;
			eHORIZ_ALIGN m_horizAlign;
			eVERTIC_ALIGN m_verticAlign;

		public:
			CElement( HWND hElement, HWND hParent, LPRECT rcFixed, bool scalable, eHORIZ_ALIGN horiz, eVERTIC_ALIGN vertic );

			void Resize( double dX, double dY, LPRECT rcMaxExtent );
		};

		typedef std::map< UINT, CElement > ElementMap;
		ElementMap m_mapElements;

	public:
		CScalableLayout();
		virtual ~CScalableLayout();

		void AddElement( UINT uiId, HWND hElement, bool scalable = true, eHORIZ_ALIGN horiz = eHORIZ_ALIGN_CENTER, eVERTIC_ALIGN vertic = eVERTIC_ALIGN_CENTER );
		void AddElement( UINT uiId, bool scalable = true, eHORIZ_ALIGN horiz = eHORIZ_ALIGN_CENTER, eVERTIC_ALIGN vertic = eVERTIC_ALIGN_CENTER );
		void RemoveElement( UINT uiId );
		void Flush();

	protected:
		virtual void DoResize();
	};
}