#pragma once

#include <vector>
#include "EncodingOptions.h"

namespace Joker
{
	class CEncoderThread
	{
	public:
		CEncoderThread( CEncodingOptions * pEncodingOptions, std::vector< CString > const & arrayFiles );
		virtual ~CEncoderThread();

		void CreateThread();
		void StopThread();
		void EncodeFile( CString const & csFile );

	private:
		DWORD Run();
		static DWORD RunCallback( CEncoderThread * pThis );

	private:
		HANDLE m_hThread;
		HANDLE m_hEventEndList;
		HANDLE m_hEventEndFile;
		std::vector< CString > m_arrayFiles;
		CEncodingOptions * m_pEncodingOptions;
	};
}