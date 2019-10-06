#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"
#include <iostream>
using namespace sf;


int size = 75;

enum class gameState {
	Normal,
	Promotion
};

//helper functions
void promotion(int shape, bool isWhite, gameState &state, Board &b, int p) {
	int white = 0;
	if (isWhite) white = 0; else white = 1;
	state = gameState::Normal;
	b.f[p].isPromoting = false;
	b.f[p].shape = shape;
	b.board[b.f[p].boardPos.y][b.f[p].boardPos.x] = shape;
	b.f[p].piece.setTextureRect(IntRect(size * (shape - 1), size * white, size, size));
}

int main() {
	RenderWindow window;
	window.create(VideoMode(600, 600), "Chess!");

	Event e;
	Mouse m;

	gameState state = gameState::Normal;

	//setup 
	Texture t, t1, t2, t3;
	t.loadFromFile("images/chesspieces.png");
	t1.loadFromFile("images/chessboard.png");
	t2.loadFromFile("images/p1.png");
	t3.loadFromFile("images/p2.png");

	Sprite s(t1);
	Sprite p1(t2); 
	Sprite p2(t3);
	Board b;

	p1.setPosition(200, 300);

	for (int i = 0; i < b.f.size(); i++) b.f[i].piece.setTexture(t);
	b.loadPosition();

	bool move = false;
	bool whiteTurn = true;
	float dx = 0, dy = 0;
	int n = 0;
	int p = 0;
	Vector2f oldPos;

	//game loop
	while (window.isOpen()) {
		for (int i = 0; i < b.f.size(); i++) {
			if (b.f[i].isPromoting) {
				state = gameState::Promotion;
				p = i;
				break;
			}
		}

		Vector2i mousePos = m.getPosition(window);
		if (state == gameState::Normal) {
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					window.close();
				}
				if (e.type == Event::MouseButtonPressed) {
					if (e.key.code == Mouse::Left) {
						for (int i = 0; i < b.f.size(); i++) {
							if (b.f[i].piece.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
								move = true;
								n = i;
								oldPos = b.f[n].piece.getPosition();
								dx = mousePos.x - b.f[n].piece.getPosition().x;
								dy = mousePos.y - b.f[n].piece.getPosition().y;
							}
						}
					}
				}
				if (e.type == Event::MouseButtonReleased) {

					//movement logic
					if (e.key.code == Mouse::Left) {
						move = false;
						if ((b.f[n].isWhite && whiteTurn) || (!b.f[n].isWhite && !whiteTurn)) {

							Vector2f p = b.f[n].piece.getPosition() + Vector2f(size, size) - Vector2f(30, 30);
							Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));

							//can move
							if (b.f[n].canMove(newPos.x / size, newPos.y / size, b.getPiece(newPos.x / size, newPos.y / size), b.board, b.f) && (newPos.x > -1 && newPos.x < 600 && newPos.y > -1 && newPos.y < 600)) {

								//en passant reset
								for (int i = 0; i < b.f.size(); i++) {
									if (i != n) b.f[i].enPassant = false;
								}
								//move
								b.f[n].piece.setPosition(newPos);
								b.f[n].boardPos = Vector2i(int(newPos.x / size), int(newPos.y / size));

								//taking logic
								if (b.board[(int)(newPos.y / size)][(int)(newPos.x / size)] != 0) {
									b.board[(int)(newPos.y / size)][(int)(newPos.x / size)] = 0;

									for (std::size_t i = 0; i < b.f.size(); i++) {
										if (i != n) {
											if (b.f[i].boardPos.x == (int)(newPos.x / size) && b.f[i].boardPos.y == (int)(newPos.y / size)) {
												b.f.erase(b.f.begin() + i);
												break;
											}
										}
									}
								}


								//castling
								if (!b.f[n].castled && b.f[n].shape == 5) {
									for (int i = 0; i < b.f.size(); i++) {
										if (b.f[i].shape == 1) {
											//white
											if (b.f[i].isWhite) {
												if (b.f[n].castling == 1 && b.f[i].boardPos.x == b.f[n].boardPos.x + 1) {
													b.f[i].boardPos = Vector2i(b.f[n].boardPos.x - 1, b.f[n].boardPos.y);
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x] = 0;
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x - 2] = 1;
													b.f[i].piece.setPosition(newPos.x - size, newPos.y);
												}
												if (b.f[n].castling == 2 && b.f[i].boardPos.x == b.f[n].boardPos.x - 2) {
													b.f[i].boardPos = Vector2i(b.f[n].boardPos.x - 2, b.f[n].boardPos.y);
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x] = 0;
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x + 3] = 1;
													b.f[i].piece.setPosition(newPos.x + size, newPos.y);
												}
											}//black
											else if (!b.f[i].isWhite) {
												if (b.f[n].castling == 3 && b.f[i].boardPos.x == b.f[n].boardPos.x + 1) {
													b.f[i].boardPos = Vector2i(b.f[n].boardPos.x - 1, b.f[n].boardPos.y);
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x] = 0;
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x - 2] = -1;
													b.f[i].piece.setPosition(newPos.x - size, newPos.y);
												}
												if (b.f[n].castling == 4 && b.f[i].boardPos.x == b.f[n].boardPos.x - 2) {
													b.f[i].boardPos = Vector2i(b.f[n].boardPos.x - 2, b.f[n].boardPos.y);
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x] = 0;
													b.board[b.f[i].boardPos.y][b.f[i].boardPos.x + 3] = -1;
													b.f[i].piece.setPosition(newPos.x + size, newPos.y);
												}
											}
										}
									}

								}

								//en passant, 1-white, 2-black
								if (b.f[n].epCase != 0 && b.f[n].shape == 6) {
									switch (b.f[n].epCase) {
									case 1:
										for (int i = 0; i < b.f.size(); i++) {
											if (b.f[i].boardPos.x == b.f[n].boardPos.x && b.f[i].boardPos.y == b.f[n].boardPos.y + 1) {
												b.f.erase(b.f.begin() + i);
												break;
											}
										}
										b.board[b.f[n].boardPos.y + 1][b.f[n].boardPos.x] = 0;
										break;
									case 2:
										for (int i = 0; i < b.f.size(); i++) {
											if (b.f[i].boardPos.x == b.f[n].boardPos.x && b.f[i].boardPos.y == b.f[n].boardPos.y - 1) {
												b.f.erase(b.f.begin() + i);
												break;
											}
										}
										b.board[b.f[n].boardPos.y - 1][b.f[n].boardPos.x] = 0;
										break;
									}
								}


								//update board
								b.board[(int)(oldPos.y / size)][int(oldPos.x / size)] = 0;
								if (b.f[n].isWhite) b.board[b.f[n].boardPos.y][b.f[n].boardPos.x] = b.f[n].shape;
								else if (!b.f[n].isWhite) b.board[b.f[n].boardPos.y][b.f[n].boardPos.x] = -b.f[n].shape;
								whiteTurn = !whiteTurn;


							}
							else b.f[n].piece.setPosition(oldPos);
						}
						else b.f[n].piece.setPosition(oldPos);
					}

				}

			}
			if (move) b.f[n].piece.setPosition(mousePos.x - dx, mousePos.y - dy);


			window.clear(Color::Black);
			window.draw(s);
			for (int i = 0; i < b.f.size(); i++) window.draw(b.f[i].piece);
			window.display();
		}

		if (state == gameState::Promotion) {
			p1.setPosition(0, 0);
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					window.close();
				}
				//check for promotion
				if (e.type == Event::MouseButtonReleased) {
					if (mousePos.y > 250 && mousePos.y < 335) {
						if (mousePos.x > 104 && mousePos.x < 180)
						{
							b.f[p].promotion = 1; 
						}
						if (mousePos.x > 180 && mousePos.x < 280)
						{
							b.f[p].promotion = 2; 
						}
						if (mousePos.x > 280 && mousePos.x < 365)
						{
							b.f[p].promotion = 3; 
						}
						if (mousePos.x > 365 && mousePos.x < 460)
						{
							b.f[p].promotion = 4; 
						}
					}
				}
			}
			if (b.f[p].promotion != 0) 
				promotion(b.f[p].promotion, b.f[p].isWhite, state, b, p);

			window.clear(Color::Black);
			window.draw(s);
			for (int i = 0; i < b.f.size(); i++) window.draw(b.f[i].piece);
			if (b.f[p].isWhite) window.draw(p1); else window.draw(p2);
			window.display();
		}

	}
	return 0;
}

