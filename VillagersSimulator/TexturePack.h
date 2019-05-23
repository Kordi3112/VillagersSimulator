#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//its container for textures this same kind f.e buttons for MapEditor
class TexturePack
{
public:
	TexturePack();
	~TexturePack();
	//
	bool loadNewTexture(std::string textureName, std::string path); //f.e. ...loadNewtexture("Button_01", "../data/texturepacks/MapEditorButtons/Button_01");
	//
	sf::Texture* getTexturePtr(std::string name) const; //return nullptr if nothing find
	sf::Texture* getTexturePtr(unsigned id) const; //return nullptr if nothing find
	std::string  getTextureName(unsigned id) const;
	int			 getTextureId(std::string name) const; //return -1 if nothing find
	std::string  getPath(unsigned id) const;
	//
	bool changeName(std::string previousName, std::string nextName);
	bool changeName(unsigned id, std::string newName);

	//
	int	number() const;
	//
	bool deleteTexture(std::string name); //return false if nothing find
	bool deleteTexture(unsigned id); //return false if nothing find
	//
	void releaseAll();
private:
	std::vector<sf::Texture*> m_textureContainer;
	std::vector<std::string> m_nameContainer;
	std::vector<std::string> m_pathContainer;

};

