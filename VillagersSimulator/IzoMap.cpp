#include "IzoMap.h"

IzoMap::IzoMap()
{
}

IzoMap::~IzoMap()
{
	release();
}

void IzoMap::draw(sf::RenderWindow& window)
{
	sf::Image image;
	image.create(getWidth(), getHeight());

	for (int x = 0; x < getWidth(); x++)
	{
		for (int y = 0; y < getHeight(); y++)
		{
			image.setPixel(x, y, sf::Color(255*getBlockValue(x, y), 255 * getBlockValue(x, y), 255 * getBlockValue(x, y)));
		}
		
	}

	sf::Texture texture;
	texture.create(getWidth(), getHeight());
	texture.loadFromImage(image);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	window.draw(sprite);
}

bool IzoMap::create(sf::Vector2i size)
{
	if (size.x < 1 or size.y < 1)return false;

	m_fieldValue = new float* [size.x];

	for (int x = 0; x < size.x; x++)
	{
		m_fieldValue[x] = new float[size.y];
	}

	m_size = size;

	return true;
}

bool IzoMap::create(int width, int height)
{
	return create(sf::Vector2i(width, height));
}

void IzoMap::fillValue(float value)
{
	for (int x = 0; x < m_size.x; x++)
	{
		for (int y = 0; y < m_size.y; y++)
		{
			m_fieldValue[x][y] = value;
		}
	}
}

bool IzoMap::setBlockValue(int x, int y, float value)
{
	//block is outside the map
	if (x < 0 or x >= m_size.x or y < 0 or y >= m_size.y)
		return false;

	m_fieldValue[x][y] = value;

	return true;
}

bool IzoMap::setBlockValue(sf::Vector2i field, float value)
{
	//block is outside the map
	if (field.x < 0 or field.x >= m_size.x or field.y < 0 or field.y >= m_size.y)
		return false;

	m_fieldValue[field.x][field.y] = value;

	return true;
}

float IzoMap::getBlockValue(int x, int y) const
{
	if (x < 0 or x >= m_size.x or y < 0 or y >= m_size.y)
		return 0.0f;

	return m_fieldValue[x][y];
}

float IzoMap::getBlockValue(sf::Vector2i field) const
{
	if (field.x < 0 or field.x >= m_size.x or field.y < 0 or field.y >= m_size.y)
		return 0.0f;

	return m_fieldValue[field.x][field.y];
}

sf::Vector2i IzoMap::getSize() const
{
	return m_size;
}

int IzoMap::getWidth() const
{
	return m_size.x;
}

int IzoMap::getHeight() const
{
	return m_size.y;
}

void IzoMap::release()
{
	for (int width = 0; width < m_size.x; width++)
	{
		delete[] m_fieldValue[width];
	}

	delete[] m_fieldValue;
}


void IzoMap::Tools::gradientRegion(IzoMap* izoMap, sf::Rect<int> rect, sf::Vector2i rayPosA, sf::Vector2i rayPosB, float startValue, float endValue)
{
	//Equation:
	//Ax + By + C = 0

	float A, B, C;

	if (rayPosB.x - rayPosA.x != 0)
	{
		A = 1.0f;
		B = -static_cast<float>(rayPosB.y - rayPosA.y) / static_cast<float>(rayPosB.x - rayPosA.x);

		C = -B * rayPosA.x - rayPosA.y;
	}
	else
	{
		A = 1;
		B = 0;
		C = -rayPosA.x;
	}


	float s = sqrt((rayPosA.x - rayPosB.x) * (rayPosA.x - rayPosB.x) + (rayPosA.y - rayPosB.y) * (rayPosA.y - rayPosB.y)); //distance between A and B

	//calculating value for each field in rect

	for (int x = rect.left; x <= rect.left + rect.width; x++)
	{
		for (int y = rect.top; y <= rect.top + rect.height; y++)
		{
			//P(x,y)
			float d = abs(A * x + B * y + C) / sqrt(A * A + B * B);
			float c = sqrt((rayPosA.x - x) * (rayPosA.x - x) + (rayPosA.y - y) * (rayPosA.y - y)); //between P and A
			float r = sqrt(c * c - d * d);

			//lerp
			//izoMap->setBlockValue(x, y, (endValue - startValue) * (r / s));
			izoMap->setBlockValue(x, y, (endValue - startValue) * (r / s) );
			//izoMap->setBlockValue(x, y, d/1000);
		}
	}
	
}

void IzoMap::Tools::createHole(IzoMap* izoMap, sf::Vector2i field, float radius, float valueShift)
{
	///CHECKING IF FIELD IS RADIUS
	for (int x = 0; x < izoMap->getWidth(); x++)
	{
		/**/
		for (int y = 0; y < izoMap->getHeight(); y++)
		{
			
			//checking if field is inside square 2*radius x 2*radius size
			if (field.x - radius < x or field.x + radius > x or field.y - radius < y or field.y + radius > y)
			{
				//in
				const float r2 = (x - field.x) * (x - field.x) + (y - field.y) * (y - field.y); // r2 = r * r
				
				//check if block is in radius 
				if (r2 < (radius * radius))
				{
					//field in hole
					//lerp
					izoMap->m_fieldValue[x][y] += valueShift * (1 - sqrt(r2) / ( radius));
				}
			}
			else continue;
			
			
		}
		
	}
}

void IzoMap::Tools::createHoles(IzoMap* izoMap, std::vector<sf::Vector2i> fields, std::vector<float> radiuses, std::vector<float> valueShifts)
{

	for (int x = 0; x < izoMap->getWidth(); x++)
	{
		for (int y = 0; y < izoMap->getHeight(); y++)
		{

			float sumValue = 0;
			unsigned pointsInRange = 0;
			float shiftSum = 0;
			//checking for each points
			for (int i = 0; i < fields.size(); i++)
			{
				float r = sqrt((fields[i].x - x) * (fields[i].x - x) + (fields[i].y - y) * (fields[i].y - y));

				if (r <= radiuses[i]) {
					//in range
					pointsInRange++;
					shiftSum += valueShifts[i];
					sumValue += r / radiuses[i] * valueShifts[i];
				}				
			}

			if (pointsInRange != 0)
				izoMap->setBlockValue(x, y, shiftSum / pointsInRange);
		}
	}

}
