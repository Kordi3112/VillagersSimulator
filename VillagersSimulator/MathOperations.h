#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>
#include <vector>

class MathOperations
{
public:
	
	static bool areTwoRectanglesConnected(sf::Vector2f coord11, sf::Vector2f coord12, sf::Vector2f coord21, sf::Vector2f coord22);
	static bool areTwoRectanglesConnected(sf::Vector2f coord11, sf::Vector2f coord12, sf::Vector2f cameraPos,  sf::Rect<float> viewPort, sf::Vector2u screenSize, float zoom);
	//
	static sf::Vector2f pointRelativeTo(sf::Vector2f point, sf::Vector2f reference);
	static void pointRelativeToR(sf::Vector2f& point, sf::Vector2f reference);

	//
	static sf::Vector2f rotate(sf::Vector2f point, float angle);
	static void rotateR(sf::Vector2f& point, float angle);
	//
	static sf::Vector2f rotate(sf::Vector2f point, sf::Vector2f center, float angle);
	static void rotateR(sf::Vector2f& point, sf::Vector2f center, float angle);
	//
	static bool isPointInPolygon(sf::Vector2f point, std::vector<sf::Vector2f> verticles);
};

