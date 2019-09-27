#include "Board.h"

void Board::loadPosition()
{

	int k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 0 : 1;
			f[k].piece.setTextureRect(IntRect(size*x, size*y, size, size));
			f[k].piece.setPosition(size*j, size*i);

			//isWhite? shape? etc.
			if (y == 0) f[k].isWhite = true; else f[k].isWhite = false;
			f[k].shape = abs(n);
			f[k].boardPos = Vector2i(j, i);
			k++;
		}
	}

}


int Board::getPiece(int x, int y)
{
	return board[y][x];
}
