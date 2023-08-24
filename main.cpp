#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.cpp"
#include "player.cpp"
#include "gameOver.cpp"
#include "instructions.cpp"
using namespace std;
using namespace sf;

Sprite pieces[24];	//array of pieces
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

Player player1;

const int boardSize = 8;	//size of board
const int tileSize = 58;	//size of tiles

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

bool isCaptureValid(int oldRow, int oldCol, int newRow, int newCol) {
	// Calculate the row and column of the tile that should be captured
	int captureRow = (oldRow + newRow) / 2;
	int captureCol = (oldCol + newCol) / 2;

	// Check if the capturing move is diagonally adjacent
	if (abs(newRow - oldRow) == 2 && abs(newCol - oldCol) == 2) {
		// Check if the destination tile is empty and the capturing tile has an opponent's piece
		if (board_arr[newRow][newCol] == 0 && board_arr[captureRow][captureCol] == player1.opponentPiece) {
			return true;
		}
	}
	return false;
}

bool canPieceCaptureAgain(int newRowVar, int newColVar, int currentPiece, int k){
	if (k == 2 || k == -2) {	//if piece is king
        if (isCaptureValid(newRowVar, newColVar, newRowVar + 2, newColVar + 2) ||
            isCaptureValid(newRowVar, newColVar, newRowVar + 2, newColVar - 2) ||
            isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar + 2) ||
            isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar - 2)) {	
            return true;
        }
    }
	if((isCaptureValid(newRowVar, newColVar, newRowVar + 2, newColVar + 2) && currentPiece == -1)|| 
	(isCaptureValid(newRowVar, newColVar, newRowVar + 2, newColVar - 2) && currentPiece == -1) || 
	(isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar + 2) && currentPiece == 1) || 
	(isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar - 2)&& currentPiece == 1)){	//if piece is not king
		return true;
	}
	return false;
}

//loading Sounds
Music pop;
Music start;
Music checker;
Music w;
Music k;
Music wrong;
Music KillSound;
void PopSound(){
	
	if(!pop.openFromFile("sounds/pop.ogg")){
		cout << "Error loading sound" << endl;
	}
	pop.setVolume(100.f);
	pop.play();
}
void startSound(){
	
	if(!start.openFromFile("sounds/board-start.ogg")){
		cout << "Error loading sound" << endl;
	}
	start.play();
}
void checkerSound(){
	
	if(!checker.openFromFile("sounds/checker.ogg")){
		cout << "Error loading sound" << endl;
	}
	checker.play();
}
void winSound(){

	if(!w.openFromFile("sounds/win.ogg")){
		cout << "Error loading sound" << endl;
	}
	w.play();
}
void KingSound(){

	if(!k.openFromFile("sounds/king.ogg")){
		cout << "Error loading sound" << endl;
	}
	k.play();
}
void wrongMoveSound(){

	if(!wrong.openFromFile("sounds/wrong_piece.ogg")){
		cout << "Error loading sound" << endl;
	}
	wrong.play();
}
void killSound(){

	if(!KillSound.openFromFile("sounds/kill.ogg")){
		cout << "Error loading sound" << endl;
	}
	KillSound.play();
}

void Kill(int &oldRow, int &oldCol, int &newRow, int &newCol, int &captureRow, int &captureCol, int &n){
    // Update the game state
	pieces[n].setPosition(newCol * tileSize, newRow * tileSize);
    board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
    board_arr[oldRow][oldCol] = 0;
    board_arr[captureRow][captureCol] = 0;
	player1.moves = 0;
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
		if(player1.currentPlayerPiece == 1){
			player1.red_score++;
			cout << "Red Score: " << player1.red_score << endl;
			player1.black_left--;
			cout << "Black Left: " << player1.black_left << endl;
			cout << "---------------------------------" << endl;	//print line
		}
		else{
			player1.black_score++;
			cout << "Black Score: " << player1.black_score << endl;
			player1.red_left--;
			cout << "Red Left: " << player1.red_left << endl;
			cout << "---------------------------------" << endl;	//print line
		}
        pieces[capturedPieceIndex].setPosition(-100, -100); // Move it off the screen
		killSound();
    }

    // Finish the move and switch players' turns
    player1.pieceSelected = false;
    player1.switchPlayerTurn();
}

