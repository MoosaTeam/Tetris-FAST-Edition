#include "Background.h"

// constructor
Background::Background() {

	backgroundTexture = new Texture[2];
	
	if (!backgroundTexture[0].loadFromFile("Textures/backgroundFrame1.png"))
		cout << "Textures/backgroundFrame1.png failed" << endl;

	if (!backgroundTexture[1].loadFromFile("Textures/backgroundFrame2.png"))
		cout << "Textures/backgroundFrame2.png failed" << endl;
	
	backgroundSprite = new Sprite(backgroundTexture[0]);
	backgroundSprite->setPosition(Vector2f(0.f, 0.f));
	backgroundSprite->setScale(Vector2f(10.f, 10.f));

}

// Destructor
Background::~Background() {

	delete[] backgroundTexture;
	delete backgroundSprite;

}

// Update Function
void Background::Update(RenderWindow& window) {

	// gets the time
	time = clock.getElapsedTime();

	// checks if the time passed is 1 second
	if (time.asSeconds() > 1.f) {
		clock.restart();

		// changes the texture
		if (&backgroundSprite->getTexture() == &backgroundTexture[0])
			backgroundSprite->setTexture(backgroundTexture[1]);
		else
			backgroundSprite->setTexture(backgroundTexture[0]);

	}

	// draws the background onto the screen 
	window.draw(*backgroundSprite);

}