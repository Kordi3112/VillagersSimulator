#include "DialogWindow.h"

ve::Button::Button()
{
}


ve::CircleButton::CircleButton()
{
}

ve::CircleButton::CircleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3)
{
	this->setTextures(texture1, texture2, texture3);
}

ve::CircleButton::CircleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, float radius)
{
	this->setTextures(texture1, texture2, texture3);
	this->setRadius(radius);
}

ve::CircleButton::CircleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, float radius, sf::Vector2f position)
{
	this->setTextures(texture1, texture2, texture3);
	this->setRadius(radius);
	this->setPosition(position);
}

ve::CircleButton::~CircleButton()
{
}

ve::ButtonType ve::CircleButton::type() const
{
	return CIRCLE_BUTTON;
}

void ve::Button::checkButtonStatus(sf::Vector2f clickerPosition)
{
	
	if (this->m_clickAnimation == true)
	{
	

		if (this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime * 0.33f)
		{
			//first etap
			if (this->getClickState() == ve::ClickState::CLICKED)
				this->setAnimationStage(ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK1);
			else this->setAnimationStage(ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK1);
			return;
		}
		else if(this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime * 0.66f)
		{
			//second...
			if (this->getClickState() == ve::ClickState::CLICKED)
				this->setAnimationStage(ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK2);
			else this->setAnimationStage(ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK2);
			return;
		}
		else if (this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime)
		{
			//third...
			if (this->getClickState() == ve::ClickState::CLICKED)
				this->setAnimationStage(ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK2);
			else this->setAnimationStage(ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK2);

			return;
		}
		else
		{
			//end
			this->m_clickAnimation = false;

			if (this->getClickState() != ve::ClickState::CLICKED) //it means that unclick animation is ended
			{
				this->unlock();
			}
			else
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
						this->unclick();
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
	if (this->m_clickAnimation)
	{
		if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK1)
		{
			circleShape.setTexture(this->getTexture3());
			circleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK2)
		{
			circleShape.setTexture(this->getTexture3());
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK3)
		{
			circleShape.setTexture(this->getTexture3());
			circleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK1)
		{
			circleShape.setTexture(this->getTexture1());
			circleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK2)
		{
			circleShape.setTexture(this->getTexture1());
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK3)
		{
			circleShape.setTexture(this->getTexture1());
			circleShape.setScale(1.04f, 1.04f);
		}
	}
	else
	{
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
	}
	//
	

	
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

void ve::Button::setTextures(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3)
{
	this->setTexture1(texture1);
	this->setTexture2(texture2);
	this->setTexture3(texture3);
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
	this->m_isClicked = true;
}
void ve::Button::unclick()
{
	this->m_clock.restart();
	this->m_clickAnimation = true;
	this->m_clickState = ve::ClickState::MOUSE_ON_OBJECT;
}
void ve::Button::endAnimation()
{
	this->m_clickAnimation = false;
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

ve::RectangleButton::RectangleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3)
{
	this->setTextures(texture1, texture2, texture3);
}

ve::RectangleButton::RectangleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, sf::Vector2f size)
{
	this->setTextures(texture1, texture2, texture3);
	this->setSize(size);
}

ve::RectangleButton::RectangleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, sf::Vector2f size, sf::Vector2f position)
{
	this->setTextures(texture1, texture2, texture3);
	this->setSize(size);
	this->setPosition(position);
}

ve::RectangleButton::~RectangleButton()
{
}

ve::ButtonType ve::RectangleButton::type() const
{
	return RECTANGLE_BUTTON;
}

