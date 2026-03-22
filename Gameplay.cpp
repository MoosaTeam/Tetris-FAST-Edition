#include "Gameplay.h"

// constructor
Gameplay::Gameplay() {

	// setting intial variable values
	gameOver = false;
	createBlock = true;
	moveBlock = true;

	isButtonPressed = false;
	isLineComplete = true;
	speed = 1.f;
	currBlock = 0;
	nextBlock = 0;

	score = lines = 0;
	level = 1;

	block = nullptr;

	rows = 20;
	cols = 10;

	// creating grid
	grid = new int* [rows];
	for (int i = 0; i < rows; i++)
		grid[i] = new int[cols] {0};

	// loading block textures
	blockTextures = new Texture[8];
	if (!blockTextures[0].loadFromFile("Textures/cyan_tile.png"))
		cout << "Textures/cyan_tile.png failed" << endl;
	if (!blockTextures[1].loadFromFile("Textures/blue_tile.png"))
		cout << "Textures/blue_tile.png failed" << endl;
	if (!blockTextures[2].loadFromFile("Textures/orange_tile.png"))
		cout << "Textures/orange_tile.png failed" << endl;
	if (!blockTextures[3].loadFromFile("Textures/yellow_tile.png"))
		cout << "Textures/yellow_tile.png failed" << endl;
	if (!blockTextures[4].loadFromFile("Textures/green_tile.png"))
		cout << "Textures/green_tile.png failed" << endl;
	if (!blockTextures[5].loadFromFile("Textures/purple_tile.png"))
		cout << "Textures/purple_tile.png failed" << endl;
	if (!blockTextures[6].loadFromFile("Textures/red_tile.png"))
		cout << "Textures/red_tile.png failed" << endl;
	if (!blockTextures[7].loadFromFile("Textures/white_tile.png"))
		cout << "Textures/white_tile.png failed" << endl;

	// creating a new sprite
	blockSprite = new Sprite(blockTextures[0]);
	blockSprite->setScale(Vector2f(3.f, 3.f));

	LCcol = LCrow = 0;

	font = new Font("Fonts/ThaleahFat.ttf");
	LC_Score = new Text(*font, "+100");
	LC_Score->setCharacterSize(100);

	isMove = isRotate = isMatch = isPlace = false;
	moveBuffer = new SoundBuffer("Sounds/BlockMoveSound.wav");
	rotateBuffer = new SoundBuffer("Sounds/BlockRotateSound.wav");
	matchBuffer = new SoundBuffer("Sounds/LineMatchSound.wav");
	placeBuffer = new SoundBuffer("Sounds/BlockPlaceSound.wav");

	moveSound = new Sound(*moveBuffer);
	rotateSound = new Sound(*rotateBuffer);
	matchSound = new Sound(*matchBuffer);
	placeSound = new Sound(*placeBuffer);

}

// destructor
Gameplay::~Gameplay() {

	if (block != nullptr)
		delete block;

	delete[] blockTextures;
	
	delete blockSprite;

	for (int i = 0; i < rows; i++)
		delete[] grid[i];
	delete[] grid;

	delete moveBuffer, rotateBuffer, matchBuffer, placeBuffer;
	delete moveSound, rotateSound, matchSound, placeSound;

	delete font, LC_Score;

}

