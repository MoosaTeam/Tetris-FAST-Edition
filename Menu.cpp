#include "Menu.h"

Menu::Menu() {

	backgroundTexture = new Texture;
	playTexture = new Texture;
	playHoverTexture = new Texture;
	quitTexture = new Texture;
	quitHoverTexture = new Texture;
	playClickTexture = new Texture;
	quitClickTexture = new Texture;

	hitbox = new RectangleShape;

	if (!backgroundTexture->loadFromFile("Textures/Menu_GUI.png"))
		cout << "Textures/Menu_GUI.png failed" << endl;

	if (!playTexture->loadFromFile("Textures/ButtonPlay.png"))
		cout << "Textures/ButtonPlay.png failed" << endl;
	if (!playHoverTexture->loadFromFile("Textures/HButtonPlay.png"))
		cout << "Textures/HButtonPlay.png failed" << endl;
	if (!quitTexture->loadFromFile("Textures/ButtonQuit.png"))
		cout << "Textures/ButtonQuit.png failed" << endl;
	if (!quitHoverTexture->loadFromFile("Textures/HButtonQuit.png"))
		cout << "Textures/HButtonQuit.png failed" << endl;
	if (!playClickTexture->loadFromFile("Textures/PButtonPlay.png"))
		cout << "Textures/PButtonPlay.png failed" << endl;
	if (!quitClickTexture->loadFromFile("Textures/PButtonQuit.png"))
		cout << "Textures/PButtonQuit.png failed" << endl;

	sprite = new Sprite(*backgroundTexture);
	sprite->setScale(Vector2f(10.f, 10.f));

	hitbox->setSize(Vector2f(32.f, 7.f));
	hitbox->setScale(Vector2f(10.f, 10.f));

	isClicked = false;
	playClick = false;

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

Menu::~Menu() {

	delete backgroundTexture, playTexture, quitTexture;
	delete playHoverTexture, quitHoverTexture;
	delete sprite;
	delete hitbox;
	delete hoverSound, clickSound, hoverSoundBuffer, clickSoundBuffer;

}

void Menu::Update(RenderWindow& window) {

	sprite->setTexture(*backgroundTexture);
	window.draw(*sprite);

	for (int i = 0; i < 2; i++) {
		hitbox->setPosition(Vector2f(440.f, 420.f + (i * 130.f)));
		Hover(window, i);
		window.draw(*sprite);
	}

}

void Menu::Hover(RenderWindow& window, int i) {

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
				sprite->setTexture(*quitHoverTexture);

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
					option = "quit";
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
				sprite->setTexture(*quitTexture);
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
			sprite->setTexture(*quitTexture);
			if (option == "quit") {
				sprite->setTexture(*quitClickTexture);
				if (ClickDelay()) {
					option = "";
					window.close();
					isClicked = false;
				}
			}
		}
	}

}

bool Menu::ClickDelay() {

	time = clock.getElapsedTime();

	if (time.asSeconds() >= 1.f) {
		clock.restart();
		return true;
	}
	else
		return false;
	
}

bool Menu::getPlayClick() {
	return playClick;
}

void Menu::setPlayClick(bool val) {
	playClick = val;
}


