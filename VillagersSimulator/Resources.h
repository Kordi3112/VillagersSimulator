#pragma once
#include "TexturePack.h"
//its is container for all global resoures in game f.e. textures
class Resources
{
public:
	//
	TexturePack texturepack1;
	TexturePack texturepack2;
	TexturePack texturepack3;
	TexturePack texturepack4;
	///MAP CREATOR
	TexturePack mapCreator_Buttons;
	TexturePack mapCreator_Backgrounds;
	//
	void load(); //load all resources to memory 
};
