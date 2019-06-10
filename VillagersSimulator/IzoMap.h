#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>

//use f.e to create High Map, it stores value for given x and y
class IzoMap
{
public:
	IzoMap();
	IzoMap(int width, int height);
	IzoMap(sf::Vector2i size);
	~IzoMap();
	//TO DELETE
	void draw(sf::RenderWindow& window);
	//
	bool create(sf::Vector2i size);
	bool create(int width, int height);
	//fills whole ArrayOneValuel;
	void fillValue(float value);
	//
	bool setBlockValue(int x, int y, float value);
	bool setBlockValue(sf::Vector2i field, float value);
	//
	float getBlockValue(int x, int y) const;
	float getBlockValue(sf::Vector2i field) const;
	//
	//
	sf::Vector2i getSize() const;
	int getWidth() const;
	int getHeight() const;
	///TOOLS
	class Tools
	{
	public:
		//giadent
		static void giadentWholeMap(IzoMap* izoMap, float direction, float xshift, float startValue, float endValue); //direction is in radians
		static void gradientRegion(IzoMap* izoMap, sf::Rect<int> rect, sf::Vector2i rayPosA, sf::Vector2i rayPosB, float startValue, float endValue);
		//make the circle deffrences	
		static void createHole(IzoMap* izoMap, sf::Vector2i field, float radius, float valueShift);
		static void createHoles(IzoMap* izoMap, std::vector<sf::Vector2i> fields, std::vector<float> radiuses, std::vector<float> valueShifts);
		//

	};
	///
	void release();
private:
	//Array for values
	float** m_fieldValue;
	sf::Vector2i m_size;
};

