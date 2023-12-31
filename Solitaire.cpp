#include"Solitaire.h"
Solitaire::Solitaire(vector<Texture*> Ts) :Sorted_Pile(4)
{
	vector<Card*> all_cards;
	for (int i = 0; i < 13; i++) {
		all_cards.push_back(new Card(spades, i + 1, Ts[i], Ts[Ts.size() - 1], black));
	}

	for (int i = 13; i < 26; i++) {
		all_cards.push_back(new Card(hearts, (i + 1) - 13, Ts[i], Ts[Ts.size() - 1], red));
	}

	for (int i = 26; i < 39; i++) {
		all_cards.push_back(new Card(clubs, (i + 1) - 26, Ts[i], Ts[Ts.size() - 1], black));
	}

	for (int i = 39; i < 52; i++) {
		all_cards.push_back(new Card(diamonds, (i + 1) - 39, Ts[i], Ts[Ts.size() - 1], red));
	}

	random_device rd;
	mt19937 gen(rd());
	shuffle(all_cards.begin(), all_cards.end(), gen);

	int n = 0;
	for (int i = 0; i < 24; i++) {
		Position P;
		P.x = 105;
		P.y = 63;
		all_cards[n]->setPos(P);
		MainDeck.push(all_cards[n++]);
	}

	for (int i = 0; i < 7; i++) {
		StackoCards temp;
		Position P;

		for (int j = 0; j <= i; j++) {

			P.x = 425 + (195 * i);
			P.y = 300 + (30 * j);
			all_cards[n]->setPos(P);
			temp.push(all_cards[n++]);
		}
		SubDecks.push_back(temp);

		SubDecks[i].top().Flip();
	}

	background.loadFromFile("background.png");
	backg.setTexture(background);
	level = 1;
	score = 0;
	font.loadFromFile("font.otf");
}



bool Solitaire::clickedInCard(vector<Sprite*>& ToBeDragged, vector<Card*>& cards, Vector2i pos)
{
	if (!outOfMainDeck.isEmpty() and outOfMainDeck.top().img.getGlobalBounds().contains(Vector2f(pos.x, pos.y))) {
		outOfMainDeck.top().setMovement(true);
		ToBeDragged.push_back(&outOfMainDeck.top().img);
		cards.push_back(&outOfMainDeck.top());
		found_in_deck = 12;
		return true;
	}


	for (int i = 0; i < SubDecks.size(); i++) {
		SubDecks[i].findCard(ToBeDragged, cards, pos);
		if (ToBeDragged.size() > 0) {
			found_in_deck = i;
			return true;
		}
	}
	return false;
}

bool Solitaire::clickedOnMainDeck(Vector2i pos)
{

	if (pos.x >= 105 and pos.x <= 257 and pos.y >= 63 and pos.y <= 268) {
		return true;
	}
	return false;
}

void Solitaire::openCards()
{
	if (MainDeck.isEmpty())
	{
		Position Q;
		Q.x = 105;
		Q.y = 63;
		while (!outOfMainDeck.isEmpty()) {
			outOfMainDeck.top().UnFlip();
			outOfMainDeck.top().setPos(Q);
			MainDeck.push(&outOfMainDeck.top());
			outOfMainDeck.pop();

		}
		rem = 0;
		return;
	}
	for (int i = 0; i < level and !MainDeck.isEmpty(); i++) {
		MainDeck.top().Flip();
		outOfMainDeck.push(&MainDeck.top());
		MainDeck.pop();
	}
	rem = level;

}

