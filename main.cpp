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
		if (!font.loadFromFile("arial.ttf"))
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


Sprite pieces[24];	//array of piec
int orignal_board_arr[8][8] = {	//board array
	-9, -1, -9,-1, -9,-1, -9,-1,	// --------
	-1, -9,-1, -9,-1, -9,-1, -9,// player 1
	-9, -1, -9,-1, -9,-1, -9,-1,// --------

	0, -9, 0, -9, 0, -9, 0, -9,
	-9, 0, -9, 0, -9, 0, -9, 0,

	1, -9, 1, -9, 1, -9, 1, -9,// --------
	-9, 1, -9, 1, -9, 1, -9, 1, // player 2
	1, -9, 1, -9, 1, -9, 1, -9// --------
	
};
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
	int currentKingPiece = 2;
	int opponentKingPiece = -2;
	bool pieceSelected = false;
	int notYourTurn = 0;
	int red_score = 0;
	int black_score = 0;
	int red_left = 12;
	int black_left = 12;
	int moves = 0;

	void resetPlayer(){
		//reset all values back
		currentPlayerPiece = 1;
		opponentPiece = -1;
		currentKingPiece = 2;
		opponentKingPiece = -2;
		pieceSelected = false;
		notYourTurn = 0;
		red_score = 0;
		black_score = 0;
		red_left = 12;
		black_left = 12;
		moves = 0;
		cout << "Reset values" << endl;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				board_arr[i][j] = orignal_board_arr[i][j];
				cout << board_arr[i][j];
			}
			cout << endl;
		}

	}
	
	void switchPlayerTurn(){
		if(currentPlayerPiece == 1 && currentKingPiece == 2){
			currentPlayerPiece = -1;
			currentKingPiece = -2;
			opponentPiece = 1;
			opponentKingPiece = 2;
		}
		else{
			currentPlayerPiece = 1;
			currentKingPiece = 2;
			opponentPiece = -1;
			opponentKingPiece = -2;
		}
	}
	
	
};

Player player1;

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
		if (!f.loadFromFile("arial.ttf"))
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

