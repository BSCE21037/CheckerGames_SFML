#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int boardSize = 8;	//size of board
const int tileSize = 59;	//size of tiles
int tileCheck = 0;			//check if tile is white or black
int tileValue[8][8];			//value of tile


int size = 5;	//size of piece

Sprite pieces[24];	//array of piec
int board_arr[8][8] = {	//board array
	-9, -1, -9,-1, -9,-1, -9,-1,	// --------
	-1, -9,-1, -9,-1, -9,-1, -9,// player 1
	-9, -1, -9,-1, -9,-1, -9,-1,// --------

	0, -9, 0, -9, 0, -9, 0, -9,
	-9, 0, -9, 0, -9, 0, -9, 0,

	1, -9, 1, -9, 1, -9, 1, -9,// --------
	-9, 1, -9, 1, -9, 1, -9, 1, // player 2
	1, -9, 1, -9, 1, -9, 1, -9// --------
	
};

void loadPosition(){
	int k = 0;
	// float xOffset = 0.1 * tileSize; // Adjust this value for horizontal spacing
    // float yOffset = 0.0000000001 * tileSize; // Adjust this value for vertical spacing

	for(int i = 0; i < boardSize; i++){
		for(int j = 0; j < boardSize; j++){
			int n = board_arr[i][j];
			if(!n){
				continue;
			}
			else if(n == -1){
				pieces[k].setTextureRect(IntRect(0.7 * 0, 0, 0.7, 0.7));
				pieces[k].setPosition(j * tileSize, i * tileSize);
				k++;
			}
			else if(n == 1){
				pieces[k].setTextureRect(IntRect(0.7 * 1, 0, 0.7, 0.7));
				pieces[k].setPosition(j * tileSize, i * tileSize);
				k++;
			}
		}
	}	
}


//RectangleShape tile(sf::Vector2f(tileSize, tileSize));	//create tile   (global variable)
// CircleShape checkerPiece(40.f);                         //create checker piece  (global variable)

// void drawChessBoard(RenderWindow &window){              //draw chess board function

	
// 	bool isWhite = true;	//is tile white or black

// 	for(int i = 0; i < boardSize; i++){                 //for loop
// 		for(int j = 0; j < boardSize; j++){             //nested for loop
// 			tileValue[i][j] = -99;                      //set tile value to -99
// 		}
// 	}
   
//     for (int i = 0; i < boardSize; ++i){		//draw board
//         for (int j = 0; j < boardSize; ++j){	//draw board

