#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
private:
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];

public:
	Menu(float width, float height)
	{
		if (!font.loadFromFile("font/arial.ttf"))
		{
			cout << "Error loading text" << endl;	//print error message
		}

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("Play");
		menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Exit");
		menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		selectedItemIndex = 0;
	}
	~Menu(){
	}

	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
	}
	void MoveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	void MoveDown()
	{
		if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	bool isMouseOverItem(const sf::Vector2i& mousePos) const
	{
		for (size_t i = 0; i < MAX_NUMBER_OF_ITEMS; ++i)
		{
			const sf::FloatRect bounds = menu[i].getGlobalBounds();
			if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
			{
				return true;
			}
		}
		return false;
	}
	int GetPressedItem() { return selectedItemIndex; }

};