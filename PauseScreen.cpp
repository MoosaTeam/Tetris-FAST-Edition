#include "PauseScreen.h"

PauseScreen::PauseScreen() {

	backgroundTexture = new Texture;
	resumeTexture = new Texture;
	resumeHoverTexture = new Texture;
	menuTexture = new Texture;
	menuHoverTexture = new Texture;
	resumeClickTexture = new Texture;
	menuClickTexture = new Texture;

	hitbox = new RectangleShape;

	if (!backgroundTexture->loadFromFile("Textures/Pause_GUI.png"))
		cout << "Textures/Pause_GUI.png failed" << endl;

	if (!resumeTexture->loadFromFile("Textures/ButtonResume.png"))
		cout << "Textures/ButtonResume.png failed" << endl;
	if (!resumeHoverTexture->loadFromFile("Textures/HButtonResume.png"))
		cout << "Textures/HButtonResume.png failed" << endl;
	if (!menuTexture->loadFromFile("Textures/ButtonMenu.png"))
		cout << "Textures/ButtonMenu.png failed" << endl;
	if (!menuHoverTexture->loadFromFile("Textures/HButtonMenu.png"))
		cout << "Textures/HButtonMenu.png failed" << endl;
	if (!resumeClickTexture->loadFromFile("Textures/PButtonResume.png"))
		cout << "Textures/PButtonResume.png failed" << endl;
	if (!menuClickTexture->loadFromFile("Textures/PButtonMenu.png"))
		cout << "Textures/PButtonMenu.png failed" << endl;

	sprite = new Sprite(*backgroundTexture);
	sprite->setScale(Vector2f(10.f, 10.f));

	hitbox->setSize(Vector2f(32.f, 7.f));
	hitbox->setScale(Vector2f(10.f, 10.f));

	isClicked = false;
	resumeClick = false;
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

PauseScreen::~PauseScreen() {

	delete backgroundTexture, resumeTexture, menuTexture;
	delete resumeHoverTexture, menuHoverTexture;
	delete sprite;
	delete hitbox;
	delete hoverSound, clickSound, hoverSoundBuffer, clickSoundBuffer;

}

void PauseScreen::Update(RenderWindow& window) {

	sprite->setTexture(*backgroundTexture);
	window.draw(*sprite);

	for (int i = 0; i < 2; i++) {
		hitbox->setPosition(Vector2f(430.f + (i * 10.f), 380.f + (i * 130.f)));
		Hover(window, i);
		window.draw(*sprite);
	}

}

void PauseScreen::Hover(RenderWindow& window, int i) {

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
				sprite->setTexture(*resumeHoverTexture);
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
					option = "resume";
				else
					option = "menu";
			}
		}
		else {

			if (i == 0)
				isClickSound[0] = false;
			else
				isClickSound[1] = false;

			if (i == 0)
				isHoverSound[0] = false;
			else
				isHoverSound[1] = false;

			if (i == 0)
				sprite->setTexture(*resumeTexture);
			else
				sprite->setTexture(*menuTexture);
		}
	}
	else {
		if (i == 0) {
			sprite->setTexture(*resumeTexture);
			if (option == "resume") {
				sprite->setTexture(*resumeClickTexture);
				if (ClickDelay()) {
					option = "";
					resumeClick = true;
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

bool PauseScreen::ClickDelay() {

	time = clock.getElapsedTime();

	if (time.asSeconds() >= 1.f) {
		clock.restart();
		return true;
	}
	else
		return false;

}

bool PauseScreen::getResumeClick() {
	return resumeClick;
}

void PauseScreen::setResumeClick(bool val) {
	resumeClick = val;
}

bool PauseScreen::getMenuClick() {
	return menuClick;
}

void PauseScreen::setMenuClick(bool val) {
	menuClick = val;
}



