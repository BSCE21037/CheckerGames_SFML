#include <SFML/Graphics.hpp>
using namespace sf;

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