int Solitaire::droped_on(Vector2i pos)
{
	for (int i = 0; i < Sorted_Pile.size(); i++) {
		if (pos.x >= (1010 + (i * (195))) and pos.x <= (1164 + (i * (185))) and pos.y >= 63 and pos.y <= 268)
		{
			return i + 7;
		}

	}
	for (int i = 0; i < SubDecks.size(); i++) {
		if (i == found_in_deck)
			continue;
		if (SubDecks[i].isEmpty() and pos.x >= 425 + (195 * i) and pos.x <= 425 + (195 * i) + 153 and pos.y >= 300 and pos.y <= 300 + 206)
			return i;

		if (!SubDecks[i].isEmpty() and SubDecks[i].top().img.getGlobalBounds().contains(static_cast<Vector2f>(pos))) {
			return i;
		}
	}
	return -1;

}
void Solitaire::Move(int droped_on_deck, vector<Card*>& moving) {

	if (found_in_deck == 12) {
		if (droped_on_deck >= 7) {

			Position pos;
			pos.x = 1010 + ((195) * (droped_on_deck - 7));
			pos.y = 63;
			cout << pos.x << " " << pos.y << endl;
			moving[0]->setPos(pos);

			Sorted_Pile[droped_on_deck - 7].push(moving[0]);
			outOfMainDeck.pop();
			rem--;
			if (rem == 0 and !outOfMainDeck.isEmpty()) {
				if (outOfMainDeck.size() < level)
					rem = outOfMainDeck.size();
				else
					rem = level;
			}
			score += 10;
			/*if (!SubDecks[found_in_deck].isEmpty())
				SubDecks[found_in_deck].top().Flip();*/
			return;
		}
		Vector2f p;
		if (SubDecks[droped_on_deck].isEmpty()) {
			p.x = 425 + (195 * droped_on_deck);
			p.y = 300 - 30;
		}
		else
			p = SubDecks[droped_on_deck].top().img.getPosition();
		SubDecks[droped_on_deck].push(&outOfMainDeck.top());
		SubDecks[droped_on_deck].top().img.setPosition(p.x, p.y + (30));
		outOfMainDeck.pop();
		rem--;
		if (rem == 0 and !outOfMainDeck.isEmpty()) {
			if (outOfMainDeck.size() < level)
				rem = outOfMainDeck.size();
			else
				rem = level;
		}
		score += 5;
		return;
	}

	if (droped_on_deck >= 7) {
		Position pos;
		pos.x = 1010 + ((195) * (droped_on_deck - 7));
		pos.y = 63;
		cout << pos.x << " " << pos.y << endl;
		moving[0]->setPos(pos);

		Sorted_Pile[droped_on_deck - 7].push(moving[0]);
		SubDecks[found_in_deck].pop();
		if (!SubDecks[found_in_deck].isEmpty())
			SubDecks[found_in_deck].top().Flip();
		score += 10;
		return;
	}


	StackoCards temp;
	for (int i = 0; i < moving.size(); i++) {
		temp.push(&SubDecks[found_in_deck].top());
		SubDecks[found_in_deck].pop();
	}
	if (!SubDecks[found_in_deck].isEmpty())
		SubDecks[found_in_deck].top().Flip();
	Vector2f p;
	if (SubDecks[droped_on_deck].isEmpty()) {
		p.x = 425 + (195 * droped_on_deck);
		p.y = 300 - 30;
	}
	else
		p = SubDecks[droped_on_deck].top().img.getPosition();
	int size = temp.size();
	for (int i = 0; i < size; i++) {
		SubDecks[droped_on_deck].push(&temp.top());
		SubDecks[droped_on_deck].top().img.setPosition(p.x, p.y + (30 * (i + 1)));
		temp.pop();
	}
	score += 5;
}

void Solitaire::revert(vector<Card*>& moving)
{/*
	P.x = 425 + (195 * i);
	P.y = 300 + (30 * j);*/

	if (found_in_deck == 12) {
		Card* t;
		t = &outOfMainDeck.top();
		outOfMainDeck.pop();

		Vector2f P;
		if (outOfMainDeck.isEmpty()) {
			P.x = 268 + (0 * 30);
			P.y = 63;
		}
		else
			P = outOfMainDeck.top().img.getPosition();

		outOfMainDeck.push(t);
		//outOfMainDeck.push(moving[0]);

		outOfMainDeck.top().img.setPosition(P.x + 30, P.y);
		outOfMainDeck.top().setMovement(false);

		return;
	}

	StackoCards temp;
	for (int i = 0; i < moving.size(); i++) {
		temp.push(&SubDecks[found_in_deck].top());
		SubDecks[found_in_deck].pop();
	}
	Vector2f p;
	if (SubDecks[found_in_deck].isEmpty()) {
		p.x = 425 + (195 * found_in_deck);
		p.y = 300 - 30;
	}
	else
		p = SubDecks[found_in_deck].top().img.getPosition();
	int size = temp.size();
	for (int i = 0; i < size; i++) {
		SubDecks[found_in_deck].push(&temp.top());
		SubDecks[found_in_deck].top().img.setPosition(p.x, p.y + (30 * (i + 1)));
		temp.pop();
	}
}

void Solitaire::undo()
{
	if (Ustate.hasData) {
		Ustate.cameFrom->push(&Ustate.WentTo->top());
		Ustate.cameFrom->top().setPos(Ustate.prePos);
		Ustate.WentTo->pop();
	}
}

void Solitaire::redo()
{
	if (RState.hasData) {
		RState.cameFrom->push(&Ustate.WentTo->top());
		RState.cameFrom->top().setPos(Ustate.prePos);
		RState.WentTo->pop();
	}
}


bool Solitaire::isValidMove(int n, vector<Card*>& moving)
{
	if (n >= 7) {
		if (Sorted_Pile[n - 7].isEmpty() and moving.size() == 1 and moving[0]->getNO() == 1)
			return true;
		if (moving.size() == 1 and Sorted_Pile[n - 7].top().getClr() == moving[0]->getClr() and Sorted_Pile[n - 7].top().getFamily() == moving[0]->getFamily() and Sorted_Pile[n - 7].top().getNO() == moving[0]->getNO() - 1)
			return true;
	}
	if (n != 12 and SubDecks[n].isEmpty() and moving[0]->getNO() == 13)
		return true;
	if (n != 12 and SubDecks[n].top().getNO() - 1 == moving[0]->getNO() and SubDecks[n].top().getClr() != moving[0]->getClr())
		return true;

	return false;
}
