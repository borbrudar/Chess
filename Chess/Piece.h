#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Piece {
public:
	bool canMove(int x, int y,int piece, int board[8][8]);
	bool attackingAllies(int x, int y, int piece);
	bool moveThroughPieces(int x, int y,int board[8][8]);

public:
	Sprite piece;
	bool isWhite;
	//1 - rook, 2 -knight, 3- bishop, 4-queen, 5-king, 6-pawn
	int shape = 0;
	Vector2i boardPos;
	int size = 75;
	bool taken = false, firstTurn = true;

};