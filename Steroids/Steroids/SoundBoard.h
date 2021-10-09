#pragma once
#include <SFML/Audio.hpp>

class SoundBoard
{
private:
	sf::SoundBuffer crushBuffer;
	sf::SoundBuffer shootBuffer;
	sf::Sound crushSound;
	sf::Sound shootSound;
	sf::Music music;

public:
	SoundBoard();
	void playCrush();
	void playShoot();
	bool playMusic(std::string path);
	void setVolume(float volume);
	void stopMusic();
};