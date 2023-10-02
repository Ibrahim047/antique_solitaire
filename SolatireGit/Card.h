#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdexcept>

enum family { spades, clubs, diamonds, hearts };
enum color { red, black };

using namespace std;
using namespace sf;


struct Position {

	int x;
	int y;
};

class Card
{
	bool isFliped;
	family type;
	int card_no;
	Texture* card_flipped;

	Texture* card_open;

	color clr;
	Position pos;
	bool moving;

public:
	Sprite img;

	Card(family t, int cn, Texture* open, Texture* close, color c);
	color getClr();
	void Flip();
	void UnFlip();
	bool isOpen();
	void setPos(Position val);
	void print(RenderWindow& window);
	void setMovement(bool n);
	bool isMoving();
	int getNO();
	family getFamily();
};