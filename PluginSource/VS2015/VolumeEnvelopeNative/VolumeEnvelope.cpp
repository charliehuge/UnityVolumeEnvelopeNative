#include "VolumeEnvelope.h"
#include <math.h>


VolumeEnvelope::VolumeEnvelope(double sampleDuration)
{
	_sampleDuration = sampleDuration;
	_startTime = -1;
}


VolumeEnvelope::~VolumeEnvelope()
{
}

void VolumeEnvelope::SetEnvelope(double startTime, double attackDuration, double sustainDuration, double releaseDuration)
{
	_startTime = startTime;
	_attackDuration = attackDuration;
	_attackEndTime = startTime + attackDuration;
	_sustainDuration = sustainDuration;
	_sustainEndTime = _attackEndTime + sustainDuration;
	_releaseDuration = releaseDuration;
	_releaseEndTime = _sustainEndTime + releaseDuration;
}

void VolumeEnvelope::ProcessBuffer(float *buffer, int numSamples, int numChannels, double dspTime)
{
	if (IsAvailable() || (dspTime + _sampleDuration * numSamples / numChannels) < _startTime)
	{
		for (int i = 0; i < numSamples; ++i)
		{
			buffer[i] = 0;
		}
		return;
	}

	float volume = 0;
	int i, j;

	for (i = 0; i < numSamples; i += numChannels)
	{
		if (_startTime < 0 || dspTime < _startTime)
		{
			for (j = 0; j < numChannels; ++j)
			{
				buffer[i + j] = 0;
			}
		}
		else if (_attackDuration > 0 && dspTime < _attackEndTime)
		{
			volume = (float)pow((dspTime - _startTime) / _attackDuration, 4);
			
			for (j = 0; j < numChannels; ++j)
			{
				buffer[i + j] *= volume;
			}
		}
		else if (dspTime < _sustainEndTime)
		{
			// do nothing (no attenuation)
		}
		else if (_releaseDuration > 0 && dspTime < _releaseEndTime)
		{
			volume = (float)pow((_releaseEndTime - dspTime) / _releaseDuration, 4);
			
			for (j = 0; j < numChannels; ++j)
			{
				buffer[i + j] *= volume;
			}
		}
		else
		{
			for (j = 0; j < numChannels; ++j)
			{
				buffer[i + j] = 0;
			}

			_startTime = -1;
		}

		dspTime += _sampleDuration;
	}
}

bool VolumeEnvelope::IsAvailable()
{
	return _startTime < 0;
}
