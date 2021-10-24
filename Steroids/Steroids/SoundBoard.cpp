#include "SoundBoard.h"

SoundBoard::SoundBoard()
{
	if (this->crushBuffer.loadFromFile("audio/Crush.wav"))
		this->crushSound.setBuffer(this->crushBuffer);
	if (this->shootBuffer.loadFromFile("audio/Shoot.wav"))
		this->shootSound.setBuffer(this->shootBuffer);
	if (this->selectBuffer.loadFromFile("audio/Select.wav"))
		this->selectSound.setBuffer(this->selectBuffer);
	if (this->clickBuffer.loadFromFile("audio/Click.wav"))
		this->clickSound.setBuffer(this->clickBuffer);
	this->shootSound.setVolume(50);
	this->selectSound.setVolume(50);
	this->clickSound.setVolume(50);
}

void SoundBoard::playCrush()
{
	this->crushSound.play();
}

void SoundBoard::playSelect()
{
	this->selectSound.play();
}

void SoundBoard::playClick()
{
	this->clickSound.play();
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
	this->music.stop();
}