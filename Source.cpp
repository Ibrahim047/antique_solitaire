#include<SFML/Graphics.hpp>
#include"Solitaire.h"
#include"Card.h"
#include<stdexcept>
using namespace std;

void load_textures(vector<Texture* >& textures) {
	int n = 0;
	for (int i = 1; i <= 13; i++) {
		textures.push_back(new Texture);
		textures[n++]->loadFromFile("s" + to_string(i) + ".png");
	}
	for (int i = 1; i <= 13; i++) {
		textures.push_back(new Texture);
		textures[n++]->loadFromFile("h" + to_string(i) + ".png");
	}
	for (int i = 1; i <= 13; i++) {
		textures.push_back(new Texture);
		textures[n++]->loadFromFile("c" + to_string(i) + ".png");
	}
	for (int i = 1; i <= 13; i++) {
		textures.push_back(new Texture);
		textures[n++]->loadFromFile("d" + to_string(i) + ".png");
	}
	textures.push_back(new Texture);
	textures[n]->loadFromFile("back.png");

}

int main() {

	vector<sf::Texture* > textures;
	vector<Sprite*> ToBeDragged;
	vector<Card*> movingCards;
	vector<Vector2f> movement;

	load_textures(textures);
	bool closed;
	Solitaire S(textures);


	sf::ContextSettings settings;
	settings.attributeFlags = sf::ContextSettings::Debug;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window", sf::Style::Default, settings);
	bool moving = false;

	while (window.isOpen()) {


		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				// Perform your action here when the "R" key is pressed
				// For example, you can reset a game, reload a level, or perform any desired action.
				// Add your code here.
				std::cout << "The 'R' key is pressed!" << std::endl;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U) {
				// Perform your action here when the "R" key is pressed
				// For example, you can reset a game, reload a level, or perform any desired action.
				// Add your code here.
				std::cout << "The 'U' key is pressed!" << std::endl;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {

					Vector2i pos = Mouse::getPosition(window);
					if (S.clickedOnMainDeck(pos)) {
						S.openCards();
						ToBeDragged.clear();
						movingCards.clear();
						movement.clear();
						closed = true;
						break;
					}
					if (S.clickedInCard(ToBeDragged, movingCards, pos)) {
						closed = false;
						moving = true;
						for (int i = 0; i < ToBeDragged.size(); i++) {

							Vector2f move = ToBeDragged[i]->getPosition() - Vector2f(pos.x, pos.y);
							movement.push_back(move);
						}
					}


				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					Vector2i pos = Mouse::getPosition(window);
					if (!closed) {


						moving = false;

						int n = S.droped_on(pos);
						if (n > 1 and movingCards.size() == 0)
							continue;
						if (n == -1 or !S.isValidMove(n, movingCards))
							S.revert(movingCards);
						else {
							S.Move(n, movingCards);
						}
						ToBeDragged.clear();
						if (!movingCards.empty())
							for (int i = 0; i < movingCards.size(); i++) {
								movingCards[i]->setMovement(false);
							}
						movingCards.clear();

						movement.clear();
					}
				}

			}
		}

		if (moving && !ToBeDragged.empty()) {
			for (int i = 0; i < ToBeDragged.size(); i++) {
				Vector2f t = Vector2f(Mouse::getPosition(window)) + movement[i];
				ToBeDragged[i]->setPosition(t);
			}
		}

		window.clear();

		S.Display(window);
		if (!ToBeDragged.empty()) {
			for (int i = 0; i < ToBeDragged.size(); i++) {
				window.draw(*ToBeDragged[i]);
			}

		}

		window.display();

	}

	return 0;

}


// ager main galat cards rekh data hon sorted pile main to revert hona chai .. exception a rhi ha
