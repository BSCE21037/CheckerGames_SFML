#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int boardSize = 8;	//size of board
const int tileSize = 80;	//size of tiles
int tileCheck = 0;			//check if tile is white or black
int tileValue[8][8];			//value of tile

int size = 56;	//size of piece

Sprite pieces[24];	//array of pieces

int board[8][8] = {	//board array
	-1, 0,-1, 0,-1, 0,-1, 0,// --------
	 0,-1, 0,-1, 0,-1, 0,-1,// player 1
	-1, 0,-1, 0,-1, 0,-1, 0,// --------

	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,

	 0,-1, 0,-1, 0,-1, 0,-1,// --------
	-1, 0,-1, 0,-1, 0,-1, 0,// player 2
	 0,-1, 0,-1, 0,-1, 0,-1 // --------
};


RectangleShape tile(sf::Vector2f(tileSize, tileSize));	//create tile   (global variable)
CircleShape checkerPiece(40.f);                         //create checker piece  (global variable)

void drawChessBoard(RenderWindow &window){              //draw chess board function

	
	bool isWhite = true;	//is tile white or black

	for(int i = 0; i < boardSize; i++){                 //for loop
		for(int j = 0; j < boardSize; j++){             //nested for loop
			tileValue[i][j] = -99;                      //set tile value to -99
		}
	}
   
    for (int i = 0; i < boardSize; ++i){		//draw board
        for (int j = 0; j < boardSize; ++j){	//draw board

            tile.setFillColor(isWhite ? sf::Color::White : sf::Color::Black);	//if white true then color white else color black
            tile.setPosition(j * tileSize, i * tileSize);						//set position of tile within the row
            window.draw(tile);													//draw tile
			if(tile.getFillColor() == sf::Color::Black){                        //if tile is black
				tileValue[i][j] = 0;                                            //set tile value to 0
			}
            isWhite = !isWhite;													//flip color
        }
        isWhite = !isWhite;														//flip color before next row
    }	
}
//--
// void drawCheckerPiece(RenderWindow &window){        //draw chess board function

// 	bool isRed = true;	//is piece white or black
// 	int player1Pieces = 12;     //number of pieces for player 1     
// 	int player2Pieces = 12;     //number of pieces for player 2

// 	int Player1Tiles = 3;       //number of rows of tiles for player 1
// 	int Player2Tiles = 5;       //number of starting rows of tiles for player 2

//     for (int i = 0; i < boardSize; ++i){		//draw board
//         for (int j = 0; j < boardSize; ++j){	//draw board
// 				if(i < Player1Tiles){                                    //if row is less than player 1 tiles

// 					checkerPiece.setFillColor(isRed ? sf::Color::Red : sf::Color::Blue);	//if red true then color red else color blue
// 					checkerPiece.setPosition(j * tileSize, i * tileSize);               //set position of piece within the row
// 					if(tileValue[i][j] == 0){                                        //if tile value is 0
// 						window.draw(checkerPiece);                                  //draw piece
// 						tileValue[i][j] =  1;                                       //set tile value to 1
// 					}
// 					isRed = !isRed;													//flip color
// 				}
// 				else if(Player2Tiles <= i){
// 					checkerPiece.setFillColor(isRed ? sf::Color::Blue : sf::Color::Red);	//if red true then color blue else color red
// 					checkerPiece.setPosition(j * tileSize, i * tileSize);           //set position of piece within the row
// 					if(tileValue[i][j] == 0){                                       //if tile value is 0
// 						window.draw(checkerPiece);                                  //draw piece
// 						tileValue[i][j] =  1;                                       //set tile value to 1
// 					}
// 					isRed = !isRed;                                                 //flip color
// 				}
// 		}
// 		isRed = !isRed;														//flip color before next row	
// 	}
// }


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 400), "Checkers"); //create window

	int fps = 60;	//set fps to 60
	window.setFramerateLimit(fps);	//set fps limit

	bool movePiece = false;	//check if piece is moving
	float dx = 0, dy = 0;	//delta x and delta y
	float speed = 0.1;		//speed of piece


	Texture red;								//create texture
	if(!red.loadFromFile("red_piece.png")){		//if texture does not load
		cout << "Error loading red piece" << endl;	//print error message
	}

	Sprite redPiece;  							//create sprite
	redPiece.setTexture(red);					//set texture to sprite
	redPiece.setScale(0.05, 0.05);				//set scale of sprite


    while (window.isOpen()) //while window is open
    {
		Vector2i mousePos = Mouse::getPosition(window); //get mouse position
        sf::Event event;    //create event
        while (window.pollEvent(event)) //while window is polling for event
        {
			switch (event.type) //switch statement for event type
			{

			case Event::MouseButtonPressed:    //if key is pressed    
                if(event.mouseButton.button == Mouse::Left){    //if left mouse button is pressed
					if(redPiece.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){	//if mouse is within bounds of sprite
						movePiece = true;	//set move piece to true
						dx = event.mouseButton.x - redPiece.getPosition().x;	//set delta x
						dy = event.mouseButton.y - redPiece.getPosition().y;	//set delta y

					}
                    cout << "mouse x: " << mousePos.x << endl;  //print mouse x position
                    cout << "mouse y: " << mousePos.y << endl;  //print mouse y position
					// cout << "tile x: " << mousePos.x / tileSize << endl;    //print tile x position
					// cout << "tile y: " << mousePos.y / tileSize << endl;    //print tile y position
					// cout << "tile value: " << tileValue[mousePos.y / tileSize][mousePos.x / tileSize] << endl;  //print tile value
					//write a code for the movement of the piece
                    
                }
                break;        //break
            
            case Event::MouseButtonReleased:	//released
				if(event.mouseButton.button == Mouse::Left){	//if left mouse button is released
					movePiece = false;	//set move piece to false
				}
				break;          //break

			case Event::Closed: //if window is closed
				window.close();     //close window
				break;                  //break

			}
			if(movePiece){	//if piece is moving
				redPiece.setPosition(mousePos.x - dx, mousePos.y - dy);	//set position of piece
			}	
            
        }

        window.clear(); //clear window
        //drawChessBoard(window);        //draw chess board
		window.draw(redPiece); 		//draw red piece
        window.display();    //display window
    }

		window.display();       //display window
	
    return 0;
} 
