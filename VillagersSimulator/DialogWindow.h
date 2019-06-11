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
		void setTextures(sf::Texture* texture);
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
		void setClickState(ClickState state);
		bool m_isClicked = false;
		/*
		*/
	protected:

		void setAnimationStage(ve::ClickAnimationStage stage);
		//
		sf::Vector2f m_position;
		float m_rotation;
		//
		//bool m_isClicked = false;
		ClickState m_clickState;
		//
		sf::Texture* m_texture1 = nullptr;
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
		int addButton(std::string name, ve::Button* button);//returns button id
		//
		ve::Button* getButtonPtr(int id);
		ve::Button* getButtonPtr(std::string name);
		//
		int getClickedButtonId() const;
		std::string getName(int id);
		//
		bool isButtonClicked(int id);
		//
		void release(); //clean up buttons
	private:
		std::vector<Button*> m_container;
		std::vector<std::string> m_names;
		int m_lastClickedButtonId = -1;
		//
		unsigned m_maximumClickedButtons = 1;
		std::vector<unsigned> m_clickedButtonsId;
	};

	class Slider//
	{
	public:
		Slider();
		~Slider();
		//
		//
		void setBackgroundTexture(sf::Texture* texture);
		//
		sf::Texture* getBackgroundTexture() const;
		//
		void setSize(sf::Vector2f size);
		sf::Vector2f getSize() const;
		//
		void draw(sf::RenderWindow& window);
		//
		void setSliderColor(sf::Color color);
		void setSliderPointerColor(sf::Color color);
		void setPosition(sf::Vector2f position);
		void setValue(float value);
		//
		sf::Vector2f getPosition() const;
		sf::Color getSliderColor() const;
		sf::Color getSliderPointerColor() const;
		//
		float getValue() const;
		//
		void checkStatus(sf::Vector2f clikerPosition);
	private:
		bool isMouseInPointerArea(sf::Vector2f clikerPosition);

		sf::Texture* m_texture = nullptr;
		sf::Color m_pointerColor;
		sf::Color m_sliderColor;
		sf::Vector2f m_size;//value
		sf::Vector2f m_position;

		float m_value = 0.5f;
	};

	class ButtonMenu
	{
	public:
		ButtonMenu();
		~ButtonMenu();
		ButtonMenu(sf::Texture* texture, sf::Vector2f size);
		void init();//automaticly when created
		///INIT BUTTON
		void initButton();
		void setButtonTextures(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3);
		void setButtonSize(sf::Vector2f size);
		void setButtonPosition(sf::Vector2f position);
		///SET
		void setBackgroundTexture(sf::Texture* texture);
		void setPosition(sf::Vector2f position);
		void setSize(sf::Vector2f size);
		///GET
		bool isActive() const;
		//
		sf::Vector2f getButtonSize() const;
		sf::Vector2f getButtonPosition() const;
		//
		sf::Vector2f getPosition() const;
		sf::Vector2f getSize() const;
		///DRAW
		//
		void draw(sf::RenderWindow& window);
		///CHECK
		void checkStatus(sf::Vector2f clickerPosition);
		///ADD
		void addComponent(std::string name, ButtonsPanel* Panel);
		void addComponent(std::string name, Button* button);
		void addComponent(std::string name, Slider* slider);
		///GET
		ButtonsPanel* getComponentButtonPanel(std::string name);
		Button* getComponentButton(std::string name);
		Slider* getComponentSlider(std::string name);
		///RELEASE
		void releaseAllComponents();
		void releaseInitButton();
	private:
		std::vector<ButtonsPanel*> m_containerPanel;
		std::vector<std::string> m_containerPanelName;
		std::vector<Button*> m_containerButton;
		std::vector<std::string> m_containerButtonName;
		std::vector<Slider*> m_containerSlider;
		std::vector<std::string> m_containerSliderName;
		sf::Texture* m_backgroundTexture = nullptr;
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		//
		bool m_isActive = false;
		//
		RectangleButton* m_initButton = nullptr;
	};

	class TextBox
	{
	public:
		//
		enum Text_Place {
			TEXT_MIDDLE,
			TEXT_RIGHT,
			TEXT_LEFT,
			TEXT_TOP,
			TEXT_BOTTOM,
		};


		//
		TextBox();
		~TextBox();
		//
		void setSize(sf::Vector2f size);
		sf::Vector2f getSize() const;
		//
		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition() const;
		//
		void setBackgroundColor(sf::Color color);
		sf::Color geBackgroundColor();
		//
		void setString(std::string text);
		std::string getString() const;
		//
		void setTextSize(float size);
		float getTextSize();
		//
		void setTextFont(sf::Font* font);
		sf::Font* getTextFont();
		//
		void setTextColor(sf::Color color);
		sf::Color getTextColor();
		//
		void setStyle(sf::Uint32 style);
		sf::Uint32 getStyle();
		//
		void setMargins(sf::Vector2f margins);
		sf::Vector2f getMargins() const;
		//
		void setTextPlace(Text_Place x, Text_Place y);
		Text_Place getTextPlaceX() const;
		Text_Place getTextPlaceY() const;
		//
		void draw(sf::RenderWindow& window);
	private:
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		sf::Color m_color;
		sf::Font* m_font;
		float m_textSize;
		sf::Color m_textcolor;
		std::string m_text;
		sf::Uint32 m_style;
		sf::Vector2f m_margins;
		Text_Place m_placeX = Text_Place::TEXT_MIDDLE;
		Text_Place m_placeY = Text_Place::TEXT_MIDDLE;

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
		int addElement(std::string name, Button* dialogWindow);
		int addElement(std::string name, Slider* dialogWindow);
		int addElement(std::string name, TextBox* dialogWindow);
		//
		void releaseAllElements();
		//
		void checkStatus(sf::Vector2f clickerPosition);
		//
		void draw(sf::RenderWindow& window);
		//
		Button* getButtonPtr(unsigned id);
		Button* getButtonPtr(std::string name);
		//
		Slider* getSliderPtr(unsigned id);
		Slider* getSliderPtr(std::string name);
		//
		TextBox* getTextBoxPtr(unsigned id);
		TextBox* getTextBoxPtr(std::string name);
	private:
		//
		std::vector<Button*> m_buttonContainer;
		std::vector<std::string> m_buttonNames;
		//
		std::vector<Slider*> m_sliderContainer;
		std::vector<std::string> m_sliderNames;
		//
		std::vector<TextBox*> m_textBoxContainer;
		std::vector<std::string> m_textBoxNames;

	};


}

