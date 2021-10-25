#pragma once
#include <SFML/Audio.hpp>

class SoundBoard
{
private:
	sf::SoundBuffer crushBuffer;
	sf::SoundBuffer shootBuffer;
	sf::SoundBuffer selectBuffer;
	sf::SoundBuffer clickBuffer;
	sf::Sound crushSound;
	sf::Sound shootSound;
	sf::Sound selectSound;
	sf::Sound clickSound;
	sf::Music music;
	sf::SoundBuffer musicBuffer;

public:
	SoundBoard();
	void playCrush();
	void playShoot();
	void playSelect();
	void playClick();
	bool playMusic(std::string path);
	void setVolume(float volume);
	void stopMusic();
	sf::SoundBuffer getMusicBuffer();
};