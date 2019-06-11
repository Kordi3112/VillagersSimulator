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
		else if (this->m_clock.getElapsedTime().asMilliseconds() < this->m_animationClickTime * 0.66f)
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
			//circleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_CLICK3)
		{
			circleShape.setTexture(this->getTexture3());
			circleShape.setScale(1.04f, 1.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK1)
		{
			circleShape.setTexture(this->getTexture1());
			//circleShape.setScale(2.04f, 2.04f);
		}
		else if (this->getAnimationStage() == ve::ClickAnimationStage::ANIMATIONSTAGE_UNCLICK2)
		{
			circleShape.setTexture(this->getTexture1());
			circleShape.setScale(1.04f, 1.04f);
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
			circleShape.setScale(1.54f, 1.54f);
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

void ve::Button::setTextures(sf::Texture* texture)
{
	setTextures(texture, texture, texture);
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
	rectangleShape.setOrigin(this->getSize() / 2.0f);

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


/*
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
*/
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
	std::vector<int> clickedButtons;

	for (int i = 0; i < m_container.size(); i++)
	{
		//for each button check status
		m_container[i]->checkButtonStatus(clickerPosition);

		
		if (m_container[i]->getClickState() == ve::ClickState::CLICKED)
		{
			clickedButtons.push_back(i);

			if (m_lastClickedButtonId == i)
			{
				//everything is good
			}
			else
			{
				//turn off other buttons
				for (int j = 0; j < m_container.size(); j++)
				{
					if (i == j)continue;

					m_container[i]->setClickState(ve::ClickState::NONE_CLICK);
					m_container[i]->endAnimation();
				}
			}

			//firts call
			if (m_lastClickedButtonId == -1)
			{
				m_lastClickedButtonId = i;
			}
		}
		else
		{
			if (m_lastClickedButtonId == i)
			{
				m_lastClickedButtonId = -1;
			}
		}
		
		
	}


}

void ve::ButtonsPanel::setMaximumClickedButtons(unsigned var)
{
	this->m_maximumClickedButtons = var;
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
	button->setClickState(ve::ClickState::NONE_CLICK);

	m_container.push_back(button);
	m_names.push_back("unnamed");

	return m_container.size() - 1;
}

int ve::ButtonsPanel::addButton(std::string name, ve::Button* button)
{
	if (button == nullptr)
		return -1;

	button->setAdditionalParameters(ve::LOCK_WHEN_CLICKED);
	button->setClickState(ve::ClickState::NONE_CLICK);

	m_container.push_back(button);
	m_names.push_back(name);

	return m_container.size() - 1;
}


ve::Button* ve::ButtonsPanel::getButtonPtr(int id)
{
	if (id < 0 or id >= this->m_container.size())
		return nullptr;

	return this->m_container[id];
}

ve::Button* ve::ButtonsPanel::getButtonPtr(std::string name)
{
	for (int i = 0; i < m_names.size(); i++)
	{
		if (name == m_names[i])
			return m_container[i];
		
	}

	return nullptr;
}

int ve::ButtonsPanel::getClickedButtonId() const
{
	return m_lastClickedButtonId;
}

std::string ve::ButtonsPanel::getName(int id)
{
	if (id < 0 || id >= m_container.size())
		return std::string();

	else return m_names[id];
}

bool ve::ButtonsPanel::isButtonClicked(int id)
{
	if (id < 0 or id >= this->m_container.size())
		return false;

	if (this->m_container[id]->getClickState() == ve::ClickState::CLICKED)return true;
	else return false;
}
/*
bool ve::ButtonsPanel::isButtonUnclicked(int id)
{
	if (id < 0 or id >= this->m_container.size())
		return false;

	if (this->m_container[id]->getClickState() == ve::ClickState::CLICKED)return false;
	else return true;
}
*/

void ve::ButtonsPanel::release()
{
	for (int i = 0; i < this->m_container.size(); i++)
	{
		if (this->m_container[i] != nullptr)
			delete this->m_container[i];
	}

	this->m_container.clear();

}

ve::ButtonMenu::ButtonMenu()
{
}
ve::ButtonMenu::~ButtonMenu()
{
}
ve::ButtonMenu::ButtonMenu(sf::Texture* texture, sf::Vector2f size)
{
}

void ve::ButtonMenu::initButton()
{
	if (m_initButton == nullptr)
	{
		m_initButton = new RectangleButton();
		m_initButton->setAdditionalParameters(LOCK_WHEN_CLICKED);
		
	}
	
}

void ve::ButtonMenu::setButtonTextures(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3)
{
	m_initButton->setTextures(texture1,texture2, texture3);

}

void ve::ButtonMenu::setButtonSize(sf::Vector2f size)
{
	m_initButton->setSize(size);
}

void ve::ButtonMenu::setButtonPosition(sf::Vector2f position)
{
	m_initButton->setPosition(position);
}

void ve::ButtonMenu::setBackgroundTexture(sf::Texture* texture)
{
	m_backgroundTexture = texture;
}

void ve::ButtonMenu::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void ve::ButtonMenu::setSize(sf::Vector2f size)
{
	m_size = size;
}

bool ve::ButtonMenu::isActive() const
{
	return m_isActive;
}

sf::Vector2f ve::ButtonMenu::getButtonSize() const
{
	return m_initButton->getSize();
}

sf::Vector2f ve::ButtonMenu::getButtonPosition() const
{
	return m_initButton->getPosition();
}

sf::Vector2f ve::ButtonMenu::getPosition() const
{
	return m_position;
}

sf::Vector2f ve::ButtonMenu::getSize() const
{
	return m_size;
}




void ve::ButtonMenu::draw(sf::RenderWindow& window)
{
	//INIT BUTTON
	m_initButton->draw(window);

	if (isActive())
	{
		//BACKGROUND
		sf::RectangleShape background;
		background.setTexture(m_backgroundTexture);
		background.setSize(m_size);
		background.setPosition(m_position);
		background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);

		window.draw(background);
		
		//BUTTONS
		for (int i = 0; i < m_containerButton.size(); i++)
		{
			m_containerButton[i]->draw(window);
		}
		//PANELS
		for (int i = 0; i < m_containerPanel.size(); i++)
		{
			m_containerPanel[i]->draw(window);
		}
		//SLIDER
		for (int i = 0; i < m_containerSlider.size(); i++)
		{
			m_containerSlider[i]->draw(window);
		}
	}
	
}

void ve::ButtonMenu::checkStatus(sf::Vector2f clickerPosition)
{
	m_initButton->checkButtonStatus(clickerPosition);
	//
	if (m_initButton->getClickState() == ve::ClickState::CLICKED)
		m_isActive = true;
	else m_isActive = false;
	///CHECK COMPONENTS STATUS

	if (isActive())
	{
		//BUTTONS
		for (int i = 0; i < m_containerButton.size(); i++)
		{
			m_containerButton[i]->checkButtonStatus(clickerPosition);
		}
		//PANELS
		for (int i = 0; i < m_containerPanel.size(); i++)
		{
			m_containerPanel[i]->checkStatus(clickerPosition);
		}
		//SLIDER
		for (int i = 0; i < m_containerSlider.size(); i++)
		{
			m_containerSlider[i]->checkStatus(clickerPosition);
		}
	}
	
}

void ve::ButtonMenu::addComponent(std::string name, ButtonsPanel* Panel)
{
	m_containerPanel.push_back(Panel);
	m_containerPanelName.push_back(name);
}

void ve::ButtonMenu::addComponent(std::string name, Button* Panel)
{
	m_containerButton.push_back(Panel);
	m_containerButtonName.push_back(name);
}

void ve::ButtonMenu::addComponent(std::string name, Slider* Panel)
{
	m_containerSlider.push_back(Panel);
	m_containerSliderName.push_back(name);
}

ve::ButtonsPanel* ve::ButtonMenu::getComponentButtonPanel(std::string name)
{
	for (int i = 0; i < m_containerPanelName.size(); i++)
	{
		if(m_containerPanelName[i] == name)
		{
			return m_containerPanel[i];
		}
	}

	return nullptr;
}

ve::Button* ve::ButtonMenu::getComponentButton(std::string name)
{
	for (int i = 0; i < m_containerButtonName.size(); i++)
	{
		if (m_containerButtonName[i] == name)
		{
			return m_containerButton[i];
		}
	}

	return nullptr;
}

ve::Slider* ve::ButtonMenu::getComponentSlider(std::string name)
{
	for (int i = 0; i < m_containerSliderName.size(); i++)
	{
		if (m_containerSliderName[i] == name)
		{
			return m_containerSlider[i];
		}
	}

	return nullptr;
}


void ve::ButtonMenu::releaseAllComponents()
{
	//PANELS
	for (int i = 0; i < m_containerPanel.size(); i++)
	{
		m_containerPanel[i]->release();
		delete m_containerPanel[i];
	}

	m_containerPanelName.clear();

	//BUTTONS
	for (int i = 0; i < m_containerButton.size(); i++)
	{
		delete m_containerButton[i];
	}

	m_containerButtonName.clear();
	//SLIDERS
	for (int i = 0; i < m_containerSlider.size(); i++)
	{
		delete m_containerSlider[i];
	}
	
	m_containerSliderName.clear();
}

void ve::ButtonMenu::releaseInitButton()
{
	delete m_initButton;
}

ve::Slider::Slider()
{
}

ve::Slider::~Slider()
{
}

void ve::Slider::setBackgroundTexture(sf::Texture* texture)
{
	this->m_texture = texture;
}

sf::Texture* ve::Slider::getBackgroundTexture() const
{
	return this->m_texture;
}

void ve::Slider::setSize(sf::Vector2f size)
{
	this->m_size = size;
}

void ve::Slider::draw(sf::RenderWindow& window)
{

	sf::RectangleShape begin;
	begin.setPosition(getPosition().x - 0.475f * getSize().x, getPosition().y);
	begin.setSize(sf::Vector2f(getSize().x * 0.05f, getSize().y));
	begin.setFillColor(this->getSliderColor());
	begin.setOrigin(begin.getSize().x / 2.0f, begin.getSize().y / 2.0f);
	//
	sf::RectangleShape slider;
	slider.setPosition(getPosition());
	slider.setSize(sf::Vector2f(getSize().x * 0.9f, getSize().y * 0.25f));
	slider.setFillColor(this->getSliderColor());
	slider.setOrigin(slider.getSize().x / 2.0f, slider.getSize().y / 2.0f);
	//
	sf::RectangleShape end;
	end.setPosition(getPosition().x + 0.475f * getSize().x, getPosition().y);
	end.setSize(sf::Vector2f(getSize().x * 0.05f, getSize().y));
	end.setFillColor(this->getSliderColor());
	end.setOrigin(end.getSize().x / 2.0f, end.getSize().y / 2.0f);
	//
	sf::RectangleShape pointer;
	pointer.setPosition(getPosition().x + (m_value - 0.5) * 0.8 * getSize().x, getPosition().y);
	pointer.setSize(sf::Vector2f(getSize().x * 0.1f, getSize().y));
	pointer.setFillColor(this->getSliderPointerColor());
	pointer.setOrigin(pointer.getSize().x / 2.0f, pointer.getSize().y / 2.0f);
	///SHOW
	window.draw(begin);
	window.draw(end);
	window.draw(slider);
	window.draw(pointer);

}

void ve::Slider::setSliderColor(sf::Color color)
{
	m_sliderColor = color;
}
void ve::Slider::setSliderPointerColor(sf::Color color)
{
	m_pointerColor = color;
}
void ve::Slider::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void ve::Slider::setValue(float value)
{
	if (value > 1.0f)value = 1.0f;
	if (value < 0.0f)value = 0.0f;

	m_value = value;
}

sf::Vector2f ve::Slider::getPosition() const
{
	return m_position;
}

sf::Color ve::Slider::getSliderColor() const
{
	return m_sliderColor;
}
sf::Color ve::Slider::getSliderPointerColor() const
{
	return m_pointerColor;
}
float ve::Slider::getValue() const
{
	return m_value;
}
void ve::Slider::checkStatus(sf::Vector2f clikerPosition)
{
	if (isMouseInPointerArea(clikerPosition)) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			if ((clikerPosition.x >= getPosition().x - 0.40f * getSize().x) && (clikerPosition.x <= getPosition().x + 0.40f * getSize().x))
			{
				this->m_value = (clikerPosition.x - getPosition().x + 0.40f * getSize().x) * 1.25f / getSize().x;
				if (m_value > 1) m_value = 1;
				if (m_value < 0) m_value = 0;
			}
		}
	}

}
sf::Vector2f ve::Slider::getSize() const
{
	return m_size;
}
bool ve::Slider::isMouseInPointerArea(sf::Vector2f clickerPosition)
{
	if ((clickerPosition.x <= getPosition().x + ((m_value - 0.5f) * 0.8f + 0.05f) * getSize().x) && (clickerPosition.x >= getPosition().x + ((m_value - 0.5f) * 0.8f - 0.05f) * getSize().x) && (clickerPosition.y >= getPosition().y - 0.5f * getSize().y) && (clickerPosition.y <= getPosition().y + 0.5f * getSize().y)) return true;
	else return false;
}

