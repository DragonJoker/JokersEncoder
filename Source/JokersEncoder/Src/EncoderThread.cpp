#include "stdafx.h"

#include "EncoderThread.h"

using namespace Joker;

#define DEF_TIMEOUT	1000

//*************************************************************************************************

CEncoderThread::CEncoderThread( CEncodingOptions * pEncodingOptions, std::vector< CString > const & arrayFiles )
	:	m_arrayFiles( arrayFiles )
	,	m_pEncodingOptions( pEncodingOptions )
	,	m_hEventEndFile( NULL )
	,	m_hEventEndList( NULL )
	,	m_hThread( NULL )
{
}

CEncoderThread::~CEncoderThread()
{
}

void CEncoderThread::CreateThread()
{
	m_hEventEndFile = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hEventEndList = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hThread = ::CreateThread( NULL, 0, LPTHREAD_START_ROUTINE( RunCallback ), this, 0, NULL );
}

void CEncoderThread::StopThread()
{
	if ( m_hEventEndList && m_hThread )
	{
		::SetEvent( m_hEventEndList );

		if ( ::WaitForSingleObject( m_hThread, DEF_TIMEOUT ) == WAIT_TIMEOUT )
		{
			::TerminateThread( m_hThread, 0xFFFFFFFF );
			m_hThread = NULL;
		}

		::CloseHandle( m_hEventEndList );
		m_hEventEndList = NULL;

		::CloseHandle( m_hEventEndFile );
		m_hEventEndFile = NULL;
	}
}

