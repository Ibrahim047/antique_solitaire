#pragma once
#include<SFML/Graphics.hpp>
#include"Card.h"
#include"Stack_o_Cards.h"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<random>
#include<stdexcept>

using namespace std;



class Solitaire {
	

	struct state {
		bool hasData = false;
		Position prePos;

		StackoCards* cameFrom;
		StackoCards* WentTo;

		void set(Position pre, StackoCards* came, StackoCards* Went) {
			hasData = true;
			prePos = pre, cameFrom = came, WentTo = Went;
		}

		

	};
	vector<StackoCards> SubDecks;
	vector<StackoCards> Sorted_Pile;
	StackoCards MainDeck;
	StackoCards outOfMainDeck;
	Texture background;
	Sprite backg;
	Font font;
	int level;
	int found_in_deck;
	int rem;
	Text Score;
	int score;
	state Ustate;
	state RState;
public:
	Solitaire(vector<Texture*> Ts);
	void Display(RenderWindow& Window);
	bool isValidMove(int n, vector<Card*>& moving);
	bool areAllCardsSorted();
	bool clickedInCard(vector<Sprite*>& ToBeDragged,vector<Card*>& cards, Vector2i pos);
	bool clickedOnMainDeck(Vector2i pos);
	void openCards();
	int droped_on(Vector2i pos);
	void Move(int droped_on_deck, vector<Card*>& moving);
	void undo();
	void redo();
	void revert(vector<Card*>& moving);

};