void ve::DialogWindowControler::draw(sf::RenderWindow& window)
{
	//Buttons
	for (int i = 0; i < m_buttonContainer.size(); i++)
	{
		m_buttonContainer[i]->draw(window);
	}

	//Sliders
	for (int i = 0; i < m_sliderContainer.size(); i++)
	{
		m_sliderContainer[i]->draw(window);
	}
	//TextBoxes
	for (int i = 0; i < m_textBoxContainer.size(); i++)
	{
		m_textBoxContainer[i]->draw(window);
	}
}

ve::Button* ve::DialogWindowControler::getButtonPtr(unsigned id)
{
	if (id  <0 || id >= m_buttonContainer.size())
		return nullptr;

	return m_buttonContainer[id];
}

ve::Button* ve::DialogWindowControler::getButtonPtr(std::string name)
{
	for (int i = 0; i < m_buttonNames.size(); i++)
	{
		if (m_buttonNames[i] == name)
			return m_buttonContainer[i];
	}

	return nullptr;
}
//
ve::Slider* ve::DialogWindowControler::getSliderPtr(unsigned id)
{
	if (id < 0 || id >= m_sliderContainer.size())
		return nullptr;

	return m_sliderContainer[id];
}

ve::Slider* ve::DialogWindowControler::getSliderPtr(std::string name)
{
	for (int i = 0; i < m_sliderNames.size(); i++)
	{
		if (m_sliderNames[i] == name)
			return m_sliderContainer[i];
	}

	return nullptr;
}

