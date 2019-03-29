#include "FilesList.h"


void CFilesList::SetLog(CLog *TLog)
{
	Log = TLog; // assign pointer to log object
}

void CFilesList::Read(std::string Folder)
{

	LPCSTR file = Folder.c_str(); // path shoudl end with: //*
    WIN32_FIND_DATA FindFileData;	// variable wiith file data

	hFind = FindFirstFile(file, &FindFileData); //finds first file

	if (hFind != INVALID_HANDLE_VALUE) //if there is files and location
	{
		do 
		{
			if((std::string)(FindFileData.cFileName) != "." && (std::string)FindFileData.cFileName != "..")	FilesNames.push_back(FindFileData.cFileName);	//push file names to vector instead "." and ".."	
		} 
		while (FindNextFile(hFind, &FindFileData)); // do it for every file
		FindClose(hFind); //close finding oject
	}
	else Log->WriteTxt("Can't find files in scripts folder or Scripts folder");
}

std::vector<std::string> CFilesList::GetFileNames()
{
	return FilesNames; // return vector with files names
}