bool ve::RectangleButton::isMouseInButtonArea(sf::Vector2f clickerPosition)
{
	if (clickerPosition.x >= (this->getPosition().x - this->getSize().x / 2.0f) and clickerPosition.x <= (this->getPosition().x + this->getSize().x / 2.0f))
	{
		if (clickerPosition.y >= (this->getPosition().y - this->getSize().y / 2.0f) and clickerPosition.y <= (this->getPosition().y + this->getSize().y / 2.0f))
			return true;
		else return false;
	}
	else return false;
}
void ve::RectangleButton::draw(sf::RenderWindow& window)
{
	sf::RectangleShape rectangleShape;
	rectangleShape.setSize(this->getSize());
	rectangleShape.setPosition(this->getPosition());
	rectangleShape.setOrigin(this->getSize()/2.0f);

	//
	if (this->m_clickAnimation)
	{
		if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK1)
		{
			rectangleShape.setTexture(this->getTexture3());
			rectangleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK2)
		{
			rectangleShape.setTexture(this->getTexture3());
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK3)
		{
			rectangleShape.setTexture(this->getTexture3());
			rectangleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK1)
		{
			rectangleShape.setTexture(this->getTexture1());
			rectangleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK2)
		{
			rectangleShape.setTexture(this->getTexture1());
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK3)
		{
			rectangleShape.setTexture(this->getTexture1());
			rectangleShape.setScale(1.04f, 1.04f);
		}
	}
	else
	{
		switch (this->m_clickState)
		{
		case ve::ClickState::NONE_CLICK:
		{
			rectangleShape.setTexture(this->getTexture1());
			break;
		}
		case ve::ClickState::MOUSE_ON_OBJECT:
		{
			rectangleShape.setTexture(this->getTexture2());
			break;
		}
		case ve::ClickState::CLICKED:
		{
			rectangleShape.setTexture(this->getTexture3());
			break;
		}
		}
	}
	//



	///TEXT
	//TODO:

	window.draw(rectangleShape);
}

void ve::RectangleButton::setSize(sf::Vector2f size)
{
	this->m_size = size; 
}

sf::Vector2f ve::RectangleButton::getSize() const
{
	return this->m_size;
}



ve::DialogWindowControler::DialogWindowControler()
{
}

ve::DialogWindowControler::~DialogWindowControler()
{
}

void ve::DialogWindowControler::addElement(ve::Button* dialogWindow)
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

ve::ButtonsPanel::ButtonsPanel()
{
}

ve::ButtonsPanel::~ButtonsPanel()
{
	this->release();
}

void ve::ButtonsPanel::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < this->m_container.size(); i++)
		this->m_container[i]->draw(window);
}

void ve::ButtonsPanel::checkStatus(sf::Vector2f clickerPosition)
{
	
	//checkStatus to all buttons
	for (int i = 0; i < this->m_container.size(); i++)
	{
		this->m_container[i]->checkButtonStatus(clickerPosition);
		//check if number of maximum clicked buttons is correct
		if (this->m_container[i]->getClickState() == ve::ClickState::CLICKED)
		{
			//check if button is already notices as clicked button
			bool isOnList = false;

			for (int j = 0; j < this->m_clickedButtonsId.size(); j++)
			{
				if (this->m_clickedButtonsId[j] == i)isOnList = true;
			}

			if (isOnList)
			{
				//everything is good
				this->m_container[i]->lock();
			}
			else
			{
				//check if there is space for next button to clicked list
				if (this->m_clickedButtonsId.size() >= this->getMaximumClickedButtons())
				{
					//there is no space
					//make space for new button
					if (this->m_clickedButtonsId.size() == 1)
					{
						this->m_clickedButtonsId[0] = i;
					}
					else
					{
						for (int j = this->m_clickedButtonsId.size() - 1; j > 0; j++)
						{

						}
					}

				
				}
				else
				{
					//add new button to list
					this->m_clickedButtonsId.push_back(i);
					continue;
				}
			}
		}
	}
	/*
	//
	//checkStatus to all buttons
	for (int i = 0; i < this->m_container.size(); i++)
	{
		this->m_container[i]->checkButtonStatus(clickerPosition);
		
	}
	*/
}

void ve::ButtonsPanel::setMaximumClickedButtons(unsigned val)
{
	this->m_maximumClickedButtons = val;
}

unsigned ve::ButtonsPanel::getMaximumClickedButtons() const
{
	return this->m_maximumClickedButtons;
}

int ve::ButtonsPanel::addButton(ve::Button* button)
{
	if (button == nullptr)
		return -1;

	button->setAdditionalParameters(ve::LOCK_WHEN_CLICKED);
	this->m_container.push_back(button);

	return this->m_container.size() - 1;
}


ve::Button* ve::ButtonsPanel::getButtonPtr(int id)
{
	if (id < 0 or id >= this->m_container.size())
		return nullptr;

	return this->m_container[id];
}

bool ve::ButtonsPanel::isButtonClicked(int id)
{
	if (id < 0 or id >= this->m_container.size())
		return false;

	if (this->m_container[id]->getClickState() == ve::ClickState::CLICKED)return true;
	else return false;
}

void ve::ButtonsPanel::release()
{
	for (int i = 0; i < this->m_container.size(); i++)
	{
		if(this->m_container[i]!=nullptr)
		delete this->m_container[i];
	}

	this->m_container.clear();

}
