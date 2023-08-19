#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

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

class Player{

public:
	int currentPlayerPiece = 1;
	int opponentPiece = -1;
	bool pieceSelected = false;
	int notYourTurn = 0;
	
	bool canPieceCaptureAgain(int newRowVar, int newColVar){
		if(isCaptureValid(newRowVar, newColVar, newRowVar + 2, newColVar + 2) || isCaptureValid(newRowVar, newColVar, newRowVar + 2, newColVar - 2) || isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar + 2) || isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar - 2)){
			return true;
		}
		return false;
	}
	void switchPlayerTurn(){
		if(currentPlayerPiece == 1){
			currentPlayerPiece = -1;
			opponentPiece = 1;
		}
		else{
			currentPlayerPiece = 1;
			opponentPiece = -1;
		}
	}
	bool isCaptureValid(int oldRow, int oldCol, int newRow, int newCol) {
		// Calculate the row and column of the tile that should be captured
		int captureRow = (oldRow + newRow) / 2;
		int captureCol = (oldCol + newCol) / 2;

		// Check if the capturing move is diagonally adjacent
		if (abs(newRow - oldRow) == 2 && abs(newCol - oldCol) == 2) {
			// Check if the destination tile is empty and the capturing tile has an opponent's piece
			if (board_arr[newRow][newCol] == 0 && board_arr[captureRow][captureCol] == opponentPiece) {
				return true;
			}
		}
		return false;
	}
	
};

Player player1;

const int boardSize = 8;	//size of board
const int tileSize = 59;	//size of tiles
int tileCheck = 0;			//check if tile is white or black
int tileValue[8][8];			//value of tile


int size = 5;	//size of piece


