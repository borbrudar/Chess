#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Piece {
public:
	bool canMove(int x, int y,int piece, int board[8][8], std::vector<Piece> &f);
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
	//1 - white right, 2 -white left, 3 -black small, 4 -black big
	int castling = 0;
	bool castled = false;
	//en passant for pawns; 1 - white, 2 - black
	bool enPassant = false;
	int epCase = 0;
	//promotion 1- rook, 2- knight, 4 - bishop, 4 - queen
	int promotion = 0;
	bool isPromoting = false;
};