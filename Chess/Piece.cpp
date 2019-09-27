#include "Piece.h"

bool Piece::canMove(int x, int y,int piece, int board[8][8])
{
	//return for all piece types
	
	switch (shape) {
	case 1://rook
		if (attackingAllies(x, y,piece)) return false;
		if (moveThroughPieces(x, y, board)) return false;
		if (x == boardPos.x || y == boardPos.y) return true; else return false;
		break;
	case 2://knight
		if (attackingAllies(x, y, piece)) return false;
		if ((abs(x - boardPos.x) == 2 && abs(y - boardPos.y) == 1) || (abs(x - boardPos.x) == 1 && abs(y - boardPos.y) == 2)) return true; else return false;
		break;
	case 3://bishop
		if (attackingAllies(x, y, piece)) return false;
		if (moveThroughPieces(x, y, board)) return false;
		if (abs(x - boardPos.x) == abs(y - boardPos.y)) return true; else return false;
		break;
	case 4://queen
		if (attackingAllies(x, y, piece)) return false;
		if (moveThroughPieces(x, y, board)) return false;
		if (abs(x - boardPos.x) == abs(y - boardPos.y)) return true; 
		else if (x == boardPos.x || y == boardPos.y) return true;
		else return false;
	case 5://king
		if (attackingAllies(x, y, piece)) return false;
		if (abs(x - boardPos.x) <= 1 && abs(y - boardPos.y) <= 1) return true; else return false;
		break;
	case 6://pawns
		if (attackingAllies(x, y, piece)) return false;
		//attacking
		if (isWhite) {
			if (board[boardPos.y - 1][boardPos.x + 1] < 0 && ((y == boardPos.y - 1) && (x == boardPos.x + 1))) return true;
			if (board[boardPos.y - 1][boardPos.x - 1] < 0 && ((y == boardPos.y - 1) && (x == boardPos.x - 1))) return true;
		}													   							
		else {												   							
			if (board[boardPos.y + 1][boardPos.x + 1] > 0 && ((y == boardPos.y + 1) && (x == boardPos.x + 1))) return true;
			if (board[boardPos.y + 1][boardPos.x - 1] > 0 && ((y == boardPos.y + 1) && (x == boardPos.x - 1))) return true;
		}																				
		/*if (board[boardPos.y - 1][boardPos.x - 1] != 0 || board[boardPos.y - 1][boardPos.x + 1] != 0) {
			if (abs(x - boardPos.x) == abs(y - boardPos.y) && ((isWhite && (y - boardPos.y) == -1) || (!isWhite && (y - boardPos.y) == 1))) {
				firstTurn = false;
				return true;
			}
		}*/
		//block if ahead
		if(isWhite )
			if (board[boardPos.y - 1][boardPos.x] != 0) return false; 
		else if(!isWhite) 
			if (board[boardPos.y + 1][boardPos.x] != 0) return false;
		//other stuff
		if (x != boardPos.x) return false;
		if (isWhite && (y - boardPos.y) == -1 || !isWhite && (y - boardPos.y) == 1) {
			firstTurn = false;
			return true;
		} 
		if ((firstTurn && isWhite && (y - boardPos.y) == -2) || (firstTurn && !isWhite && (y - boardPos.y) == 2)) {
			firstTurn = false;
			return true;
		}
		else return false;
		break;
	}
	return true;
}

bool Piece::attackingAllies(int x, int y,int piece)
{
	if (piece != 0) {
		if ((isWhite && piece >= 1) || (!isWhite && piece <= -1)) {
			return true;
		}
	}
	return false;
}

bool Piece::moveThroughPieces(int x, int y, int board[8][8])
{ 
	float stepDirX = (float)x - (float)boardPos.x;
	if (stepDirX > 0)
	{
		stepDirX = 1;
	}
	else if (stepDirX <= 0) {
		stepDirX = -1;
	}
	float stepDirY = (float)y - (float)boardPos.y;
	if (stepDirY > 0)
	{
		stepDirY = 1;
	}
	else if (stepDirY <= 0) {
		stepDirY = -1;
	}
	Vector2f tempPos = Vector2f((float)boardPos.x, (float)boardPos.y);
	tempPos.x += stepDirX;
	tempPos.y += stepDirY;

	while(tempPos.x != x && tempPos.y != y){
		if (board[(int)tempPos.y][(int)tempPos.x] != 0) {
			return true;
		}
		tempPos.x += stepDirX;
		tempPos.y += stepDirY;
			
	}

	return false;
}
