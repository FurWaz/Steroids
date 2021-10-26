#include "SoundInfo.h"
#include <iostream>
#include <memory.h>

void SoundInfo::update(float dt)
{
	if (this->sampleRate == 0) return;
	float newTime = this->time + dt;
	double sum = 0;

	unsigned long startIndex = this->time * this->sampleRate * this->channelCount;
	unsigned long endIndex = newTime * this->sampleRate * this->channelCount;

	if (endIndex >= this->len || startIndex >= this->len)
	{
		endIndex = 0;
		startIndex = 0;
		this->sampleRate = 0;
		this->channelCount = 0;
		if (this->len > 0)
			delete this->buffer;
		if (this->cont != nullptr)
			this->cont->func();
	}

	for (unsigned long i = startIndex; i < endIndex; i++)
		sum += abs(this->buffer[i]);
	sum /= ((endIndex - startIndex) * 20000);
	this->bassLevel += (sum - this->bassLevel) * dt * 4;
	this->time = newTime;
}

float SoundInfo::getBassLevel()
{
	return this->bassLevel;
}

void SoundInfo::stopSound()
{
	this->time = (this->len / this->sampleRate); // just setting the time well after the song's end
}

void SoundInfo::setSoundBuffer(sf::SoundBuffer buf)
{
	this->len = buf.getSampleCount();
	this->sampleRate = buf.getSampleRate();
	this->channelCount = buf.getChannelCount();
	this->buffer = (sf::Int16*) malloc(sizeof(sf::Int16) * this->len);
	memcpy((void*)this->buffer, buf.getSamples(), this->len * sizeof(sf::Int16));
	this->time = 0;
}

void SoundInfo::setSoundProgress(float sec)
{
	this->time = sec;
}