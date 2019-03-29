#ifndef FilesList_h
#define FilesList_h

#include <Windows.h>
#include <vector>
#include <string>
#include "Log.h"

class CFilesList
{

public:

	void SetLog(CLog *TLog); // Set log pointer

	void Read(std::string Folder); //reads files names found in directory

	std::vector<std::string> GetFileNames(); //returns names found with function Read

private:

	HANDLE hFind; //holder for file properties

	std::vector<std::string> FilesNames; // files names found in directory

	CLog *Log; // pointer to log object
};

#endif