//             tile.setFillColor(isWhite ? sf::Color::White : sf::Color::Black);	//if white true then color white else color black
//             tile.setPosition(j * tileSize, i * tileSize);						//set position of tile within the row
//             window.draw(tile);													//draw tile
// 			if(tile.getFillColor() == sf::Color::Black){                        //if tile is black
// 				tileValue[i][j] = 0;                                            //set tile value to 0
// 			}
//             isWhite = !isWhite;													//flip color
//         }
//         isWhite = !isWhite;														//flip color before next row
//     }	
// }
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

	sf::RenderWindow window(sf::VideoMode(453, 454), "Checkers"); //create window

	int fps = 60;	//set fps to 60
	window.setFramerateLimit(fps);	//set fps limit

	bool movePiece = false;	//check if piece is moving
	float dx = 0, dy = 0;	//delta x and delta y
	float speed = 0.1;		//speed of piece
	int n = 0;

	Vector2f originalPos; // Store the original position of the piece
	Vector2f oldPos;			//old position of piece


	Texture red, black, board;								//create texture
	if(!red.loadFromFile("red_piece.png")){		//if texture does not load
		cout << "Error loading red piece" << endl;	//print error message
	}
	if(!board.loadFromFile("board0.png")){		//if texture does not load
		cout << "Error loading the game board" << endl;	//print error message
	}
	if(!black.loadFromFile("black.png")){		//if texture does not load
		cout << "Error loading black piece" << endl;	//print error message
	}

	Sprite boardSprite;								//create sprite
	boardSprite.setTexture(board);					//set texture to sprite
	//boardSprite.setScale(0.25, 0.25);					//set scale of sprite

	loadPosition();		//load position of pieces


	Sprite redPiece;  							//create sprite
	redPiece.setTexture(red);					//set texture to sprite
	redPiece.setScale(0.02, 0.02);				//set scale of sprite

	Sprite blackPiece;  							//create sprite
	blackPiece.setTexture(black);					//set texture to sprite	
	//blackPiece.setScale(0.05, 0.05);				//set scale of sprite


	for(int i = 0; i < 12; i++){		//for loop
		pieces[i].setTexture(red);		//set texture to sprite
		pieces[i].setScale(0.02, 0.02);	//set scale of sprite
	}
	for(int i = 12; i < 24; i++){		//for loop
		pieces[i].setTexture(black);		//set texture to sprite
		pieces[i].setScale(0.05, 0.05);	//set scale of sprite
	}

    while (window.isOpen()) //while window is open
    {
		Vector2i mousePos = Mouse::getPosition(window); //get mouse position
        Event event;    //create event
        while (window.pollEvent(event)) //while window is polling for event
        {
			switch (event.type) //switch statement for event type
			{

			case Event::MouseButtonPressed:    //if key is pressed    
                if(event.mouseButton.button == Mouse::Left){    //if left mouse button is pressed
					for(int i=0; i<24; i++){
						if(pieces[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){	//if mouse is within bounds of sprite
							movePiece = true;	//set move piece to true
							n = i;
							dx = event.mouseButton.x - pieces[i].getPosition().x;	//set delta x
							dy = event.mouseButton.y - pieces[i].getPosition().y;	//set delta y
            				oldPos = pieces[i].getPosition();					// Store the original position before moving
							originalPos = pieces[n].getPosition();

						}
					}
                    cout << "mouse x: " << mousePos.x << endl;  //print mouse x position
                    cout << "mouse y: " << mousePos.y << endl;  //print mouse y position
					// cout << "tile x: " << mousePos.x / tileSize << endl;    //print tile x position
					// cout << "tile y: " << mousePos.y / tileSize << endl;    //print tile y position
					// cout << "tile value: " << tileValue[mousePos.y / tileSize][mousePos.x / tileSize] << endl;  //print tile value
					//write a code for the movement of the piece
                    
                }
                break;        //break
            
            case Event::MouseButtonReleased:	//if key is released

				// if(event.mouseButton.button == Mouse::Left){	//if left mouse button is released
				// 	movePiece = false;	//set move piece to false
				// 	Vector2f p = pieces[n].getPosition() + Vector2f(tileSize/2, tileSize/2);	//get position of piece
				// 	//oldPos = static_cast<Vector2f>(mousePos);;	//create vector2f
				// 	Vector2f newPos = Vector2f(tileSize * int(p.x / tileSize), tileSize * int(p.y / tileSize));	//get new position of piece
				// 	cout << "newPos: " << newPos.x << " " << newPos.y << endl;
				// 	if(board_arr[int(newPos.y / tileSize)][int(newPos.x / tileSize)] == -9){
				// 		//invalid move/ invalid tile
				// 		pieces[n].setPosition(oldPos);	//set position of piece
				// 		//pieces[n].setPosition(dx,dy);	//set position of piece
				// 	}
				// 	else{
				// 		//valid move
				// 		pieces[n].setPosition(newPos);	//set position of piece
				// 	}
				// }
				// break;	//break
				
				if (event.mouseButton.button == Mouse::Left) {
					movePiece = false;

					// Get the center position of the dropped piece
					Vector2f p = pieces[n].getPosition() + Vector2f(tileSize / 2, tileSize / 2);

					// Convert pixel coordinates to grid coordinates
					int newRow = static_cast<int>(p.y / tileSize);
					int newCol = static_cast<int>(p.x / tileSize);

					// Calculate the new position based on grid coordinates
					Vector2f newPos = Vector2f(newCol * tileSize, newRow * tileSize);

					// Check if the move is valid and within bounds
					if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize &&
						board_arr[newRow][newCol] != -9) {
						// Valid move
						pieces[n].setPosition(newPos);
					} else {
						// Invalid move, revert to the original position
						pieces[n].setPosition(originalPos);
					}
				}

				break;	//break


			case Event::Closed: //if window is closed
				window.close();     //close window
				break;                  //break

			}
			if(movePiece){	//if piece is moving
				pieces[n].setPosition(mousePos.x - dx, mousePos.y - dy);	//set position of piece
				oldPos = pieces[n].getPosition(); // Update oldPos while the piece is being moved
			}	
            
        }

        window.clear(); //clear window
        //drawChessBoard(window);        //draw chess board
		window.draw(boardSprite);	//draw red piece
		for(int i = 0; i < 24; i++){	//for loop
			window.draw(pieces[i]);		//draw pieces
		}
        window.display();    //display window
    }

		
	
    return 0;
}