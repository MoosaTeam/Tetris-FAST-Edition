#include "GameOver.h"

GameOver::GameOver() {

	backgroundTexture = new Texture;
	playTexture = new Texture;
	playHoverTexture = new Texture;
	menuTexture = new Texture;
	menuHoverTexture = new Texture;
	playClickTexture = new Texture;
	menuClickTexture = new Texture;

	hitbox = new RectangleShape;

	if (!backgroundTexture->loadFromFile("Textures/Game_Over_GUI.png"))
		cout << "Textures/Game_Over_GUI.png failed" << endl;

	if (!playTexture->loadFromFile("Textures/ButtonRetry.png"))
		cout << "Textures/ButtonRetry.png failed" << endl;
	if (!playHoverTexture->loadFromFile("Textures/HButtonRetry.png"))
		cout << "Textures/HButtonRetry.png failed" << endl;
	if (!menuTexture->loadFromFile("Textures/ButtonMenu.png"))
		cout << "Textures/ButtonMenu.png failed" << endl;
	if (!menuHoverTexture->loadFromFile("Textures/HButtonMenu.png"))
		cout << "Textures/HButtonMenu.png failed" << endl;
	if (!playClickTexture->loadFromFile("Textures/PButtonRetry.png"))
		cout << "Textures/PButtonRetry.png" << endl;
	if (!menuClickTexture->loadFromFile("Textures/PButtonMenu.png"))
		cout << "Textures/PButtonMenu.png" << endl;

	sprite = new Sprite(*backgroundTexture);
	sprite->setScale(Vector2f(10.f, 10.f));

	hitbox->setSize(Vector2f(32.f, 7.f));
	hitbox->setScale(Vector2f(10.f, 10.f));

	isClicked = false;
	playClick = false;
	menuClick = false;

	delayCount = 0;

	option = "";

	hoverSoundBuffer = new SoundBuffer("Sounds/GUIHoverSound.wav");
	clickSoundBuffer = new SoundBuffer("Sounds/GUIButtonPress.wav");

	hoverSound = new Sound(*hoverSoundBuffer);
	clickSound = new Sound(*clickSoundBuffer);

	hoverSound->setVolume(10.f);
	clickSound->setVolume(50.f);

	for (int i = 0; i < 2; i++) {
		isHoverSound[i] = false;
		isClickSound[i] = false;
	}

}

GameOver::~GameOver() {

	delete backgroundTexture, playTexture, menuTexture;
	delete playHoverTexture, menuHoverTexture;
	delete sprite;
	delete hitbox;
	delete hoverSound, clickSound, hoverSoundBuffer, clickSoundBuffer;

}

void GameOver::Update(RenderWindow& window) {

	sprite->setTexture(*backgroundTexture);
	window.draw(*sprite);

	for (int i = 0; i < 2; i++) {
		hitbox->setPosition(Vector2f(440.f, 410.f + (i * 100.f)));
		Hover(window, i);
		window.draw(*sprite);
	}

}

void GameOver::Hover(RenderWindow& window, int i) {

	mousePosWindow = Mouse::getPosition(window);
	if (!isClicked) {
		if (hitbox->getGlobalBounds().contains(Vector2f(mousePosWindow))) {

			if (i == 0 && !isHoverSound[0]) {
				isHoverSound[0] = true;
				hoverSound->stop();
				hoverSound->play();
			}
			else if (i == 1 && !isHoverSound[1]) {
				isHoverSound[1] = true;
				hoverSound->stop();
				hoverSound->play();
			}

			if (i == 0)
				sprite->setTexture(*playHoverTexture);
			else
				sprite->setTexture(*menuHoverTexture);

			if (Mouse::isButtonPressed(Mouse::Button::Left)) {

				if (i == 0 && !isClickSound[0]) {
					isClickSound[0] = true;
					clickSound->stop();
					clickSound->play();
				}
				else if (!isClickSound[1]) {
					isClickSound[1] = true;
					clickSound->stop();
					clickSound->play();
				}

				isClicked = true;
				clock.restart();
				if (i == 0)
					option = "play";
				else
					option = "menu";
			}
		}
		else {

			if (i == 0)
				isHoverSound[0] = false;
			else
				isHoverSound[1] = false;

			if (i == 0)
				sprite->setTexture(*playTexture);
			else
				sprite->setTexture(*menuTexture);
		}
	}
	else {

		if (i == 0)
			isClickSound[0] = false;
		else
			isClickSound[1] = false;

		if (i == 0) {
			sprite->setTexture(*playTexture);
			if (option == "play") {
				sprite->setTexture(*playClickTexture);
				if (ClickDelay()) {
					option = "";
					playClick = true;
					isClicked = false;
				}
			}
		}
		else if (i == 1) {
			sprite->setTexture(*menuTexture);
			if (option == "menu") {
				sprite->setTexture(*menuClickTexture);
				if (ClickDelay()) {
					option = "";
					menuClick = true;
					isClicked = false;
				}
			}
		}
	}

}

bool GameOver::ClickDelay() {

	time = clock.getElapsedTime();

	if (time.asSeconds() >= 1.f) {
		clock.restart();
		return true;
	}
	else
		return false;
	
}

bool GameOver::getPlayClick() {
	return playClick;
}

void GameOver::setPlayClick(bool val) {
	playClick = val;
}

bool GameOver::getMenuClick() {
	return menuClick;
}

void GameOver::setMenuClick(bool val) {
	menuClick = val;
}