ve::TextBox* ve::DialogWindowControler::getTextBoxPtr(unsigned id)
{
	if (id < 0 || id >= m_textBoxContainer.size())
		return nullptr;

	return m_textBoxContainer[id];
}

ve::TextBox* ve::DialogWindowControler::getTextBoxPtr(std::string name)
{
	for (int i = 0; i < m_textBoxNames.size(); i++)
	{
		if (m_textBoxNames[i] == name)
			return m_textBoxContainer[i];
	}

	return nullptr;
}
////

ve::TextBox::TextBox()
{
}

ve::TextBox::~TextBox()
{
}

void ve::TextBox::setSize(sf::Vector2f size)
{
	m_size = size;
}

sf::Vector2f ve::TextBox::getSize() const
{
	return m_size;
}

void ve::TextBox::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f ve::TextBox::getPosition() const
{
	return m_position;
}

void ve::TextBox::setBackgroundColor(sf::Color color)
{
	m_color = color;
}

sf::Color ve::TextBox::geBackgroundColor()
{
	return m_color;
}

void ve::TextBox::setString(std::string text)
{
	m_text = text;
}

std::string ve::TextBox::getString() const
{
	return m_text;
}



void ve::TextBox::setTextSize(float size)
{
	m_textSize = size;
}

float ve::TextBox::getTextSize()
{
	return m_textSize;
}