// update function to constantly update the game
void Gameplay::Update(RenderWindow& window) {

	// gets the time
	time = clock.getElapsedTime();
	time2 = clock.getElapsedTime();

	// creates a new block whenever there is no moving block on screen
	if (createBlock) {

		if (isPlace)
			isPlace = false;

		// chooses a random block
		if (currBlock == 0) {
			currBlock = randRange(1, 8);
			nextBlock = randRange(1, 8);
		}
		else {
			currBlock = nextBlock;
			nextBlock = randRange(1, 8);
		}

		if (nextBlock == currBlock) {
			if (nextBlock == 7)
				nextBlock = 1;
			else
				nextBlock++;
		}
			
		if (block != nullptr)
			delete block;

		// creates the randomly chosen block
		if (currBlock == 1) {
			block = new CyanTile();
		}
		else if (currBlock == 2) {
			block = new BlueTile();
		}
		else if (currBlock == 3) {
			block = new OrangeTile();
		}
		else if (currBlock == 4) {
			block = new YellowTile();
		}
		else if (currBlock == 5) {
			block = new GreenTile();
		}
		else if (currBlock == 6) {
			block = new PurpleTile();
		}
		else if (currBlock == 7) {
			block = new RedTile();
		}

		moveBlock = true;
		clock.restart();

		// adds it onto the grid
		for (int i = 0; i < 4; i++) {
			int x = block->pos[i].first;
			int y = block->pos[i].second;
			if (grid[x][y] == 0) {
				grid[x][y] = currBlock;
			}
			else {
				gameOver = true;
				return;
			}
		}
		
		createBlock = false;


	}

	// check for keyboard movements for block controls
	if (block != nullptr) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			if (!isButtonPressed) {

				if (!isRotate) {
					isRotate = true;
					rotateSound->stop();
					rotateSound->play();
				}

				isButtonPressed = true;
				block->rotate(grid, rows, cols);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
			if (!isButtonPressed) {

				if (!isMove) {
					isMove = true;
					moveSound->stop();
					moveSound->play();
				}

				isButtonPressed = true;
				block->moveBlock(grid, rows, cols, "right");
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			if (!isButtonPressed) {

				if (!isMove) {
					isMove = true;
					moveSound->stop();
					moveSound->play();
				}

				isButtonPressed = true;
				block->moveBlock(grid, rows, cols, "left");
			}
		}
		else {

			if (isRotate)
				isRotate = false;
			if (isMove)
				isMove = false;

			isButtonPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Down))
			speed = 0.05f;
		else {
			speed = 1.f - ((level / 10.f) - 0.10f);
		}
	}
	
	// block movement speed and checks to see if block can move or not
	if (time.asSeconds() > speed && block != nullptr) {
		clock.restart();
		moveBlock = true;
		for (int i = 0; i < 4; i++) {
			int x = block->pos[i].first;
			int y = block->pos[i].second;
			if (x == 19) {
				moveBlock = false;
				break;
			}

			if (!block->find({x + 1, y}) && grid[x + 1][y] != 0) {
				moveBlock = false;
				break;
			}
			
		}

		if (moveBlock) {
			move();
		}
		else {

			if (!isPlace) {
				isPlace = true;
				placeSound->stop();
				placeSound->play();
			}

			delete block;
			block = nullptr;
			createBlock = true;
		}
	}

	// draws the final grid on screen
	for (int i = 0; i < rows; i++) {
		isLineComplete = true;
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == 1) {
				blockSprite->setTexture(blockTextures[0]);
			}
			else if (grid[i][j] == 2) {
				blockSprite->setTexture(blockTextures[1]);
			}
			else if (grid[i][j] == 3) {
				blockSprite->setTexture(blockTextures[2]);
			}
			else if (grid[i][j] == 4) {
				blockSprite->setTexture(blockTextures[3]);
			}
			else if (grid[i][j] == 5) {
				blockSprite->setTexture(blockTextures[4]);
			}
			else if (grid[i][j] == 6) {
				blockSprite->setTexture(blockTextures[5]);
			}
			else if (grid[i][j] == 7) {
				blockSprite->setTexture(blockTextures[6]);
			}
			else if (grid[i][j] == 8) {
				blockSprite->setTexture(blockTextures[7]);
			}

			if (grid[i][j] != 0) {
				blockSprite->setPosition(Vector2f(417.5f + 10.f + (j * 35.f), 42.5f + 10.f + (i * 35.f)));
				window.draw(*blockSprite);
			}
			else
				isLineComplete = false;
			
		}

		

		if (isLineComplete && block == nullptr) {

			createBlock = false;

			LC_Score->setPosition(Vector2f(417.5f + 10.f + (2.5 * 35.f), 42.5f + 10.f + (6 * 35.f)));
			window.draw(*LC_Score);

			if (LCrow == 0)
				LCrow = i;


			if (lineCompleteDelay(window)) {

				if (isMatch)
					isMatch = false;

				score += 100;
				lines++;
				lineComplete(i);

				if (lines % 10 == 0) {
					level++;
				}
				createBlock = true;
				LCrow = 0;
				LCcol = 0;
			}
		}
	}

	if (nextBlock == 1) {
		blockSprite->setTexture(blockTextures[0]);
		for (int i = 0; i < 4; i++) {
			blockSprite->setPosition(Vector2f(932.5f + (i * 35.f), 220.f));
			window.draw(*blockSprite);
		}
	}
	else if (nextBlock == 2) {
		blockSprite->setTexture(blockTextures[1]);
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				blockSprite->setPosition(Vector2f(950.f, 220.f));
			}
			else {
				blockSprite->setPosition(Vector2f(950.f + ((i - 1) * 35.f), 255.f));
			}
			window.draw(*blockSprite);
		}
	}
	else if (nextBlock == 3) {
		blockSprite->setTexture(blockTextures[2]);
		for (int i = 0; i < 4; i++) {
			if (i == 3) {
				blockSprite->setPosition(Vector2f(1020.f, 220.f));
			}
			else {
				blockSprite->setPosition(Vector2f(950.f + (i * 35.f), 255.f));
			}
			window.draw(*blockSprite);
		}
	}
	else if (nextBlock == 4) {
		blockSprite->setTexture(blockTextures[3]);
		for (int i = 0; i < 4; i++) {
			if (i == 0 || i == 1) {
				blockSprite->setPosition(Vector2f(967.5f + (i * 35.f), 220.f));
			}
			else {
				blockSprite->setPosition(Vector2f(967.5f + ((i - 2) * 35.f), 255.f));
			}
			window.draw(*blockSprite);
		}
	}
	else if (nextBlock == 5) {
		blockSprite->setTexture(blockTextures[4]);
		for (int i = 0; i < 4; i++) {
			if (i == 0 || i == 1) {
				blockSprite->setPosition(Vector2f(950.f + (i * 35.f), 255.f));
			}
			else {
				blockSprite->setPosition(Vector2f(985.f + ((i - 2) * 35.f), 220.f));
			}
			window.draw(*blockSprite);
		}
	}
	else if (nextBlock == 6) {
		blockSprite->setTexture(blockTextures[5]);
		for (int i = 0; i < 4; i++) {
			if (i == 3) {
				blockSprite->setPosition(Vector2f(985.f, 255.f));
			}
			else {
				blockSprite->setPosition(Vector2f(950.f + ((i) * 35.f), 220.f));
			}
			window.draw(*blockSprite);
		}
	}
	else if (nextBlock == 7) {
		blockSprite->setTexture(blockTextures[6]);
		for (int i = 0; i < 4; i++) {
			if (i == 0 || i == 1) {
				blockSprite->setPosition(Vector2f(950.f + (i * 35.f), 220.f));
			}
			else {
				blockSprite->setPosition(Vector2f(985.f + ((i - 2) * 35.f), 255.f));
			}
			window.draw(*blockSprite);
		}
	}

}

