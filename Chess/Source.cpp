#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"
#include <iostream>
using namespace sf;

int size = 75;


int main() {
	RenderWindow window;
	window.create(VideoMode(600, 600), "Chess!");

	Event e;
	Mouse m;

	//setup 
	Texture t,t1;
	t.loadFromFile("images/chesspieces.png");
	t1.loadFromFile("images/chessboard.png");

	Sprite s(t1);
	Board b;

	for (int i = 0; i < b.f.size(); i++) b.f[i].piece.setTexture(t);
	b.loadPosition();

	bool move = false;
	bool whiteTurn = true;
	float dx = 0, dy = 0;
	int n = 0;
	Vector2f oldPos;

	//game loop
	while (window.isOpen()) {
		Vector2i mousePos = m.getPosition(window);
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
						if (b.f[n].canMove(newPos.x / size, newPos.y / size, b.getPiece(newPos.x / size, newPos.y / size), b.board) && (newPos.x > -1 && newPos.x < 600 && newPos.y > -1 && newPos.y < 600)) {
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

							//update board
							b.board[(int)(oldPos.y / size)][int(oldPos.x / size)] = 0;
							if (b.f[n].isWhite) b.board[(int)(newPos.y / size)][int(newPos.x / size)] = b.f[n].shape;
							else if (!b.f[n].isWhite) b.board[(int)(newPos.y / size)][int(newPos.x / size)] = -b.f[n].shape;
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
	
	return 0;
}