#include "DialogWindow.h"

ve::Button::Button()
{
}


ve::CircleButton::CircleButton()
{
}

ve::CircleButton::~CircleButton()
{
}

ve::ButtonType ve::CircleButton::type() const
{
	return CIRCLE_BUTTON;
}

void ve::CircleButton::checkButtonStatus(sf::Vector2f clickerPosition)
{
	
	if (this->m_clickAnimation == true)
	{
		if (this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime * 0.33f)
		{
			//first etap
			this->m_clickState = ve::ClickState::CLICKED;
			return;
		}
		else if(this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime * 0.66f)
		{
			//second...
			this->m_clickState = ve::ClickState::MOUSE_ON_OBJECT;
			return;
		}
		else if (this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime)
		{
			//third...
			this->m_clickState = ve::ClickState::CLICKED;
			return;
		}
		else
		{
			//end
			this->m_clickAnimation = false;

			if ((this->m_additionalParameters & ve::PERMALOCK_WHEN_CLICKED) or (this->m_additionalParameters & ve::LOCK_WHEN_CLICKED))
			{
				this->m_clickState = ve::ClickState::CLICKED;
				this->lock();
			}
		}
	}


	if (this->isMouseInButtonArea(clickerPosition))
	{
		//mouse inside button
		if (this->m_clickState == ve::ClickState::NONE_CLICK or this->getClickState() == ve::ClickState::MOUSE_ON_OBJECT)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->click();
			}
			else this->setClickState(ve::ClickState::MOUSE_ON_OBJECT);
		}
		else if (this->m_clickState == ve::ClickState::CLICKED)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
		
				if (this->m_isLocked)
				{
					if (this->m_additionalParameters & PERMALOCK_WHEN_CLICKED)return;
					else if (this->m_additionalParameters & LOCK_WHEN_CLICKED)
					{
						this->unlock();
						this->setClickState(ve::ClickState::MOUSE_ON_OBJECT);
						sf::sleep(sf::milliseconds(100));
					}
					else return;
				}
				else this->click();

			}
			else
			{
				if (this->m_isLocked)return;
				else this->setClickState(ve::ClickState::MOUSE_ON_OBJECT);
			} 
		}

	}
	else
	{
		//mouse outside...
		if (this->m_isLocked)return;
		else this->m_clickState = ve::ClickState::NONE_CLICK;
	}
}

bool ve::CircleButton::isMouseInButtonArea(sf::Vector2f clickerPosition)
{
	if (sqrt((clickerPosition.x - this->m_position.x) * (clickerPosition.x - this->m_position.x) +
		(clickerPosition.y - this->m_position.y) * (clickerPosition.y - this->m_position.y)) <= this->m_radius)return true;
	else return false;
}

void ve::CircleButton::draw(sf::RenderWindow& window)
{
	sf::CircleShape circleShape;
	circleShape.setRadius(this->getRadius());
	circleShape.setPosition(this->getPosition());
	circleShape.setOrigin(sf::Vector2f(this->getRadius(), this->getRadius()));

	//
	switch (this->m_clickState)
	{
		case ve::ClickState::NONE_CLICK:
		{
			circleShape.setTexture(this->getTexture1());
			break;
		}
		case ve::ClickState::MOUSE_ON_OBJECT:
		{
			circleShape.setTexture(this->getTexture2());
			break;
		}
		case ve::ClickState::CLICKED:
		{
			circleShape.setTexture(this->getTexture3());
			break;
		}
	}

	
	///TEXT
	//TODO:

	window.draw(circleShape);
}



void ve::CircleButton::setRadius(float radius)
{
	this->m_radius = radius;
}

float ve::CircleButton::getRadius() const
{
	return this->m_radius;
}


bool ve::Button::isAreaClicked()
{
	if (this->m_isClicked)
	{
		this->m_isClicked = false;
		return true;
	}
	else return false;
}

void ve::Button::setPosition(sf::Vector2f position)
{
	this->m_position = position;
}

