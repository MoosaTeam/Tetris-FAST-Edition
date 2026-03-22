#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class UI {

private:
	
	// Variables
	Texture* gridTexture, *backgroundTexture;
	Sprite* gridSprite, *backgroundSprite;

	Font* font;
	Text* levelText, *scoreText, *linesText, *nextText;
	Text* level, *score, *lines;

public:

	// Constructor / Destructor
	UI();
	~UI();

	// Functions
	void CreateGrid();
	void CreateBackground();
	void CreateText();
	void Update(RenderWindow& window, int score, int lines, int level);

};