// returns gameover status
bool Gameplay::isGameOver() {
	return gameOver;
}

void Gameplay::setGameOver(bool val) {
	gameOver = val;
}

// moves the block one space down
void Gameplay::move() {

	pair<int, int>* tempPos = new pair<int, int>[4];

	int temp = grid[block->pos[0].first][block->pos[0].second];

	for (int i = 0; i < 4; i++) {
		tempPos[i].first = block->pos[i].first + 1;
		tempPos[i].second = block->pos[i].second;
		grid[block->pos[i].first][block->pos[i].second] = 0;
	}

	for (int i = 0; i < 4; i++) {
		grid[tempPos[i].first][tempPos[i].second] = temp;
	}

	delete[] block->pos;
	block->pos = tempPos;

}

// random selector from range low to high
int Gameplay::randRange(int low, int high) {
	return rand() % (high - low) + low;
}

// deletes a line if it is complete
void Gameplay::lineComplete(int row) {

	for (int i = 0; i < cols; i++) {
		grid[row][i] = 0;
	}

	for (int i = row; i > 0; i--) {
		for (int j = 0; j < cols; j++) {
			int temp = grid[i][j];
			grid[i][j] = grid[i - 1][j];
			grid[i - 1][j] = temp;
		}
	}

	isLineComplete = false;

}

bool Gameplay::lineCompleteDelay(RenderWindow& window) {

	if (!isMatch) {
		isMatch = true;
		matchSound->stop();
		matchSound->play();
	}

	LC_Time = LC_Clock.getElapsedTime();

	if (LCcol <= cols - 1 && LC_Time.asSeconds() >= 0.05f) {
		LC_Clock.restart();
		grid[LCrow][LCcol] = 8;
		LCcol++;
	}

	
		if (LCcol > cols - 1 && LC_Time.asSeconds() >= 0.1f) {
			LC_Clock.restart();
			return true;
		}
		else
			return false;

}

int Gameplay::getScore() {
	return score;
}

int Gameplay::getLines() {
	return lines;
}

int Gameplay::getLevels() {
	return level;
}