#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "CyanTile.h"
#include "BlueTile.h"
#include "OrangeTile.h"
#include "YellowTile.h"
#include "GreenTile.h"
#include "PurpleTile.h"
#include "RedTile.h"

using namespace std;
using namespace sf;

class Gameplay {

private:

	// variables
	int** grid;
	int rows, cols;

	Block* block;
	Texture* blockTextures;
	Sprite* blockSprite;

	bool gameOver;
	bool createBlock;
	bool moveBlock;
	int currBlock;
	int nextBlock;

	bool isButtonPressed;
	bool isLineComplete;

	int score, lines, level;

	int LCcol, LCrow;

	float speed;

	Clock clock, LC_Clock, clock2;
	Time time, LC_Time, time2;

	SoundBuffer* placeBuffer, * rotateBuffer, * moveBuffer, * matchBuffer;
	Sound* placeSound, * rotateSound, * moveSound, * matchSound;
	bool isPlace, isRotate, isMove, isMatch;

	Font* font;
	Text* LC_Score;

public:

	// constructor / destructor
	Gameplay();
	~Gameplay();

	// functions
	void Update(RenderWindow& window);
	
	bool isGameOver();
	void setGameOver(bool val);
	void move();
	int randRange(int low, int high);
	void lineComplete(int row);
	bool lineCompleteDelay(RenderWindow& window);

	int getScore();
	int getLines();
	int getLevels();

};