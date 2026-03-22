#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class GameOver {

private:

	Texture* backgroundTexture, * playTexture, * menuTexture;
	Texture* playHoverTexture, * menuHoverTexture;
	Texture* playClickTexture, * menuClickTexture;
	Sprite* sprite;

	Vector2i mousePosWindow;

	RectangleShape* hitbox;

	string option;

	bool isClicked;
	bool playClick;
	bool menuClick;
	int delayCount;

	Clock clock;
	Time time;

	SoundBuffer* hoverSoundBuffer, * clickSoundBuffer;
	Sound* hoverSound, * clickSound;
	bool isHoverSound[2], isClickSound[2];

public:

	GameOver();
	~GameOver();

	void Update(RenderWindow& window);
	void Hover(RenderWindow& window, int i);
	bool ClickDelay();


	bool getPlayClick();
	void setPlayClick(bool val);
	bool getMenuClick();
	void setMenuClick(bool val);

};

