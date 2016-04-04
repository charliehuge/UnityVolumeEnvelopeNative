#pragma once
class VolumeEnvelope
{
public:
	VolumeEnvelope(double sampleDuration);
	
	~VolumeEnvelope();

	void SetEnvelope(double startTime, double attackDuration, double sustainDuration, double releaseDuration);

	void ProcessBuffer(float *buffer, int numSamples, int numChannels, double dspTime);

	bool IsAvailable();
private:
	double _sampleDuration;
	double _startTime;
	double _attackDuration;
	double _attackEndTime;
	double _sustainDuration;
	double _sustainEndTime;
	double _releaseDuration;
	double _releaseEndTime;
};

