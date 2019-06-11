#pragma once
#include <windows.h>
#include <string>
#include <iostream>

class FileManaging
{
public:

	enum STATUS
	{
		GOOD,
		CANNOT_OPEN,
		CANNOT_READ,
		CANNOT_WRITE,
		TOO_BIG,
	};
	//
	static STATUS LoadFileToString(std::string path, std::string& bufor);
	static STATUS SaveStringToFile(std::string path, std::string& toSave);
};

