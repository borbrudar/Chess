#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <vector>

using namespace sf;

class Board {
public:
	void loadPosition();
	int getPiece(int x, int y);

	std::vector<Piece> f;
	Board() : f(std::vector<Piece>(32)) {};

	int size = 75;
	int board[8][8] =
	{
		-1,-2,-3,-4,-5,-3,-2,-1,
		-6,-6,-6,-6,-6,-6,-6,-6,
		 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0,
		 6, 6, 6, 6, 6, 6, 6, 6,
		 1, 2, 3, 4, 5, 3, 2, 1
	};

};