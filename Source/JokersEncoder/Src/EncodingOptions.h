#pragma once

namespace Joker
{
	typedef enum
	{
		eSTEREO_MODE_STANDARD,
		eSTEREO_MODE_JOINT,
		eSTEREO_MODE_DUAL,
		eSTEREO_MODE_MONO,
	}	eSTEREO_MODE;

	class CEncodingOptions
	{
	public:
		CEncodingOptions()
			: bVbr( false )
			, iCbrBitRate( 160 )
			, iVbrMinBitRate( 160 )
			, iVbrMaxBitRate( 160 )
			, iVbrQuality( 5 )
			, bVbrEnforceStrictlyMin( false )
			, bVbrEnableXingTag( false )
			, iEncodingQuality( 0 )
			, iSampleRate( 22050 )
			, bVoiceEncodingMode( false )
			, bKeepAllFrequancies( false )
			, bStrictISOComplience( false )
			, bDisableShortBlocks( false )
			, bModeFixed( false	)
			, eStereoMode( eSTEREO_MODE_STANDARD )
			, bForcedMidSideStereo( false )
		{
		}

	public:
		bool bVbr;
		int iCbrBitRate;
		int iVbrMinBitRate;
		int iVbrMaxBitRate;
		int iVbrQuality;
		bool bVbrEnforceStrictlyMin;
		bool bVbrEnableXingTag;
		int iEncodingQuality;
		int iSampleRate;
		bool bVoiceEncodingMode;
		bool bKeepAllFrequancies;
		bool bStrictISOComplience;
		bool bDisableShortBlocks;
		bool bModeFixed;
		eSTEREO_MODE eStereoMode;
		bool bForcedMidSideStereo;
	};
}