#include "MathOperations.h"

bool MathOperations::areTwoRectanglesConnected(sf::Vector2f coord11, sf::Vector2f coord12, sf::Vector2f coord21, sf::Vector2f coord22)
{
	// If one rectangle is on left side of other 
	if (coord11.x > coord22.x || coord21.x > coord12.x)
        return false; 
  
    // If one rectangle is above other 
    if (coord11.y < coord22.y || coord21.y < coord12.y)
        return false; 
  
    return true; 
}

bool MathOperations::areTwoRectanglesConnected(sf::Vector2f coord11, sf::Vector2f coord12, sf::Vector2f cameraPos, sf::Rect<float> viewPort, sf::Vector2u screenSize, float zoom)
{
	return MathOperations::areTwoRectanglesConnected(coord11, coord12, cameraPos - sf::Vector2f(viewPort.width * screenSize.x, viewPort.height * screenSize.y) / (2.f * zoom), cameraPos + sf::Vector2f(viewPort.width * screenSize.x, viewPort.height * screenSize.y) / (2.f * zoom));
}

sf::Vector2f MathOperations::pointRelativeTo(sf::Vector2f point, sf::Vector2f reference)
{
	return point - reference;
}

void MathOperations::pointRelativeToR(sf::Vector2f& point, sf::Vector2f reference)
{
	point -= reference;
}

sf::Vector2f MathOperations::rotate(sf::Vector2f point, float angle)
{
	return sf::Vector2f(point.x*cos(angle) - point.y*sin(angle), point.x * sin(angle) + point.y * cos(angle));
}

void MathOperations::rotateR(sf::Vector2f& point, float angle)
{
	point = sf::Vector2f(point.x * cos(angle) - point.y * sin(angle), point.x * sin(angle) + point.y * cos(angle));
}

sf::Vector2f MathOperations::rotate(sf::Vector2f point, sf::Vector2f center, float angle)
{
	
	return MathOperations::rotate(MathOperations::pointRelativeTo(point, center), angle);
}

void MathOperations::rotateR(sf::Vector2f& point, sf::Vector2f center, float angle)
{
	point = MathOperations::rotate(MathOperations::pointRelativeTo(point, center), angle);
}

bool MathOperations::isPointInPolygon(sf::Vector2f point, std::vector<sf::Vector2f> verticles)
{
	//all verticles reference to point (point is a center) 
	for (int i = 0; i < verticles.size(); i++)
	{
		//MathOperations::rotateR(verticles[i])
		MathOperations::pointRelativeToR(verticles[i], point);

	}

	verticles.push_back(verticles[0]);

	unsigned crossCounter = 0;//

	//checking if line crossing all sides
	for (int i = 0; i < verticles.size()-1; i++)
	{
		///using claim of Darboux

		//checking verical
		const float v1x_v2x = verticles[i].x * verticles[i + 1].x;
		if (v1x_v2x <= 0)
		{

			const float v1y_v2y = verticles[i].y * verticles[i + 1].y;
			if (v1y_v2y < 0)
			{
				crossCounter++;
				continue;
			}
			else if (v1y_v2y > 0)
			{
				continue;
			}
			else
			{
				//line cross the vertex
				int previous = i - 1;
				if (previous < 0) previous = 0;

				if (verticles[previous].y * verticles[i + 1].y < 0)
					continue;
				else
				{
					crossCounter++;
					continue;
				}
			}

		}
		else if (v1x_v2x > 0)
		{
			//this same side: left or right

			if (verticles[i].y + verticles[i + 1].y > 0)
			{
				//right side
				const float v1y_v2y = verticles[i].y * verticles[i + 1].y;
				if (v1y_v2y < 0)
				{
					crossCounter++;
					continue;
				}
				else if (v1y_v2y > 0)
				{
					continue;
				}
				else
				{
					//line cross the vertex
					int previous = i - 1;
					if (previous < 0) previous = 0;

					if (verticles[previous].y * verticles[i + 1].y < 0)
						continue;
					else
					{
						crossCounter++;
						continue;
					}
				}

			}
			else
			{
				//left
				continue;
			}
		}
	}

	if (crossCounter % 2)return false;
	else return true;
}
