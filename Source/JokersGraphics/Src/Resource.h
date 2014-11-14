#pragma once

#include "JokersGraphicsPrerequisites.h"

namespace Joker
{
	class JGRA_API CResource
	{
	protected:
		CResource( unsigned int uiID )
			:	m_iRef( 1 ),
				m_uiID( uiID )
		{
		}
		virtual ~CResource(){}

	public:
		void Ref()
		{
			m_iRef++;
		}

		int Release()
		{
			int iReturn = --m_iRef;

			if ( m_iRef <= 0 )
			{
				iReturn = 0;
			}

			return iReturn;
		}

		inline unsigned int GetId()const { return m_uiID; }

	protected:
		int m_iRef;				//!< The number of times this resource is used
		unsigned int m_uiID;	//!< The resource ID
	};
}