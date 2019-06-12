#include "DrawObject.h"

DrawObject::DrawObject()
{
}

DrawObject::~DrawObject()
{
}

int DrawObject::getObjectId(std::string name) const
{
	for(int i=0; i<m_objectsContainer.size(); i++)
	{
		if (m_objectsContainer[i].name == name)
		{
			return i;
		}
	}

	return -1;
}

int  DrawObject::createObject(std::string name, sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin)
{
	m_objectsContainer.push_back(Object(name, texture, size, origin));

	return m_objectsContainer.size() - 1;
}

bool DrawObject::addLocation(std::string objectName, sf::Vector2f position)
{
	return addLocation(getObjectId(objectName), position);
}

bool DrawObject::addLocation(int objectId, sf::Vector2f position)
{
	if (objectId < 0 || objectId >= m_objectsContainer.size())
		return false;

	m_objectsContainer[objectId].positions.push_back(position);
	return true;
}

bool DrawObject::draw(int id, sf::RenderWindow& window)
{
	if (id < 0 || id >= m_objectsContainer.size())
		return false;


	sf::RectangleShape rectangleShape;
	rectangleShape.setTexture(m_objectsContainer[id].texture);
	rectangleShape.setSize(m_objectsContainer[id].size);
	rectangleShape.setOrigin(m_objectsContainer[id].origin);
	
	for (int i = 0; i < m_objectsContainer[id].positions.size(); i++)
	{
		rectangleShape.setPosition(m_objectsContainer[id].positions[i]);
		window.draw(rectangleShape);
	}

	return true;
}

bool DrawObject::draw(std::string name, sf::RenderWindow& window)
{
	return draw(getObjectId(name), window);
}

bool DrawObject::draw(int id, sf::RenderTexture& window)
{
	if (id < 0 || id >= m_objectsContainer.size())
		return false;


	sf::RectangleShape rectangleShape;
	rectangleShape.setTexture(m_objectsContainer[id].texture);
	rectangleShape.setSize(m_objectsContainer[id].size);
	rectangleShape.setOrigin(m_objectsContainer[id].origin);

	for (int i = 0; i < m_objectsContainer[id].positions.size(); i++)
	{
		rectangleShape.setPosition(m_objectsContainer[id].positions[i]);
		window.draw(rectangleShape);
	}

	return true;
}

bool DrawObject::draw(std::string name, sf::RenderTexture& window)
{
	return draw(getObjectId(name), window);
}

void DrawObject::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_objectsContainer.size(); i++)
	{
		draw(i, window);
	}
}

void DrawObject::draw(sf::RenderTexture& window)
{
	for (int i = 0; i < m_objectsContainer.size(); i++)
	{
		draw(i, window);
	}
}


DrawObject::Object::Object()
{

}

DrawObject::Object::Object(std::string name, sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin)
{
	DrawObject::Object::name = name;
	DrawObject::Object::texture = texture;
	DrawObject::Object::size = size;
	DrawObject::Object::origin = origin;
}