bool isValidMoveAvailable(Player& player, int pieceIndex)
{
    // Get the row and column of the piece
    int row = static_cast<int>(pieces[pieceIndex].getPosition().y / tileSize);
    int col = static_cast<int>(pieces[pieceIndex].getPosition().x / tileSize);

    // Check possible moves for regular pieces
    if (abs(player.currentPlayerPiece) == 1)
    {
        // Check diagonally forward left
        if (row - 1 >= 0 && col - 1 >= 0 &&
            board_arr[row - 1][col - 1] == 0)
        {
            return true;
        }
        
        // Check diagonally forward right
        if (row - 1 >= 0 && col + 1 < boardSize &&
            board_arr[row - 1][col + 1] == 0)
        {
            return true;
        }
    }
    // Check possible moves for king pieces
    else if (abs(player.currentPlayerPiece) == 2)
    {
        // Check diagonally forward left
        if (row - 1 >= 0 && col - 1 >= 0 &&
            board_arr[row - 1][col - 1] == 0)
        {
            return true;
        }
        
        // Check diagonally forward right
        if (row - 1 >= 0 && col + 1 < boardSize &&
            board_arr[row - 1][col + 1] == 0)
        {
            return true;
        }

        // Check diagonally backward left
        if (row + 1 < boardSize && col - 1 >= 0 &&
            board_arr[row + 1][col - 1] == 0)
        {
            return true;
        }
        
        // Check diagonally backward right
        if (row + 1 < boardSize && col + 1 < boardSize &&
            board_arr[row + 1][col + 1] == 0)
        {
            return true;
        }
    }

    return false;
}