void loadPosition(){
	int k = 0;

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

void Kill(int &oldRow, int &oldCol, int &newRow, int &newCol, int &captureRow, int &captureCol, int &n){
    // Update the game state
	pieces[n].setPosition(newCol * tileSize, newRow * tileSize);
    board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
    board_arr[oldRow][oldCol] = 0;
    board_arr[captureRow][captureCol] = 0;

    // Find the index of the captured piece in the pieces array
    int capturedPieceIndex = -1;
    for (int i = 0; i < 24; i++) {
        if (pieces[i].getPosition() == Vector2f(captureCol * tileSize, captureRow * tileSize)) {
            capturedPieceIndex = i;
            break;
        }
    }

    if (capturedPieceIndex != -1) {
        // Update the visual representation (remove the captured piece)
        pieces[capturedPieceIndex].setPosition(-100, -100); // Move it off the screen
    }

    // Finish the move and switch players' turns
    player1.pieceSelected = false;
    player1.switchPlayerTurn();
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

	RenderWindow window(VideoMode(453, 454), "Checkers"); //create window

	int fps = 60;	//set fps to 60
	window.setFramerateLimit(fps);	//set fps limit

	bool movePiece = false;	//check if piece is moving
	float dx = 0, dy = 0;	//delta x and delta y
	float speed = 0.1;		//speed of piece
	int n = 0;
	bool call_is_capture;

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

	loadPosition();		//load position of pieces

	Sprite redPiece;  							//create sprite
	redPiece.setTexture(red);					//set texture to sprite	

	Sprite blackPiece;  							//create sprite
	blackPiece.setTexture(black);					//set texture to sprite	


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
							if(pieces[i].getTexture() == &red){	//if texture is red
								if(player1.currentPlayerPiece == -1){
									cout << "Red piece selected" << endl;	//print message
									player1.pieceSelected = true;	//set piece selected to true
									movePiece = true;	//set move piece to true
									n = i;
									dx = event.mouseButton.x - pieces[i].getPosition().x;	//set delta x
									dy = event.mouseButton.y - pieces[i].getPosition().y;	//set delta y
									oldPos = pieces[i].getPosition();					// Store the original position before moving
									originalPos = pieces[n].getPosition();	// Store the original position before moving
									player1.switchPlayerTurn();	//switch player turn
								}
								else{
									cout << "It is Black Player turn" << endl;	//print message
									player1.notYourTurn = 1;	//set not your turn to 1
								}

							}
							else if(pieces[i].getTexture() == &black){	//if texture is black
								if(player1.currentPlayerPiece == 1){
									cout << "Black piece selected" << endl;	//print message
									player1.pieceSelected = true;	//set piece selected to true
									movePiece = true;	//set move piece to true
									n = i;
									dx = event.mouseButton.x - pieces[i].getPosition().x;	//set delta x
									dy = event.mouseButton.y - pieces[i].getPosition().y;	//set delta y
									oldPos = pieces[i].getPosition();					// Store the original position before moving
									originalPos = pieces[n].getPosition();	// Store the original position before moving
									player1.switchPlayerTurn();	//switch player turn
								}
								else{
									cout << "It is Red Player turn" << endl;	//print message
									player1.notYourTurn = 1;	//set not your turn to 1
								}
							}
							else{
								cout << "Select a piece" << endl;	//print message
							}
							
						}
					}
                    cout << "mouse x: " << mousePos.x << endl;  //print mouse x position
                    cout << "mouse y: " << mousePos.y << endl;  //print mouse y position
                }
                break;        //break
            
            case Event::MouseButtonReleased:	//if key is released
				
				if (event.mouseButton.button == Mouse::Left) {
					// Get the center position of the dropped piece
					Vector2f p = pieces[n].getPosition() + Vector2f(tileSize / 2, tileSize / 2);

					// Convert pixel coordinates to grid coordinates
					int newRow = static_cast<int>(p.y / tileSize);
					int newCol = static_cast<int>(p.x / tileSize);

					int oldRow = static_cast<int>(originalPos.y / tileSize);
					int oldCol = static_cast<int>(originalPos.x / tileSize);

					// Calculate the new position based on grid coordinates
					Vector2f newPos = Vector2f(newCol * tileSize, newRow * tileSize);

					if (player1.pieceSelected == true) {
					
						movePiece = false;	//set move piece to false

						if(player1.notYourTurn == 1){
							player1.notYourTurn = 0;
						}
						// Check if the move is valid and within bounds
						if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize &&
							board_arr[newRow][newCol] != -9) {
								// Valid move
								if(board_arr[newRow][newCol] == 0){
									if (abs(newRow - oldRow) == 2 && abs(newCol - oldCol) == 2) {
										if ((player1.currentPlayerPiece == 1 && newRow > oldRow) || (player1.currentPlayerPiece == -1 && newRow < oldRow)){
											cout << "Jump Check" << endl;
											// Check if the move is a jump
											int jumpRow = (newRow + oldRow) / 2;
											int jumpCol = (newCol + oldCol) / 2;

											if (board_arr[jumpRow][jumpCol] != 0) {
												// Valid jump
												// pieces[n].setPosition(newPos);
												// board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
												// board_arr[oldRow][oldCol] = 0;
												// board_arr[jumpRow][jumpCol] = 0;
												// player1.pieceSelected = false;
												cout << "Kill func call" << endl;
												Kill(oldRow, oldCol, newRow, newCol, jumpRow, jumpCol, n);
												// board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
												// board_arr[oldRow][oldCol] = 0;
												player1.pieceSelected = false;
												player1.switchPlayerTurn();	//switch player turn
											}
											else{
												// Invalid move, revert to the original position
												player1.switchPlayerTurn();	//switch player turn
												pieces[n].setPosition(originalPos);
											}
										}
										else{
												// Invalid move, revert to the original position
												player1.switchPlayerTurn();	//switch player turn
												pieces[n].setPosition(originalPos);
											}
									}
									else if (abs(newRow - oldRow) == 1 && abs(newCol - oldCol) == 1 && board_arr[newRow][newCol] == 0){
										 if ((player1.currentPlayerPiece == 1 && newRow > oldRow) || (player1.currentPlayerPiece == -1 && newRow < oldRow)) {
											pieces[n].setPosition(newPos);
											board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
											board_arr[oldRow][oldCol] = 0;
											player1.pieceSelected = false;
										}
										else{
											// Invalid move, revert to the original position
											player1.switchPlayerTurn();	//switch player turn
											pieces[n].setPosition(originalPos);
										}
									}
									else{
										// Invalid move, revert to the original position
										player1.switchPlayerTurn();	//switch player turn
										pieces[n].setPosition(originalPos);
									}
								}
								else if(board_arr[newRow][newCol] == 1){
									// Invalid move, revert to the original position
									player1.switchPlayerTurn();	//switch player turn
									pieces[n].setPosition(originalPos);
								}
								else if(board_arr[newRow][newCol] == -1){
									// Invalid move, revert to the original position
									player1.switchPlayerTurn();	//switch player turn
									pieces[n].setPosition(originalPos);
								}
								else if(board_arr[newRow][newCol] == -9){
									// Invalid move, revert to the original position
									player1.switchPlayerTurn();	//switch player turn
									pieces[n].setPosition(originalPos);
								}

						} else if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize &&
							board_arr[newRow][newCol] == -9) {
							// Invalid move, revert to the original position
							player1.switchPlayerTurn();	//switch player turn
							pieces[n].setPosition(originalPos);
						}

						cout << "board_arr[newRow][newCol] = " << board_arr[newRow][newCol] << endl;
						cout << "board_arr[oldRow][oldCol] = " << board_arr[oldRow][oldCol] << endl;
						// print whole board values
						for(int i = 0; i < boardSize; i++){
							for(int j = 0; j < boardSize; j++){
								cout << board_arr[i][j] << " ";
							}
							cout << endl;
						}
					}
				}else{
					cout << "Player , please select a piece to move!" << endl;
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