sf::Vector2f ve::Button::getPosition() const
{
	return this->m_position;
}

void ve::Button::setTexture1(sf::Texture* texture)
{
	this->m_texture1 = texture;
}

sf::Texture* ve::Button::getTexture1() const
{
	return this->m_texture1;
}

void ve::Button::setTexture2(sf::Texture* texture)
{
	this->m_texture2 = texture;
}

sf::Texture* ve::Button::getTexture2() const
{
	return this->m_texture2;
}

void ve::Button::setTexture3(sf::Texture* texture)
{
	this->m_texture3 = texture;
}

sf::Texture* ve::Button::getTexture3() const
{
	return this->m_texture3;
}

void ve::Button::setClicked(bool isClicked)
{
	this->m_isClicked = isClicked;
}
void ve::Button::click()
{
	this->m_clock.restart();
	this->m_clickAnimation = true;
	this->m_clickState = ve::ClickState::CLICKED;
}
ve::ClickState ve::Button::getClickState() const
{
	return this->m_clickState;
}
ve::ClickAnimationStage ve::Button::getAnimationStage() const
{
	return this->m_clickAnimationStage;
}
void ve::Button::setAdditionalParameters(unsigned macros)
{
	this->m_additionalParameters = macros;
}
void ve::Button::lock()
{
	this->m_isLocked = true;
}
void ve::Button::unlock()
{
	this->m_isLocked = false;
}
void ve::Button::setClickState(ClickState state)
{
	this->m_clickState = state;
}
void ve::Button::setAnimationStage(ve::ClickAnimationStage stage)
{
	this->m_clickAnimationStage = stage;
}
/*
void ve::DialogWindow::setText(std::string text)
{
	this->m_text = text;
}

std::string ve::DialogWindow::getText() const
{
	return this->m_text;
}

void ve::DialogWindow::setColor(sf::Color color)
{
	this->m_color = color;
}

sf::Color ve::DialogWindow::getColor() const
{
	return this->m_color;
}

void ve::DialogWindow::setOutlineColor(sf::Color color)
{
	this->m_outlineColor = color;
}

sf::Color ve::DialogWindow::getOutlineColor() const
{
	return this->m_outlineColor;
}

void ve::DialogWindow::setOutlineThickness(float thickness)
{
	this->m_outlineThickness = thickness;
}

float ve::DialogWindow::getOutlineThickness() const
{
	return this->m_outlineThickness;
}

void ve::DialogWindow::setFont(sf::Font* font)
{
	this->m_font = font;
}

sf::Font* ve::DialogWindow::getFont() const
{
	return this->m_font;
}
*/
ve::RectangleButton::RectangleButton()
{
}

ve::RectangleButton::~RectangleButton()
{
}

ve::ButtonType ve::RectangleButton::type() const
{
	return RECTANGLE_BUTTON;
}



ve::DialogWindowControler::DialogWindowControler()
{
}

ve::DialogWindowControler::~DialogWindowControler()
{
}

void ve::DialogWindowControler::addElement(Button* dialogWindow)
{
	this->m_buttonContainer.push_back(dialogWindow);
}

void ve::DialogWindowControler::releaseAllElements()
{
	for (int i = 0; i < this->m_buttonContainer.size(); i++)
		delete m_buttonContainer[i];

	m_buttonContainer.clear();
}

void ve::DialogWindowControler::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < this->m_buttonContainer.size(); i++)
	{
		this->m_buttonContainer[i]->draw(window);
	}
}

ve::Button* ve::DialogWindowControler::getButtonPtr(unsigned id)
{
	if (id < this->m_buttonContainer.size())
		return this->m_buttonContainer[id];

	else return nullptr;
}

ve::PolygonButton::PolygonButton()
{
}

ve::PolygonButton::~PolygonButton()
{
}

ve::ButtonType ve::PolygonButton::type() const
{
	return POLYGON_BUTTON;
}



