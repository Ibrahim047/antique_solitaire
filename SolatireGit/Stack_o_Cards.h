#pragma once
#include<vector>
#include<stdexcept>

using namespace std;

class StackoCards {
	vector<Card*> Cards;

public:
	StackoCards() :Cards() {

	}

	void push(Card* val) {
		Cards.push_back(val);
	}

	Card& top() {
		return *Cards[Cards.size() - 1];
	}

	void pop() {
		Cards.pop_back();
	}

	int size() {
		return Cards.size();
	}

	bool isEmpty() {
		return Cards.empty();
	}

	


};