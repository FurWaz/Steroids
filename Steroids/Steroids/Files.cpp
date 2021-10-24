#include "Files.h"
#include <Windows.h>
#include <iostream>

std::string Files::getFileName(std::string str)
{
	unsigned int index = 0;
	for (unsigned int i = 0; i < str.size(); i++)
		if (str.at(i) == '/' || str.at(i) == '\\')
			index = i+1;
	return str.substr(index, str.size() - index);
}

Files::Files()
{
	this->startFolder = "C:";
	this->selectedFile = "";

	size_t size = 256;
	char* buffer = (char*) malloc(sizeof(char) * size);
	_dupenv_s(&buffer, &size, "HOMEDRIVE");
	this->homeDirectory += buffer;
	_dupenv_s(&buffer, &size, "HOMEPATH");
	this->homeDirectory += buffer;
	std::cout << "home directory: [" << this->homeDirectory << "]" << std::endl;
}

std::string Files::getHomeDirectory()
{
	return this->homeDirectory;
}

std::string Files::getStartFolder()
{
	return this->startFolder;
}

void Files::setStartFolder(std::string str)
{
	this->startFolder = str;
}

std::vector<std::string> Files::getFiles()
{
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA((this->startFolder + "\\*").c_str(), &data);
	std::cout << "listing files of " << this->startFolder+"\\*" << std::endl;
	std::vector<std::string> list;
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			std::string name = data.cFileName;
			if (name.size() < 4) continue;
			std::string ext = name.substr(name.size() - 4, 4);
			if (ext == ".wav" || ext == ".mp3" ||
				ext == ".ogg" || ext == "flac")
				list.push_back(std::string(this->startFolder + "\\" + name));
		} while (FindNextFileA(hFind, &data));
		FindClose(hFind);
	}
	return list;
}

std::string Files::getSelectedFile()
{
	return this->selectedFile;
}