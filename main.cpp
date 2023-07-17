#include <SFML/Graphics.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITEMS 3 //number of menu items
using namespace std;
using namespace sf;

const int boardSize = 8;	//size of board
const int tileSize = 80;	//size of tiles

RectangleShape tile(sf::Vector2f(tileSize, tileSize));	//create tile

void drawChessBoard(RenderWindow &window){
	
	bool isWhite = true;	//is tile white or black
   

    for (int i = 0; i < boardSize; ++i){		//draw board
        for (int j = 0; j < boardSize; ++j){	//draw board

            tile.setFillColor(isWhite ? sf::Color::White : sf::Color::Black);	//if white true then color white else color black
            tile.setPosition(j * tileSize, i * tileSize);						//set position of tile within the row
            window.draw(tile);													//draw tile
            isWhite = !isWhite;													//flip color
        }
        isWhite = !isWhite;														//flip color before next row
    }	

}
//--
void drawCheckerPiece(RenderWindow &window){
	
	bool isRed = true;	//is piece white or black
    CircleShape checkerPiece(40.f);
	int player1Pieces = 12;
	int player2Pieces = 12;

	int Player1Tiles = 3;
	int Player2Tiles = 5;

    for (int i = 0; i < boardSize; ++i){		//draw board
        for (int j = 0; j < boardSize; ++j){	//draw board

			  

			
				if(i < Player1Tiles){

					checkerPiece.setFillColor(isRed ? sf::Color::Red : sf::Color::Blue);	//if white true then color white else color black
					checkerPiece.setPosition(j * tileSize, i * tileSize);
					
					if(j%2!=0){
						if(i%2==0){
							window.draw(checkerPiece);													//draw tile
						}
					}
					else if(j%2==0 && i%2!=0){
						window.draw(checkerPiece);
					}
					isRed = !isRed;													//flip color
				}
				else if(Player2Tiles <= i){
					checkerPiece.setFillColor(isRed ? sf::Color::Blue : sf::Color::Red);	//if white true then color white else color black
					//tile.setPosition(tile.getPosition() + sf::Vector2f((tileSize - checkerPiece.getRadius()) / 2, (tileSize - checkerPiece.getRadius()) / 2));						//set position of tile within the row
					checkerPiece.setPosition(j * tileSize, i * tileSize);
					if(j%2!=0){
						if(i%2==0){
							window.draw(checkerPiece);													//draw tile
						}
						//window.draw(checkerPiece);													//draw tile
					}													//draw tile
					else if(j%2==0 && i%2!=0){
						window.draw(checkerPiece);
					}
					isRed = !isRed;
				}
		}
		isRed = !isRed;														//flip color before next row	
	}
}

int main()
{
    bool move = false;
    double dx = 0, dy = 0;

    // Vector2i pos = Mouse::getPosition(window);
	sf::RenderWindow window(sf::VideoMode(tileSize * boardSize, tileSize * boardSize), "Checkers");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type) //switch statement for event type
			{
			case Event::MouseButtonPressed:    //if key is released    
                if(event.mouseButton.button == Mouse::Left){
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    cout << "mouse x: " << mousePos.x << endl;
                    cout << "mouse y: " << mousePos.y << endl;
                    
                }
                break;
            
            case Event::MouseButtonReleased:
				

				break;          //break
			case Event::Closed: //if window is closed
				window.close();     //close window

				break;                  //break

			}
            
        }

        window.clear(sf::Color::White);
        drawChessBoard(window);
		drawCheckerPiece(window);
        window.display();
    }

		window.display();       //display window
	
    return 0;
}