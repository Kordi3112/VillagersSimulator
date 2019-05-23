#include "TexturePack.h"



TexturePack::TexturePack()
{
}


TexturePack::~TexturePack()
{
	if (TexturePack::number() != 0)
	{
		TexturePack::releaseAll();
	}
}

bool TexturePack::loadNewTexture(std::string textureName, std::string path)
{
	sf::Texture* texture = new sf::Texture();

	if (texture->loadFromFile(path))
	{
		//success
		this->m_textureContainer.push_back(texture);
		this->m_nameContainer.push_back(textureName);
		this->m_pathContainer.push_back(path);

		return true;
	}
	else
	{
		//fail
		delete texture;

		return false;
	}
}

sf::Texture* TexturePack::getTexturePtr(std::string name) const
{
	for (int i = 0; i < this->m_nameContainer.size(); i++)
	{
		if (name == this->m_nameContainer[i])
		{
			return this->m_textureContainer[i];
		}
	}

	//nothing find
	return nullptr;
}

sf::Texture* TexturePack::getTexturePtr(unsigned id) const
{
	if (id < this->m_textureContainer.size())
	{
		return this->m_textureContainer[id];
	}

	//fail
	return nullptr;
}

std::string TexturePack::getTextureName(unsigned id) const
{
	if (id < this->m_nameContainer.size())
	{
		return this->m_nameContainer[id];
	}

	return std::string();
}

int TexturePack::getTextureId(std::string name) const
{
	for (int i = 0; i < this->m_nameContainer.size(); i++)
	{
		if (name == this->m_nameContainer[i])
		{
			return i;
		}
	}

	//fail
	return -1;
}

std::string TexturePack::getPath(unsigned id) const
{
	if (id < this->m_pathContainer.size())
	{
		return this->m_pathContainer[id];
	}

	return std::string();
}

bool TexturePack::changeName(std::string previousName, std::string newName)
{
	for (int i = 0; i < this->m_nameContainer.size(); i++)
	{
		if (previousName == this->m_nameContainer[i])
		{
			this->m_nameContainer[i] = newName;

			return true;
		}
	}

	return false;
}

bool TexturePack::changeName(unsigned id, std::string newName)
{
	if (id < this->m_nameContainer.size())
	{
		this->m_nameContainer[id] = newName;
	}
	else return false;
}

int TexturePack::number() const
{
	return this->m_textureContainer.size();
}

bool TexturePack::deleteTexture(std::string name)
{
	int id = TexturePack::getTextureId(name);

	if (id >= 0)
	{
		//success
		TexturePack::deleteTexture(id);
	}
	else return false;
}

bool TexturePack::deleteTexture(unsigned id)
{
	if (id < this->m_textureContainer.size())
	{
		delete this->m_textureContainer[id];
		this->m_textureContainer.erase(this->m_textureContainer.begin()+id);
		this->m_nameContainer.erase(this->m_nameContainer.begin()+id);
		this->m_pathContainer.erase(this->m_pathContainer.begin()+id);
	}
	else return false;
}

void TexturePack::releaseAll()
{
	for (int i = 0; i < this->m_textureContainer.size(); i++)
	{
		delete this->m_textureContainer[i];
	}

	this->m_textureContainer.clear();
	this->m_nameContainer.clear();
	this->m_pathContainer.clear();
}

