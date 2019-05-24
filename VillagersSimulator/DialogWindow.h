#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
//ve- visual elements
namespace ve
{
	enum ButtonType
	{
		RECTANGLE_BUTTON,
		CIRCLE_BUTTON,
		POLYGON_BUTTON

	};

	enum ClickMode
	{
		SINGLE_TEXTURE,//button texture not change
		DUEL_TEXTURE, //there are two textures, one if no clicked, secound if clicked
		TRIPLE_TEXTURE,//as like above but there is additional texture when mouse is on button
	};

	enum ClickState
	{
		NONE_CLICK,
		MOUSE_ON_OBJECT,
		CLICKED
	};

	enum ClickAnimationStage
	{
		ANIMATIONSTAGE_CLICK1,
		ANIMATIONSTAGE_CLICK2,
		ANIMATIONSTAGE_CLICK3,
		//
		ANIMATIONSTAGE_UNCLICK1,
		ANIMATIONSTAGE_UNCLICK2,
		ANIMATIONSTAGE_UNCLICK3,
	};
	//additional options
	const unsigned PERMALOCK_WHEN_CLICKED = 0x01; // 00001   u can only unlock by the command
	const unsigned LOCK_WHEN_CLICKED = 0x02;  // 000010     when u click button its is locked, when u click again it unlocked 

	//
	//INTERFACES

	class Button //f.e. Buttons etc.
	{
	public:
		Button();
		virtual ~Button() = default;
		//
		virtual void draw(sf::RenderWindow& RenderWindow) = 0;
		//
		void checkButtonStatus(sf::Vector2f clickerPosition);
		virtual bool isMouseInButtonArea(sf::Vector2f clickerPosition) = 0;
		bool isAreaClicked(); //if u check that automaticaly make isClicked = false 
		//
		virtual ButtonType type() const = 0; //helpful function used to dynamic_cast
		//
		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition() const;
		//
		void setTexture1(sf::Texture* texture);
		sf::Texture* getTexture1() const;
		//
		void setTexture2(sf::Texture* texture);
		sf::Texture* getTexture2() const;
		//
		void setTexture3(sf::Texture* texture);
		sf::Texture* getTexture3() const;
		//
		void setTextures(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3);
		//
		void setClicked(bool isClicked); //manualy set if button is clicked
		void click(); //starts click animation
		void unclick();//starts unclick animation
		void endAnimation();
		ClickState getClickState() const;
		ClickAnimationStage getAnimationStage() const;
		//
		void setAdditionalParameters(unsigned macros);
		//
		void lock();
		void unlock();
		//
		void pressButton();
		/*
		*/
	protected:

		void setClickState(ClickState state);
		void setAnimationStage(ve::ClickAnimationStage stage);
		//
		sf::Vector2f m_position;
		float m_rotation;	
		//
		bool m_isClicked = false;
		ClickState m_clickState;
		//
		sf::Texture* m_texture1= nullptr;
		sf::Texture* m_texture2 = nullptr;
		sf::Texture* m_texture3 = nullptr;
		//
		unsigned m_additionalParameters = 0;
		//
		sf::Clock m_clock; //is used to checking button click cooldown
		unsigned m_animationClickTime = 300;//in ms
		bool m_clickAnimation = false;
		ClickAnimationStage m_clickAnimationStage;
		//
		bool m_isLocked = false;
	private:

	};
	 
	//
	//
	//

	class RectangleButton : public Button
	{
	public:
		RectangleButton();
		RectangleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3);
		RectangleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, sf::Vector2f size);
		RectangleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, sf::Vector2f size, sf::Vector2f position);
		~RectangleButton();
		//
		ButtonType type() const;
		//
		bool isMouseInButtonArea(sf::Vector2f clickerPosition) override;
		//
		void draw(sf::RenderWindow& window) override;
		//
		void setSize(sf::Vector2f size);
		sf::Vector2f getSize() const;
	private:
		sf::Vector2f m_size;
	};

	class CircleButton : public Button
	{
	public:
		CircleButton();
		CircleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3);
		CircleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, float radius);
		CircleButton(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, float radius, sf::Vector2f position);
		~CircleButton();
		//
		ButtonType type() const;
		//
		bool isMouseInButtonArea(sf::Vector2f clickerPosition) override;
		//
		void draw(sf::RenderWindow& window) override;
		//
		void setRadius(float radius);
		float getRadius() const;
		//

	private:
		float m_radius;
	};
	/*
	class PolygonButton : public Button
	{
	public:
		PolygonButton();
		~PolygonButton();
		//
		ButtonType type() const;
		//
		bool isMouseInButtonArea(sf::Vector2f clickerPosition) override;
		//
		void draw(sf::RenderWindow& window) override;
	private:
		std::vector<sf::Vector2f> m_bounds;

	*/
	class ButtonsPanel //a few buttons which are connected, if some button is clicked others are unclicked, like choose one panel
	{
	public:
		ButtonsPanel();
		~ButtonsPanel();
		//
		void draw(sf::RenderWindow& window);
		//
		void checkStatus(sf::Vector2f clickerPosition);
		//
		void setMaximumClickedButtons(unsigned val); // how much buttons can be clicked it this same time
		unsigned getMaximumClickedButtons() const;
		//
		int addButton(ve::Button* button);//returns button id
		//
		ve::Button* getButtonPtr(int id);
		//
		bool isButtonClicked(int id);
		//
		void release(); //clean up buttons
	private:
		std::vector<Button*> m_container;
		//
		unsigned m_maximumClickedButtons = 1;
		std::vector<unsigned> m_clickedButtonsId;
	};


	///=////////////////////////////////////////////////////
	//  DIALOGWINDOWS CONTROLER
	///=///////////////////////////////////////////////////
	
	//controler for dialog windows
	class DialogWindowControler
	{
	public:
		DialogWindowControler();
		~DialogWindowControler();
		//
		void addElement(Button* dialogWindow);
		void releaseAllElements();
		//
		void draw(sf::RenderWindow& window);
		//
		Button* getButtonPtr(unsigned id);
	private:
		std::vector<Button*> m_buttonContainer;
	};
}


