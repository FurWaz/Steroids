#pragma once
#include <string>
#include <vector>

class Files
{
private:
	std::string startFolder;
	std::string selectedFile;
	std::string homeDirectory;

public:
	static std::string getFileName(std::string str);

	Files();
	std::string getStartFolder();
	void setStartFolder(std::string str);

	std::vector<std::string> getFiles();
	std::string getHomeDirectory();
	std::string getSelectedFile();
};