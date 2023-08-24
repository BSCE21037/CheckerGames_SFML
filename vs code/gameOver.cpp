#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 2

class GameOver
{
private:
	Font f;
	Text gameOver[MAX_NUMBER_OF_ITEMS];
	float width, height;
	int dive = 8;
	int selectedItemIndex;

public:
	GameOver(float width, float height)
	{
		this->width = width;
		this->height = height;
	}

	void setFont(int opt, int draw)
	{
		if (!f.loadFromFile("font/arial.ttf"))
		{
			cout << "Error loading text" << endl;	//print error message
		}

		if(opt == 1 && draw != 0){
			if(draw == 1){
				gameOver[0].setFont(f);
				gameOver[0].setScale(0.8, 0.8);
				gameOver[0].setFillColor(sf::Color::Black);
				gameOver[0].setString("Player 1 Wins(Greater Score)");
				gameOver[0].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

				gameOver[1].setFont(f);
				gameOver[1].setScale(0.8, 0.8);
				gameOver[1].setFillColor(sf::Color::Cyan);
				gameOver[1].setString("Press Esc to Exit\n Thanks for Playing   :)\n   made by Musa");
				gameOver[1].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
			}
			else if(draw == 2){
				gameOver[0].setFont(f);
				gameOver[0].setScale(0.8, 0.8);
				gameOver[0].setFillColor(sf::Color::Red);
				gameOver[0].setString("Player 2 Wins(Greater Score)");
				gameOver[0].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

				gameOver[1].setFont(f);
				gameOver[1].setScale(0.8, 0.8);
				gameOver[1].setFillColor(sf::Color::Cyan);
			gameOver[1].setString("Press Esc to Exit\n Thanks for Playing   :)\n   made by Musa");
				gameOver[1].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
			}
			else if(draw == 3){
				gameOver[0].setFont(f);
				gameOver[0].setScale(0.8, 0.8);
				gameOver[0].setFillColor(sf::Color::Blue);
				gameOver[0].setString("Its a Draw");
				gameOver[0].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

				gameOver[1].setFont(f);
				gameOver[1].setScale(0.8, 0.8);
				gameOver[1].setFillColor(sf::Color::Cyan);
				gameOver[1].setString("Press Esc to Exit\n Thanks for Playing   :)\n   made by Musa");
				gameOver[1].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
			}
		}
		else if(opt == 2 && draw == 0){
			gameOver[0].setFont(f);
			gameOver[0].setScale(0.8, 0.8);
			gameOver[0].setFillColor(sf::Color::Red);
			gameOver[0].setString("Player 2 Wins(Dominates the Board)");
			gameOver[0].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

			gameOver[1].setFont(f);
			gameOver[1].setScale(0.8, 0.8);
			gameOver[1].setFillColor(sf::Color::Cyan);
			gameOver[1].setString("Press Esc to Exit\n Thanks for Playing   :)\n   made by Musa");
			gameOver[1].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
		}
		else if(opt == 3 && draw == 0){
			gameOver[0].setFont(f);
			gameOver[0].setScale(0.8, 0.8);
			gameOver[0].setFillColor(sf::Color::Black);
			gameOver[0].setString("Player 1 Wins(Dominates the Board)");
			gameOver[0].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

			gameOver[1].setFont(f);
			gameOver[1].setScale(0.8, 0.8);
			gameOver[1].setFillColor(sf::Color::Cyan);
			gameOver[1].setString("Press Esc to Exit\n Thanks for Playing   :)\n   made by Musa");
			gameOver[1].setPosition(sf::Vector2f(width / dive, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		}

	}
	
	void setWidth(float w)
	{
		width = w;
	}
	void setHeight(float h)
	{
		height = h;
	}


	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(gameOver[i]);
		}
	}
	bool isMouseOverItem(const sf::Vector2i& mousePos) const
	{
		for (size_t i = 0; i < MAX_NUMBER_OF_ITEMS; ++i)
		{
			const sf::FloatRect bounds = gameOver[i].getGlobalBounds();
			if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
			{
				return true;
			}
		}
		return false;
	}
	void MoveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			gameOver[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			gameOver[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	void MoveDown()
	{
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			gameOver[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			gameOver[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}

};