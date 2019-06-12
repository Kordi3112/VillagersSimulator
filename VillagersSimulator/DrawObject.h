#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>


class DrawObject
{
public:
	//
	struct Object
	{
		Object();
		Object(std::string name, sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin);

		sf::Vector2f size;
		sf::Vector2f origin;
		std::string name; 
		sf::Texture* texture;
		std::vector<sf::Vector2f> positions;
	};

	//
	DrawObject();
	~DrawObject();
	//
	int getObjectId(std::string name) const;
	//
	//void createObject(std::string name, sf::Texture* texture);
	int createObject(std::string name, sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin);
	//
	bool addLocation(std::string objectName, sf::Vector2f position);
	bool addLocation(int objectId, sf::Vector2f position);
	//
	///
	bool draw(int id, sf::RenderWindow& window);
	//
	bool draw(std::string name, sf::RenderWindow& window);
	//
	bool draw(int id, sf::RenderTexture& window);
	//
	bool draw(std::string name, sf::RenderTexture& window);
	///
	void draw(sf::RenderWindow& window);
	void draw(sf::RenderTexture& window);
	
	//
	//
private:

	std::vector<Object> m_objectsContainer;

};

