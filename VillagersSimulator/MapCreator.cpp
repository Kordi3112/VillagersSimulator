#include "MapCreator.h"



MapCreator::MapCreator()
{
}


MapCreator::~MapCreator()
{
}

Brush::Brush()
{
}

Brush::~Brush()
{
}

void Brush::setBrushShape(BrushShape shape)
{
	this->m_brushShape = shape;
}

BrushShape Brush::getBrushShape() const
{
	return this->m_brushShape;
}

void Brush::setSize(float size)
{
	this->m_size = size;
}

float Brush::getSize() const
{
	return this->m_size;
}

void Brush::setPosition(sf::Vector2f position)
{
	this->m_position = position;
}

sf::Vector2f Brush::getPosition() const
{
	return this->m_position;
}
