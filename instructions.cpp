#include <SFML/Graphics.hpp>
using namespace sf;

class Instructions
{
public:
void draw(sf::RenderWindow &window)
	{
		Font f;
		f.loadFromFile("font/arial.ttf");
		Text text;
		Text text1;

		text.setFont(f);
		text.setScale(1.5, 1.5);
		text.setFillColor(sf::Color::Yellow);
		text.setString("Instructions:");
		text.setStyle(Text::Bold);
		text.setPosition(sf::Vector2f(0, 0));
		text1.setFont(f);
		text1.setScale(0.6, 0.6);
		text1.setFillColor(sf::Color::Yellow);
		text1.setString("	This is a 2 player checker game. Player1 has black\npieces and player2 has red pieces. The game will start\nfrom player1.\n\n	The Game is based on Basic Checker rules including\nmultiple kills and pieces becoming king. However the\nwinning criteria is as follows:\n1)If a player has no more pieces left on the board,\n   opponent wins.\n2)If a player has only one piece and opponent has 3 or\n   more pieces, opponent wins.\n3)If both players have wasted 32 moves(16 each)\n   without killing then:\n   a)The Player with greater score Wins.\n   b)If both players have same score, its a draw.\n   (1 score on each kill)\n\nPress A to start the game.");
		text1.setPosition(sf::Vector2f(0, 60));
		window.draw(text);
		window.draw(text1);
	}
};
