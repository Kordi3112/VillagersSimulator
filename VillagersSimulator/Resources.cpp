#include "Resources.h"

void Resources::load()
{
	loadTextures();
	loadFonts();
}

void Resources::loadTextures()
{
	///OBJECTS
	//environment
	objects_environment.loadNewTexture("tree", "../data/texturepacks/environment/tree.png");


	///MAP CREATOR
	//===>Buttons
	mapCreator_Buttons.loadNewTexture("menu_noClicked", "../data/texturepacks/mapCreator/buttons/menu_noClicked.png");
	mapCreator_Buttons.loadNewTexture("menu_onIt", "../data/texturepacks/mapCreator/buttons/menu_onIt.png");
	mapCreator_Buttons.loadNewTexture("menu_clicked", "../data/texturepacks/mapCreator/buttons/menu_clicked.png");
	//
	mapCreator_Buttons.loadNewTexture("circleBrush_noClicked", "../data/texturepacks/mapCreator/buttons/circleBrush_noClicked.png");
	mapCreator_Buttons.loadNewTexture("circleBrush_onIt", "../data/texturepacks/mapCreator/buttons/circleBrush_onIt.png");
	mapCreator_Buttons.loadNewTexture("circleBrush_clicked", "../data/texturepacks/mapCreator/buttons/circleBrush_clicked.png");
	//
	mapCreator_Buttons.loadNewTexture("rectangleBrush", "../data/texturepacks/mapCreator/buttons/rectangleBrush.png");
	mapCreator_Buttons.loadNewTexture("rightPanelInit", "../data/texturepacks/mapCreator/buttons/rightPanelInit.png");
	//Seawater
	mapCreator_Buttons.loadNewTexture("seawater_noClicked", "../data/texturepacks/mapCreator/buttons/seawater_noClicked.png");
	mapCreator_Buttons.loadNewTexture("seawater_onIt", "../data/texturepacks/mapCreator/buttons/seawater_onIt.png");
	mapCreator_Buttons.loadNewTexture("seawater_clicked", "../data/texturepacks/mapCreator/buttons/seawater_clicked.png");
	//water
	mapCreator_Buttons.loadNewTexture("water_noClicked", "../data/texturepacks/mapCreator/buttons/water_noClicked.png");
	mapCreator_Buttons.loadNewTexture("water_onIt", "../data/texturepacks/mapCreator/buttons/water_onIt.png");
	mapCreator_Buttons.loadNewTexture("water_clicked", "../data/texturepacks/mapCreator/buttons/water_clicked.png");
	//grass
	mapCreator_Buttons.loadNewTexture("grass_noClicked", "../data/texturepacks/mapCreator/buttons/grass_noClicked.png");
	mapCreator_Buttons.loadNewTexture("grass_onIt", "../data/texturepacks/mapCreator/buttons/grass_onIt.png");
	mapCreator_Buttons.loadNewTexture("grass_clicked", "../data/texturepacks/mapCreator/buttons/grass_clicked.png");
	//sand
	mapCreator_Buttons.loadNewTexture("sand_noClicked", "../data/texturepacks/mapCreator/buttons/sand_noClicked.png");
	mapCreator_Buttons.loadNewTexture("sand_onIt", "../data/texturepacks/mapCreator/buttons/sand_onIt.png");
	mapCreator_Buttons.loadNewTexture("sand_clicked", "../data/texturepacks/mapCreator/buttons/sand_clicked.png");
	//snow
	mapCreator_Buttons.loadNewTexture("snow_noClicked", "../data/texturepacks/mapCreator/buttons/snow_noClicked.png");
	mapCreator_Buttons.loadNewTexture("snow_onIt", "../data/texturepacks/mapCreator/buttons/snow_onIt.png");
	mapCreator_Buttons.loadNewTexture("snow_clicked", "../data/texturepacks/mapCreator/buttons/snow_clicked.png");
	//rock1
	mapCreator_Buttons.loadNewTexture("rock1_noClicked", "../data/texturepacks/mapCreator/buttons/rock1_noClicked.png");
	mapCreator_Buttons.loadNewTexture("rock1_onIt", "../data/texturepacks/mapCreator/buttons/rock1_onIt.png");
	mapCreator_Buttons.loadNewTexture("rock1_clicked", "../data/texturepacks/mapCreator/buttons/rock1_clicked.png");
	//rock2
	mapCreator_Buttons.loadNewTexture("rock2_noClicked", "../data/texturepacks/mapCreator/buttons/rock2_noClicked.png");
	mapCreator_Buttons.loadNewTexture("rock2_onIt", "../data/texturepacks/mapCreator/buttons/rock2_onIt.png");
	mapCreator_Buttons.loadNewTexture("rock2_clicked", "../data/texturepacks/mapCreator/buttons/rock2_clicked.png");
	//tree
	mapCreator_Buttons.loadNewTexture("tree_noClicked", "../data/texturepacks/mapCreator/buttons/tree_noClicked.png");
	mapCreator_Buttons.loadNewTexture("tree_onIt", "../data/texturepacks/mapCreator/buttons/tree_onIt.png");
	mapCreator_Buttons.loadNewTexture("tree_clicked", "../data/texturepacks/mapCreator/buttons/tree_clicked.png");
	//=====>Backgrounds
	mapCreator_Backgrounds.loadNewTexture("rightPanel", "../data/texturepacks/mapCreator/backgrounds/rightPanel.png");
	mapCreator_Backgrounds.loadNewTexture("table", "../data/texturepacks/mapCreator/backgrounds/table.png");
}

void Resources::loadFonts()
{
	font_Roboto_Black.loadFromFile("../data/fonts/Roboto-Black.ttf");
	font_Roboto_BlackItalic.loadFromFile("../data/fonts/Roboto-BlackItalic.ttf");
	font_Roboto_Bold.loadFromFile("../data/fonts/Roboto-Bold.ttf");
	font_Roboto_BoldItalic.loadFromFile("../data/fonts/Roboto-BoldItalic.ttf");
	font_Roboto_Italic.loadFromFile("../data/fonts/Roboto-Italic.ttf");
	font_Roboto_Light.loadFromFile("../data/fonts/Roboto-Light.ttf");
	font_Roboto_LightItalic.loadFromFile("../data/fonts/Roboto-LightItalic.ttf");
	font_Roboto_Medium.loadFromFile("../data/fonts/Roboto-Medium.ttf");
	font_Roboto_MediumItalic.loadFromFile("../data/fonts/Roboto-MediumItalic.ttf");
	font_Roboto_Regular.loadFromFile("../data/fonts/Roboto-Regular.ttf");
	font_Roboto_Thin.loadFromFile("../data/fonts/Roboto-Thin.ttf");
	font_Roboto_ThinItalic.loadFromFile("../data/fonts/Roboto-ThinItalic.ttf");
}
