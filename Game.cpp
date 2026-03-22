#include "Game.h"

// Constructor
Game::Game() {

	// Window Creation
	window = new RenderWindow(VideoMode({ 1200, 800 }), "Tetris FAST Edition", Style::Titlebar | Style::Close);

	// create background / ui / gameplay
	background = new Background;
	ui = new UI;
	gameplay = new Gameplay;
	menu = new Menu;
	gameOver = new GameOver;
	pauseScreen = new PauseScreen;

	isPauseEnabled = false;

	isGameDeleted = false;

	menuSong = new Music("Sounds/menusong.mp3");
	menuSong->setVolume(10.f);
	menuSong->setLooping(true);
	isMenuSong = false;

	gameSong = new Music("Sounds/tetrissong.mp3");
	gameSong->setVolume(10.f);
	gameSong->setLooping(true);
	isGameSong = false;

	gameOverSoundBuffer = new SoundBuffer("Sounds/GameOverSound.wav");
	isGameOver = false;

	gameOverSound = new Sound(*gameOverSoundBuffer);

}

// Destructor
Game::~Game() {

	delete window;
	delete background;
	delete ui;
	if (gameplay == nullptr) {
		delete gameplay;
	}
	delete menu;
	delete gameOver;
	delete menuSong;
	delete gameSong;
	delete gameOverSoundBuffer, gameOverSound;

}

void Game::Run() {

	// Poll events
	while (window->isOpen()) {
		while (const optional event = window->pollEvent()) {

			// Closes the game when the close button is pressed
			if (event->is<Event::Closed>()) {
				window->close();
				break;
			}
		}

		// clear the screen
		window->clear();

		// if game is not over
		if (!isPauseEnabled && !gameplay->isGameOver()) {
			background->Update(*window);

			if (isGameOver) {
				isGameOver = false;
			}

			if (!menu->getPlayClick()) {
				if (!isMenuSong) {
					isMenuSong = true;
					menuSong->play();
				}
				menu->Update(*window);
			}
			else {

				if (isMenuSong) {
					isMenuSong = false;
					menuSong->stop();
				}

				if (!isGameSong) {
					isGameSong = true;
					gameSong->play();
				}

				ui->Update(*window, gameplay->getScore(), gameplay->getLines(), gameplay->getLevels());

				gameplay->Update(*window);

				if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
					isPauseEnabled = true;
				}

			}
		}
		else if (isPauseEnabled) {

			if (isGameSong) {
				isGameSong = false;
				gameSong->pause();
			}

			pauseScreen->Update(*window);

			if (pauseScreen->getMenuClick()) {
				delete gameplay;
				gameplay = new Gameplay;
				pauseScreen->setMenuClick(false);
				menu->setPlayClick(false);
				isPauseEnabled = false;
				gameSong->stop();
			}
			else if (pauseScreen->getResumeClick()) {
				pauseScreen->setResumeClick(false);
				isPauseEnabled = false;
			}
		}
		else {

			if (isGameSong) {
				isGameSong = false;
				gameSong->stop();
			}

			if (!isGameOver) {
				isGameOver = true;
				gameOverSound->stop();
				gameOverSound->play();
			}
	
			if (!isGameDeleted) {
				delete gameplay;
				gameplay = new Gameplay;
				gameplay->setGameOver(true);
				menu->setPlayClick(false);
				isGameDeleted = true;
			}

			gameOver->Update(*window);

			if (gameOver->getPlayClick()) {
				menu->setPlayClick(true);
				gameOver->setPlayClick(false);
				gameplay->setGameOver(false);
				isGameDeleted = false;
			}
			else if (gameOver->getMenuClick()) {
				isGameDeleted = false;
				gameOver->setMenuClick(false);
				gameplay->setGameOver(false);
			}

		}

		window->display();

	}

}