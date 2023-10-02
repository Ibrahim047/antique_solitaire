#include "Card.h"
Card::Card(family t, int cn, Texture* open, Texture* close, color c) {
	type = t;
	card_no = cn;

	card_flipped = close;

	card_open = open;

	isFliped = false;
	clr = c;

	img.setTexture(*card_flipped);
	img.setScale(0.75f, 0.75f);


}

color Card::getClr()
{
	return clr;
}

void Card::Flip()
{
	isFliped = true;
	img.setTexture(*card_open);
	img.setScale(0.75f, 0.75f);
}

void Card::UnFlip()
{
	isFliped = false;
	img.setTexture(*card_flipped);
	img.setScale(0.75f, 0.75f);
}

bool Card::isOpen()
{
	return isFliped;
}

void Card::setPos(Position val) {

	pos = val;
	img.setPosition(pos.x, pos.y);
}

void Card::print(RenderWindow& window)
{
	window.draw(img);
}

void Card::setMovement(bool n)
{
	moving = n;
}

bool Card::isMoving()
{
	return moving;
}

int Card::getNO()
{
	return card_no;
}

family Card::getFamily()
{
	return type;
}