void ve::TextBox::setTextFont(sf::Font* font)
{
	m_font = font;
}

sf::Font* ve::TextBox::getTextFont()
{
	return m_font;
}

void ve::TextBox::setTextColor(sf::Color color)
{
	m_textcolor = color;
}

sf::Color ve::TextBox::getTextColor()
{
	return m_textcolor;
}

void ve::TextBox::setStyle(sf::Uint32 style)
{
	m_style = style;
}

sf::Uint32 ve::TextBox::getStyle()
{
	return m_style;
}

void ve::TextBox::setMargins(sf::Vector2f margins)
{
	m_margins = margins;
}

sf::Vector2f ve::TextBox::getMargins() const
{
	return m_margins;
}

void ve::TextBox::setTextPlace(Text_Place x, Text_Place y)
{
	m_placeX = x;
	m_placeY = y;
}

ve::TextBox::Text_Place ve::TextBox::getTextPlaceX() const
{
	return m_placeX;
}

ve::TextBox::Text_Place ve::TextBox::getTextPlaceY() const
{
	return m_placeY;
}

void ve::TextBox::draw(sf::RenderWindow& window)
{
	sf::RectangleShape box;
	box.setPosition(getPosition());
	box.setSize(getSize());
	box.setFillColor(geBackgroundColor());
	box.setOrigin(box.getSize().x / 2.0f, box.getSize().y / 2.0f);
	//
	window.draw(box);
	//
	sf::Text text;
	text.setFont(*getTextFont());
	text.setCharacterSize(getTextSize());
	text.setFillColor(getTextColor());
	text.setStyle(getStyle());
	text.setString(getString());
	//
	sf::Vector2f textPosition;
	sf::Vector2f textOrigin;
	///Placex
	if (getTextPlaceX() == Text_Place::TEXT_LEFT)
	{
		textOrigin.x = 0.0f;
		textPosition.x = getPosition().x - box.getSize().x / 2.0f + getMargins().x;
	}
	else if (getTextPlaceX() == Text_Place::TEXT_MIDDLE)
	{
		textOrigin.x = text.getGlobalBounds().width / 2.0f;
		textPosition.x = getPosition().x;
	}
	else if (getTextPlaceX() == Text_Place::TEXT_RIGHT)
	{
		textOrigin.x = text.getGlobalBounds().width;
		textPosition.x = getPosition().x + box.getSize().x / 2.0f - getMargins().x;
	}
	///Placey
	if (getTextPlaceY() == Text_Place::TEXT_TOP)
	{
		textOrigin.y = 0.0f;
		textPosition.y = getPosition().y - box.getSize().y / 2.0f + getMargins().y;
	}
	else if (getTextPlaceY() == Text_Place::TEXT_MIDDLE)
	{
		textOrigin.y = text.getGlobalBounds().height / 2.0f;
		textPosition.y = getPosition().y;
	}
	else if (getTextPlaceY() == Text_Place::TEXT_BOTTOM)
	{
		textOrigin.y = text.getGlobalBounds().height;
		textPosition.y = getPosition().y + box.getSize().y / 2.0f - getMargins().y;
	}

	text.setOrigin(textOrigin);
	text.setPosition(textPosition);
	//
	
	window.draw(text);
}






