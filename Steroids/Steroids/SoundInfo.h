#pragma once
#include <SFML/Audio.hpp>
#include "CallbackContainer.h"

class SoundInfo
{
private:
	const sf::Int16* buffer;
	unsigned long len = 0;
	unsigned int sampleRate = 0;
	unsigned char channelCount = 0;

	float time;
	double bassLevel;

	CallbackContainer* cont = nullptr;

public:
	void update(float dt);
	float getBassLevel();
	void setSoundProgress(float sec);

	void setSoundBuffer(sf::SoundBuffer buf);
	void stopSound();


	template<class T> void setCallback(void (T::* callback)(), T* c)
	{
		this->cont = new TypedCallbackContainer<T>(callback, c);
	}

	void setCallback(void (*callback)())
	{
		this->cont = new VoidCallbackContainer(callback);
	}
};