void CEncoderThread::EncodeFile( CString const & csFile )
{
	/*
		std::ifstream l_inFile( csFile, std::ios::binary);

		if( l_inFile )
		{
			//read the 12 character in front of the file
			l_inFile.read( (char *) & startID, sizeof( startID));

			//get the format chunk
			FormatChunk l_formatChunk;
			long l_formatChunkSize = sizeof( FormatChunk);

			l_inFile.read( (char *) & l_formatChunk, l_formatChunkSize);
			// the first chunk MUST be the format chunk
			if (strncmp( l_formatChunk.chunkID, "fmt ", 4) != 0)
			{
				Application->MessageBox( "This is not a valid Wave file",
					"Wav2Mp3 ERROR", MB_OK);
				return;
			}
			if (l_formatChunk.wFormatTag!=1)
			{
				Application->MessageBox( "Cannot handle compressed Wave file",
					"Wav2Mp3 ERROR", MB_OK);
				return;
			}

			// initialization of Mp3 encoder
			BE_CONFIG l_config;
			l_config.dwConfig = BE_CONFIG_LAME;
			l_config.format.LHV1.dwStructVersion = 1;
			l_config.format.LHV1.dwStructSize = sizeof( l_config);

			if (l_formatChunk.dwSamplesPerSec == 8000 || l_formatChunk.dwSamplesPerSec == 11025 ||
				l_formatChunk.dwSamplesPerSec == 12000 || l_formatChunk.dwSamplesPerSec == 16000 ||
				l_formatChunk.dwSamplesPerSec == 22050 || l_formatChunk.dwSamplesPerSec == 24000 ||
				l_formatChunk.dwSamplesPerSec == 32000 || l_formatChunk.dwSamplesPerSec == 44100 ||
				l_formatChunk.dwSamplesPerSec == 48000)
			{
				l_config.format.LHV1.dwSampleRate = l_formatChunk.dwSamplesPerSec;
				l_config.format.LHV1.dwReSampleRate = m_encodingOptions->m_sampleRate;
			}
			else
			{
				Application->MessageBox( "Unsuported sample rate",
					"Wav2Mp3 ERROR", MB_OK);
				return;
			}

			if (m_encodingOptions->m_vbr)
			{
				Console( "VBR - Bitrates : " + AnsiString(m_encodingOptions->m_vbrMinBitRate) + " - "  + AnsiString(m_encodingOptions->m_vbrMaxBitRate));
				l_config.format.LHV1.bEnableVBR = TRUE;
				l_config.format.LHV1.dwBitrate = m_encodingOptions->m_vbrMinBitRate;
				l_config.format.LHV1.dwMaxBitrate = m_encodingOptions->m_vbrMaxBitRate;
				l_config.format.LHV1.nVBRQuality = 8 - m_encodingOptions->m_vbrQuality;
				if (m_encodingOptions->m_vbrEnableXingTag)
				{
					l_config.format.LHV1.bWriteVBRHeader = FALSE;
				}
			}
			else
			{
				Console( "CBR - Bitrate : " + AnsiString(m_encodingOptions->m_cbrBitRate));
				l_config.format.LHV1.bEnableVBR = FALSE;
				l_config.format.LHV1.dwBitrate = m_encodingOptions->m_cbrBitRate;
			}

			l_config.format.LHV1.nQuality = m_encodingOptions->m_encodingQuality;
			l_config.format.LHV1.nPreset = LQP_NORMAL_QUALITY;
			l_config.format.LHV1.dwMpegVersion = MPEG1;
			l_config.format.LHV1.dwPsyModel = 0;
			l_config.format.LHV1.dwEmphasis = 0;

			if (m_encodingOptions->m_stereoMode == Mono)
			{
				l_config.format.LHV1.nMode = BE_MP3_MODE_MONO;
			}
			else if (m_encodingOptions->m_stereoMode == StandardStereo)
			{
				l_config.format.LHV1.nMode = BE_MP3_MODE_STEREO;
			}
			else if (m_encodingOptions->m_stereoMode == DualChannel)
			{
				l_config.format.LHV1.nMode = BE_MP3_MODE_DUALCHANNEL;
			}
			else if (m_encodingOptions->m_stereoMode == JointStereo)
			{
				l_config.format.LHV1.nMode = BE_MP3_MODE_JSTEREO;
			}

			if (m_encodingOptions->m_strictISOComplience)
			{
				l_config.format.LHV1.bStrictIso = TRUE;
			}
			else
			{
				l_config.format.LHV1.bStrictIso = FALSE;
			}

			l_config.format.LHV1.bCopyright = FALSE;
			l_config.format.LHV1.bCRC = FALSE;
			l_config.format.LHV1.bOriginal = FALSE;
			l_config.format.LHV1.bPrivate = FALSE;
			l_config.format.LHV1.bNoRes = TRUE;

			//skip extra formatchunk parameter, if any
			if (l_formatChunkSize < 8 + l_formatChunk.chunkSize)
			{
				char c;
				for (int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < 8 + l_formatChunk.chunkSize - l_formatChunkSize ; GL2D_SIZE_I++)
				{
					l_inFile.get( c);
				}
			}

			//get next chunk
			Chunk l_chunk;
			long l_chunkSize = sizeof( Chunk);
			l_inFile.read( (char*) & l_chunk, l_chunkSize);
			//check if it's the data chunk
			while (strncmp( l_chunk.chunkID, "data", 4) != 0)
			{
				char c;
				for (int GL2D_SIZE_I = 0 ; GL2D_SIZE_I < l_chunk.chunkSize ; GL2D_SIZE_I++)
				{
					l_inFile.get( c);
				}
				l_inFile.read((char*) & l_chunk, l_chunkSize);
			}

			//process with the encoding
			unsigned long l_numberOfSamples;
			unsigned long l_outputBufferLength;
			HBE_STREAM l_hbeStream;
			if (beInitStream( & l_config, & l_numberOfSamples, & l_outputBufferLength,
				& l_hbeStream) != BE_ERR_SUCCESSFUL)
			{
				Application->MessageBox( "Cannot perform compression",
					"Wav2Mp3 ERROR",MB_OK);
				return;
			}
			std::ofstream l_outFile( m_outFileName.c_str(), std::ios::binary);
			unsigned char * l_mp3Buffer = new unsigned char[ l_outputBufferLength];
			short * l_inputBuffer = new short[l_numberOfSamples];      //SHORT=short=16 bits

			int l_samplesPerformed = 0;
			unsigned long l_numberOfSamplesEncoded;
			while (l_samplesPerformed < l_chunk.chunkSize)
			{
				l_inFile.read( (char*) l_inputBuffer, l_numberOfSamples * 2);
				l_samplesPerformed += l_numberOfSamples * 2;
				FormEncode->PBStatus->Position = 100 * ((l_samplesPerformed * 1.0) / l_chunk.chunkSize);
				if (beEncodeChunk( l_hbeStream, l_numberOfSamples, l_inputBuffer,
					l_mp3Buffer, & l_numberOfSamplesEncoded) != BE_ERR_SUCCESSFUL)
				{
					Application->MessageBox( "Cannot perform compression",
						"Wav2Mp3 ERROR",MB_OK);
					return;
				}
				l_outFile.write((char *)l_mp3Buffer, l_numberOfSamplesEncoded);
			}
			beDeinitStream( l_hbeStream, l_mp3Buffer, & l_numberOfSamplesEncoded);
			beCloseStream( l_hbeStream);

			delete l_mp3Buffer;
			delete l_inputBuffer;
		}
	*/
}

DWORD CEncoderThread::Run()
{
	DWORD dwReturn = 0;
	DWORD dwResult;

	do
	{
		dwResult = ::WaitForSingleObject( m_hEventEndList, DEF_TIMEOUT );

		if ( dwResult == WAIT_OBJECT_0 )
		{
			CString csFile = m_arrayFiles[0];
			m_arrayFiles.erase( m_arrayFiles.begin() );
			EncodeFile( csFile );
		}
	}
	while ( dwReturn < 0 );

	return dwReturn;
}

DWORD CEncoderThread::RunCallback( CEncoderThread * pThis )
{
	DWORD dwReturn = pThis->Run();
	return dwReturn;
}

//*************************************************************************************************