int main()
{
	RenderWindow window(VideoMode(453, 454), "2 Player Checker Game", Style::Titlebar | Style::Close); //create window
	bool menu, instruc, game, result;	//create bools for menu, game, and end
	menu = true;			//set menu to true
	instruc = false;		//set instructions to false
	game = false;			//set game to false
	result = false;			//set end to false

	int fps = 60;	//set fps to 60
	window.setFramerateLimit(fps);	//set fps limit

	bool movePiece = false;	//check if piece is moving
	float dx = 0, dy = 0;	//delta x and delta y
	int n = 0;	//piece index
	int king[24];		//array to store if piece is king
	for (int i = 0; i < 24; i++)//initializing king array
	{
		king[i] = 0;
	}
	

	Vector2f originalPos; // Store the original position of the piece
	Vector2f oldPos;			//old position of piece


	Texture red, black, board;								//create texture
	if(!red.loadFromFile("sprites/red_piece.png")){		//if texture does not load
		cout << "Error loading red piece" << endl;	//print error message
	}
	if(!board.loadFromFile("sprites/board0.png")){		//if texture does not load
		cout << "Error loading the game board" << endl;	//print error message
	}
	if(!black.loadFromFile("sprites/black.png")){		//if texture does not load
		cout << "Error loading black piece" << endl;	//print error message
	}

	Sprite boardSprite;								//create sprite
	boardSprite.setTexture(board);					//set texture to sprite

	loadPosition();		//load position of pieces

	Sprite redPiece;  							//create sprite
	redPiece.setTexture(red);					//set texture to sprite	

	Sprite blackPiece;  							//create sprite
	blackPiece.setTexture(black);					//set texture to sprite	

	Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		cout << "Error loading font" << endl;
	}

	//Text textR;		//create text
	for(int i = 0; i < 12; i++){		//for loop
		pieces[i].setTexture(red);		//set texture to sprite
		pieces[i].setScale(0.022, 0.022);	//set scale of sprite
	}
	for(int i = 12; i < 24; i++){		//for loop
		pieces[i].setTexture(black);		//set texture to sprite
		pieces[i].setScale(0.07, 0.07);	//set scale of sprite
	}

	Menu menU(window.getSize().x, window.getSize().y);	//create menu

	GameOver gameover(window.getSize().x, window.getSize().y);	//create game over

	sf::Vector2i lastMousePos; // To keep track of the last mouse position

    while (window.isOpen()) //while window is open
    {
		Vector2i mousePos = Mouse::getPosition(window); //get mouse position
        Event event;    //create event
        while (window.pollEvent(event)) //while window is polling for event
        {
			switch (event.type) //switch statement for event type
			{ 
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menU.MoveUp();
						break;

					case sf::Keyboard::Down:
						menU.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menU.GetPressedItem())
						{
						case 0:
							menu = false;
							instruc = true;
							game = false;
							result = false;
							PopSound();
							break;
						case 1:
							window.close();
							break;
						}

						break;
					}

					break;

				case Event::MouseMoved:	//if mouse is moved
                
					if (mousePos.y > lastMousePos.y)
					{
						menU.MoveDown();
					}
					else if (mousePos.y < lastMousePos.y)
					{
						menU.MoveUp();
					}
                
                	lastMousePos = mousePos; // Update the last mouse position
				break;

			case Event::MouseButtonPressed:    //if key is pressed    
                if(event.mouseButton.button == Mouse::Left){    //if left mouse button is pressed
					if(menu == true){	//if menu is true
						 // Get mouse position
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);

						// Check if the mouse position is within the bounds of menu items
						if (menU.isMouseOverItem(mousePos))
						{
							// Get mouse position
							int selectedItem = menU.GetPressedItem();
							switch (selectedItem)
							{
							case 0:
								menu = false;
								instruc = true;
								game = false;
								result = false;
								PopSound();
								break;
							case 1:
								window.close();
								break;
							}
						}
					}
					else if(game == true){
						for(int i=0; i<24; i++){
							if(pieces[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){	//if mouse is within bounds of sprite
								if(pieces[i].getTexture() == &red){	//if texture is red
									if(player1.currentPlayerPiece == -1 || player1.currentKingPiece == -2){
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
										cout << "It is Player 1's turn" << endl;	//print message
										cout << "---------------------------------" << endl;	//print line
										player1.notYourTurn = 1;	//set not your turn to 1
									}

								}
								else if(pieces[i].getTexture() == &black){	//if texture is black
									if(player1.currentPlayerPiece == 1 || player1.currentKingPiece == 2){
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
										cout << "It is Player 2's turn" << endl;	//print message
										cout << "---------------------------------" << endl;	//print line
										player1.notYourTurn = 1;	//set not your turn to 1
									}
								}
								else{
									cout << "Select a piece" << endl;	//print message
									cout << "---------------------------------" << endl;	//print line
								}
								
							}
						}
						// cout << "mouse x: " << mousePos.x << endl;  //print mouse x position
						// cout << "mouse y: " << mousePos.y << endl;  //print mouse y position
					}
					else if(result == true){
						
					}
				}
                break;        //break
            
            case Event::MouseButtonReleased:	//if key is released
				
				if (event.mouseButton.button == Mouse::Left) {
					if(game == true){
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
											if (((player1.currentPlayerPiece == 1 || player1.currentKingPiece == 2) && newRow > oldRow) || ((player1.currentPlayerPiece == -1 || player1.currentKingPiece == -2) && newRow < oldRow) || board_arr[oldRow][oldCol] == 2 || board_arr[oldRow][oldCol] == -2) {
												// Check if the move is a jump
												int jumpRow = (newRow + oldRow) / 2;
												int jumpCol = (newCol + oldCol) / 2;

												if (board_arr[jumpRow][jumpCol] != 0) {
													// Valid jump
													Kill(oldRow, oldCol, newRow, newCol, jumpRow, jumpCol, n);
													if (canPieceCaptureAgain(newRow, newCol, player1.currentPlayerPiece, board_arr[newRow][newCol])) {
														cout << "You can capture again!" << endl;
														cout << "---------------------------------" << endl;	//print line
														oldPos = newPos; // Update the old position to the new position
														
													} else {
														// Finish the move and switch players' turns
														player1.pieceSelected = false;
														player1.switchPlayerTurn();
													}
													if ((player1.currentPlayerPiece == 1 && newRow == boardSize - 1) ||
														(player1.currentPlayerPiece == -1 && newRow == 0)) {
															// King me
															player1.currentPlayerPiece = player1.currentPlayerPiece * 2;
															board_arr[newRow][newCol] = player1.currentPlayerPiece; // Mark as king
															king[n] = 1;//set king to 1
															KingSound();
													}
												}
												else{
													// Invalid move, revert to the original position
													player1.switchPlayerTurn();	//switch player turn
													pieces[n].setPosition(originalPos);
													wrongMoveSound();
												}
											}
											else{
													// Invalid move, revert to the original position
													player1.switchPlayerTurn();	//switch player turn
													pieces[n].setPosition(originalPos);
													wrongMoveSound();
												}
										}
										else if (abs(newRow - oldRow) == 1 && abs(newCol - oldCol) == 1 && board_arr[newRow][newCol] == 0){
											if ((player1.currentPlayerPiece == 1 && newRow > oldRow) || (player1.currentPlayerPiece == -1 && newRow < oldRow) || (board_arr[oldRow][oldCol] == 2 || board_arr[oldRow][oldCol] == -2)) {
												pieces[n].setPosition(newPos);
												board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
												board_arr[oldRow][oldCol] = 0;
												player1.moves++;
												checkerSound();
												if ((player1.currentPlayerPiece == 1 && newRow == boardSize - 1) ||
													(player1.currentPlayerPiece == -1 && newRow == 0)) {
														// King me
														player1.currentPlayerPiece = player1.currentPlayerPiece * 2;
														board_arr[newRow][newCol] = player1.currentPlayerPiece; // Mark as king
														king[n] = 1;//set king to 1
														KingSound();
												}
												player1.pieceSelected = false;
												
											}
											else{
												// Invalid move, revert to the original position
												player1.switchPlayerTurn();	//switch player turn
												pieces[n].setPosition(originalPos);
												wrongMoveSound();
											}
										}
										else{
											// Invalid move, revert to the original position
											player1.switchPlayerTurn();	//switch player turn
											pieces[n].setPosition(originalPos);
											wrongMoveSound();
										}
									}
									else if(board_arr[newRow][newCol] == 1){
										// Invalid move, revert to the original position
										player1.switchPlayerTurn();	//switch player turn
										pieces[n].setPosition(originalPos);
										wrongMoveSound();
									}
									else if(board_arr[newRow][newCol] == -1){
										// Invalid move, revert to the original position
										player1.switchPlayerTurn();	//switch player turn
										pieces[n].setPosition(originalPos);
										wrongMoveSound();
									}
									else if(board_arr[newRow][newCol] == -9){
										// Invalid move, revert to the original position
										player1.switchPlayerTurn();	//switch player turn
										pieces[n].setPosition(originalPos);
										wrongMoveSound();
									}

							} else if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize &&
								board_arr[newRow][newCol] == -9) {
								// Invalid move, revert to the original position
								player1.switchPlayerTurn();	//switch player turn
								pieces[n].setPosition(originalPos);
								wrongMoveSound();
							}
							else{
								// Invalid move, revert to the original position
								player1.switchPlayerTurn();	//switch player turn
								pieces[n].setPosition(originalPos);
								wrongMoveSound();
							}
							// print whole board values ONLY FOR DEBUGGING
							// for(int i = 0; i < boardSize; i++){
							// 	for(int j = 0; j < boardSize; j++){
							// 		cout << board_arr[i][j] << " ";
							// 	}
							// 	cout << endl;
							// }
							if(player1.moves == 32 || (player1.black_left<=1 && player1.red_left>2) || (player1.red_left<=1 && player1.black_left>2)){
								//Game Over
								if(player1.moves == 32){
									if(player1.black_score > player1.red_score){
										//Player1 wins
										gameover.setFont(1,1);
									}
									else if(player1.black_score < player1.red_score){
										//Player 2 wins!
										gameover.setFont(1,2);
									}
									else if(player1.black_score == player1.red_score){
										//It's a draw!
										gameover.setFont(1,3);
									}
									result = true;
									menu = false;
									game = false;
									winSound();
								}
								else if(player1.black_left<=1 && player1.red_left>2){
									//Player 2 wins!
									gameover.setFont(2,0);
									result = true;
									menu = false;
									game = false;
									winSound();
								}
								else if(player1.black_left>2 && player1.red_left<=1){
									//Player 1 wins!"
									gameover.setFont(3,0);
									result = true;
									menu = false;
									game = false;
									winSound();
								}
							}
							else if((player1.black_left<=1 && player1.red_left<=2) || (player1.red_left<=1 && player1.black_left<=2)){
								if(player1.black_left == 0){
									//Player 2 wins!"
									gameover.setFont(2,0);
									result = true;
									menu = false;
									game = false;
									winSound();
								}
								else if(player1.red_left == 0){
									//Player 1 wins!"
									gameover.setFont(3,0);
									result = true;
									menu = false;
									game = false;
									winSound();
								}
								else{
									//Game Continues!"
								}
							}
						}
					}
				}else{
					if(game == true){
						cout << "Player , please select a piece to move!" << endl;
					}
				}
				break;	//break

			case Event::KeyPressed:
				if(instruc == true){
					if(event.key.code == Keyboard::A){
						menu = false;
						instruc = false;
						game = true;
						result = false;
						startSound();
					}
				}
				else if(result == true){
					//if enter pressed return to main menu
					if(event.key.code == Keyboard::Escape){
						window.close();
					}
				}
				break;

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
		if(menu == true){
			window.draw(boardSprite);	//draw menu
			menU.draw(window);
		}
		if(instruc == true){
			Instructions ins;
			ins.draw(window);

		}
		else if(game == true){
			window.draw(boardSprite);	//draw red piece
			for (int i = 0; i < 24; i++) {
				if (king[i] == 1) {
					// Calculate the position for the "K" text relative to the king piece
					Vector2f kingPosition = pieces[i].getPosition();
					Text textR("K", font, 15); // Adjust font size as needed
					textR.setPosition(kingPosition.x + 5, kingPosition.y + 5); // Adjust position as needed

					// Draw the king piece, then the associated text
					window.draw(pieces[i]);
					window.draw(textR);
				} else {
					window.draw(pieces[i]);
				}
			}
		}
		else if(result == true){
			window.clear(Color::White);	//draw board
			gameover.draw(window);
		}
        window.display();    //display window
    }
    return 0;
}