#include "SoundBoard.h"

SoundBoard::SoundBoard()
{
	if (this->crushBuffer.loadFromFile("audio/Crush.wav"))
		this->crushSound.setBuffer(this->crushBuffer);
	if (this->shootBuffer.loadFromFile("audio/Shoot.wav"))
		this->shootSound.setBuffer(this->shootBuffer);
	this->shootSound.setVolume(50);
}

void SoundBoard::playCrush()
{
	this->crushSound.play();
}

void SoundBoard::playShoot()
{
	this->shootSound.play();
}

bool SoundBoard::playMusic(std::string path)
{
	if (!this->music.openFromFile(path)) {
		return false;
	}
	this->music.play();
	return true;
}

void SoundBoard::setVolume(float volume)
{
	this->music.setVolume(volume);
}

void SoundBoard::stopMusic()
{
	if (!this->music.getStatus() != sf::Sound::Stopped)
		this->music.stop();
}