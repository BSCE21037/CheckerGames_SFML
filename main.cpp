#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int boardSize = 8;	//size of board
const int tileSize = 80;	//size of tiles
int tileCheck = 0;			//check if tile is white or black
int tileValue[8][8];			//value of tile


RectangleShape tile(sf::Vector2f(tileSize, tileSize));	//create tile   (global variable)
CircleShape checkerPiece(40.f);                         //create checker piece  (global variable)

void drawChessBoard(RenderWindow& window) {              //draw chess board function


	bool isWhite = true;	//is tile white or black

	for (int i = 0; i < boardSize; i++) {                 //for loop
		for (int j = 0; j < boardSize; j++) {             //nested for loop
			tileValue[i][j] = -99;                      //set tile value to -99
		}
	}

	for (int i = 0; i < boardSize; ++i) {		//draw board
		for (int j = 0; j < boardSize; ++j) {	//draw board

			tile.setFillColor(isWhite ? sf::Color::White : sf::Color::Black);	//if white true then color white else color black
			tile.setPosition(j * tileSize, i * tileSize);						//set position of tile within the row
			window.draw(tile);													//draw tile
			if (tile.getFillColor() == sf::Color::Black) {                        //if tile is black
				tileValue[i][j] = 0;                                            //set tile value to 0
			}
			isWhite = !isWhite;													//flip color
		}
		isWhite = !isWhite;														//flip color before next row
	}
}
//--
void drawCheckerPiece(RenderWindow& window) {        //draw chess board function

	bool isRed = true;	//is piece white or black
	int player1Pieces = 12;     //number of pieces for player 1     
	int player2Pieces = 12;     //number of pieces for player 2

	int Player1Tiles = 3;       //number of rows of tiles for player 1
	int Player2Tiles = 5;       //number of starting rows of tiles for player 2

	for (int i = 0; i < boardSize; ++i) {		//draw board
		for (int j = 0; j < boardSize; ++j) {	//draw board
			if (i < Player1Tiles) {                                    //if row is less than player 1 tiles

				checkerPiece.setFillColor(isRed ? sf::Color::Red : sf::Color::Blue);	//if red true then color red else color blue
				checkerPiece.setPosition(j * tileSize, i * tileSize);               //set position of piece within the row
				if (tileValue[i][j] == 0) {                                        //if tile value is 0
					window.draw(checkerPiece);                                  //draw piece
					tileValue[i][j] = 1;                                       //set tile value to 1
				}
				isRed = !isRed;													//flip color
			}
			else if (Player2Tiles <= i) {
				checkerPiece.setFillColor(isRed ? sf::Color::Blue : sf::Color::Red);	//if red true then color blue else color red
				checkerPiece.setPosition(j * tileSize, i * tileSize);           //set position of piece within the row
				if (tileValue[i][j] == 0) {                                       //if tile value is 0
					window.draw(checkerPiece);                                  //draw piece
					tileValue[i][j] = 2;                                       //set tile value to 1
				}
				isRed = !isRed;                                                 //flip color
			}
		}
		isRed = !isRed;														//flip color before next row	
	}
}


int main()
{
	bool move = false;      //check if piece is moving
	double dx = 0, dy = 0;  //change in x and y

	sf::RenderWindow window(sf::VideoMode(tileSize * boardSize, tileSize * boardSize), "Checkers"); //create window

	while (window.isOpen()) //while window is open
	{
		sf::Event event;    //create event
		while (window.pollEvent(event)) //while window is polling for event
		{
			switch (event.type) //switch statement for event type
			{

			case Event::MouseButtonPressed:    //if key is pressed    
				if (event.mouseButton.button == Mouse::Left) {    //if left mouse button is pressed
					Vector2i mousePos = Mouse::getPosition(window); //get mouse position
					Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); //get mouse position
					cout << "mouse x: " << mousePos.x << endl;  //print mouse x position
					cout << "mouse y: " << mousePos.y << endl;  //print mouse y position
					cout << "tile x: " << mousePos.x / tileSize << endl;    //print tile x position
					cout << "tile y: " << mousePos.y / tileSize << endl;    //print tile y position
					cout << "tile value: " << tileValue[mousePos.y / tileSize][mousePos.x / tileSize] << endl;  //print tile value
					//write a code for the movement of the piece
					if (tileValue[mousePos.y / tileSize][mousePos.x / tileSize] == 1) {   //if tile value is 1
						move = true;                                                //set move to true
					}
					else {                                                        //else
						move = false;                                            //set move to false
					}
					//write a code to drag the piece    
					if (move) {                                                    //if move is true
						dx = mousePos.x - tile.getPosition().x;                 //set dx to mouse x position - tile x position
						dy = mousePos.y - tile.getPosition().y;                //set dy to mouse y position - tile y position
					}


				}
				break;        //break

			case Event::MouseButtonReleased:	//released
				if (event.mouseButton.button == Mouse::Left)	//if left mouse button is released
				{
					move = false;   //set move to false
				}

				break;          //break

			case Event::Closed: //if window is closed
				window.close();     //close window
				break;                  //break

			}
			if (move) {   //if move is true
				checkerPiece.setPosition(Mouse::getPosition(window).x - dx, Mouse::getPosition(window).y - dy); //set position of piece to mouse position - dx and dy
			}

		}

		window.clear(sf::Color::White); //clear window
		drawChessBoard(window);        //draw chess board
		drawCheckerPiece(window);   //draw checker piece
		window.display();    //display window
	}

	window.display();       //display window

	return 0;
}