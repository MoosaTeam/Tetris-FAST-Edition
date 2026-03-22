#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Background {

private:

	// variables
	Texture* backgroundTexture;
	Sprite* backgroundSprite;
	Clock clock;
	Time time;

public:

	// Constructor / Destructor
	Background();
	~Background();

	// Functions
	void Update(RenderWindow& window);

};

