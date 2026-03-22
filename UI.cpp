#include "UI.h"

// Constructor
UI::UI() {

	CreateBackground();
	CreateGrid();
	CreateText();

}

// Destructor
UI::~UI() {

	delete backgroundSprite;
	delete[] backgroundTexture;
	delete gridSprite;
	delete gridTexture;
	delete font;
	delete scoreText;
	delete linesText;
	delete levelText;
	delete nextText;
	delete score;
	delete level;
	delete lines;
	
}

// Grid creation
void UI::CreateGrid() {

	gridTexture = new Texture;
	if (!gridTexture->loadFromFile("Textures/grid.png"))
		cout << "Textures/grid.png failed" << endl;

	gridSprite = new Sprite(*gridTexture);
	gridSprite->setPosition(Vector2f(422.5f, 47.5f));

}

void UI::CreateBackground() {

	backgroundTexture = new Texture[3];
	if (!backgroundTexture[0].loadFromFile("Textures/Play_GUI.png"))
		cout << "Textures/Play_GUI.png failed" << endl;
	if (!backgroundTexture[1].loadFromFile("Textures/PlayNext_GUI.png"))
		cout << "Textures/PlayNext_GUI.png failed" << endl;
	if (!backgroundTexture[2].loadFromFile("Textures/PlayScore_GUI.png"))
		cout << "Textures/PlayScore_GUI.png failed" << endl;

	backgroundSprite = new Sprite(backgroundTexture[0]);
	backgroundSprite->setScale(Vector2f(10.f, 10.f));

}

void UI::CreateText() {

	font = new Font;
	if (!font->openFromFile("Fonts/ThaleahFat.ttf"))
		cout << "Fonts/ThaleahFat.ttf failed" << endl;

	scoreText = new Text(*font, "SCORE:");
	scoreText->setCharacterSize(45);
	scoreText->setPosition(Vector2f(91.f, 380.f));

	linesText = new Text(*font, "LINES:");
	linesText->setCharacterSize(45);
	linesText->setPosition(Vector2f(91.f, 500.f));

	levelText = new Text(*font, "LEVEL:");
	levelText->setCharacterSize(45);
	levelText->setPosition(Vector2f(91.f, 620.f));

	nextText = new Text(*font, "NEXT:");
	nextText->setCharacterSize(60);
	nextText->setPosition(Vector2f(892.f, 50.f));

	score = new Text(*font);
	lines = new Text(*font);
	level = new Text(*font);

	score->setCharacterSize(45);
	lines->setCharacterSize(45);
	level->setCharacterSize(45);

	score->setPosition(Vector2f(190.f, 435.f));
	lines->setPosition(Vector2f(190.f, 555.f));
	level->setPosition(Vector2f(190.f, 675.f));


}

// Update the screen
void UI::Update(RenderWindow& window, int score, int lines, int level) {

	for (int i = 0; i < 3; i++) {
		backgroundSprite->setTexture(backgroundTexture[i]);
		window.draw(*backgroundSprite);
	}
	window.draw(*gridSprite);

	window.draw(*scoreText);
	window.draw(*linesText);
	window.draw(*levelText);
	window.draw(*nextText);

	this->score->setString(to_string(score));
	this->lines->setString(to_string(lines));
	this->level->setString(to_string(level));

	window.draw(*this->score);
	window.draw(*this->lines);
	window.draw(*this->level);

}