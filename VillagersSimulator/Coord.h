#pragma once
#include <SFML/Graphics.hpp>

class Coord
{
public:
	Coord();
	Coord(sf::Vector2i main);
	Coord(sf::Vector2f main);
	Coord(sf::Vector2i main, int subx, int suby); // f.e Coord(sf::Vector2f(100,100), 1, 0)  100.1, 100.0   sub is between <0,1>
	Coord(sf::Vector2f main, int subx, int suby); // f.e Coord(sf::Vector2f(100,100), 1, 0)  100.1, 100.0   sub is between <0,1>
	~Coord();
	//
	sf::Vector2i getMain() const;
	int getSubX() const;
	int getSubY() const;
	//
	void set(); //zero
	void set(sf::Vector2i main);
	void set(sf::Vector2i main, int subx, int suby);

private:
	sf::Vector2i m_main;
	int m_subx;
	int m_suby;
};

