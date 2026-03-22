#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Background.h"
#include "UI.h"
#include "Gameplay.h"
#include "Menu.h"
#include "GameOver.h"
#include "PauseScreen.h"

using namespace std;
using namespace sf;

class Game {

private:

	// Variables
	RenderWindow* window;
	Background* background;
	UI* ui;
	Gameplay* gameplay;
	Menu* menu;
	GameOver* gameOver;
	PauseScreen* pauseScreen;

	bool isPauseEnabled;

	bool isGameDeleted;

	Music* menuSong, *gameSong;
	bool isMenuSong, isGameSong;

	SoundBuffer* gameOverSoundBuffer;
	Sound* gameOverSound;
	bool isGameOver;


public:

	// Constructor / Destructor
	Game();
	~Game();

	// Functions
	void Run();

};