const int boardSize = 8;	//size of board
const int tileSize = 58;	//size of tiles
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
			// else if (n == 2 || n == -2) { // King pieces
            //     int textureIndex = (n == 2) ? 2 : -2; // Adjust texture index for kings
            //     pieces[k].setTextureRect(IntRect(0.7 * textureIndex, 0, 0.7, 0.7)); // Set texture rect for kings
            //     pieces[k].setPosition(j * tileSize, i * tileSize);
            //     k++;
            // }
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
	if (k == 2 || k == -2) {
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
	(isCaptureValid(newRowVar, newColVar, newRowVar - 2, newColVar - 2)&& currentPiece == 1)){
		return true;
	}
	return false;
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
		}
		else{
			player1.black_score++;
			cout << "Black Score: " << player1.black_score << endl;
			player1.red_left--;
			cout << "Red Left: " << player1.red_left << endl;
		}
        pieces[capturedPieceIndex].setPosition(-100, -100); // Move it off the screen
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
	RenderWindow window(VideoMode(453, 454), "2 Player Checker Game", Style::Titlebar | Style::Close); //create window
	bool menu, game, result;	//create bools for menu, game, and end
	menu = true;			//set menu to true
	game = false;			//set game to false
	result = false;			//set end to false

	int fps = 60;	//set fps to 60
	window.setFramerateLimit(fps);	//set fps limit

	bool movePiece = false;	//check if piece is moving
	float dx = 0, dy = 0;	//delta x and delta y
	//float speed = 0.1;		//speed of piece
	int n = 0;
	bool call_is_capture;
	int king[24];		//array to store if piece is king
	for (int i = 0; i < 24; i++)//initializing king array
	{
		king[i] = 0;
	}
	

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

	Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error loading font" << endl;
	}

	//Text textR;		//create text
	for(int i = 0; i < 12; i++){		//for loop
		pieces[i].setTexture(red);		//set texture to sprite
		pieces[i].setScale(0.022, 0.022);	//set scale of sprite
		// textR.setFont(font);	//set font of text
		// textR.setString("K");	//set string of text
		// textR.setCharacterSize(20);	//set character size of text
		// textR.setFillColor(Color::White);	//set fill color of text
		// textR.setPosition(pieces[i].getPosition().x + 5, pieces[i].getPosition().y + 5);	//set position of text

	}
	for(int i = 12; i < 24; i++){		//for loop
		pieces[i].setTexture(black);		//set texture to sprite
		pieces[i].setScale(0.07, 0.07);	//set scale of sprite
		// textR.setFont(font);	//set font of text
		// textR.setString("K");	//set string of text
		// textR.setCharacterSize(20);	//set character size of text
		// textR.setFillColor(Color::White);	//set fill color of text
		// textR.setPosition(pieces[i].getPosition().x + 5, pieces[i].getPosition().y + 5);	//set position of text
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
				//sleep(seconds(3));//adding delay
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
							cout << "Play button has been pressed" << endl;
							menu = false;
							game = true;
							result = false;
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
								std::cout << "Play button has been pressed" << std::endl;
								menu = false;
								game = true;
								result = false;
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
									if(player1.currentPlayerPiece == 1 || player1.currentKingPiece == 2){
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
					else if(result == true){
						// Get mouse position
						Vector2i mousePos = Mouse::getPosition(window);

						// Check if the mouse position is within the bounds of menu items
						if (menU.isMouseOverItem(mousePos))
						{
							// Get mouse position
							int selectedItem = menU.GetPressedItem();
							switch (selectedItem)
							{
							case 0:
								std::cout << "Play button has been pressed" << std::endl;
								menu = false;
								game = false;
								result = false;
								break;
							case 1:
								window.close();
								break;
							}
						}
					}
				}
                break;        //break
            
            case Event::MouseButtonReleased:	//if key is released
				
				if (event.mouseButton.button == Mouse::Left) {
					if(menu == true){}
					else if(game == true){
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
												cout << "Jump Check" << endl;
												// Check if the move is a jump
												int jumpRow = (newRow + oldRow) / 2;
												int jumpCol = (newCol + oldCol) / 2;

												if (board_arr[jumpRow][jumpCol] != 0) {
													// Valid jump
													cout << "Kill func call" << endl;
													Kill(oldRow, oldCol, newRow, newCol, jumpRow, jumpCol, n);
													if (canPieceCaptureAgain(newRow, newCol, player1.currentPlayerPiece, board_arr[newRow][newCol])) {
														cout << "You can capture again!" << endl;
														oldPos = newPos; // Update the old position to the new position
														
													} else {
														// Finish the move and switch players' turns
														player1.pieceSelected = false;
														player1.switchPlayerTurn();
													}
													cout << "Checking king promotion conditions..." << endl;
													if ((player1.currentPlayerPiece == 1 && newRow == boardSize - 1) ||
														(player1.currentPlayerPiece == -1 && newRow == 0)) {
															// King me
															player1.currentPlayerPiece = player1.currentPlayerPiece * 2;
															board_arr[newRow][newCol] = player1.currentPlayerPiece; // Mark as king
															cout << "King me!" << endl;
															king[n] = 1;//set king to 1
													}
													else{
														cout << "Not king me!" << endl;
													}
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
											if ((player1.currentPlayerPiece == 1 && newRow > oldRow) || (player1.currentPlayerPiece == -1 && newRow < oldRow) || (board_arr[oldRow][oldCol] == 2 || board_arr[oldRow][oldCol] == -2)) {
												pieces[n].setPosition(newPos);
												board_arr[newRow][newCol] = board_arr[oldRow][oldCol];
												board_arr[oldRow][oldCol] = 0;
												player1.moves++;
												cout << "Checking king promotion conditions..." << endl;
												if ((player1.currentPlayerPiece == 1 && newRow == boardSize - 1) ||
													(player1.currentPlayerPiece == -1 && newRow == 0)) {
														// King me
														player1.currentPlayerPiece = player1.currentPlayerPiece * 2;
														board_arr[newRow][newCol] = player1.currentPlayerPiece; // Mark as king
														cout << "King me!" << endl;
														king[n] = 1;//set king to 1
														//player1.switchPlayerTurn();	//switch player turn
												}
												else{
													cout << "Not king me!" << endl;
												}
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
							if(player1.moves == 32 || (player1.black_left<=11 && player1.red_left>2) || (player1.red_left<=11 && player1.black_left>2)){
								cout << "Game over!" << endl;
								if(player1.moves == 32){
									if(player1.black_score > player1.red_score){
										cout << "Player 1 wins!" << endl;
										gameover.setFont(1,1);
									}
									else if(player1.black_score < player1.red_score){
										cout << "Player 2 wins!" << endl;
										gameover.setFont(1,2);
									}
									else if(player1.black_score == player1.red_score){
										cout << "It's a draw!" << endl;
										gameover.setFont(1,3);
									}
									result = true;
									menu = false;
									game = false;
								}
								else if(player1.black_left<=11 && player1.red_left>2){
									cout << "Player 2 wins!" << endl;
									gameover.setFont(2,0);
									result = true;
									menu = false;
									game = false;
								}
								else if(player1.black_left>2 && player1.red_left<=11){
									cout << "Player 1 wins!" << endl;
									gameover.setFont(3,0);
									result = true;
									menu = false;
									game = false;
								}
							}
							else if((player1.black_left<=1 && player1.red_left<=2) || (player1.red_left<=1 && player1.black_left<=2)){
								if(player1.black_left == 0){
									cout << "Player 2 wins!" << endl;
									gameover.setFont(2,0);
									result = true;
									menu = false;
									game = false;
								}
								else if(player1.red_left == 0){
									cout << "Player 1 wins!" << endl;
									gameover.setFont(3,0);
									result = true;
									menu = false;
									game = false;
								}
								else{
									cout << "Game Continues!" << endl;
								}
							}

						}
						
					}
					// else if(result  == true){
						
					// }
				}else{
					if(menu == true){}
					else if(game == true){
						cout << "Player , please select a piece to move!" << endl;
					}
				}
				break;	//break

			case Event::KeyPressed:
				if(result == true){
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
        //drawChessBoard(window);        //draw chess board
		if(menu == true){
			window.draw(boardSprite);	//draw menu
			menU.draw(window);
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
			window.draw(boardSprite);	//draw menu
			gameover.draw(window);
		}
        window.display();    //display window
    }
    return 0;
}