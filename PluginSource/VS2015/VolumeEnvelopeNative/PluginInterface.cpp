#include "VolumeEnvelope.h"

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

extern "C"
{
	EXPORT_API VolumeEnvelope *VolumeEnvelope_New(double sampleDuration)
	{
		return new VolumeEnvelope(sampleDuration);
	}

	EXPORT_API void VolumeEnvelope_Delete(VolumeEnvelope *env)
	{
		delete env;
	}

	EXPORT_API void VolumeEnvelope_SetEnvelope(VolumeEnvelope *env, double startTime, double attackDuration, double sustainDuration, double releaseDuration)
	{
		if (env)
		{
			env->SetEnvelope(startTime, attackDuration, sustainDuration, releaseDuration);
		}
	}

	EXPORT_API void VolumeEnvelope_ProcessBuffer(VolumeEnvelope *env, float *buffer, int numSamples, int numChannels, double dspTime)
	{
		if (env)
		{
			env->ProcessBuffer(buffer, numSamples, numChannels, dspTime);
		}
	}

	EXPORT_API bool VolumeEnvelope_IsAvailable(VolumeEnvelope *env)
	{
		if (env)
		{
			return env->IsAvailable();
		}

		return false;
	}
}