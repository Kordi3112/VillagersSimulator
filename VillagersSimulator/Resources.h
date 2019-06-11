#pragma once
#include "TexturePack.h"
//its is container for all global resoures in game f.e. textures
class Resources
{
public:
	//////////////////////////////
	///TEXTUREPACKS
	////////////////////////////
	///OBJECTS
	TexturePack objects_environment;
	TexturePack objects_creatures;
	TexturePack objects_buildings;

	///MAP CREATOR
	TexturePack mapCreator_Buttons;
	TexturePack mapCreator_Backgrounds;
	//////////////////////////////
	///FONTS
	////////////////////////////
	sf::Font font_Roboto_Black;
	sf::Font font_Roboto_BlackItalic;
	sf::Font font_Roboto_Bold;
	sf::Font font_Roboto_BoldItalic;
	sf::Font font_Roboto_Italic;
	sf::Font font_Roboto_Light;
	sf::Font font_Roboto_LightItalic;
	sf::Font font_Roboto_Medium;
	sf::Font font_Roboto_MediumItalic;
	sf::Font font_Roboto_Regular;
	sf::Font font_Roboto_Thin;
	sf::Font font_Roboto_ThinItalic;


	//
	void load(); //load all resources to memory 

private:
	void loadTextures();
	void loadFonts();
};