////
ve::DialogWindowControler::DialogWindowControler()
{
}

ve::DialogWindowControler::~DialogWindowControler()
{
}

int ve::DialogWindowControler::addElement(std::string name, Button* dialogWindow)
{
	m_buttonContainer.push_back(dialogWindow);
	m_buttonNames.push_back(name);

	return m_buttonContainer.size() - 1;
}

int ve::DialogWindowControler::addElement(std::string name, Slider* dialogWindow)
{
	m_sliderContainer.push_back(dialogWindow);
	m_sliderNames.push_back(name);

	return m_sliderContainer.size() - 1;
}

int ve::DialogWindowControler::addElement(std::string name, TextBox* dialogWindow)
{
	m_textBoxContainer.push_back(dialogWindow);
	m_textBoxNames.push_back(name);

	return m_textBoxContainer.size() - 1;
}

void ve::DialogWindowControler::releaseAllElements()
{
	//Buttons
	for (int i = 0; i < m_buttonContainer.size(); i++)
	{
		delete m_buttonContainer[i];
	}

	m_buttonNames.clear();

	//Sliders
	for (int i = 0; i < m_sliderContainer.size(); i++)
	{
		delete m_sliderContainer[i];
	}

	m_sliderNames.clear();

	//TextBoxes
	for (int i = 0; i < m_textBoxContainer.size(); i++)
	{
		delete m_textBoxContainer[i];
	}

	m_textBoxNames.clear();
}

void ve::DialogWindowControler::checkStatus(sf::Vector2f clickerPosition)
{
	//Buttons
	for (int i = 0; i < m_buttonContainer.size(); i++)
	{
		m_buttonContainer[i]->checkButtonStatus(clickerPosition);
	}

	//Sliders
	for (int i = 0; i < m_sliderContainer.size(); i++)
	{
		m_sliderContainer[i]->checkStatus(clickerPosition);
	}

	//TextBoxes
	//.....
}
