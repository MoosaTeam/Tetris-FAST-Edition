#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Menu {

private:

	Texture* backgroundTexture, * playTexture, * quitTexture;
	Texture* playHoverTexture, * quitHoverTexture;
	Texture* playClickTexture, * quitClickTexture;
	Sprite* sprite;

	Vector2i mousePosWindow;

	RectangleShape* hitbox;

	string option;

	bool isClicked;
	bool playClick;
	int delayCount;

	Clock clock;
	Time time;

	SoundBuffer* hoverSoundBuffer, * clickSoundBuffer;
	Sound* hoverSound, *clickSound;
	bool isHoverSound[2], isClickSound[2];
	
public:

	Menu();
	~Menu();

	void Update(RenderWindow& window);
	void Hover(RenderWindow& window, int i);
	bool ClickDelay();


	bool getPlayClick();
	void setPlayClick(bool val);

};